# Entrega 2 de Internet de las Cosas

**Autor:** Johan Sebastian Soto Ramirez  
**Programa:** Ingeniería de Software, Politécnico Grancolombiano  
**Profesor:** Jesús Antonio Figueroa Guerrero

Control de dos luces LED mediante Arduino Uno y un HC-05 simulado en Mokxi.
La base académica son las lecturas de los escenarios 1 a 5, la guía de la actividad y la sesión de clase.
Se conservan los pines del diagrama: Bluetooth en RX0/TX1 y LED en D2/D3.
Se realizaron 50 pruebas principales: diez de B, R, A, 0 y X, además de una comprobación del alias V.
Las 50 pruebas cumplieron el resultado esperado en la simulación.

## Descargas directas

- [Artículo PDF](Entrega_2_IEEE.pdf)
- [Artículo Word](Entrega_2_IEEE.docx)
- [Tabla completa de 50 pruebas](Anexo_50_pruebas.pdf)
- [Proyecto completo con capturas y scripts](Entrega_2_completa.zip)

## Abrir el proyecto

- [Repositorio público](https://github.com/sotobit/iot-entrega-2-bluetooth)
- [Abrir el circuito completo en Mokxi](https://mokxi.com/github.com/sotobit/iot-entrega-2-bluetooth/blob/main/diagram.mokxi.json)

El enlace apunta al archivo nativo completo. Abrir solamente el repositorio desde el importador puede reconstruir un circuito distinto a partir del código.

Si el enlace del simulador no carga, descarga el archivo nativo y abre [Mokxi](https://app.mokxi.com/).
En **Save ▾ → Open JSON or SPICE…**, selecciona simulacion/Entrega2.mokxi.json.
Pulsa **Run**, abre **Bluetooth** y espera a que aparezca **HC-05 — Connected · 9600 baud**.
Escribe una orden y pulsa **Send** o Enter. Espera la respuesta antes de enviar otra.
**Back** permite volver al monitor serial.

| Orden | LED verde | LED rojo | Respuesta |
| --- | --- | --- | --- |
| B o V | Encendido | Apagado | OK |
| R | Apagado | Encendido | OK |
| A | Encendido | Encendido | OK |
| 0 | Apagado | Apagado | OK |
| X | Conserva el estado anterior | Conserva el estado anterior | INVALIDO |

Las letras son mayúsculas. B conserva el comando indicado en la transcripción; V es un alias.
El protocolo usa un carácter por orden. CR, LF y el carácter espacio se ignoran.

## Archivos locales

| Ruta | Contenido |
| --- | --- |
| informe/Entrega 2 IEEE.pdf | Artículo de cuatro páginas, con Abstract e Index Terms. |
| informe/Entrega 2 IEEE.docx | Artículo editable con la plantilla IEEE proporcionada. |
| informe/Anexo de las 50 pruebas.pdf | Las 50 filas de resultados. |
| codigo/ControlBluetooth/ControlBluetooth.ino | Código completo, comentado en español. |
| simulacion/Entrega2.mokxi.json | Circuito y código en un solo archivo portable. |
| simulacion/Exportacion_editor.mokxi.json | Copia descargada desde el editor que ejecutó las pruebas. |
| resultados/pruebas_50.csv y .json | Todos los registros, repetición, fecha y captura asociada. |
| resultados/monitor_serial_50_original.txt | Texto del monitor sin filtrar durante la ejecución. |
| resultados/monitor_serial_con_alias_original.txt | Monitor con la prueba adicional V. |
| resultados/capturas/ | Una imagen por prueba, diseño inicial, alias V y terminal Bluetooth. |
| resultados/graficas/ | Gráficas PNG/SVG y recortes identificados de capturas auténticas. |
| resultados/verificacion.json | Comprobaciones de los datos y del código exportado. |
| FUENTES.md | Quince referencias, incluidas cinco lecturas del curso y tres publicaciones científicas. |
| BASE_ACADEMICA.md | Relación con cada escenario y pasos para verificar el sketch en Arduino. |
| REQUISITOS.md | Correspondencia entre indicaciones y evidencias. |
| pruebas/ | Scripts que construyen el circuito, ejecutan pruebas y generan el informe. |

En GitHub, el código y el archivo nativo se presentan también en la raíz para abrirlos directamente.
Entrega_2_completa.zip conserva esta organización de carpetas e incluye todas las evidencias.

## Conexiones

- D2 → resistencia de 220 Ω → ánodo verde. Cátodo a GND.
- D3 → resistencia de 220 Ω → ánodo rojo. Cátodo a GND.
- TXD del HC-05 → RX0 del Arduino Uno.
- TX1 del Arduino Uno → 1 kΩ → nodo de RXD del HC-05.
- Nodo de RXD → 2 kΩ → GND. Divisor nominal: 3,33 V cuando D3 entrega 5 V.
- VCC del adaptador HC-05 → 5 V. GND común.

En hardware físico, 5 V solo corresponde a una placa adaptadora con regulador que admita esa entrada.
Verifica la variante y su ficha técnica; no conectes directamente 5 V a RXD del módulo.
Configura el modo datos a **9600 baudios, 8N1**. El estado conectado de esta práctica pertenece al modelo del simulador.

## Cómo se hicieron las pruebas

Se ejecutaron diez ciclos de **B → R → A → X → 0**. X se envía con ambos LED encendidos y debe conservarlos.
Playwright escribió las órdenes en el panel Bluetooth y contrastó las líneas visibles del monitor con los estados esperados.
Se guardó una captura real por orden. Después se verificó el alias V como prueba 51.
El número tiempo_ms procede de millis() del Arduino simulado: no representa latencia de radio.
La UART es compartida por el HC-05 y la observación en el monitor USB. Las órdenes se envían desde el panel Bluetooth.
Los mensajes bajo uno1 y bt1 corresponden a la emisión y recepción de la misma comunicación; el CSV conserva una fila del Uno por orden.

El sketch también se compiló con Arduino CLI 1.6.0 y el núcleo Arduino AVR 1.8.8 para arduino:avr:uno.
El resultado fue 2668 bytes de programa y 190 bytes de variables globales. El registro original está en resultados/compilacion_arduino_uno_original.txt.

Para repetir la automatización, instala Node.js, Chrome y Playwright (npm install playwright), y ejecuta:

    node pruebas/ejecutar_pruebas.cjs

El script sustituye los resultados por una nueva ejecución. Conserva antes una copia si necesitas comparar sesiones.
Para regenerar gráficas y Word, instala las dependencias de pruebas/requirements.txt y ejecuta:

    python pruebas/crear_circuito.py
    python pruebas/preparar_informe.py

El PDF del artículo se exportó con Microsoft Word instalado en el equipo.
El documento editable también puede abrirse con una suite gratuita; al exportarlo, revisa nuevamente la paginación.

## Alcance

Se comprobó la ruta **terminal Bluetooth virtual → HC-05 modelado → RX0/TX1 del Arduino → LED D2/D3**, y la confirmación de retorno.
El simulador no transmite radiofrecuencia ni se conecta a un teléfono físico.
No se midieron alcance, interferencias, consumo eléctrico ni latencia inalámbrica.
Las capturas y los registros corresponden a una simulación ejecutada, sin muestras ni imágenes inventadas.
