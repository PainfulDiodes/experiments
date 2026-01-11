#define PIN_CLK 12
#define PIN_RST 13

int clk_state = LOW;


void setup() {
  Serial.begin(9600);

  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);

  digitalWrite(PIN_RST, LOW);
  delay(500);
  digitalWrite(PIN_RST, HIGH);

  Serial.print("clock\n");

}

void loop() {
  clock_pulse();
}

void clock_pulse() {
  // clk_state = HIGH;
  digitalWrite(PIN_CLK, HIGH);
  // delay(1);
  // clk_state = LOW;
  digitalWrite(PIN_CLK, LOW);
  // delay(1);
}
