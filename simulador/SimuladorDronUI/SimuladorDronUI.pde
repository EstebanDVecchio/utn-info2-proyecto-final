// SimuladorDronUI.pde
// TEST TEMPORAL REVERTIBLE para verificar el firmware por puerto serie.

import processing.serial.*;

Serial puerto;
String nombrePuerto = "Sin conectar";
String ultimaTrama = "-";
char ledActual = 'G';

int lx = 512, ly = 512, rx = 512, ry = 512, pot = 512;
int b1 = 0, b2 = 0;

float dronX = 400;
float dronY = 300;

void setup() {
  size(800, 600);
  surface.setTitle("Test Firmware Dron (Revertible)");

  String[] puertos = Serial.list();
  if (puertos.length > 0) {
    nombrePuerto = puertos[0];
    for (String p : puertos) {
      if (p.contains("ttyACM") || p.contains("ttyUSB")) {
        nombrePuerto = p;
        break;
      }
    }
    try {
      puerto = new Serial(this, nombrePuerto, 115200);
      puerto.clear();
    } catch (Exception e) {
      nombrePuerto = "Error al abrir " + nombrePuerto;
      puerto = null;
    }
  }
}

void draw() {
  leerSerial();

  background(24, 28, 36);

  // Mover el dron de prueba con joystick izq. y velocidad del potenciómetro
  float velMax = map(pot, 0, 1023, 1.0, 8.0);
  float dx = map(lx, 0, 1023, -1, 1);
  float dy = map(ly, 0, 1023, -1, 1);
  if (abs(dx) < 0.08) dx = 0;
  if (abs(dy) < 0.08) dy = 0;

  dronX = constrain(dronX + dx * velMax, 20, width - 20);
  dronY = constrain(dronY + dy * velMax, 20, height - 20);

  // Dibujar dron de prueba
  noStroke();
  fill(80, 200, 255);
  ellipse(dronX, dronY, 28, 28);

  // Dibujar joystick derecho como puntero auxiliar
  float jx = map(rx, 0, 1023, width - 150, width - 30);
  float jy = map(ry, 0, 1023, 30, 150);
  stroke(90);
  noFill();
  rect(width - 150, 30, 120, 120);
  noStroke();
  fill(255, 190, 70);
  ellipse(jx, jy, 12, 12);

  // HUD simple de diagnóstico
  fill(230);
  textSize(14);
  text("Puerto: " + nombrePuerto, 20, 30);
  text("Trama:  " + ultimaTrama, 20, 52);
  text("Joy Izq: (" + lx + ", " + ly + ")  Btn1: " + b1, 20, 78);
  text("Joy Der: (" + rx + ", " + ry + ")  Btn2: " + b2, 20, 100);
  text("Pot (Vel): " + pot + "  (velMax=" + nf(velMax, 1, 2) + ")", 20, 122);
  text("LED enviado: " + ledActual + "  | Teclas: [G] Verde  [Y] Amarillo  [R] Rojo  [Espacio] Centrar", 20, height - 24);
}

void leerSerial() {
  if (puerto == null) return;
  while (puerto.available() > 0) {
    String linea = puerto.readStringUntil('\n');
    if (linea == null) break;
    linea = trim(linea);
    if (linea.length() == 0) continue;

    String[] partes = split(linea, ',');
    if (partes.length == 7) {
      try {
        lx = int(partes[0]);
        ly = int(partes[1]);
        rx = int(partes[2]);
        ry = int(partes[3]);
        pot = int(partes[4]);
        b1 = int(partes[5]);
        b2 = int(partes[6]);
        ultimaTrama = linea;
      } catch (Exception e) {
        // Ignorar trama incompleta al iniciar
      }
    }
  }
}

void keyPressed() {
  if (key == ' ') {
    dronX = width / 2.0;
    dronY = height / 2.0;
    return;
  }
  char c = Character.toUpperCase(key);
  if (c == 'G' || c == 'Y' || c == 'R') {
    ledActual = c;
    if (puerto != null) {
      puerto.write(c);
    }
  }
}
