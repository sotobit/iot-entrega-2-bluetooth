/* Entrega 2 - Internet de las Cosas
 * Johan Sebastian Soto Ramirez
 * UNO: LED verde D8, rojo D9; HC-05 TXD -> D2, RXD <- D3.
 * En montaje fisico: divisor de 1 kohm/2 kohm entre D3 y RXD.
 * Configurar el HC-05 en modo datos, 9600 baudios, 8N1.
 * Cada comando ocupa un byte. CR, LF y espacios se ignoran.
 */
#include <SoftwareSerial.h>

const byte LED_VERDE = 8;
const byte LED_ROJO = 9;
SoftwareSerial bluetooth(2, 3); // RX de Arduino, TX de Arduino
unsigned int registro = 0;

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  Serial.begin(9600);      // Monitor USB: evidencia de las pruebas
  bluetooth.begin(9600);   // Enlace UART con el HC-05
  Serial.println(F("LISTO: V/B=verde R=rojo A=ambos 0=apagar"));
  Serial.println(F("id,tiempo_ms,comando,verde,rojo,resultado"));
}

void procesarComando(char comando) {
  if (comando == '\r' || comando == '\n' || comando == ' ') return;
  bool valido = true;
  switch (comando) {
    case 'V': // V de verde; B conserva la letra de la transcripcion
    case 'B':
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ROJO, LOW);
      break;
    case 'R':
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ROJO, HIGH);
      break;
    case 'A':
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ROJO, HIGH);
      break;
    case '0':
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ROJO, LOW);
      break;
    default:
      valido = false; // Un comando desconocido conserva las salidas
  }
  registro++;
  Serial.print(registro); Serial.print(',');
  Serial.print(millis()); Serial.print(',');
  Serial.print(comando); Serial.print(',');
  Serial.print(digitalRead(LED_VERDE)); Serial.print(',');
  Serial.print(digitalRead(LED_ROJO)); Serial.print(',');
  Serial.println(valido ? F("OK") : F("INVALIDO"));
  // La terminal Bluetooth recibe tambien una confirmacion.
  bluetooth.print(comando);
  bluetooth.println(valido ? F(":OK") : F(":INVALIDO"));
}

void loop() {
  if (bluetooth.available() > 0) {
    procesarComando((char)bluetooth.read());
  }
}
