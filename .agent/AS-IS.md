# Stato as-is / As-is state

**Verificato il:** 2026-10-04 — **fonte:** `date +%F`, `platformio.ini`, `.github/workflows/build.yml`, `git tag`, `gh release list`, `gh run list`, `gh issue list`, `grep` su `src/`, `ls`; nessun dispositivo né server OTA contattato, nessuna compilazione locale

## In produzione

Il progetto è un firmware ESP32 (`board = esp32doit-devkit-v1`, framework Arduino, ambiente predefinito `esp32-prod`, ambienti `esp32-test` ed `esp32-ota`). La pubblicazione è automatica: ogni push su `master` fa partire il workflow «Build & Upload ESP32 Firmware OTA» (`.github/workflows/build.yml`), che calcola la versione, crea il tag e la release GitHub con `firmware.bin` e carica il binario sul server OTA indicato dal secret `OTA_UPLOAD_URL`. Non esiste un ramo `production`. L'ultima release è `v1.4.22+202610031558` (pubblicata il 2026-10-03T15:59:04Z, contrassegnata «Latest»), e l'ultima esecuzione del workflow, 2026-10-03T15:58:30Z sul commit «regole: chiusura del lavoro…», è `success` (`gh run list`, `gh release list`). Questo dice cosa è stato rilasciato, non cosa gira: la versione realmente in esecuzione sul dispositivo e il contenuto del server OTA sono **non verificati**. Nota: il workflow non ha `paths-ignore`, quindi anche un push di sola documentazione produce una release e un aggiornamento OTA (episodio del 2026-10-02 descritto in `.agent/STATE.md`).

## Cosa c'è nel codice o nei documenti

- **Struttura**: `src/` con `main.cpp`, `mqtt`, `webserver`, `pump_controller`, `config_api`, `config_validator`, `trigger_firmware_check`, `update/`, `logger`, `telnet_logger`, `mirror_serial`, `mail` (`ls src`); filesystem SPIFFS e partizioni OTA (`partitions_ota.csv`), dati in `data/` (config di esempio, prod, test e `index.html`).
- **Versione**: `scripts/generate_version.py` (script `pre:` in `platformio.ini`) genera `include/version_auto.h` (non tracciato); il workflow passa `VERSION_OVERRIDE`. La copia locale dice `v1.4.10` ed è obsoleta rispetto all'ultimo tag. Ultimo tag: `v1.4.22+202610031558` (32 tag in totale, `git tag | wc -l`).
- **Funzioni presenti nei sorgenti** (`grep`): watchdog di task a 8 s (`esp_task_wdt_init(8, true)` in `main.cpp:334`), WiFi power save `WIFI_PS_MIN_MODEM` (`main.cpp:181`), sincronizzazione NTP con `configTime` (`main.cpp:225`), deep sleep con `esp_sleep_enable_timer_wakeup` (`main.cpp:499`), fallback ad access point se il WiFi non si connette (`WiFi.softAP`, `main.cpp:190`), MQTT su connessione TLS quando la porta non è 1883, con `setInsecure()` cioè senza verifica del certificato (`mqtt.cpp:355-362`).
- **Test**: `test/` contiene solo il `README` di PlatformIO; nessun test unitario. `make test` usa Wokwi (`wokwi-cli`), non eseguito.
- **CI**: il workflow compila `esp32-prod` con PlatformIO su `ubuntu-latest`; le ultime esecuzioni risultano `success`. La compilazione locale non è stata rieseguita (`pio` è installato, ma lo script di versione riscriverebbe `include/version_auto.h`).

## Non esiste ancora o è dismesso

Le issue sono tutte `OPEN` (`gh issue list --state open`, 2026-10-04), tra cui: TLS MQTT con verifica (#8, #25), brown-out e batteria (#7), media dei sensori (#6), dormita dinamica (#9, #22), rilevamento perdite (#10), backoff WiFi (#11), timestamp NTP sui messaggi (#12), OTA progressivo (#13), QoS 1 (#14), crash report (#15), metriche (#16), power save (#17, #27 — il codice usa già `WIFI_PS_MIN_MODEM`, quindi lo stato dell'issue non è riconciliato con il codice), misura del suolo solo al boot (#19), throttling MQTT (#20), report del watchdog via MQTT (#23), deduplicazione telemetria (#26). Il server OTA e il backend non stanno in questo repository (`ANALISI_ARCHITETTURA.md`: «Non incluso qui»).

## Modifiche del 2026-10-04 nel repository, non ancora rilasciate sui dispositivi

Committate con `[skip ci]`: nessun rilascio OTA parte da queste; arriveranno ai dispositivi con la prossima build di `master`.

- `/api/soil` espone le letture reali (`soilValue`, `soilPercent` assegnate da `readSoil()`): prima restituiva sempre 0 (`globalSoil`/`globalPerc` mai assegnati, ora tolti).
- `sendMail` non contiene più server, utente e password nel sorgente: li legge da NVS (namespace `mail`: `server`, `user`, `pass`, `port`) e, se non configurati, non tenta la connessione. Non ha nessun chiamante nel firmware.
- La password dell'access point di configurazione (`Bonsai-Setup-<deviceId>`) non è più fissa: è derivata dal dispositivo (`src/ap_password.cpp`, SHA-256 di `bonsai-ap-v1:<deviceId>`, 10 caratteri) e si calcola con `python3 tools/ap_password.py <deviceId>`. Dopo l'OTA la vecchia password fissa non vale più. La derivazione è pubblica per chi legge il repository e conosce il `deviceId` dell'SSID: è per-dispositivo, non un segreto forte.
- Build `pio run` (env `esp32-prod`) riuscita: flash 69,3%, RAM 16,0%. **Non provato su hardware**: avvio dell'AP con la nuova password, connessione di un client, lettura NVS, digest mbedtls sul chip (il confronto con Python è stato fatto su host con un'altra implementazione di SHA-256).

## Non verificato

- Versione in esecuzione sul dispositivo e contenuto del server OTA.
- Esito di una compilazione locale e comportamento su hardware dei commit di sicurezza del 26-27/01 (watchdog, timeout, pompa spenta prima del deep sleep).
- Se le altre issue elencate sopra corrispondano a funzioni già in parte presenti nel codice.

## Discrepanze da correggere in file guida

- `ANALISI_ARCHITETTURA.md` («Problemi aperti», punto 1): dice che il boot resta bloccato senza config WiFi e senza AP; in `main.cpp:190` c'è un `WiFi.softAP`, quindi il punto è almeno in parte superato. Restano veri il punto 2 (`globalSoil`/`globalPerc` definiti in `webserver.cpp:10-11` e mai assegnati altrove) e il punto 4 (`mail.cpp:27-30` con server e credenziali segnaposto cablati).
- `PIANO_OPERATIVO.md` è un piano (lavoro da fare): andrebbe riportato in issue.

## Documenti di dettaglio

- `Readme.md`: panoramica, comandi `make`, struttura.
- `ANALISI_ARCHITETTURA.md`: analisi dell'architettura (vedi discrepanze sopra).
- `PIANO_OPERATIVO.md`: piano operativo a fasi.
- `docs/INDEX.md`: indice generato; `docs/storico/`: documenti superati.
