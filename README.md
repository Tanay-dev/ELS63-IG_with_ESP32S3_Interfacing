# ELS63-IG_with_ESP32S3_Interfacing

Connect ESP32 UART2 TX (GPIO17) to the ESL63‑IG EVK’s MCU\_RXD pin on J5, and ESP32 UART2 RX (GPIO16) to the EVK’s MCU\_TXD pin on J5, with a shared ground between the two boards. Ensure the EVK is powered (via its USB or a proper 3.3 V/5 V supply) and both sides use 115200 baud, 8‑N‑1, with no hardware flow control.
