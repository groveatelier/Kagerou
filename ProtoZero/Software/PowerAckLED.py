from machine import Pin
import neopixel
import time
import math
import urandom

# RP2040-Zero の RGB LED NeoPixel 1個、GPIO16
np = neopixel.NeoPixel(Pin(16), 1)

'''
電源が入った時に RP2040-Zero に搭載されているRGB LEDを
光らせます。 いろいろしているけど、光って消すだけと変わらな
かった...。
'''
def kagerou_komorebi_breath(duration=3.0):
    base_color = (50, 32, 12)  # 木漏れ日の琥珀色
    steps = 80  # 滑らかさ
    for i in range(steps):
        # 呼吸の基本波（cosで自然な明滅）
        breath = (1 - math.cos(math.pi * i / (steps - 1))) / 2
        # 木漏れ日の揺らぎ（±5%程度のランダム）
        flicker = 1.0 + (urandom.getrandbits(8) / 255 - 0.5) * 0.10
        # 色の微細な揺らぎ（±2）
        drift_r = urandom.getrandbits(3) - 4
        drift_g = urandom.getrandbits(3) - 4
        drift_b = urandom.getrandbits(3) - 4
        r = int((base_color[0] + drift_r) * breath * flicker)
        g = int((base_color[1] + drift_g) * breath * flicker)
        b = int((base_color[2] + drift_b) * breath * flicker)
        # 範囲を安全に
        r = max(0, min(255, r))
        g = max(0, min(255, g))
        b = max(0, min(255, b))

        np[0] = (r, g, b)
        np.write()

    # --- 最後の色を基準に穏やにフェードアウト ---
    fade_steps = 60       # 滑らかさ
    fade_time = 1.5       # 消えるまでの時間（ここを伸ばせばもっと穏やかに）
    r0 = r
    g0 = g
    b0 = b
    for i in range(fade_steps):
        ratio = 1 - (i / (fade_steps - 1))
        r = int(r0 * ratio)
        g = int(g0 * ratio)
        b = int(b0 * ratio)
        np[0] = (r, g, b)
        np.write()
        time.sleep(fade_time / fade_steps)
    # 完全に消灯
    np[0] = (0, 0, 0)
    np.write()
