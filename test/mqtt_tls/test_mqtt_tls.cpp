// Test unitario standalone per mqttTlsMode (issue #25).
// Non richiede Arduino/PlatformIO: compilare ed eseguire con
//   g++ -std=c++11 -I src test/mqtt_tls/test_mqtt_tls.cpp -o /tmp/test_mqtt_tls && /tmp/test_mqtt_tls

#include <cassert>
#include <cstdio>
#include "mqtt_tls.h"

int main() {
  // Default storico: porta 1883 senza flag -> in chiaro
  assert(mqttTlsMode(false, 1883, false) == MqttTlsMode::Plain);
  // Porta 8883 -> TLS anche senza flag
  assert(mqttTlsMode(false, 8883, false) == MqttTlsMode::Insecure);
  assert(mqttTlsMode(false, 8883, true) == MqttTlsMode::CaVerified);
  // Flag esplicito su porta non standard
  assert(mqttTlsMode(true, 1883, false) == MqttTlsMode::Insecure);
  assert(mqttTlsMode(true, 9999, true) == MqttTlsMode::CaVerified);
  // Il CA senza TLS non attiva nulla
  assert(mqttTlsMode(false, 1883, true) == MqttTlsMode::Plain);

  printf("OK: tutti i casi di mqttTlsMode verificati\n");
  return 0;
}
