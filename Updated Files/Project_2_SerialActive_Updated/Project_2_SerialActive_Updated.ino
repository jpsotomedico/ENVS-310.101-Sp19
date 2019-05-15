// Juan Pablo Soto
//University of Baltimore

//************************water sensor
const int read = A1; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data
//end water sensor**********************************
//UV Sensor***********************************
#include <Wire.h>
#include <Adafruit_SI1145.h>
Adafruit_SI1145 uv = Adafruit_SI1145();
//end UV Sensor****************
//DHT Sensor****************************
#include <DHT.h>
//Constants
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
//Variables*************
float outputVis; //a
float outputIr;//a
float outputUv; //a
float outputHum;//b
float outputTemp;//b
float outputVolgate;//c
float outputPh;//d
float outputWaterLevel;//

float ouputThermistor;//e

//NeoPixel********************************
 #include <FastLED.h>
 #define NUM_LEDS 60
 #define DATA_PIN 6
  CRGB leds[NUM_LEDS];
 //End Neopixl***********************************
 //thermistor**********************************
 #define THERMISTORPIN A2 
 #define SERIESRESISTOR 10000   

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
void setup()
{
    Serial.begin(9600);

  //UV*****************************************
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
// Serial.println("OK!");
  //end UV********************************************
   //DHT*************************************
    dht.begin();
   //DHTEND************************************ 
//**********************NeoPixl
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
//************************endNeoPixl

  
  //****************************water sensor
  //Begin serial communication
 // end weater sensor *********************
 //**********************************ph meter 
pinMode(LED,OUTPUT);  
  //Serial.println("pH meter experiment!");    //Test the serial monitor
 //end ph meter*******************************
 
}

void loop()
{
   
//UV**********************************************
 // Serial.println("===================");
 //  Serial.println(myThermistor());
   ouputThermistor = myThermistor();
  //  Serial.print("Vis: "); Serial.println(uv.readVisible());
  outputVis = (uv.readVisible());
 // Serial.print("IR: "); Serial.println(uv.readIR());
  outputIr = (uv.readIR());
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());

  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
 // Serial.print("UV: ");  Serial.println(UVindex);
  outputUv = (UVindex);
  
//end UV*****************************************************
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
   ///loop to load LED
    for (int x = 0; x<24;x = x+2){
      leds[x]= CRGB::Blue;
       };
       for (int z = 1; z<24;z = z+2){
      leds[z]= CRGB::Red;
       };
      
   
        FastLED.show(); 
 //       delay(30); 
  //Water sensor*****************************************
  value = analogRead(read); //Read data from analog pin and store it to value variable
 // myWaterSensor(value);
  outputWaterLevel = value;

//end Water Sensor*********************************
  
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

   // read the sensor:

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
    }
}//end of loop 
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

/*
void myWaterSensor(int value){

if (value<=480){ 
    Serial.println("Water level: 0mm - Empty!"); 
  }
  else if (value>480 && value<=530){ 
    Serial.println("Water level: 0mm to 5mm"); 
  }
  else if (value>530 && value<=615){ 
    Serial.println("Water level: 5mm to 10mm"); 
  }
  else if (value>615 && value<=660){ 
    Serial.println("Water level: 10mm to 15mm"); 
  } 
  else if (value>660 && value<=680){ 
    Serial.println("Water level: 15mm to 20mm"); 
  }
  else if (value>680 && value<=690){ 
    Serial.println("Water level: 20mm to 25mm"); 
  }
  else if (value>690 && value<=700){ 
    Serial.println("Water level: 25mm to 30mm"); 
  }
  else if (value>700 && value<=705){ 
    Serial.println("Water level: 30mm to 35mm"); 
  }
  else if (value>705){ 
    Serial.println("Water level: 35mm to 40mm"); 
  }
  
  
  }
  */
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
 
  
