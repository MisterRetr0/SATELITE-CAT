// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

//SENSOR DE SONIDO DELANTE
const int trigPinDel = 5;
const int echoPinDel = 18;

//SENSOR DE SONIDO DERECHA
const int trigPinDer = 33;
const int echoPinDer = 32;

//SENSOR DE SONIDO ATRAS
const int trigPinAtr = 25;
const int echoPinAtr = 26;

//SENSOR DE SONIDO IZQUIERDA
const int trigPinIzq = 4;
const int echoPinIzq = 2;

// Definir los pines LEDS
const int ledDel = 12;
const int ledDer = 14;
const int ledAtr = 23;
const int ledIzq = 13;

const float rango = 12;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long durationDel, durationDer, durationAtr, durationIzq;
float cmDel, cmDer, cmAtr, cmIzq;

void setup(void) {
  Serial.begin(115200);

  //SENSOR ULTRASONICO
    
    //SENSOR DE SONIDO DELANTE
  pinMode(trigPinDel, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinDel, INPUT); // Sets the echoPin as an Input

   //SENSOR DE SONIDO DERECHA
  pinMode(trigPinDer, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinDer, INPUT); // Sets the echoPin as an Input

 //SENSOR DE SONIDO ATRAS
  pinMode(trigPinAtr, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinAtr, INPUT); // Sets the echoPin as an Input


 //SENSOR DE SONIDO IZQUIERDA
  pinMode(trigPinIzq, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinIzq, INPUT); // Sets the echoPin as an Input


//LEDS LADOS
  pinMode(ledDel, OUTPUT);
  pinMode(ledDer, OUTPUT);
  pinMode(ledAtr, OUTPUT);
  pinMode(ledIzq, OUTPUT);


  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(1000);
}

void loop() {
  /* Get new sensor events with the readings */
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.println("-----------DATOS DEL SATELITE (Cada segundo)-----------");

  Serial.println("-----------GIROSCOPIO-----------");
  /* Print out the values */
  Serial.print("Aceleracion X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotacion X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperatura: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
//-----------------------FIN GIROSCOPIO


  Serial.println("-----------SENSOR ULTRASONICO-----------");
  
//SENSOR US DELANTE

  digitalWrite(trigPinDel, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinDel, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDel, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationDel = pulseIn(echoPinDel, HIGH);
  
  // Calculate the distance
  cmDel = durationDel * SOUND_SPEED/2;
  
  if(cmDel <= rango){
    digitalWrite(ledDel, HIGH);
  }else{
    digitalWrite(ledDel, LOW);
  }
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distancia Delante: ");
  Serial.println((String) cmDel + "cm");

//SENSOR US DERECHA
  digitalWrite(trigPinDer, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinDer, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDer, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationDer = pulseIn(echoPinDer, HIGH);
  
  // Calculate the distance
  cmDer = durationDer * SOUND_SPEED/2;
  
  
  if(cmDer <= rango){
    digitalWrite(ledDer, HIGH);
  }else{
    digitalWrite(ledDer, LOW);
  }
  

  // Prints the distance in the Serial Monitor
  Serial.print("Distancia Derecha: ");
  Serial.println((String) cmDer + "cm");

//SENSOR US ATRAS
  
  digitalWrite(trigPinAtr, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinAtr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinAtr, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationAtr = pulseIn(echoPinAtr, HIGH);
  
  // Calculate the distance
  cmAtr = durationAtr * SOUND_SPEED/2;
 
  if(cmAtr <= rango){
    digitalWrite(ledAtr, HIGH);
  }else{
    digitalWrite(ledAtr, LOW);
  }
  

  // Prints the distance in the Serial Monitor
  Serial.print("Distancia Atras: ");
  Serial.println((String) cmAtr + "cm");

//SENSOR US IZQUIERDA
  
  digitalWrite(trigPinIzq, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinIzq, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinIzq, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationIzq = pulseIn(echoPinIzq, HIGH);
  
  // Calculate the distance
  cmIzq = durationIzq * SOUND_SPEED/2;

  
  if(cmIzq <= rango){
    digitalWrite(ledIzq, HIGH);
  }else{
    digitalWrite(ledIzq, LOW);
  }
  
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distancia Izquierda: ");
  Serial.println((String) cmIzq + "cm");
  Serial.println("-----------FIN DE DATOS segundo-----------");

  delay(1000);
}