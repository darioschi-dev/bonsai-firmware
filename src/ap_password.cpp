#include "ap_password.h"
#include "mbedtls/sha256.h"

static const char AP_ALPHABET[] = "23456789abcdefghjkmnpqrstuvwxyz"; // 31 caratteri
static const size_t AP_PASSWORD_LEN = 10;

String deriveApPassword(const String& deviceId) {
  const String input = "bonsai-ap-v1:" + deviceId;
  unsigned char digest[32];
  mbedtls_sha256_context ctx;
  mbedtls_sha256_init(&ctx);
  mbedtls_sha256_starts(&ctx, 0); // 0 = SHA-256
  mbedtls_sha256_update(&ctx, reinterpret_cast<const unsigned char*>(input.c_str()), input.length());
  mbedtls_sha256_finish(&ctx, digest);
  mbedtls_sha256_free(&ctx);

  String out;
  out.reserve(AP_PASSWORD_LEN);
  for (size_t i = 0; i < AP_PASSWORD_LEN; i++) {
    out += AP_ALPHABET[digest[i] % 31];
  }
  return out;
}
