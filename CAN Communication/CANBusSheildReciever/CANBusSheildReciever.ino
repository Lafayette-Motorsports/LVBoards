#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 9;   // Seeed Studio Shield uses D9
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);

  while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("CAN init failed! Retrying...");
    delay(1000);
  }

  Serial.println("CAN initialized successfully!");
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN.checkReceive() == CAN_MSGAVAIL) {

    unsigned long rxId;
    byte len = 0;
    byte buf[8];

    CAN.readMsgBuf(&rxId, &len, buf);

    Serial.println("------ CAN Message Received ------");

    Serial.print("ID: 0x");
    Serial.println(rxId, HEX);

    Serial.print("Length: ");
    Serial.println(len);

    Serial.print("HEX Data: ");
    for (int i = 0; i < len; i++) {
      if (buf[i] < 0x10) Serial.print("0");  // leading zero
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("ASCII: ");
    for (int i = 0; i < len; i++) {
      if (isPrintable(buf[i])) {
        Serial.print((char)buf[i]);
      } else {
        Serial.print(".");
      }
    }
    Serial.println();

    Serial.println("----------------------------------\n");
  }
}