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
