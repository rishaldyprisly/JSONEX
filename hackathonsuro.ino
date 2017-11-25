
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
//Token ID
char auth[] = "54786c6635394d289871dd40db2b5c8e";

// WiFi credentials.
// Gunakan "" Jika WiFi tidak memiliki password (Open Network).
char ssid[] = "Hackathon 2";
char pass[] = "dilohackathon123";

#define DHTPIN 4   
#define DHTTYPE DHT11  

#define trigPin 25
#define echoPin 26

#define trigPin2 14
#define echoPin2 15

#define trigPin3 18
#define echoPin3 19

#define trigPin4 22
#define echoPin4 23

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;
void setup() {
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  timer.setInterval(2000L, count);
  timer.setInterval(2000L, measuretemp);

}

void count() {
long duration, distance, a1, a2, a3, a4, total, terisi;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  long duration2, distance2;
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  
  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3/2) / 29.1;
  
  long duration4, distance4;
  digitalWrite(trigPin4, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = (duration4/2) / 29.1;

  if (distance < 20)
  { 
    a1 = 1;
  }
  if (distance > 20)
  {
    a1 = 0;
  }

  if (distance2 < 20){
    a2 = 1;
  } 

  if (distance2 > 20){
    a2 = 0;
  }
  if (distance3 < 20){
    a3 = 1;
  } 

  if (distance3 > 20){
    a3 = 0;
  }
   if (distance4 < 20){
    a4 = 1;
  } 

  if (distance4 > 20){
    a4 = 0;
  }


  terisi = a1+a2+a3+a4;
  int kapasitas = 100;
  total = kapasitas - terisi;
  Blynk.virtualWrite(V1, terisi);
  Blynk.virtualWrite(V2, total);
  
 // Serial.print("A1 = "); Serial.print(distance);  Serial.print("   A2 = ");  Serial.print(distance2);  Serial.print("  A3 = "); Serial.print(distance3);  Serial.print("   A4 = ");  Serial.println(distance4);
 // Serial.print("A1 = "); Serial.print(a1);  Serial.print("   A2 = ");Serial.print(a2); Serial.print("   A3 = ");Serial.print(a3); Serial.print("   A4 = ");Serial.print(a4);Serial.print("  Total terisi = ");Serial.print(terisi); Serial.print("  kapasitas = "); Serial.println(total); 
delay(1000);
  
}


void measuretemp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V4, t);
}
void loop () {
  Blynk.run();
  timer.run();
}
