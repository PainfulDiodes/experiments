#define PIN_RST 9
#define PIN_CS 10
#define PIN_MOSI 11
#define PIN_MISO 12
#define PIN_SCK 13  

#define PIN_SCK_INT 2  
#define PIN_CS_INT 3  

volatile unsigned int cache[8] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
// volatile unsigned int cache2[8] = {HIGH,LOW,HIGH,HIGH,HIGH,LOW,LOW,HIGH};
volatile unsigned int bitCount;
bool rst,cs,mosi,miso,sck,old_sck;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RST, INPUT);
  pinMode(PIN_CS, INPUT);
  pinMode(PIN_MOSI, INPUT);
  pinMode(PIN_MISO, OUTPUT);
  pinMode(PIN_SCK, INPUT);

  // attachInterrupt(digitalPinToInterrupt(PIN_SCK_INT), sckFallingInterruptHandler, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_SCK_INT), sckRisingInterruptHandler, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_CS_INT), csFallingInterruptHandler, FALLING);
  //attachInterrupt(digitalPinToInterrupt(PIN_CS_INT), csRisingInterruptHandler, RISING);
}

void loop(){}

void sckRisingInterruptHandler() {
  cache[bitCount]=digitalRead(PIN_MOSI);
  bitCount++;
  digitalWrite(PIN_MISO,cache[bitCount]);
}

// void sckFallingInterruptHandler() {
// }

void csFallingInterruptHandler() { // active low
  bitCount=0;
  digitalWrite(PIN_MISO,cache[bitCount]); // output bit 0
}

// void csRisingInterruptHandler() {
//   Serial.print(cache[0]);
//   Serial.print(cache[1]);
//   Serial.print(cache[2]);
//   Serial.print(cache[3]);
//   Serial.print(cache[4]);
//   Serial.print(cache[5]);
//   Serial.print(cache[6]);
//   Serial.print(cache[7]);
//   Serial.print("\n");
// }
