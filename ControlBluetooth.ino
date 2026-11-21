/* Entrega 2 - Internet de las Cosas
 * Johan Sebastian Soto Ramirez
 * Pines de la guia: verde D2, rojo D3; HC-05 TXD -> RX0.
 * TX1 -> divisor de 1 kohm/2 kohm -> RXD del HC-05.
 * Configurar el HC-05 en modo datos, 9600 baudios, 8N1.
 * Cada comando ocupa un byte. CR, LF y espacios se ignoran.
 */
const byte LED_VERDE = 2;
const byte LED_ROJO = 3;
unsigned int registro = 0;

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  Serial.begin(9600); // UART de la placa: RX0 y TX1, como en la guia
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
  // TX1 envia el registro y esta confirmacion al HC-05.
  // El monitor serial permite observar la misma comunicacion.
  Serial.print(comando);
  Serial.println(valido ? F(":OK") : F(":INVALIDO"));
}

void loop() {
  if (Serial.available() > 0) {
    procesarComando((char)Serial.read());
  }
}
