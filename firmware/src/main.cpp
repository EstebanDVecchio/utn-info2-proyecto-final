// main.cpp
// Punto de entrada del firmware (PlatformIO).

#include <Arduino.h>

#include "alertas.h"
#include "config.h"
#include "controladorDron.h"

namespace {
unsigned long ultimoEnvioMs = 0;
}  // namespace

void setup() {
  Serial.begin(BAUDIOS);
  inicializarControles();
  inicializarAlertas();
}

void loop() {
  procesarAlertasSerial();

  const unsigned long ahoraMs = millis();
  if (ahoraMs - ultimoEnvioMs >= PERIODO_ENVIO_MS) {
    ultimoEnvioMs = ahoraMs;
    const EstadoControles estado = leerControles();
    enviarControlesSerial(estado);
  }
}
