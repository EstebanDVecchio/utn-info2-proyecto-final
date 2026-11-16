// config.h
// Configuración central del hardware: pines, velocidad serial y temporización

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Comunicación serial
constexpr unsigned long BAUDIOS = 115200;
constexpr unsigned long PERIODO_ENVIO_MS = 20;  // 50 Hz

// Pines de entradas analógicas (joysticks y potenciómetro)
// Nota: IZQ y DER X/Y intercambiados por orientación física de los módulos en protoboard.
constexpr uint8_t PIN_JOY_IZQ_X = A1;
constexpr uint8_t PIN_JOY_IZQ_Y = A0;
constexpr uint8_t PIN_JOY_DER_X = A3;
constexpr uint8_t PIN_JOY_DER_Y = A2;
constexpr uint8_t PIN_POT_VELOCIDAD = A4;

// Pines de botones de los joysticks
constexpr uint8_t PIN_BTN_IZQ = 2;
constexpr uint8_t PIN_BTN_DER = 3;

// Pines de LEDs indicadores de estado
constexpr uint8_t PIN_LED_VERDE = 9;
constexpr uint8_t PIN_LED_AMARILLO = 10;
constexpr uint8_t PIN_LED_ROJO = 11;

#endif
