# Registro condiviso / Shared log

## 2026-10-02 19:38 CEST — atk — OPERAZIONE

- Decisione o attività: creato il registro condiviso e il marcatore `AGENT-ACTIVE.md` con `atk scaffold`, secondo la struttura di collaborazione tra agenti di agent-toolkit (`templates/agent/`).
- Verifiche o fonti: nessuna; sono file di partenza.
- File o commit: `.agent/STATE.md`, `AGENT-ACTIVE.md`; non committati.
- Prossimo passo o blocchi: aggiungere al repository la sezione di collaborazione in `AGENTS.md` se manca (`atk scaffold --rules`), poi revisionare e committare.

## 2026-10-02 22:16 CEST — Claude (Sonnet 5.5, session id 655f4d57-994c-48ba-bd9a-5f6f92fa3779) — OPERAZIONE — id: bonsai-20261002-merge-su-master

- Decisione o attività: su richiesta di Dario il branch fix/firmware-critical-issues è stato unito a master con fast-forward (master non si era mosso: 11 commit avanti, 0 indietro) e il branch cancellato in locale e su GitHub; da ora si lavora su master. Nei commit uniti, del 26-27/01/2026: timeout del WiFi, riconnessione MQTT con backoff, misura periodica del suolo nel loop, pompa spenta prima del deep sleep e sleep rinviato a pompa accesa, sleep dinamico con telemetria deduplicata e watchdog, timeout OTA e risparmio energetico del WiFi; più i file di regole (AGENTS.md, CLAUDE.md, .agent, hook commit-msg) e version_auto.h e compile_commands.json tolti dal tracciamento perché generati dalla build.
- Verifiche o fonti: git merge --ff-only, git log, GitHub master e locale allo stesso commit (e173f92). NON verificato: la compilazione e il comportamento sull'hardware (PlatformIO non è installato su questo Mac e non c'è un test automatico di questi commit): prima di caricare il firmware sull'ESP32 compilare con pio run e provare sul banco.
- File o commit: nessuna modifica di codice; fast-forward fino a e173f92.
- Prossimo passo o blocchi: compilare e provare sul banco i commit di sicurezza (pompa, deep sleep, watchdog) prima del prossimo rilascio OTA.
- Soggetto: merge-su-master

## 2026-10-02 22:22 CEST — Claude (Sonnet 5.5, session id 655f4d57-994c-48ba-bd9a-5f6f92fa3779) — OPERAZIONE — id: bonsai-20261002-rilasci-involontari

- Decisione o attività: ogni push su master di questo repository fa partire il workflow «Build & Upload ESP32 Firmware OTA» (.github/workflows/build.yml): compila, crea il tag e la release GitHub con firmware.bin e carica il firmware sul server OTA (secret OTA_UPLOAD_URL). I miei tre push di oggi, compresi due che erano solo diario e correzione di un hook, hanno quindi pubblicato tre rilasci: v1.4.18+202610022016 (merge dei commit del branch fix), v1.4.18+202610022017 e v1.4.19+202610022017 (ora «Latest»), tutti con il passo di upload concluso con successo. Prima di oggi l'ultimo rilascio era v1.4.17+202601260838. Conseguenza: se il dispositivo interroga quel server OTA e confronta la versione, al prossimo risveglio può aggiornarsi alla 1.4.19, che contiene i commit di sicurezza del 26-27/01 (pompa spenta prima del deep sleep, watchdog, timeout) mai provati su hardware con questa pipeline. Non so se il server OTA tenga solo l'ultima versione né se il dispositivo sia acceso: da verificare da Dario.
- Verifiche o fonti: gh run list e gh release list; la compilazione è riuscita in CI per tutte e tre le esecuzioni (quindi il codice compila); il comportamento sull'hardware non è verificato. PlatformIO installato sul Mac (uv tool install platformio, versione 6.2.0).
- File o commit: nessuna modifica di codice. Questa voce è pubblicata con [skip ci] per non produrre un altro rilascio.
- Prossimo passo o blocchi: Dario decide se riportare il server OTA alla v1.4.17 (e se cancellare i tre rilasci), e se escludere dal workflow i push che non toccano il firmware (paths-ignore su *.md, .agent, .githooks, docs).
- Lezione: un workflow che pubblica un rilascio e un aggiornamento OTA a ogni push su master fa di ogni commit, anche di sola documentazione, un rilascio di produzione: prima di pushare su un repository controllare .github/workflows e ciò che il push innesca, non solo i test locali.
- Soggetto: rilasci-involontari

