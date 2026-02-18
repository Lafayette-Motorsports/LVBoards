#include <SPI.h>
#include <mcp_can.h>

// For Elegoo MCP2515 CAN module
#define CAN_CS 10            // Chip Select pin (connect to MCP2515 CS)
#define CAN_SPEED CAN_500KBPS
#define CAN_CRYSTAL MCP_8MHZ  // Elegoo uses 8 MHz crystal

MCP_CAN CAN(CAN_CS);         // Create CAN object

// Set to true for internal loopback test (no other CAN device required)
bool testLoopback = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // SPI setup
  pinMode(CAN_CS, OUTPUT);
  digitalWrite(CAN_CS, HIGH); // Deselect MCP2515
  SPI.begin();
  Serial.println("SPI initialized successfully");

  // Initialize CAN
  if (CAN.begin(MCP_ANY, CAN_SPEED, CAN_CRYSTAL) == CAN_OK) {
    Serial.println("CAN BUS Shield initialized successfully!");
  } else {
    Serial.println("CAN BUS Shield initialization failed!");
    while (1); // Halt
  }

  // Set CAN mode
  if (testLoopback) {
    CAN.setMode(MCP_LOOPBACK);  // Internal test mode
    Serial.println("CAN mode: LOOPBACK (internal test)");
  } else {
    CAN.setMode(MCP_NORMAL);    // Normal CAN bus mode (use CANH/CANL)
    Serial.println("CAN mode: NORMAL (external bus communication)");
    Serial.println("Ensure a 120Ω termination resistor is across CANH and CANL if only two nodes.");
  }

  Serial.println("Starting CAN communication...");
}

void loop() {
  // ---------------------------
  // 1. Send a message
  // ---------------------------
  byte sendData[8] = {0,1,2,3,4,5,6,7}; // Example data

  if (CAN.sendMsgBuf(0x100, 0, 8, sendData) == CAN_OK) {
    Serial.print("Sent: ");
    for (int i=0; i<8; i++) {
      if (sendData[i]<0x10) Serial.print("0"); // Leading zero
      Serial.print(sendData[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("Error sending message");
  }

  // ---------------------------
  // 2. Check for received messages
  // ---------------------------
  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    unsigned long rxId;
    byte len = 0;
    byte rxBuf[8];

    CAN.readMsgBuf(&rxId, &len, rxBuf);

    Serial.print("Received ID: 0x");
    if (rxId < 0x100) Serial.print("0");
    Serial.print(rxId, HEX);
    Serial.print(" Data: ");
    for (int i=0; i<len; i++) {
      if (rxBuf[i] < 0x10) Serial.print("0");
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("No message received");
  }

  delay(500); // Avoid flooding Serial monitor
}
