# Istruzioni per gli agenti

Tipo di repository: codice.

<!-- atk-scaffold:prima-di-iniziare 829ddadf -->
## Prima di iniziare

- Leggere `git status` e `git diff` prima di modificare file; non sovrascrivere né annullare modifiche altrui senza richiesta esplicita dell'utente.
- Leggere `AGENT-ACTIVE.md` per intero: se una voce elenca file o un'area che si sovrappone al task che si sta per iniziare, non procedere in silenzio ma segnalarlo all'utente.
- Leggere `.agent/STATE.md` (almeno le ultime 3-5 voci) per operazioni, decisioni, verifiche e blocchi lasciati da qualunque agente già interpellato.

<!-- atk-scaffold:lavoro-in-corso cb5813fc -->
## Lavoro in corso (`AGENT-ACTIVE.md`)

`AGENT-ACTIVE.md`, alla radice del repository, segnala **chi sta lavorando adesso e a cosa**, così che agenti in parallelo non lavorino sugli stessi file o sullo stesso task e non cancellino le modifiche l'uno dell'altro. Il repository è una working directory condivisa, non un worktree isolato per sessione. Prima di iniziare un task non banale che modifica file lo si legge per intero: se una voce elenca file o un'area che si sovrappone, non si procede in silenzio ma lo si segnala all'utente. All'inizio del task si aggiunge la propria voce (template nel file), alla fine si rimuove; nessuna voce resta più a lungo della sessione che l'ha creata. Non si rimuove mai la voce di un altro agente senza aver verificato che sia davvero stale (processo terminato, oppure chiedendo all'utente). Non ha storico: l'archivio è Git. Nessun segreto o dato personale.

<!-- atk-scaffold:registro-condiviso-delle-operazioni-e-delle-decisioni a6401b7a -->
## Registro condiviso delle operazioni e delle decisioni

`.agent/STATE.md` è il registro cronologico unico e append-only. Qualunque agente interpellato può e deve aggiungere le proprie operazioni e decisioni rilevanti; nessun agente o fornitore ne ha ownership esclusiva. Ogni voce ha un heading con data, agente e modello (l'identificatore di sessione ha la sua regola, più sotto) e indica inoltre tipo (`OPERAZIONE` o `DECISIONE`), attività o decisione, verifiche o fonti, file o commit, prossimo passo o blocchi. Le rettifiche sono nuove voci che richiamano quella corretta. Niente segreti né dati personali non necessari.

<!-- atk-scaffold:session-id-nelle-voci-del-registro 885ffe26 -->
## Session id nelle voci del registro

Ogni voce di `.agent/STATE.md` ha un heading `## AAAA-MM-GG HH:MM TZ — <agente> (<modello>, session id <id-sessione>) — <TIPO>`: l'id della sessione che ha scritto la voce serve a riaprire quella conversazione per chiarimenti. Per Claude è la variabile d'ambiente `$CLAUDE_CODE_SESSION_ID` (uguale al nome del file `.jsonl` in `~/.claude/projects/<cartella>/`), per Codex l'id (uuid finale) nel nome del rollout in `~/.codex/sessions/`, per Antigravity l'id della conversazione se l'agente lo può leggere; se non è recuperabile scrivere `session id n/d`, senza inventarlo. Dentro le parentesi niente trattini lunghi (`—`), che separano i campi dell'heading.

<!-- atk-scaffold:soggetto-delle-voci-del-registro 5b54a8e7 -->
## Soggetto delle voci del registro

Una voce di `.agent/STATE.md` che tratta una questione precisa (un ticket, un impianto, una pratica, una decisione) scrive il bullet `- Soggetto: <soggetto>` con un valore breve, stabile e specifico (es. `T019`, `novoli-ups`), sempre lo stesso per la stessa questione. `atk context brief` mostra come aperto solo il «Prossimo passo o blocchi» della voce più recente di ogni soggetto: una voce nuova sullo stesso soggetto supera le precedenti, anche se scrive «nessuno», senza bisogno di `Chiude:`. Due questioni diverse con lo stesso soggetto si oscurano a vicenda: nel dubbio scegliere il valore più specifico. Senza `Soggetto:` la voce si comporta come prima; le voci storiche non si riscrivono. Un ticket o un item il cui `status` cambia per una decisione registrata va aggiornato nello stesso task (il brief legge anche quello).

<!-- atk-scaffold:lezioni-dal-campo b9f22651 -->
## Lezioni dal campo

Quando in un task impari qualcosa di **carattere generale** (un errore che chiunque potrebbe ripetere, un'abitudine che ha evitato un danno), scrivilo nella voce di `.agent/STATE.md` con il bullet `- Lezione: <una regola, con l'esempio che l'ha originata>` (un bullet per lezione). `atk lessons` le raccoglie da tutti i diari e le propone a Dario: una lezione entra nelle regole o nelle skill (`delegate/LESSONS.md`) solo se lui la conferma. Non serve per la cronaca del lavoro (sta in «Decisione o attività») né per ciò che vale solo per questo repository (quello è una decisione vigente).

<!-- atk-scaffold:stato-degli-item 65686a5b -->
## Stato degli item (frontmatter dei README)

Il frontmatter di un README item ha `status` con **uno solo** di questi valori, scritti così: `open`, `in_progress`, `waiting_vendor`, `waiting_customer`, `planned`, `monitoring`, `resolved`, `closed` (significati in `agent-toolkit/docs/CONTEXT.md`, sezione «Vocabolario di status»). Mai una frase nello `status`: il dettaglio (data, motivo, cosa si attende) va in `status_note`. Quando cambia lo stato di un item, nello stesso task si aggiorna `status` nel README **e** la riga di stato nel registro riassuntivo del dossier, se esiste (es. `REGISTRO_TICKET.md`), dove lo stato inizia con lo stesso valore canonico: `- **Stato:** resolved (28/08/2026, batteria sbloccata)`. Dove ogni unità ha un README, il README è la fonte di verità e il registro riassuntivo è una vista che serve a leggere in fretta senza aprire ogni cartella; dove le unità sono righe o sezioni di un tracker senza README, la fonte di verità è il tracker `.md` (regola «Formato dei tracker»). Lo stesso insieme di unità ha una sola fonte di verità, mai due. Il campo `status` è riservato allo stato di un'unità: il ruolo di un file (registro, tracker) si scrive in `role` (`role: registro`), mai in `status`. `atk context lint` avvisa degli `status` fuori vocabolario e `atk context normalize-status` li porta al vocabolario.

<!-- atk-scaffold:flusso-di-lavoro-tra-agenti 4959e362 -->
## Flusso di lavoro tra agenti

Chi riceve un task legge `.agent/STATE.md` e lo classifica: una **DECISIONE** richiede una scelta dell'utente (proporre le opzioni, non decidere da soli), una **OPERAZIONE** si esegue secondo le regole del repository. Non c'è una divisione fissa di aree tra gli agenti con accesso diretto al repository.

**Budget di lettura:** <documento di sintesi del progetto>, poi le ultime voci di `.agent/STATE.md`; i documenti di dettaglio solo se il task li richiede.

**Handoff a fine sessione:** test verdi, propria voce rimossa da `AGENT-ACTIVE.md`, nuova voce in `.agent/STATE.md` con prossimo passo o blocchi, ed elenco esplicito di ciò che è verificato, validato solo staticamente o da provare altrove.

<!-- atk-scaffold:git 1017154a -->
## Git (solo developer)

Il lavoro avviene direttamente su `main`, senza PR né feature branch obbligatori. **Alla fine di ogni task che modifica file tracciati, completato e verificato, l'agente committa e pubblica (`git push`)**: solo i file del task, con il messaggio nel formato della cronologia del repository, senza chiedere conferma. L'unico vincolo è il **rilascio in produzione**, cioè il push sul branch `production` (o il deploy equivalente di un repository): lo esegue l'agente solo su richiesta esplicita dell'utente. Se un repository ha un `pre-push` che esegue controlli, il push li rispetta e non li aggira. Un branch solo per refactor grandi, esperimenti o riscritture che si potrebbero abbandonare (`git switch -c experiment/<nome>`), poi merge o cancellazione.

<!-- atk-scaffold:mai-inventare a3fdf861 -->
## Mai inventare

Non si inventa nulla. Un fatto, una data, un'ora, un numero, un nome, un percorso, il tipo di un repository, un esito o una causa si leggono da una fonte (il file, il comando, il codice, il registro, l'orologio con `date`) oppure si dichiarano «non verificato»: mai scritti a memoria o per verosimiglianza, nemmeno nei registri, nei documenti, nelle mappe e nei messaggi di commit. Se manca la fonte, si cerca; se non si trova, si scrive che non c'è e si chiede. Regola data a voce da Dario il 2026-10-02, dopo orari e date scritti a memoria nei registri e un tipo di repository dichiarato senza averlo guardato.

<!-- atk-scaffold:nessun-debito-tecnico-lasciato-dietro 554f4acd -->
## Nessun debito tecnico lasciato dietro

Una modifica non lascia residui. Se cambia una regola, un formato o un dato, nello stesso task si sanano tutti i punti che lo ripetono (testi scritti a mano, documenti, skill, registri, altri repository) e prima di chiudere si cerca con `grep` la vecchia formulazione. Se qualcosa non si può sanare subito, si scrive nel registro un punto aperto con il motivo e cosa resta da fare, mai un'incoerenza taciuta. Quando due fonti divergono, si risale alla decisione o al commit da cui nasce la divergenza e lo si scrive nel registro: l'incoerenza si spiega, oltre che correggerla.

<!-- atk-scaffold:messaggi-di-commit 96adae43 -->
## Messaggi di commit

Nel messaggio di un commit o di una PR non compare alcun riferimento all'AI: né `Co-Authored-By` né firme, né il nome di un assistente o di un modello (Claude, Sonnet, Opus, Codex, GPT, Gemini e simili), nemmeno per dire chi ha fatto cosa: quello sta in `.agent/STATE.md`. Il messaggio descrive cosa cambia nel repository. La regola è imposta da `.githooks/commit-msg`, che rifiuta il commit (anche quelli fatti a mano): lo installa `atk scaffold --hooks --apply`, che imposta anche `git config core.hooksPath .githooks` (impostazione locale: dopo ogni clone, anche su Ubuntu, va rifatta con lo stesso comando) e `atk doctor` avvisa se manca.

<!-- atk-scaffold:chiusura-del-lavoro-e-stato-as-is 945e408d -->
## Chiusura del lavoro e stato as-is

`.agent/AS-IS.md` è il riepilogo corto, con lo stesso nome in ogni repository, di com'è oggi il sistema, produzione compresa: cosa gira e in quale versione, cosa non esiste ancora o è dismesso, con data e fonte della verifica, e rimandi ai documenti di dettaglio. Non è un diario né un elenco di cose da fare. Un lavoro da fare è un'issue GitHub (repository di codice) o una scheda (dossier); il «Prossimo passo o blocchi» del registro rimanda al suo numero (`#N`) oppure scrive «nessuno».

A chiusura di un lavoro completato e verificato, nello stesso task e prima di dichiararlo chiuso: (1) se c'è un'issue GitHub collegata, aggiornala con un commento con l'esito e il commit e chiudila se il lavoro è finito (`Closes #N` nel messaggio di commit); se non c'è un'issue, il messaggio di commit dice «senza issue». (2) Se il lavoro ha risolto qualcosa che era aperto, o ha portato in produzione qualcosa che era un'issue o era segnato come inesistente, aggiorna `.agent/AS-IS.md` e la sua data di verifica. (3) Se il lavoro nasce da un task Google e il legame è scritto (id o titolo nell'issue, nella scheda o nella voce di registro), proponi all'utente di completarlo; lo completi solo con il suo ok in quella sessione. Non crei né modifichi task di tua iniziativa.

<!-- atk-scaffold:documenti bcb0deb5 -->
## Documenti (`docs/`)

La cartella `docs/` contiene solo documenti vivi e leggibili. Ogni documento vivo ha sotto il titolo la riga `> **Stato:** vivo — **Verificato il:** AAAA-MM-GG — **Controlla se cambia:** `percorso`, `altro/percorso``: la data è l'ultima volta che qualcuno ha confrontato il testo con la realtà, e i percorsi sono ciò che, se cambia, lo rende da ricontrollare. Un documento superato, una bozza chiusa o un duplicato si sposta con `git mv` in `docs/storico/` (non si cancella) e non si legge per default. `docs/INDEX.md` è generato (`atk docs index --apply`) e non si modifica a mano. Quando un lavoro cambia ciò che un documento descrive, lo si aggiorna nello stesso task e se ne aggiorna la data; `atk docs check` e `atk doctor` segnalano quelli da ricontrollare, i superati fuori da `docs/storico/` e un indice non aggiornato. Un documento generato da uno script ha la riga `> **Stato:** generato` (senza data, perché il suo contenuto è deterministico). Il limite di documenti narrativi vivi (8; 12 per un portale grande) è una linea guida: un repository può sforarlo se il motivo è scritto nel registro `.agent/STATE.md` o nel file dedicato. I documenti si scrivono e si aggiornano solo in italiano, senza coppie bilingui da tenere allineate; una traduzione si genera a fine lavoro, su richiesta.
