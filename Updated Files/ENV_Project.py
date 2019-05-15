
#!/usr/bin/python
import serial
import time
import mysql.connector

mydb = mysql.connector.connect(
  host="127.0.0.1",
  user="admin",
  passwd="",
  database = 'envdb')


print(mydb)
mycursor  = mydb.cursor()
#Serial port should be checked after every installation 
ser = serial.Serial('/dev/ttyACM0',9600, timeout = 100);
time.sleep(1)
print "iniciando"

varPh = float
varVol = float
varWl = float
varHum = float
varTemp = float
varUv = float
varTher = float
# sql = 'INSERT INTO data (ph, volt, waterlevel, humidity, temperature, uv,thermistor) VALUES (%s,%s,%s,%s,%s,%s,%s)';
# val = (varPh, varVol, varWl, varHum, varTemp, varUv,varTher)
while True:
    #ph
    ser.write('1');
    varPh = (ser.readline());
    print (varPh);
    time.sleep(2);
    #Volt
    ser.write('2');
    varVol = (ser.readline());
    print (varVol);
    time.sleep(2);
    #water Leel
    ser.write('3');
    varWl = (ser.readline());
    print (varWl);
    time.sleep(2);
    #Hum
    ser.write('4');
    varHum = (ser.readline());
    print (varHum);
    time.sleep(2);
    #Temp
    ser.write('5');
    varTemp = (ser.readline());
    print (varTemp);
    time.sleep(2);
    #UV
    ser.write('6');
    varUv = (ser.readline());
    print (varUv);
    time.sleep(2);
    #thermis
    ser.write('7');
    varTher = (ser.readline());
    print (varTher);
    time.sleep(2);
    mycursor.execute("""INSERT INTO data (ph, volt, waterlevel, humidity, temperature, uv,thermistor) VALUES (%s,%s,%s,%s,%s,%s,%s)""", (varPh, varVol, varWl, varHum, varTemp, varUv,varTher)
);
    mydb.commit();
