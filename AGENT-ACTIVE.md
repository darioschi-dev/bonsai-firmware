# AGENT-ACTIVE — chi sta lavorando adesso

File condiviso tra tutti gli agenti (Claude, Codex, Antigravity/`agy`, Copilot) per segnalare **lavoro in corso in questo momento**, non ancora concluso. Non è un diario (quello è `.agent/STATE.md`). Esiste solo per un motivo: questa repo è una working directory condivisa su disco, non un worktree isolato per sessione — più agenti possono scrivere sugli stessi file in parallelo senza saperlo. Questo file rende visibile "chi sta toccando cosa adesso" prima che diventi un conflitto.

## Regole (obbligatorie per tutti gli agenti)

1. **Prima di iniziare o delegare un task non banale che modifica file**: leggere questo file per intero. Se un'altra voce elenca file o un'area che si sovrappone al task che si sta per iniziare, **non procedere in silenzio**: segnalarlo all'utente e chiedere come procedere (aspettare, coordinarsi, procedere comunque).
2. **All'inizio del task**: aggiungere una voce in fondo alla sezione "Voci attive" col template sotto.
3. **Alla fine del task** (concluso, fallito, o abbandonato): rimuovere la propria voce. Nessuna voce deve restare qui più a lungo della sessione che l'ha creata.
4. **Non rimuovere mai la voce di un altro agente** senza prima aver verificato che sia davvero stale (processo terminato: controllare `ps aux`, `~/.codex/session_index.jsonl` + mtime dei rollout in `~/.codex/sessions/`, o chiedere direttamente all'utente). Una voce vecchia non è automaticamente morta.
5. Se si trova una voce palesemente stale (sessione confermata terminata, non solo presunta), si può rimuovere — annotare brevemente il motivo nel messaggio con cui la si toglie, se rilevante per l'utente.
6. Nessun segreto, credenziale o dato cliente in questo file.
7. Questo file **non ha retention né storico**: se non c'è nessun task in corso, resta con la sola sezione vuota. Non è un archivio — l'archivio è la history git.

## Template voce

```markdown
### [agente] (session id [id-sessione]) · [area/file principali] · dal [YYYY-MM-DD HH:MM]
- **Task:** una riga su cosa si sta facendo.
- **Note:** eventuali dettagli utili a chi controlla prima di iniziare qualcosa di sovrapponibile (opzionale).
```

---

## Voci attive
