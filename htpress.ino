#include <Wire.h>
#include <LPS331.h>

LPS331 ps;
unsigned int alt,alt1,alt2=0,alt3;
int min,i;
int max;
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }

  ps.enableDefault();
}

void loop()
{
  float pressure = ps.readPressureInchesHg();
  unsigned int altitude = ps.pressureToAltitudeFeet(pressure);
  float temperature = ps.readTemperatureF();
  alt=altitude;
  if (alt<min)
  {
    min=alt;
  }
 if (alt>max)
 {
  max=alt;
 }
 
 alt3=(max-min)%3600;
 
  Serial.print("min: ");
  Serial.print(min);
  
  Serial.print(" ft\ta: ");
  Serial.print("max:");
  Serial.print(max);
  Serial.print(" ft\ta: ");
  
  
  Serial.print(alt3);
  Serial.print(" ft\tt: ");
  Serial.print(temperature);
  Serial.println(" deg F");

  delay(1000);
}
