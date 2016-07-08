/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low accelerometer and
magnetometer data registers. They can be converted to units of g and
gauss using the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM303D gives a magnetometer X axis reading of 1982 with
its default full scale setting of +/- 4 gauss. The M_GN specification
in the LSM303D datasheet (page 10) states a conversion factor of 0.160
mgauss/LSB (least significant bit) at this FS setting, so the raw
reading of -1982 corresponds to 1982 * 0.160 = 317.1 mgauss =
0.3171 gauss.

In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
registers actually contain a left-aligned 12-bit number, so the lowest
4 bits are always 0, and the values should be shifted right by 4 bits
(divided by 16) to be consistent with the conversion factors specified
in the datasheets.

Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
with its default full scale setting of +/- 2 g. Dropping the lowest 4
bits gives a 12-bit raw value of -1009. The LA_So specification in the
LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
1009 mg = 1.009 g.
*/

#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

int j[300];
int k[300];
int i;
double roll;
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  pinMode(13,OUTPUT);
}

void loop()
{ 
 
  for (i=0;i<200;i++)
  { 
    compass.read();
  roll=atan2(compass.a.x, compass.a.z) * 180/PI;
  Serial.print("roll");
  Serial.print("\t");
  Serial.println(-roll);
    j[i]=compass.a.x;
  
   k[i]=compass.m.x;
   Serial.print("compass.a.x");
   Serial.print("\t");
  Serial.print(j[i]);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  
  Serial.print("compass.m.x");
  Serial.print("\t");
  Serial.print(k[i]);
  Serial.println("\n");
  if(((abs(j[i])-abs(j[i-1])>2200 )||(abs(j[i-1])-abs(j[i])>2200 ) )|| ((abs(k[i])-abs(k[i-1])>60)||(abs(k[i-1])-abs(k[i])>60))) //&& (k[i++]-k[i])>50) ||((-roll)>178))
 { Serial.println("interrupt");
  digitalWrite(13,HIGH);
 }
  else 
  digitalWrite(13,LOW);
  
  delay(1000);
  }
}

/*
  snprintf(report, sizeof(report), "A(i): %6d %6d %6d    M: %6d %6d %6d",
    compass.a.x, compass.a.y, compass.a.z,
    compass.m.x, compass.m.y, compass.m.z);
  
 Serial.println(report);
 
  */
  
 
 
