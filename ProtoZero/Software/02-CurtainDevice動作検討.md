# Kagerou (陽炎)  
## 🌸 カーテンデバイス制御のプログラム 2026/4/19

Andoroidアプリで Switchbotのカーテンデバイスを操作する  
プログラムを検討する。 音声コマンドで操作するモードとRP2040からの  
信号でカーテンデバイスを操作する二種類の方法を持ちたい。

カーテンデバイスを操作する為には、以下のコードが必要。  
Gemini にサンプルを作ってもらった。

```
1. 事前準備
API を叩くために、SwitchBot アプリから以下の情報を取得してください。

Open Token: アプリの「プロフィール」>「設定」>「アプリバージョン」を 10 回タップして開発者向けオプションを表示し、取得します。

Client Secret: 同じ画面で取得します。

Device ID: API のデバイスリスト取得エンドポイント から取得します。

2. Android コードサンプル (Kotlin)
SwitchBot API v1.1 では、セキュリティのために 署名（sign） が必要です。以下は、カーテンを「開く」コマンドを送信するシンプルな関数です。

import okhttp3.*
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.RequestBody.Companion.toRequestBody
import java.util.*
import javax.crypto.Mac
import javax.crypto.spec.SecretKeySpec
import android.util.Base64

fun controlCurtain(command: String) { // command は "open" または "close"
    val token = "あなたのOPEN_TOKEN"
    val secret = "あなたのCLIENT_SECRET"
    val deviceId = "あなたのDEVICE_ID"
    
    val nonce = UUID.randomUUID().toString()
    val t = System.currentTimeMillis().toString()
    val data = token + t + nonce
    
    // HMAC-SHA256 で署名を作成
    val secretKeySpec = SecretKeySpec(secret.toByteArray(), "HmacSHA256")
    val mac = Mac.getInstance("HmacSHA256")
    mac.init(secretKeySpec)
    val sign = Base64.encodeToString(mac.doFinal(data.toByteArray()), Base64.NO_WRAP)

    val client = OkHttpClient()
    val mediaType = "application/json; charset=utf-8".toMediaType()
    
    // カーテン操作用のJSONボディ
    val json = """
        {
            "command": "$command",
            "parameter": "default",
            "commandType": "command"
        }
    """.trimIndent()

    val request = Request.Builder()
        .url("https://api.switch-bot.com/v1.1/devices/$deviceId/commands")
        .post(json.toRequestBody(mediaType))
        .addHeader("Authorization", token)
        .addHeader("sign", sign)
        .addHeader("nonce", nonce)
        .addHeader("t", t)
        .build()

    // ネットワーク処理なので別スレッドで実行
    Thread {
        try {
            val response = client.newCall(request).execute()
            println("Response: ${response.body?.string()}")
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }.start()
}

3. 実装のポイント
依存ライブラリ: OkHttp を使用しています。build.gradle に implementation("com.squareup.okhttp3:okhttp:4.x.x") を追加してください。

パーミッション: AndroidManifest.xml に <uses-permission android:name="android.permission.INTERNET" /> が必要です。

署名の生成: v1.1 から必須となった sign ヘッダーの生成が少し複雑ですが、上記のコードで対応しています。

4. 「七式」への組み込み
昨日の「ライト消灯」の流れに組み込むなら、Nana1st.kt の onReceive 内で、以下のように分岐させるのが面白いでしょう。

val command = intent.getStringExtra("command") ?: ""

if (command == "CURTAIN_OPEN") {
    controlCurtain("open")
} else if (command == "OFF") {
    // 昨日のUSB送信処理（ライト消灯）
}

```

