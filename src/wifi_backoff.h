#pragma once

// Calcola il ritardo (ms) prima del prossimo tentativo di riconnessione WiFi.
// Backoff esponenziale: 5s, 10s, 20s, 40s, poi fisso a 60s (vedi issue #11).
// constexpr: la logica è verificata a compile time dagli static_assert sotto,
// quindi ogni `pio run` la ricontrolla senza bisogno di un eseguibile di test
// separato (qui non è disponibile un compilatore host per un test standalone).
constexpr unsigned long wifiBackoffDelayMs(int attempt) {
  return (attempt < 1) ? 5000UL
       : (attempt > 4) ? 60000UL
       : (5000UL << (attempt - 1));
}

static_assert(wifiBackoffDelayMs(1) == 5000UL, "primo tentativo: 5s");
static_assert(wifiBackoffDelayMs(2) == 10000UL, "secondo tentativo: 10s");
static_assert(wifiBackoffDelayMs(3) == 20000UL, "terzo tentativo: 20s");
static_assert(wifiBackoffDelayMs(4) == 40000UL, "quarto tentativo: 40s");
static_assert(wifiBackoffDelayMs(5) == 60000UL, "dal quinto tentativo: cap 60s");
static_assert(wifiBackoffDelayMs(100) == 60000UL, "resta al cap anche con molti tentativi");
static_assert(wifiBackoffDelayMs(0) == 5000UL, "input non valido trattato come primo tentativo");
static_assert(wifiBackoffDelayMs(-5) == 5000UL, "input negativo trattato come primo tentativo");
