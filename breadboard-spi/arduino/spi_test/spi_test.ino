// test SPI

#define PIN_DO0 2
#define PIN_DO1 3
#define PIN_DO2 4
#define PIN_DO3 5
#define PIN_DO4 6
#define PIN_DO5 7
#define PIN_DO6 8
#define PIN_DO7 9
#define PIN_LD_ 10
#define PIN_SER_OUT 11
#define PIN_CS 12
#define PIN_CLK 13
#define PIN_DI0 14
#define PIN_DI1 15
#define PIN_DI2 16
#define PIN_DI3 17
#define PIN_DI4 18
#define PIN_DI5 19
#define PIN_DI6 20
#define PIN_DI7 21

int ld_state = HIGH;
int clk_state = LOW;

void setup() {
  Serial.begin(9600);

  log_header();

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PIN_DO0, OUTPUT);
  pinMode(PIN_DO1, OUTPUT);
  pinMode(PIN_DO2, OUTPUT);
  pinMode(PIN_DO3, OUTPUT);
  pinMode(PIN_DO4, OUTPUT);
  pinMode(PIN_DO5, OUTPUT);
  pinMode(PIN_DO6, OUTPUT);
  pinMode(PIN_DO7, OUTPUT);
  pinMode(PIN_LD_, OUTPUT);
  pinMode(PIN_SER_OUT, INPUT);
  pinMode(PIN_CS, INPUT);
  pinMode(PIN_DI0, INPUT);
  pinMode(PIN_DI1, INPUT);
  pinMode(PIN_DI2, INPUT);
  pinMode(PIN_DI3, INPUT);
  pinMode(PIN_DI4, INPUT);
  pinMode(PIN_DI5, INPUT);
  pinMode(PIN_DI6, INPUT);
  pinMode(PIN_DI7, INPUT);  

  // initial states
  ld_state = HIGH;
  clk_state = LOW;

  digitalWrite(PIN_CLK, clk_state); 
  digitalWrite(PIN_LD_, ld_state); 

  clock_pulse();

  digitalWrite(PIN_DO0, HIGH); 
  digitalWrite(PIN_DO1, HIGH); 
  digitalWrite(PIN_DO2, LOW); 
  digitalWrite(PIN_DO3, HIGH); 
  digitalWrite(PIN_DO4, HIGH); 
  digitalWrite(PIN_DO5, LOW); 
  digitalWrite(PIN_DO6, HIGH); 
  digitalWrite(PIN_DO7, HIGH);   

  clock_pulse();

  ld_state = LOW;
  digitalWrite(PIN_LD_,ld_state);

  log_inputs();
  
  clock_pulse();

  ld_state = HIGH;
  digitalWrite(PIN_LD_,ld_state);

  log_inputs();

  for (int x = 0; x < 16; x++) {
    clock_pulse();
  }
  Serial.print("end\n");

}

void loop() {
}

void clock_pulse() {
  clk_state = HIGH;
  digitalWrite(PIN_CLK, clk_state);
  log_inputs();
  clk_state = LOW;
  digitalWrite(PIN_CLK, clk_state);
  log_inputs();
}

void log_inputs() {
  Serial.print(ld_state);
  Serial.print("\t");
  Serial.print(clk_state);
  Serial.print("\t");
  Serial.print(digitalRead(PIN_SER_OUT));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_CS));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI0));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI1));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI2));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI3));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI4));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI5));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI6));
  Serial.print("\t");
  Serial.print(digitalRead(PIN_DI7));
  Serial.print("\n");
}

void log_header() {
  Serial.print("/LD");
  Serial.print("\t");
  Serial.print("CLK");
  Serial.print("\t");
  Serial.print("SER");
  Serial.print("\t");
  Serial.print("CS");
  Serial.print("\t");
  Serial.print("DI0");
  Serial.print("\t");
  Serial.print("DI1");
  Serial.print("\t");
  Serial.print("DI2");
  Serial.print("\t");
  Serial.print("DI3");
  Serial.print("\t");
  Serial.print("DI4");
  Serial.print("\t");
  Serial.print("DI5");
  Serial.print("\t");
  Serial.print("DI6");
  Serial.print("\t");
  Serial.print("DI7");
  Serial.print("\n");
}
