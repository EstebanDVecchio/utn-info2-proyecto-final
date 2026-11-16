// alertas.h
// Interfaz del módulo de LEDs de estado recibidos por puerto serie.

#ifndef ALERTAS_H
#define ALERTAS_H

// Configura los pines de los LEDs como salida y los inicializa apagados.
void inicializarAlertas();

// Actualiza los LEDs según el comando recibido ('G', 'Y' o 'R').
void aplicarAlerta(char comando);

// Lee comandos pendientes del puerto serie sin bloquear el bucle principal.
void procesarAlertasSerial();

#endif  // ALERTAS_H
