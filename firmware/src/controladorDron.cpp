// controladorDron.cpp
// Implementación del módulo de entradas declarado en controladorDron.h.

#include "controladorDron.h"
#include "config.h"

#include <Arduino.h>

void inicializarControles() {
  pinMode(PIN_BTN_IZQ, INPUT_PULLUP);
  pinMode(PIN_BTN_DER, INPUT_PULLUP);
}

EstadoControles leerControles() {
  EstadoControles estado;
  estado.lx = analogRead(PIN_JOY_IZQ_X);
  estado.ly = analogRead(PIN_JOY_IZQ_Y);
  estado.rx = analogRead(PIN_JOY_DER_X);
  estado.ry = analogRead(PIN_JOY_DER_Y);
  estado.pot = analogRead(PIN_POT_VELOCIDAD);

  // Con INPUT_PULLUP el botón lee LOW al presionarse, así que se invierte a 1 = presionado.
  estado.b1 = (digitalRead(PIN_BTN_IZQ) == LOW) ? 1 : 0;
  estado.b2 = (digitalRead(PIN_BTN_DER) == LOW) ? 1 : 0;
  return estado;
}

void enviarControlesSerial(const EstadoControles& estado) {
  Serial.print(estado.lx);
  Serial.print(',');
  Serial.print(estado.ly);
  Serial.print(',');
  Serial.print(estado.rx);
  Serial.print(',');
  Serial.print(estado.ry);
  Serial.print(',');
  Serial.print(estado.pot);
  Serial.print(',');
  Serial.print(estado.b1);
  Serial.print(',');
  Serial.print(estado.b2);
  Serial.print('\n');
}
