#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;
int led1 = 9;
int led2 = 6;

// mess with this number to adjust TWINklitude :)
// lower number = more sensitive
#define MOVE_THRESHOLD 45

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started serial monitor");
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  Serial.println("Reading lsm");
  lsm.read();
  Serial.print("Accel X: "); Serial.print((int)lsm.accelData.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)lsm.accelData.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)lsm.accelData.z);     Serial.print(" ");

  double storedVector = lsm.accelData.x*lsm.accelData.x;
  storedVector += lsm.accelData.y*lsm.accelData.y;
  storedVector += lsm.accelData.z*lsm.accelData.z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: ");
  Serial.println(storedVector);
  Serial.println("Wait a bit");
  // wait a bit
  delay(100);
 
 // get new data!
  Serial.println("Reading lsm");
  lsm.read();
  double newVector = lsm.accelData.x*lsm.accelData.x;
  newVector += lsm.accelData.y*lsm.accelData.y;
  newVector += lsm.accelData.z*lsm.accelData.z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);
  
  // are we moving 
  if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
    Serial.println("Twinkle!");
//    digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
//    digitalWrite(led2, HIGH);
    for (int i = 0; i <= 64; i++) {
    analogWrite(led1, i);
    analogWrite(led2, i);
    delay(10);
    }
    delay(100);
//    digitalWrite(led1, LOW);   // turn the LED off (LOW is the voltage level)
//    digitalWrite(led2, LOW);
    for (int i = 64; i >= 0; i--) {
    analogWrite(led1, i);
    analogWrite(led2, i);
    delay(10);
    }
  } else {
    Serial.println("No Twinkling");
  }
}
