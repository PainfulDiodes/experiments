// RA8875 - wire - Uno  
// VIN - brown - +5v  
// GND - orange - GND  
// SCK - yellow - 13  
// MISO - green - 12  
// MOSI - blue - 11  
// CS - purple - 10  
// RST - grey - 9  


#define PIN_RST 9
#define PIN_CS 10
#define PIN_MOSI 11
#define PIN_MISO 12
#define PIN_SCK 13  

#define PIN_SCK_INT 2  
#define PIN_CS_INT 3  


void setup() {
  Serial.begin(9600);
  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_MISO, INPUT);
  pinMode(PIN_SCK, OUTPUT);

  digitalWrite(PIN_RST, LOW);
  delay(500);
  digitalWrite(PIN_RST, HIGH);

  Serial.println("----");

}

void loop(){
  selectSPI(true);
  char response1 = transferSPI(0x80);
  char response2 = transferSPI(0x00);
  selectSPI(false);

  delay(1000);

  selectSPI(true);
  char response3 = transferSPI(0x40);
  char response4 = transferSPI(0x00);
  selectSPI(false);

  Serial.print("0x");
  Serial.print((unsigned char)response1, HEX);
  Serial.print(" 0x");
  Serial.print((unsigned char)response2, HEX);
  Serial.print(" 0x");
  Serial.print((unsigned char)response3, HEX);
  Serial.print(" 0x");
  Serial.println((unsigned char)response4, HEX);

  delay(1000);
}


void selectSPI(bool sel) {
  digitalWrite(PIN_CS, sel ? LOW : HIGH);
}

char transferSPI(char data) {
  char received = 0;
  for (int i = 7; i >= 0; i--) {
    // Set MOSI according to the current bit
    digitalWrite(PIN_MOSI, (data >> i) & 0x01);

    // Pulse SCK HIGH
    digitalWrite(PIN_SCK, HIGH);

    // Read MISO and set the corresponding bit in received
    received <<= 1;
    if (digitalRead(PIN_MISO)) {
      received |= 0x01;
    }

    // Pulse SCK LOW
    digitalWrite(PIN_SCK, LOW);
  }
  return received;
}
