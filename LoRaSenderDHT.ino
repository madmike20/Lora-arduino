#include <SPI.h>
#include <LoRa.h>
// Basé sur le code de LadyAda traduit et modifie par moi, domaine public
#include "DHT.h"
#define DHTPIN 8 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
 
int counter = 0;

void setup() {
  Serial.println("DHTxx test!");
 dht.begin();
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // La lecture du capteur prend 250ms
 // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 // pour lire en farenheit, il faut le paramère (isFahrenheit = true) :
 float f = dht.readTemperature(true);
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
  Serial.print("Sending packet: ");
  Serial.println(counter);
Serial.println("TEmperature :" );
Serial.println(t);
Serial.println("humidiy :" );
Serial.println(h );
  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
   LoRa.print("Temperature ");
  LoRa.print(t);
   LoRa.print("Humidity ");
  LoRa.print(h);
  
  LoRa.endPacket();

  counter++;

  delay(5000);
}
