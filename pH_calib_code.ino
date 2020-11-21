


// REEED PH measurement sketch

float calibration =6.3; //change this value to calibrate
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;

void setup() {
 Serial.begin(9600);
}
 
void loop() {
 for(int i=0;i<10;i++) 
 { 
   buf[i]=analogRead(analogInPin);
   delay(30);
  }
 for(int i=0;i<9;i++)
 {
   for(int j=i+1;j<10;j++)
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
 for(int i=2;i<8;i++)     //take the average value of 6 center sample
    avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;     //convert the analog into millivolt
 float phValue = 5.70 * pHVol - calibration;   //convert the millivolt into pH value
 Serial.print(" pH = ");
 Serial.println(phValue);
 
 delay(500);

 //Success
}
