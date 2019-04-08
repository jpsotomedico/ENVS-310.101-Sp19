
 #include <FastLED.h>
 #define NUM_LEDS 60
 #define DATA_PIN 6
 #include <Wire.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();
  CRGB leds[NUM_LEDS];
  //************************water sensor
const int read = A1; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data
//end water sensor**********************************
//************************ph meter
#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;  
//end ph meter*********************************
//DHT Sensor****************************
#include <DHT.h>
//Constants
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
 //thermistor**********************************
 #define THERMISTORPIN A2 
 #define SERIESRESISTOR 10000   
//Variables*************

float outputUv; //a
float outputHum;//b
float outputTemp;//b
float outputVolgate;//c
float outputPh;//d
float outputWaterLevel;//
float ouputThermistor;//e
 
  
  void setup() {
      Serial.begin(9600);

  // put your setup code here, to run once:
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
//UV
   //DHT*************************************
    dht.begin();
   //DHTEND************************************ 
 if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
 
}
void loop() {
  // put your main code here, to run repeatedly:
  LEDLights();
  outputWaterLevel = waterLevel();
  outputUv = uvRead();
  ouputThermistor = myThermistor();
  loopingOutput();
//pH SENSOR************************************
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
              outputVolgate = (voltage);
                    outputPh = (pHValue);


  }
  //DHT************************************
  //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    outputHum = hum;
    temp= dht.readTemperature();
    outputTemp =temp;
    
    //Print temp and humidity values to serial monitor
  //  Serial.print("Humidity: ");
  //  Serial.print(hum);
  //    Serial.print(" %, Temp: ");
  //  Serial.print(temp);
  //  Serial.println(" Celsius");


   
 //endDHT****************************** 
  
    loopingOutput();

}
float myThermistor(){
    float reading;
 
  reading = analogRead(THERMISTORPIN);
 
 // Serial.print("Analog reading "); 
 // Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = SERIESRESISTOR / reading;  // 10K / (1023/ADC - 1)
 // Serial.print("Thermistor resistance "); 
 // Serial.println(reading);
  return reading;
  

  
  }



float uvRead(){
   float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  return UVindex;
  
  }

void LEDLights(){
    for (int x = 0; x<24;x = x+2){
      leds[x]= CRGB::Blue;
       };
       for (int z = 1; z<24;z = z+2){
      leds[z]= CRGB::Red;
       };
      
   
        FastLED.show(); 
        delay(30);
  }
float waterLevel(){
  value = analogRead(read); //Read data from analog pin and store it to value variable

  return value;
  }

void  loopingOutput(){
    if (Serial.available() > 0) {
    int inByte = Serial.read();
    
    switch (inByte) {
      case '1':
         // Serial.println("Ph");
            Serial.println(outputPh);
            Serial.flush();
        break;
             case '2':
   //   Serial.println("Volt");
      Serial.println(outputVolgate);
            Serial.flush();

        break;
      case '3':
      //Serial.println("Water Level");
      Serial.println(outputWaterLevel);
      Serial.flush();

      
        break;
      case '4':
    //  Serial.println("Hum");
      Serial.println(outputHum);
            Serial.flush();

      
        break;
      case '5':
     //  Serial.println("Temp");
      Serial.println(outputTemp);
            Serial.flush();

     
        break;
 
      case '6':
    //  Serial.println("UV");
      Serial.println(outputUv);
            Serial.flush();

     
        break;
       case '7':
     //   Serial.println("Thermis");
        Serial.println(ouputThermistor);
              Serial.flush();
        break;

 
      default:
  
        break;
        }
    };
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  
 }//if
  return avg;
 }// END of average array 
    
    
   
