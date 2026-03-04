#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 9;     // CS pin for CAN shield
MCP_CAN CAN(SPI_CS_PIN);       // Create CAN object

const int CAN_ID = 0x100;      
const int BAUDRATE = CAN_500KBPS;  // Library uses predefined speeds

void setup() {
  Serial.begin(115200);

  if (CAN.begin(MCP_ANY, BAUDRATE, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN initialized successfully!");
  } else {
    Serial.println("CAN init failed!");
    while (1);
  }

  CAN.setMode(MCP_NORMAL);
}

void loop() {
  byte data[8] = {0,1,2,3,4,5,6,7};

  if (CAN.sendMsgBuf(CAN_ID, 0, 8, data) == CAN_OK) {
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }

  delay(1000);
}