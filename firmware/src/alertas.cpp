// alertas.cpp
// Implementación del módulo de LEDs declarado en alertas.h.

#include "alertas.h"
#include "config.h"

#include <Arduino.h>

namespace {

void establecerLeds(bool verde, bool amarillo, bool rojo) {
  digitalWrite(PIN_LED_VERDE, verde ? HIGH : LOW);
  digitalWrite(PIN_LED_AMARILLO, amarillo ? HIGH : LOW);
  digitalWrite(PIN_LED_ROJO, rojo ? HIGH : LOW);
}

}  // namespace

void inicializarAlertas() {
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_AMARILLO, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  establecerLeds(false, false, false);
}

void aplicarAlerta(char comando) {
  switch (comando) {
    case 'G':
      establecerLeds(true, false, false);
      break;
    case 'Y':
      establecerLeds(false, true, false);
      break;
    case 'R':
      establecerLeds(false, false, true);
      break;
    default:
      break;
  }
}

void procesarAlertasSerial() {
  while (Serial.available() > 0) {
    char comando = static_cast<char>(Serial.read());
    aplicarAlerta(comando);
  }
}
