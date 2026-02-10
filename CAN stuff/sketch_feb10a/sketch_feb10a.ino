#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 10

MCP_CAN CAN(CAN_CS);


void setup() {
  while (1){
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ)) {
      Serial.println("CAN init failed, retrying...");
      delay(100);
    }

    Serial.println("CAN init OK!");
    CAN.setMode(MCP_NORMAL);
  }

}