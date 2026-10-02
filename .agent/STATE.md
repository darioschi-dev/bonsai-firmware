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
