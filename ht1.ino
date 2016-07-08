

#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

int j[300];
int k[300];
int i;
double roll;
unsigned int sampletime;
double acc;
int h;
unsigned int now;
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
compass.read();
now=millis();
Serial.println(compass.a.z);
acc=(compass.a.z)*0.061;
Serial.print("acc");
Serial.print("\t");
Serial.print(acc);
Serial.print("\n");
sampletime=millis()-now;

h=0.5*acc*sampletime*sampletime;
Serial.print("h");
Serial.print("\t");
Serial.print(h);
Serial.print("\t");
Serial.println("\n");
if (h==0.5)
{
  digitalWrite(13,HIGH);
}
delay(500);
}
