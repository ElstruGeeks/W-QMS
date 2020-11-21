int sensorPin = A0;
float volt;
float ntu;
 
void setup()
{
  Serial.begin(9600);               // We will use the Serial Monitor to read the NTU of the water
}
void loop()
{

    volt = 0;               
    for(int i=0; i<800; i++)         //The voltage from the sensor is quite noisy 
    {                                //so I take 800 samples and then average those samples
        int sensorvalue = analogRead(A0);
        volt += sensorvalue * (5.0 / 1024.0);  //Convert the analog reading （0~1023） to a voltage (0 ~ 5V)
    }
    volt = volt/800;
    volt = round_to_dp(volt,1);      //Round the volt number to 1 decimal place
 
    if(volt < 2.5){                  //The equation only works between 2.5V ~ 4.2V,
      ntu = 3000;                    //so set any readings below 2.5V with 3000NTU
    }else{                           
      ntu = -1120.4*square(volt)+5742.3*volt-4352.9;  // Calculate the current NTU
    }
    if(ntu <0){
      ntu = 0;                       //If the NTU turns out to be under 0, set it to 0.
    }
  Serial.print("voltage = ");
  Serial.println(volt);
  delay(600);
  Serial.print("NTU = ");
  Serial.println(ntu);
  delay(600);
}
 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