## 2026-10-02 22:42 CEST — Claude (Sonnet 5.5, session id 63ffcf64-e8d6-4f3c-b7e2-c1d69da68c3a) — DECISIONE

- Decisione o attività: su richiesta dell'utente dichiarato in `AGENTS.md` il tipo del repository, `Tipo di repository: codice.` (dedotto dal tipo nei domini di atk: coding = codice, dossier e raccolta = documentazione). Non cambia il comportamento: la regola Git del 2026-10-02 vale per tutti i tipi, la riga rende il tipo esplicito.
- Verifiche o fonti: `atk domains tree`, assenza della riga in `AGENTS.md`.
- File o commit: `AGENTS.md`, questa voce.
- Prossimo passo o blocchi: nessuno.
- Soggetto: tipo-repository-dichiarato

## 2026-10-04 16:17 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: AS-IS-DOCS-BONSAIFW-20261004

- Decisione o attività: `.agent/AS-IS.md` compilato; archiviata in `docs/storico/` la lista dei miglioramenti del firmware (roadmap duplicata dalle issue: watchdog, risparmio energetico e NTP sono già nel codice).
- Verifiche o fonti: [V] `esp_task_wdt`, `WIFI_PS_MIN_MODEM` e `configTime` presenti in `src/main.cpp`; ogni push su `master` rilascia automaticamente (ultima release `v1.4.22+202610031558`, CI riuscita). [non verificato] versione sul dispositivo, contenuto del server OTA, compilazione locale.
- File o commit: `.agent/AS-IS.md`, `docs/`; commit di questa voce (la voce segue di poco il commit del lavoro).
- Prossimo passo o blocchi: `ANALISI_ARCHITETTURA.md` punto 1 in parte superato (`WiFi.softAP` in `main.cpp:190`, con password di configurazione nel sorgente), punti 2 e 4 ancora veri (`globalSoil`/`globalPerc` mai assegnati; `mail.cpp:27-30` con credenziali segnaposto); issue #17 e #27 aperte ma il codice usa già `WIFI_PS_MIN_MODEM`; `PIANO_OPERATIVO.md` è un piano da portare in issue.
- Soggetto: as-is-docs

## 2026-10-04 17:06 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: REGOLE-DOCUMENTI-PROPAGATE-20261004

- Decisione o attività: aggiornata con `atk scaffold --merge --update` la sezione gestita «Documenti» del file guida (marcatore `atk-scaffold:documenti`): il limite di 8 documenti vivi è una linea guida sforabile con il motivo scritto nel registro, documenti solo in italiano, documenti generati con riga «generato».
- Verifiche o fonti: [V] cambiate solo due righe del file guida (marcatore e paragrafo), controllate con `git diff --numstat`.
- File o commit: `AGENTS.md` o `CLAUDE.md` (nei repository dove `AGENTS.md` è un collegamento); commit di questa voce.
- Prossimo passo o blocchi: nessuno.
- Soggetto: regole-documenti

## 2026-10-04 17:31 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: FIRMWARE-SICUREZZA-20261004

