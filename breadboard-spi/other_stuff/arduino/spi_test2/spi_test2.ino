// test SPI

#define PIN_DO0 2
#define PIN_DO1 3
#define PIN_DO2 4
#define PIN_DO3 5
#define PIN_DO4 6
#define PIN_DO5 7
#define PIN_DO6 8
#define PIN_DO7 9
#define PIN_LD 10
#define PIN_CS 11
#define PIN_CLK 12
#define PIN_RES 13
#define PIN_DI0 14
#define PIN_DI1 15
#define PIN_DI2 16
#define PIN_DI3 17
#define PIN_DI4 18
#define PIN_DI5 19
#define PIN_DI6 20
#define PIN_DI7 21

const uint8_t DO_PINS[8] = {
  PIN_DO0, PIN_DO1, PIN_DO2, PIN_DO3,
  PIN_DO4, PIN_DO5, PIN_DO6, PIN_DO7
};

const uint8_t DI_PINS[8] = {
  PIN_DI0, PIN_DI1, PIN_DI2, PIN_DI3,
  PIN_DI4, PIN_DI5, PIN_DI6, PIN_DI7
};


void setup() {
  Serial.begin(9600);

  pinMode(PIN_DO0, OUTPUT);
  pinMode(PIN_DO1, OUTPUT);
  pinMode(PIN_DO2, OUTPUT);
  pinMode(PIN_DO3, OUTPUT);
  pinMode(PIN_DO4, OUTPUT);
  pinMode(PIN_DO5, OUTPUT);
  pinMode(PIN_DO6, OUTPUT);
  pinMode(PIN_DO7, OUTPUT);
  pinMode(PIN_LD, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_DI0, INPUT);
  pinMode(PIN_DI1, INPUT);
  pinMode(PIN_DI2, INPUT);
  pinMode(PIN_DI3, INPUT);
  pinMode(PIN_DI4, INPUT);
  pinMode(PIN_DI5, INPUT);
  pinMode(PIN_DI6, INPUT);
  pinMode(PIN_DI7, INPUT);  

  digitalWrite(PIN_CLK, LOW); 
  digitalWrite(PIN_LD, HIGH);
  digitalWrite(PIN_CS, HIGH); 

  dataOut(0);
}

void loop() {
  for(unsigned char v=0; v<256; v++) {
    dataOut(v);
    digitalWrite(PIN_LD, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_LD, HIGH);
    for(int i=0; i<8; i++) clockPulse();
    unsigned char inVal = dataIn();
    Serial.print("Out: 0x");
    Serial.print(v, HEX);
    Serial.print(" In: 0x");
    Serial.println(inVal, HEX);
    delay(1000);
  }
}

void dataOut(unsigned char value) {
  for (uint8_t i = 0; i < 8; ++i) {
    digitalWrite(DO_PINS[i], (value >> i) & 0x01 ? HIGH : LOW);
  }
}

unsigned char dataIn() {
  unsigned char value = 0;
  for (uint8_t i = 0; i < 8; ++i) {
    if (digitalRead(DI_PINS[i]) == HIGH) {
      value |= (1 << i);
    }
  }
  return value;
}

void clockPulse() {
  digitalWrite(PIN_CLK, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_CLK, LOW);
  delayMicroseconds(10);
}