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

char report[480];
double roll,Pitch,Yaw;
double acc;
long lastDisplayTime;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  pinMode(13,OUTPUT);
}

void loop()
{ double min;
double max;
double max1;
double min1;
int i,j;
//double minavg;
//double maxavg;

  compass.read();

  snprintf(report, sizeof(report), "A(i): %6d %6d %6d    M: %6d %6d %6d",
    (compass.a.x>>3), (compass.a.y>>3), (compass.a.z>>4),
    (compass.m.x>>2), (compass.m.y>>2),(compass.m.z>>2));
  Serial.println(report);
  acc=(compass.a.z>>4)*0.001;
  if(acc<min)
  {
    min=acc;
  //  min1=min1+min;
   
  }
  if(acc>max)
  {
    max=acc;
    //max1=max1+max;
 }
 
    //minavg=min1/8;
   // maxavg=max1/8; 
  Serial.print("acc");
  Serial.print("\t");
  Serial.print(acc);
 Serial.print("\t");
 if ((millis() - lastDisplayTime) > 1000)
 {
  Serial.print("min");
  Serial.print("\t");
  Serial.print(min);
  Serial.print("\t");
  Serial.print("max");
  Serial.print("\t");
  Serial.print(max);
  // Serial.print("minavg");
  Serial.print("\t");
  //Serial.print(minavg);
  Serial.print("\t");
  //Serial.print("maxavg");
  Serial.println("\t");
//  Serial.println(maxavg);
  
 lastDisplayTime=millis();
 }   
// maxavg=max/8;
 //minavg=min/8;
 
 roll=atan2(compass.a.x, compass.a.z) * 180/PI;
Pitch = atan2(compass.a.x, sqrt(abs(compass.a.y*compass.a.y) +abs( compass.a.z*compass.a.z))) * 180/PI;
  Yaw=atan2(compass.a.y,compass.a.x)* 180/PI;
  if(roll<0)
  {
  roll+=180;
  }
  Serial.print("Roll motion");
  Serial.print("\t");
  Serial.print(roll);
  Serial.print("\t");
    Serial.print("pitch");
  Serial.print("\t");
  Serial.println(Pitch);
  
  //while(roll<178);
//  digitalWrite(13,LOW);
 // delay(1000);
  if ((roll)>170)
  {
    digitalWrite(13,HIGH);
  }
 else
  digitalWrite(13,LOW);
  
  delay(1500);
}
