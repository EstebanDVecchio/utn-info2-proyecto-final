# Controlador de Dron + Simulador

Proyecto con dos partes:

| Carpeta | Herramienta | Descripción |
|---|---|---|
| `firmware/` | PlatformIO (Arduino Uno) | Código del controlador del dron |
| `simulador/SimuladorDronUI/` | Processing 4 | Interfaz/simulador en PC |

## Estructura

```
.
├── platformio.ini          # Config PlatformIO (apunta a firmware/)
├── firmware/
│   ├── include/            # Headers (.h): config, controladorDron, alertas
│   ├── src/                # main.cpp y fuentes (.cpp)
│   ├── lib/                # Librerías privadas
│   └── test/               # Tests unitarios
├── simulador/
│   └── SimuladorDronUI/
│       ├── SimuladorDronUI.pde   # setup()/draw(), bucle principal
│       ├── Dron.pde              # estado, física y dibujo cenital
│       ├── Integrador.pde        # métodos numéricos (Euler, semi-implícito, RK4)
│       ├── Camara.pde            # seguimiento y zoom
│       ├── Entrada.pde           # serial + teclado de respaldo
│       ├── Mapa.pde              # grilla, límites, obstáculos
│       └── HUD.pde               # información en pantalla
└── docs/                   # Informe, diagramas y capturas
```

## Conexiones (Arduino UNO)

| Componente | Pin |
|---|---|
| Joystick izq. X / Y / botón | A1 / A0 / D2 |
| Joystick der. X / Y / botón | A3 / A2 / D3 |
| Potenciómetro (velocidad) | A4 |
| LED verde / amarillo / rojo (220 Ω) | D9 / D10 / D11 |

> **Nota:** Los ejes X/Y de ambos joysticks están intercambiados respecto al rotulado del módulo por la orientación física de 90° en la protoboard.

## Protocolo serial (115200 baudios)

- **Arduino → PC**: `lx,ly,rx,ry,pot,b1,b2\n` (valores de 0 a 1023, botones 0 o 1) a 50 Hz
- **PC → Arduino**: `G` | `Y` | `R` (estado de los LEDs)

> El monitor serie y el simulador no pueden usar el puerto a la vez: cerrá uno antes de abrir el otro.
> En Linux, el usuario debe pertenecer al grupo `dialout`: `sudo usermod -aG dialout $USER`

## Uso en VS Code

Extensiones recomendadas (VS Code las sugiere al abrir la carpeta):
PlatformIO IDE, Processing.

Tareas (`Ctrl+Shift+P` → *Tasks: Run Task*):

- **Firmware: Compilar**
- **Firmware: Subir al Arduino**
- **Firmware: Monitor serie**
- **Simulador: Ejecutar (Processing)**
- **Simulador: Abrir en Processing IDE**

También funcionan los botones de la barra de PlatformIO y el botón ▶ de la extensión Processing al abrir el `.pde`.
