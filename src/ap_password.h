#pragma once
#include <Arduino.h>

// Password dell'AP di configurazione, derivata dal deviceId:
// SHA-256("bonsai-ap-v1:" + deviceId), primi 10 byte, ciascuno mappato con
// (byte % 31) su un alfabeto senza caratteri ambigui (niente 0/o/1/i/l).
// Stesso algoritmo di tools/ap_password.py.
String deriveApPassword(const String& deviceId);
