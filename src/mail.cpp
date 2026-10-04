#include "mail.h"
#include <WiFiClientSecure.h>
#include "mbedtls/base64.h"
#include <Preferences.h>

// ------------------------------------------------------------
// Base64 helper
// ------------------------------------------------------------
String base64Encode(const String &data) {
    size_t out_len = 0;
    size_t in_len  = data.length();
    unsigned char out[256];

    mbedtls_base64_encode(out, sizeof(out), &out_len,
                          (const unsigned char *)data.c_str(), in_len);

    return String((char *)out);
}

// ------------------------------------------------------------
// SMTP SEND MAIL
// ------------------------------------------------------------
bool sendMail(const String& subject, const String& body)
{
    // Credenziali SMTP da NVS (namespace "mail"): chiavi server, user, pass, port (default 465)
    Preferences mailPrefs;
    mailPrefs.begin("mail", true);
    String smtpServer = mailPrefs.getString("server", "");
    String username   = mailPrefs.getString("user", "");
    String password   = mailPrefs.getString("pass", "");
    int smtpPort      = mailPrefs.getInt("port", 465);
    mailPrefs.end();

    if (smtpServer.isEmpty() || username.isEmpty()) {
        Serial.println("[MAIL] SMTP non configurato (NVS namespace 'mail': server/user/pass/port): invio saltato");
        return false;
    }

    WiFiClientSecure client;
    client.setInsecure();

    Serial.println("[MAIL] Connessione al server SMTP...");

    if (!client.connect(smtpServer.c_str(), smtpPort)) {
        Serial.println("[MAIL] Connessione SMTP fallita");
        return false;
    }

    auto send = [&](const String& s) {
        client.println(s);
        delay(30);
    };

    send("EHLO esp32");
    send("AUTH LOGIN");

    send(base64Encode(username));
    send(base64Encode(password));

    send("MAIL FROM:<" + String(username) + ">");
    send("RCPT TO:<" + String(username) + ">");
    send("DATA");

    send("Subject: " + subject);
    send("From: ESP32 <" + String(username) + ">");
    send("To: <" + String(username) + ">");
    send("");

    send(body);

    send(".");
    send("QUIT");

    Serial.println("[MAIL] Email inviata con successo!");
    return true;
}
