// test behaviour of single PISO shift register

/*
| Net      | 74LS165    | Nano              | Nano I/O |
|----------|------------|-------------------|----------|
| /LD      | 1 SH /LD   | D14 / A0          | Output   |
| CLK      | 2 CLK      | D15 / A1          | Output   |
| D4       | 3 E        | D16 / A2          | Output   |
| D5       | 4 F        | D17 / A3          | Output   |
| D6       | 5 G        | D18 / A4          | Output   |
| D7       | 6 H        | D19 / A5          | Output   |
| /SER_OUT | 7 /QH      | D4                | Input    |
| GND      | 8 GND      | GND               |          |
| SER_OUT  | 9 QH       | D5                | Input    |
| DATA_SER | 10 SER     | D6                | Output   |
| D0       | 11 A       | D7                | Output   |
| D1       | 12 B       | D8                | Output   |
| D2       | 13 C       | D9                | Output   |
| D3       | 14 D       | D10               | Output   |
| CLK_INH  | 15 CLK_INH | D11 / COPI / MOSI | Output   |
| +5V      | 16 VCC     | +5v               |          |
 */

#define PIN_SH_LD 14
#define PIN_CLK 15
#define PIN_E 16
#define PIN_F 17
#define PIN_G 18
#define PIN_H 19
#define PIN_QH_ 4
#define PIN_QH 5
#define PIN_SER 6
#define PIN_A 7
#define PIN_B 8
#define PIN_C 9
#define PIN_D 10
#define PIN_CLK_INH 11

#define DELAY_TIME 1

void setup() {
  Serial.begin(9600);
  Serial.print("setup\n");
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PIN_SH_LD, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_H, OUTPUT);
  pinMode(PIN_QH_, INPUT);
  pinMode(PIN_QH, INPUT);
  pinMode(PIN_SER, OUTPUT);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_CLK_INH, OUTPUT);

  Serial.print("init\n");

  digitalWrite(PIN_SH_LD, HIGH); 
  digitalWrite(PIN_CLK_INH, LOW); 

  Serial.print("set data bus\n");

  digitalWrite(PIN_A, HIGH); 
  digitalWrite(PIN_B, HIGH); 
  digitalWrite(PIN_C, HIGH); 
  digitalWrite(PIN_D, HIGH); 
  digitalWrite(PIN_E, HIGH); 
  digitalWrite(PIN_F, HIGH); 
  digitalWrite(PIN_G, HIGH); 
  digitalWrite(PIN_H, HIGH);   
  digitalWrite(PIN_SER, LOW); 
  
  Serial.print("write\n");

  digitalWrite(PIN_CLK_INH, HIGH); 
  do_clock_pulse();
  digitalWrite(PIN_SH_LD,LOW);
  do_clock_pulse();
  do_clock_pulse();
  do_clock_pulse();
  digitalWrite(PIN_SH_LD,HIGH);
  do_clock_pulse();
  digitalWrite(PIN_CLK_INH, LOW); 

  Serial.print("done with write\n");

  for (int x = 0; x < 16; x++) {
    log_inputs();
    do_clock_pulse();
  }
  Serial.print("end setup\n");

}

void loop() {
  // do_pulse(PIN_CLK, 4000);
}

void do_clock_pulse() {
  do_pulse(PIN_CLK, DELAY_TIME);
}

void do_pulse(int pin, int time) {
  digitalWrite(pin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);                     
  digitalWrite(pin, LOW); 
  digitalWrite(LED_BUILTIN, LOW); 
  delay(time);                     
}

void log_inputs() {
  Serial.print(digitalRead(PIN_QH));
  Serial.print(digitalRead(PIN_QH_));
  Serial.print("\n");
}
