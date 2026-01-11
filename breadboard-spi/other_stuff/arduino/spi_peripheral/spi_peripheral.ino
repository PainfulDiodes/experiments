#define PIN_RST 9
#define PIN_CS 10
#define PIN_MOSI 11
#define PIN_MISO 12
#define PIN_SCK 13

int rst,cs,mosi,miso,sck,old_rst,old_sck,old_cs;

void setup() {
  Serial.begin(9600);
  Serial.print("SPI sniffer\n");

  pinMode(PIN_RST, INPUT);
  pinMode(PIN_CS, INPUT);
  pinMode(PIN_MOSI, INPUT);
  pinMode(PIN_MISO, INPUT);
  pinMode(PIN_SCK, INPUT);

  readpins();
  old_sck=sck;
  old_rst=rst;
  old_cs=cs;
}

void loop() {
    readpins();
    if(old_sck!=sck || old_rst!=rst || old_cs!=cs) {
      old_sck=sck;
      old_rst=rst;
      old_cs=cs;
      printpins();
    }
}

void readpins() {
  rst = digitalRead(PIN_RST);
  cs = digitalRead(PIN_CS);
  mosi = digitalRead(PIN_MOSI);
  miso = digitalRead(PIN_MISO);
  sck = digitalRead(PIN_SCK);
}

void printpins() {
  Serial.print(rst);
  Serial.print(" ");
  Serial.print(cs);
  Serial.print(" ");
  Serial.print(mosi);
  Serial.print(" ");
  Serial.print(miso);
  Serial.print(" ");
  Serial.print(sck);
  Serial.print("\n");
}
