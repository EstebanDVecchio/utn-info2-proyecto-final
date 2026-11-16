// controladorDron.h
// Interfaz del módulo de entradas: joysticks, potenciómetro y botones.

#ifndef CONTROLADOR_DRON_H
#define CONTROLADOR_DRON_H

#include <stdint.h>

// Lecturas crudas de los controles físicos del mando.
struct EstadoControles {
  int lx;
  int ly;
  int rx;
  int ry;
  int pot;
  uint8_t b1;
  uint8_t b2;
};

// Configura los pines de entrada (botones con pull-up interno).
void inicializarControles();

// Lee todos los ejes analógicos y botones del controlador.
EstadoControles leerControles();

// Envía la trama "lx,ly,rx,ry,pot,b1,b2\n" por puerto serie.
void enviarControlesSerial(const EstadoControles& estado);

#endif  // CONTROLADOR_DRON_H
