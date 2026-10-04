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