- Decisione o attività: su scelta di Dario del 2026-10-04 («puoi fare quello che vuoi, basta che metti [skip-ci] nel messaggio di commit»; usata la forma riconosciuta da GitHub `[skip ci]`) tre correzioni: (1) `src/mail.cpp`: server, utente e password SMTP non sono più nel sorgente ma in NVS (namespace `mail`), `sendMail` non tenta la connessione se non configurata (non ha chiamanti); (2) `src/webserver.cpp/.h`: `/api/soil` espone `soilValue` e `soilPercent` assegnati da `readSoil()` (prima sempre 0); (3) password dell'access point derivata dal dispositivo (`src/ap_password.cpp`, `tools/ap_password.py`, `Readme.md`), scelta di Dario fra quattro opzioni.
- Verifiche o fonti: [V] `pio run` (esp32-prod) SUCCESS, flash 69,3%, RAM 16,0%; `tools/ap_password.py` dà `ja5kw4wmtt` per `aabbccddeeff` e `bw6tenm4fs` per `240ac4123456`, uguali al C++ compilato su host. [non verificato] nessuna prova su hardware (AP con la nuova password, NVS, digest mbedtls sul chip); `deviceId` vuoto all'avvio dell'AP darebbe una password uguale per tutti (nessun fallback aggiunto).
- File o commit: `src/mail.cpp`, `src/main.cpp`, `src/webserver.cpp`, `src/webserver.h`, `src/ap_password.cpp`, `src/ap_password.h`, `tools/ap_password.py`, `Readme.md`, `.agent/AS-IS.md`; commit con `[skip ci]`, quindi nessun rilascio OTA automatico.
- Prossimo passo o blocchi: prima del prossimo rilascio provare su un dispositivo l'AP con la password derivata (e avvisare che `bonsai123` non vale più); un push successivo su `master` senza `[skip ci]` rilascia anche queste modifiche; decidere se aggiungere un setter per le credenziali mail.
- Soggetto: firmware-sicurezza

## 2026-10-04 22:03 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: REGOLA-PROJECT-ALIGNER-PROPAGATA-20261004

- Decisione o attività: aggiunta con `atk scaffold --merge --update` la sezione gestita «Allineamento del progetto (skill `project-aligner`)» al file guida: in questo repository di codice, all'inizio e alla chiusura di un lavoro e prima e dopo un rilascio in produzione si segue la skill globale `project-aligner`. Ricevono anche la regola «Test prima del codice»: prima non erano riconosciuti come repository di codice.
- Verifiche o fonti: [V] il tipo `coding` viene dal registro dei domini (`~/.config/agent-toolkit/domains.yaml`); cambiate solo le righe del marcatore e dei paragrafi aggiunti (`git diff --numstat`).
- File o commit: `AGENTS.md` o `CLAUDE.md` (dove `AGENTS.md` è un collegamento); commit di questa voce.
- Prossimo passo o blocchi: nessuno.
- Soggetto: regole-project-aligner

## 2026-10-04 22:06 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: INCIDENTE-RILASCIO-OTA-NON-VOLUTO-20261004

