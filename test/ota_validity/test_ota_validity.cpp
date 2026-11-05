// Test unitario standalone per otaShouldMarkValid (issue #5).
//   g++ -std=c++11 -I src test/ota_validity/test_ota_validity.cpp -o /tmp/test_ota_validity && /tmp/test_ota_validity

#include <cassert>
#include <cstdio>
#include "ota_validity.h"

int main() {
  assert(otaShouldMarkValid(true) == true);    // config caricata: app valida
  assert(otaShouldMarkValid(false) == false);  // config non caricata: lascia scattare il rollback

  printf("OK: tutti i casi di otaShouldMarkValid verificati\n");
  return 0;
}
