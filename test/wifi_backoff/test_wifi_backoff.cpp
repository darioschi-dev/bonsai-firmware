// Test unitario standalone per wifiBackoffDelayMs (issue #11).
// Non richiede Arduino/PlatformIO: compilare ed eseguire con
//   g++ -std=c++11 -I src test/wifi_backoff/test_wifi_backoff.cpp -o /tmp/test_wifi_backoff && /tmp/test_wifi_backoff

#include <cassert>
#include <cstdio>
#include "wifi_backoff.h"

int main() {
  assert(wifiBackoffDelayMs(1) == 5000UL);
  assert(wifiBackoffDelayMs(2) == 10000UL);
  assert(wifiBackoffDelayMs(3) == 20000UL);
  assert(wifiBackoffDelayMs(4) == 40000UL);
  assert(wifiBackoffDelayMs(5) == 60000UL);   // cap raggiunto
  assert(wifiBackoffDelayMs(50) == 60000UL);  // resta al cap
  assert(wifiBackoffDelayMs(0) == 5000UL);    // input non valido -> trattato come 1
  assert(wifiBackoffDelayMs(-3) == 5000UL);

  printf("OK: tutti i casi di wifiBackoffDelayMs verificati\n");
  return 0;
}
