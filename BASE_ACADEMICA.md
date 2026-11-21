# Base académica de la Entrega 2

La guía de la actividad establece qué se entrega: circuito Arduino con Bluetooth, enlace serial, pruebas en simulación y artículo IEEE.
Las lecturas fundamentales explican los conceptos y el procedimiento para desarrollar esa actividad. La sesión sincrónica detalla los comandos y las evidencias.

| Lectura proporcionada | Base que se aplica | Lugar donde se refleja |
| --- | --- | --- |
| Escenario 1, Internet modelo y dominios, pp. 8–11 | Sistema embebido y transmisión de datos dentro del ecosistema IoT. | Introducción y alcance del artículo. Arduino procesa las órdenes de un enlace local. |
| Escenario 2, Direccionamiento IP propagación y redes, pp. 3–4 | Emisor, receptor, canal y Bluetooth como tecnología WPAN. | Explicación de la terminal, el módulo Bluetooth y el enlace UART. |
| Escenario 3, Pilares del IoT y sus características, pp. 6–9 | Personas, objetos, datos y procesos; control de objetos sencillos. | Usuario que envía órdenes, Arduino y LED como objetos, comandos como datos y programa como proceso. |
| Escenario 4, Arduino y Raspberry, pp. 2–6 | Pines digitales, alimentación, GND, transmisión y recepción TX/RX. | Montaje con Arduino Uno, HC-05, RX0/TX1 y LED D2/D3. |
| Escenario 5, IDE Arduino, pp. 4–13 | Seleccionar placa, verificar/compilar, usar monitor serial y programar con setup(), loop(), variables, funciones y comentarios. | Sketch C/C++, compilación oficial para Uno, monitor a 9600 baudios y explicación del programa en el artículo. |

## Correspondencia con el diagrama de la actividad

Se conservan Arduino Uno, módulo Bluetooth, protoboard, dos LED y sus resistencias, además de la asignación de pines de la figura:

| Señal | Conexión implementada |
| --- | --- |
| TXD del módulo | RX0 del Arduino. |
| TX1 del Arduino | RXD del módulo mediante divisor de 1 kΩ y 2 kΩ. |
| Salida verde | D2, con resistencia de 220 Ω. |
| Salida roja | D3, con resistencia de 220 Ω. |
| Alimentación | 5 V al adaptador con regulador y GND común. |

Las conexiones de los LED se organizan con sus cátodos a GND, para encenderlos con HIGH. El divisor es una protección añadida para RXD.
Se usan las lecturas como base conceptual y se verifican las especificaciones del hardware con la documentación del fabricante.
El alcance es control local: no se añadió una conexión a Internet, nube, direccionamiento IP ni una Raspberry Pi a este montaje.

## Verificar en Arduino IDE siguiendo el Escenario 5

1. Abre codigo/ControlBluetooth/ControlBluetooth.ino.
2. Selecciona la placa Arduino Uno en el selector de placa o en Herramientas → Placa → Arduino AVR Boards → Arduino Uno.
3. Pulsa Verificar/Compilar. Esta acción permite revisar el programa sin tener una placa conectada.
4. Si cuentas con una placa física, su puerto COM debe ser el que el sistema detecte al conectarla; no se asigna aquí un COM ficticio. La carga a hardware no forma parte de las pruebas ejecutadas.
5. Para observar un montaje físico con este sketch, el monitor serial debe usar 9600 baudios, igual que Serial.begin(9600).

La verificación automatizada del sketch se realizó con Arduino CLI, herramienta oficial que ofrece las funciones de compilación del entorno Arduino:

    arduino-cli compile --fqbn arduino:avr:uno codigo/ControlBluetooth

Se utilizó Arduino CLI 1.6.0 y Arduino AVR 1.8.8. La compilación terminó sin errores y reportó 2668 bytes de programa y 190 bytes de variables globales.
El log sin editar conserva también las advertencias del núcleo Arduino sobre parámetros no usados. No se ocultaron ni se presentaron como errores del sketch.

## Ejecutar las pruebas en el simulador

1. Abre el enlace del circuito en README o importa simulacion/Entrega2.mokxi.json en Mokxi.
2. Ejecuta Run y abre el panel Bluetooth.
3. Envía B, R, A, X y 0 de una en una, esperando la respuesta entre órdenes.
4. Observa los LED y vuelve con Back al monitor serial. La comunicación usa la UART RX0/TX1 a 9600 baudios.
5. Repite la secuencia diez veces. X se envía con ambos LED encendidos para comprobar que conserva el estado.

Las 50 pruebas incluidas se repitieron con este montaje y este código. Sus capturas y registros sustituyen los de la adaptación anterior.
En el monitor aparecen tanto mensajes del Uno como datos recibidos por el HC-05; representan la misma transmisión. El CSV conserva una fila por orden del Uno.
La prueba adicional de V se mantiene aparte de las 50 principales.

El simulador modela el módulo y su UART. Las pruebas no son mediciones de radiofrecuencia, alcance ni conexión con un teléfono físico.
