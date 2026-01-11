#define PIN_RES 9
#define PIN_CS 10

void setup() {
  Serial.begin(9600);
  pinMode(PIN_CS, INPUT);
  pinMode(PIN_RES, INPUT);
}

void loop() {
  unsigned char cs = digitalRead(PIN_CS);
  unsigned char res = digitalRead(PIN_RES);

  Serial.print("CS: ");
  Serial.print(cs);
  Serial.print(" RES: ");
  Serial.println(res);  
}
