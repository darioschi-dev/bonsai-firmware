#!/usr/bin/env python3
"""Calcola la password dell'AP di configurazione Bonsai-Setup-<deviceId>.

Uso: python3 tools/ap_password.py <deviceId>
Stesso algoritmo di src/ap_password.cpp:
SHA-256("bonsai-ap-v1:" + deviceId), primi 10 byte, (byte % 31) sull'alfabeto.
"""
import hashlib
import sys

ALPHABET = "23456789abcdefghjkmnpqrstuvwxyz"  # 31 caratteri, senza 0/o/1/i/l


def ap_password(device_id: str) -> str:
    digest = hashlib.sha256(("bonsai-ap-v1:" + device_id).encode("utf-8")).digest()
    return "".join(ALPHABET[b % 31] for b in digest[:10])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Uso: ap_password.py <deviceId>  (es. il MAC senza due punti, nell'SSID Bonsai-Setup-<deviceId>)")
    print(ap_password(sys.argv[1].strip()))