- Decisione o attività: rilascio OTA non voluto. Alle 22:04 CEST (20:04Z) il push del commit `b46e9dd` («regole: sezione sull'allineamento del progetto…») su `master` è stato fatto **senza `[skip ci]`**, contro l'istruzione di Dario del 2026-10-04 («metti [skip-ci] nel messaggio di commit»): ha avviato il workflow `build.yml`, che ha creato il tag e la release GitHub `v1.4.25+202610042004`, compilato `master` e **caricato il firmware sul server OTA** prima che io annullassi l'esecuzione (annullata alle 22:05, ma il passaggio «Upload firmware to OTA server» era già riuscito). Il firmware v1.4.25 contiene le modifiche NON provate su un dispositivo del commit `cb31b98`: password dell'access point derivata dal `deviceId`, credenziali SMTP da NVS, `/api/soil` con le letture reali.
- Verifiche o fonti: [V] `gh run list`/`gh run view` (esecuzione 37230679805, passaggi riusciti fino all'upload OTA, poi annullata); `gh release list`; il firmware controlla gli aggiornamenti all'avvio e su comando MQTT (`src/main.cpp:130`, `src/trigger_firmware_check.cpp:63`) e li applica se la versione disponibile è più nuova. [non verificato] se e quanti dispositivi hanno già scaricato v1.4.25; il comportamento del nuovo firmware su hardware.
- File o commit: nessuno (voce di cronaca); commit di questa voce con `[skip ci]`.
- Prossimo passo o blocchi: decisione di Dario sul ripristino (lasciare v1.4.25 oppure ripubblicare sull'OTA il codice precedente come versione più nuova); per i prossimi commit su `master` usare sempre `[skip ci]` (forma con lo spazio, riconosciuta da GitHub) finché le modifiche non sono provate su un dispositivo.
- Soggetto: firmware-ota

## 2026-10-04 22:10 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: RIPRISTINO-OTA-V1426-20261004

- Decisione o attività: rettifica della voce `INCIDENTE-RILASCIO-OTA-NON-VOLUTO-20261004`. Su scelta di Dario («ripubblico il codice precedente») lanciato `workflow_dispatch` di `build.yml` dal tag `v1.4.24+202610041507` (commit `df2558e`, codice senza le modifiche non provate) con `force_version=v1.4.26+202610042209`: tag, release GitHub e firmware caricato sul server OTA riusciti (esecuzione 37230978159); `v1.4.26` è ora la più nuova (`Latest`), quindi i dispositivi che non avevano ancora scaricato `v1.4.25` e quelli che l'avevano scaricata passano al codice di prima al prossimo controllo. La release `v1.4.25+202610042004` e il suo tag restano su GitHub (non cancellati).
- Verifiche o fonti: [V] il tag di partenza ha ancora la password fissa in `src/main.cpp`, nessun `src/ap_password.*` e le costanti SMTP segnaposto in `src/mail.cpp`; `gh release list` mostra `v1.4.26` come Latest; passaggi di build e di upload OTA riusciti. [non verificato] quanti dispositivi avessero già installato `v1.4.25` e se abbiano già controllato di nuovo; funzionamento sul dispositivo.
- File o commit: nessun file di codice; `master` contiene ancora le modifiche non rilasciate di `cb31b98` (password AP derivata, credenziali mail da NVS, `/api/soil`): il prossimo push su `master` senza `[skip ci]` le rilascia di nuovo; commit di questa voce con `[skip ci]`.
- Prossimo passo o blocchi: provare le modifiche su un dispositivo prima del prossimo rilascio; usare `[skip ci]` in ogni commit su `master` fino ad allora.
- Soggetto: firmware-ota

## 2026-10-04 22:34 CEST — Claude (Sonnet 5.5, session id e04c47d1-c544-4e70-8dad-56c6cffa4c14) — OPERAZIONE — id: REGOLA-PROJECT-ALIGNER-AGGIORNATA-20261004

- Decisione o attività: aggiornata con `atk scaffold --merge --update` la sezione gestita «Allineamento del progetto (skill `project-aligner`)» alla versione valida per ogni tipo di repository (il tipo anagrafato nel registro dei domini decide solo quali passi si applicano; la mappa evento → file sta nel `CLAUDE.md`).
- Verifiche o fonti: [V] cambiate solo le righe del marcatore e del paragrafo (`git diff --numstat`: +2 -2).
- File o commit: `AGENTS.md` o `CLAUDE.md` (dove `AGENTS.md` è un collegamento); commit di questa voce con `[skip ci]` (ogni push su master rilascia via OTA).
- Prossimo passo o blocchi: nessuno.
- Soggetto: regole-project-aligner

## 2026-10-17 19:23 CEST — Claude (Sonnet 5.5, session id c266f026-86d0-4a2d-98c3-3da0152d6280) — OPERAZIONE — id: HOOK-COMMIT-MSG-AGGIORNATO-20261017

- Soggetto: bonsai-firmware
- Decisione o attività: aggiornato .githooks/commit-msg al template di agent-toolkit con `atk scaffold --update --apply --hooks` (il doctor lo segnalava più vecchio): controlla anche l'orario delle voci di registro e richiede #N o «senza issue» nel messaggio di commit.
- Verifiche o fonti: [V] dry-run e apply; [V] il solo file modificato è .githooks/commit-msg; [V] repository pulito e senza voci in AGENT-ACTIVE.md prima di iniziare.
- File o commit: .githooks/commit-msg, .agent/STATE.md.
- Prossimo passo o blocchi: nessuno.

## 2026-11-03 08:21 CET — Claude (Sonnet 5, session id 6cfa7c77-f0c7-43d8-bc39-b5b97c5834ae) — OPERAZIONE — id: TRIAGE-ISSUE-20261103

- Soggetto: triage-issue-bonsai
- Decisione o attività: sessione autonoma di triage delle issue aperte. Lette tutte le 24 issue aperte e confrontate con il codice attuale su master. Dodici risultavano già risolte da commit precedenti mai chiusi: #3 (pump failsafe, maxRunMs+alert, commit b587cd2), #4 (watchdog task-level + health MQTT, commit 22790f7 e precedenti), #6 (median-of-3 su 5 campioni in readSoil, già nel codice), #9 e #22 (duplicate, sleep dinamico calculateSleepSeconds, commit 22790f7), #17 e #27 (duplicate, WiFi.setSleep(WIFI_PS_MIN_MODEM), commit 8c14e1d), #19 (measurement_interval consumato nel loop, già nel codice), #20 (backoff MQTT + dedup telemetria, commit 69f4795 e 22790f7), #23 (health/watchdog ogni 30s, commit 22790f7), #26 (dedup telemetria wifi/firmware, commit 22790f7). Chiuse tutte con commento che cita file, righe e commit. Per la #11 (riconnessione WiFi con backoff esponenziale), non ancora implementata, scritto codice nuovo: src/wifi_backoff.h (funzione pura constexpr con static_assert verificati a ogni compilazione: rosso con un valore atteso sbagliato, poi verde) e integrazione in loop() di src/main.cpp (tentativi di riconnessione 5s/10s/20s/40s/60s, dopo 5 fallimenti deep sleep di recupero di 15 minuti con lo stesso guard di sicurezza «mai se la pompa è accesa» già in uso altrove nel file); commit 2d70fb9 con [skip ci]. Issue #3, #4, #5, #7, #8, #10, #12, #13, #14, #15, #16, #25, #28, #29 saltate: #5 (OTA rollback) chiama già esp_ota_mark_app_valid_cancel_rollback() ma non è verificabile da qui se il rollback automatico del bootloader sia davvero abilitato (serve sdkconfig/hardware); #7 (brown-out/batteria) richiederebbe di inventare una soglia di tensione o un fattore di partitore non documentati in nessun file del repository (contro la regola «mai inventare»); #12 (timestamp ISO8601) ha già un timestamp NTP ma in formato epoch, non ISO8601 come richiesto, cambio rimandato per non introdurre una modifica di formato del payload MQTT senza una decisione esplicita; #8/#25 (TLS), #10 (leak detection, richiede un sensore di corrente ACS712 non presente), #13 (OTA progressivo), #14 (QoS1), #15 (crash reporting), #16 (metriche) sono enhancement non banali, saltati per restare su issue piccole e ben definite come richiesto; #1 è l'issue di tracking generale, non un fix; #28 è su VS Code/gh CLI, non tocca il firmware; #29 è la ricognizione del 2026-10-04, già in gran parte superata dalle chiusure di oggi.
- Verifiche o fonti: [V] lettura di src/main.cpp, src/pump_controller.cpp, src/mqtt.cpp, src/mqtt.h, platformio.ini; [V] git log -S su ogni simbolo citato per risalire al commit che lo ha introdotto; [V] pio run -e esp32-prod e pio run -e esp32-test entrambi SUCCESS dopo l'aggiunta di wifi_backoff.h e l'integrazione in main.cpp (RAM 16,0%, Flash 69,3%); [V] gh run list dopo il push: nessuna nuova esecuzione del workflow OTA ([skip ci] rispettato). Compilatori diretti (g++/clang++) bloccati dal sistema di permessi di questa sessione non interattiva: il test della funzione pura wifiBackoffDelayMs() è quindi negli static_assert dentro l'header, verificati da pio run, non da un eseguibile standalone; resta un file test/wifi_backoff/test_wifi_backoff.cpp non eseguito in questa sessione, utilizzabile a mano con g++ da chi ha un compilatore host disponibile. Non verificato: comportamento su hardware reale (nessun ESP32 collegato), rollback automatico OTA (#5).
- File o commit: src/wifi_backoff.h, src/main.cpp (commit 2d70fb9); nessuna modifica di codice per le dodici chiusure per verifica (solo commenti GitHub); questa voce.
- Prossimo passo o blocchi: #12 (timestamp ISO8601) e #5 (verifica rollback OTA su hardware) restano aperte, serve una sessione con accesso a un ESP32 fisico o una decisione su formato payload MQTT; #7 richiede a Dario le specifiche del partitore di tensione della batteria prima di poter calcolare una percentuale reale.
- Lezione: in questo repository ogni push su master senza `[skip ci]` innesca un rilascio OTA reale (vedi voce INCIDENTE-RILASCIO-OTA-NON-VOLUTO-20261004): per qualunque commit di codice non ancora provato su hardware, `[skip ci]` è obbligatorio, non opzionale.

## 2026-11-03 17:04 CET — Claude (Sonnet 5.5, session id 97e5904c-9e6f-431a-939d-6f9647d93ee3) — OPERAZIONE — id: CI-SOLO-SU-CODICE-20261103

- Soggetto: ci-build-ota
- Decisione o attività: su richiesta di Dario il workflow build.yml parte ora solo se cambiano src/, include/, lib/, data/, scripts/, platformio.ini o partitions_ota.csv (filtro paths su push; workflow_dispatch resta). Il workflow stesso non è tra i percorsi, perché modificarlo non deve produrre un firmware e un upload OTA. Verificato su YAML valido e sugli ultimi 6 commit: 5 (documenti, registro, hook) non avrebbero fatto partire la build, 1 (2d70fb9, firmware) sì.
- Causa del problema: dal 04/10 ogni push su master faceva partire build, tag e release, anche per documenti e hook. Oggi due mie push (AGENTS.md 14:03 e hook commit-msg 15:59) hanno fatto partire due build, entrambe fallite al passo di compilazione (src/main.cpp:339, esp_task_wdt_init(8, true) a due argomenti non accettato dalla versione attuale di Arduino-ESP32; la riga è del 11/11/2025, la piattaforma espressif32 non è fissata in platformio.ini e l'ultima build riuscita è del 04/10). Prima della compilazione il workflow ha però già creato i tag v1.4.27+202611031403 e v1.4.28+202611031600 e le due release GitHub (senza firmware.bin, perché la compilazione è fallita); l'upload al server OTA è un passo successivo e non è stato eseguito.
- Verifiche o fonti: gh run list e view, git ls-remote --tags, log della corsa fallita.
- File o commit: .github/workflows/build.yml, questa voce.
- Prossimo passo o blocchi: decisione di Dario su (1) le due release e i due tag vuoti, (2) la correzione della chiamata esp_task_wdt_init o il blocco della versione della piattaforma.

## 2026-11-03 17:11 CET — Claude (Sonnet 5.5, session id 97e5904c-9e6f-431a-939d-6f9647d93ee3) — OPERAZIONE — id: PIATTAFORMA-8-0-0-RAMO-20261103

- Soggetto: ci-build-ota
- Decisione o attività: su scelta di Dario eliminate le due release vuote e i due tag (v1.4.27+202611031403, v1.4.28+202611031600; gh release delete --cleanup-tag); la numerazione riparte da v1.4.26. Su indicazione di Dario («se è uscita una nuova versione e possiamo usarla, mi trovi d'accordo») preparato il passaggio a espressif32 8.0.0 (Arduino-ESP32 3.3.12) sul ramo esp32-platform-8.0.0 (d058c96, non su master, per non lanciare build/release/OTA): platformio.ini fissato a 8.0.0 in entrambi gli ambienti e main.cpp con `#if ESP_ARDUINO_VERSION_MAJOR >= 3` (esp_task_wdt_reconfigure con timeout 8000 ms, panic attivo, idle task non sorvegliati; ramo #else invariato).
- Verifiche o fonti: pio run -e esp32-prod in locale: con 7.1.3 (build pulita) SUCCESS, flash 69,3% (1.135.229 B di 1.638.400); con 8.0.0 SUCCESS, flash 93,1% (1.525.831 B di 1.638.400), RAM 16,7%. La build di CI fallita oggi usava 8.0.0 senza pin (framework 4.30312.261024) ed era fallita su esp_task_wdt_init; l'ultima riuscita (04/10) usava la 7.1.3. Non verificato: il comportamento su un dispositivo reale con Arduino-ESP32 3.x (WiFi, server asincrono, OTA, watchdog con idle task non sorvegliati, deep sleep), il codice di #11 del 03/11 (riconnessione WiFi, deep sleep) mai provato su dispositivo.
- File o commit: ramo esp32-platform-8.0.0 (d058c96); questa voce.
- Prossimo passo o blocchi: decisione di Dario su cosa mettere su master (il push su master lancia build, release e upload al server OTA): 8.0.0 (flash al 93%, non provata su dispositivo) oppure fissare 7.1.3 (flash 69%, compila come a ottobre).
