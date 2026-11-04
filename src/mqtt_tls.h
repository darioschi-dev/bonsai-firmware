#pragma once

// Modalità di connessione al broker MQTT (issue #25).
//   Plain       porta in chiaro (default storico, 1883)
//   Insecure    TLS senza verifica del certificato (solo sviluppo)
//   CaVerified  TLS con verifica contro il CA caricato da SPIFFS
enum class MqttTlsMode { Plain, Insecure, CaVerified };

constexpr int MQTT_TLS_PORT = 8883;
constexpr const char* MQTT_CA_PATH = "/mqtt_ca.pem";

// TLS se il flag mqtt_tls è attivo oppure la porta è 8883. Con TLS attivo
// si verifica il certificato solo se è presente il CA, altrimenti insecure.
constexpr MqttTlsMode mqttTlsMode(bool tlsFlag, int port, bool hasCaCert) {
  return (!tlsFlag && port != MQTT_TLS_PORT) ? MqttTlsMode::Plain
       : hasCaCert ? MqttTlsMode::CaVerified
       : MqttTlsMode::Insecure;
}
