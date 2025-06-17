#include <Arduino.h>

// Serial Monitor baud
#define SERIAL_BAUD 115200
// Modem UART baud
#define MODEM_BAUD 115200

// Use UART2 on the ESP32 (RX=16, TX=17)
HardwareSerial modem(2);

// How long to wait for a response after you send a command (ms)
const uint32_t RESPONSE_TIMEOUT = 1000;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while(!Serial){}  // wait for Serial Monitor
  
  modem.begin(MODEM_BAUD, SERIAL_8N1, 16, 17);
  delay(200);

  Serial.println(F("=== ESP32 ←→ ESL63‑IG Modem Bridge ==="));
  Serial.println(F("Type any AT command and hit ↵"));
  Serial.println();
}

String inputBuffer;

void loop() {
  // 1) Read from Serial Monitor: accumulate until newline
  while (Serial.available()) {
    char c = Serial.read();
    // echo what you're typing (optional)
    Serial.write(c);
    if (c == '\r' || c == '\n') {
      if (inputBuffer.length() > 0) {
        sendAndPrint(inputBuffer);
        inputBuffer = "";
      }
    } else {
      inputBuffer += c;
    }
  }

  // 2) Print any incoming data from the modem immediately
  while (modem.available()) {
    Serial.write(modem.read());
  }
}

// Send one AT command (string without CR/LF), then print response
void sendAndPrint(const String &cmd) {
  Serial.print(F("\n---> Sending to modem: "));
  Serial.println(cmd);
  modem.println(cmd);  // append CR/LF automatically

  // Wait for response (or timeout), collect & print
  uint32_t start = millis();
  while (millis() - start < RESPONSE_TIMEOUT) {
    while (modem.available()) {
      char c = modem.read();
      Serial.write(c);
      start = millis(); // reset timeout on each received byte
    }
  }
  Serial.println(F("\n<--- End of response\n"));
}
