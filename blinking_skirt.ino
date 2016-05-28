/* Code taken from https://learn.adafruit.com/sparkle-skirt/code and then modified a little to suit my purpose*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>

// #define DEBUG_ON

Adafruit_LSM303 lsm;
int led1 = 9;
int led2 = 6;

// mess with this number to adjust TWINklitude :)
// lower number = more sensitive
#define MOVE_THRESHOLD 45

void setup() 
{
  #ifdef DEBUG_ON
  Serial.begin(9600);
  Serial.println("Started serial monitor");
  #endif
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    #ifdef DEBUG_ON
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    #endif
    while (1);
  }
}

void loop() 
{
  #ifdef DEBUG_ON
  Serial.println("Reading lsm");
  #endif
  lsm.read();
  #ifdef DEBUG_ON
  Serial.print("Accel X: "); Serial.print((int)lsm.accelData.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)lsm.accelData.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)lsm.accelData.z);     Serial.print(" ");
  #endif

  double storedVector = lsm.accelData.x*lsm.accelData.x;
  storedVector += lsm.accelData.y*lsm.accelData.y;
  storedVector += lsm.accelData.z*lsm.accelData.z;
  storedVector = sqrt(storedVector);

  #ifdef DEBUG_ON
  Serial.print("Len: ");
  Serial.println(storedVector);
  Serial.println("Wait a bit");
  #endif

  // wait a bit
  delay(1000);
 
 // get new data!
  #ifdef DEBUG_ON
  Serial.println("Reading lsm");
  #endif
  lsm.read();
  double newVector = lsm.accelData.x*lsm.accelData.x;
  newVector += lsm.accelData.y*lsm.accelData.y;
  newVector += lsm.accelData.z*lsm.accelData.z;
  newVector = sqrt(newVector);
  #ifdef DEBUG_ON
  Serial.print("New Len: ");
  Serial.println(newVector);
  #endif
  
  // are we moving 
  if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
    #ifdef DEBUG_ON
    Serial.println("Twinkle!");
    #endif

    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(500);
  } else {
    #ifdef DEBUG_ON
    Serial.println("No Twinkling");
    #endif
    delay(1000);
  }
}
