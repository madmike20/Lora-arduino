#include <SPI.h>
#include <LoRa.h>
const int AOUTpin=0;  //the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int DOUTpin=8;  //the DOUT pin of the CO sensor goes into digital pin D8 of the arduino
const int ledPin=13;  //the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DOUTpin, INPUT);  //sets the pin as an input to the arduino
pinMode(ledPin, OUTPUT);  //sets the pin as an output of the arduino
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  value= analogRead(AOUTpin);  //reads the analaog value from the CO sensor’s AOUT pin
limit= digitalRead(DOUTpin);  //reads the digital value from the CO sensor’s DOUT pin


  Serial.print("Sending packet: ");
  Serial.println(counter);
Serial.print("CO value: ");
Serial.println(value);  //prints the CO value
  // send packet
  LoRa.beginPacket();
  LoRa.print("Message N° ");
  LoRa.print(counter);
    LoRa.print(" : CO value ");
  LoRa.print(value);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
