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

#define RA8875_DATAWRITE 0x00 
#define RA8875_DATAREAD  0x40
#define RA8875_CMDWRITE  0x80
#define RA8875_CMDREAD   0xC0

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

  digitalWrite(PIN_CS, HIGH);
}

void loop(){
  readAllRegisters();  
  Serial.println();
  delay(1000);
}

void readAllRegisters() {
  unsigned char cache[256];
  for(int i = 0; i < 256; i++) {
    cache[i] = readReg(i);
  }

  for(int i = 0; i < 256; i++) {
    Serial.print(cache[i], HEX);
    Serial.print(" ");
  }
}

unsigned char readReg(int reg) {
  digitalWrite(PIN_CS, LOW);

  transferSPI(RA8875_CMDWRITE); 

  // digitalWrite(PIN_CS, HIGH);
  // delayMicroseconds(20);
  // digitalWrite(PIN_CS, LOW);

  transferSPI(reg);

  digitalWrite(PIN_CS, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_CS, LOW);

  transferSPI(RA8875_DATAREAD);

  // digitalWrite(PIN_CS, HIGH);
  // delayMicroseconds(20);
  // digitalWrite(PIN_CS, LOW);

  char value = transferSPI(0x00);

  digitalWrite(PIN_CS, HIGH);
  return value;
}

unsigned char writeReg(int reg, int val) {
  transferSPI(RA8875_CMDWRITE);
  transferSPI(reg);
  transferSPI(RA8875_DATAWRITE);
  char value = transferSPI(0x00);
  return value;
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
