#pragma once

// Criterio per confermare l'app dopo un aggiornamento OTA (issue #5).
// Si valida a fine setup() solo se la config e' stata caricata; WiFi e MQTT non contano,
// cosi' un AP o un broker spenti non fanno tornare indietro un firmware buono.
inline bool otaShouldMarkValid(bool configLoaded) {
  return configLoaded;
}
