#define MQ2pin (0)
#define sensorPower 7
#define sensorPin A1


float Gassensor;  //variable to store sensor value
const int analoglnPin=A2;
int buf[10],temp;
unsigned long int avgValue;
float phValue=0;

void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-2 to warm up

  pinMode(sensorPower, OUTPUT);
  
  // Initially keep the sensor OFF
  digitalWrite(sensorPower, LOW);
}

void loop()
{
  PH();
  Gassensor = analogRead(MQ2pin); // read analog input pin 0
  
  Serial.print("Gas sensor: ");
  Serial.print(Gassensor);
  //get the reading from the function below and print it
  Serial.print("Soil moisture: ");
  Serial.println(readSensor());
  
  delay(1000);
  
  if(Gassensor > 300)
  {
    Serial.print(" | Smoke detected!");
  }
  
  Serial.println("");
  delay(2000); // wait 2s for next reading
}

//  This function returns the analog soil moisture measurement
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return analog moisture value
}

void PH(){
for(int i=0; i<10; i++)  
{
buf[i]=analogRead(analoglnPin);    
delay(10);    
}
for(int i=0; i<9; i++)
{
for(int j=i+1; j<10; j++)
{
if(buf[i]>buf[j])
{
temp=buf[i];
buf[i]=buf[j];
buf[j]=temp;  
}
}
}
avgValue=0;
for(int i=2;i<8;i++)
avgValue+=buf[i];
float pHVol=(float)avgValue*5.0/1024/6;
phValue=-5.70*pHVol+21.34;


Serial.print("pH value:");
Serial.println(phValue);

delay(20);
}

