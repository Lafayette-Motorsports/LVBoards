#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  while(!Serial); // Wait for Serial to connect (for some boards)

  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN BUS Shield initialized");
  } else {
    Serial.println("CAN BUS Shield init failed");
    while(1);
  }

  CAN.setMode(MCP_NORMAL);
  Serial.println("Starting CAN communication...");
}

void loop() {
  // Prepare message data
  byte data[8] = {0,1,2,3,4,5,6,7};

  // Send message
  if (CAN.sendMsgBuf(0x100, 0, 8, data) == CAN_OK) {
    Serial.print("Sent: ");
    for (int i = 0; i < 8; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("Error sending message");
  }

  // Check for received messages continuously
  while (CAN.checkReceive() == CAN_MSGAVAIL) {
    unsigned long rxId;
    byte len = 0;
    byte rxBuf[8];

    CAN.readMsgBuf(&rxId, &len, rxBuf);

    Serial.print("Received ID: 0x");
    Serial.print(rxId, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(200); // Short delay to avoid flooding Serial too much
}
