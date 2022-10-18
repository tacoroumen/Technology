#include <Arduino.h>
#include <wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Display.h"

float vallue;
float max_temp;
float current_temp;
int last_state = 1;
Adafruit_BME280 bme;

#define SEALEVELPRESSURE_HPA (1013.25)

void setup()
{
  Serial.begin(9600);
  // default settings
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }
  // put your setup code here, to run once:
  Display.clear();
}


void loop()
{
  // put your main code here, to run repeatedly:
  vallue = Serial.parseFloat();
  char received = Serial.read();
  if (received == '\n') // Max temp is finished, so process max temp.
  {
    max_temp = vallue;
    Serial.print("The maximum temperature is set at: ");
    Serial.print(max_temp);
    Serial.println(" Degrees");
    vallue = 0;
    last_state = 0;
  }
  else
  {
    Serial.print("Temperature = ");
    Serial.println(bme.readTemperature());
  }
  if (bme.readTemperature() > max_temp && last_state != 1)
  {
    Display.show("Open");
    Serial.println("Open windows");
    while (received != '\n')
    {
      received = Serial.read();
    }
    last_state = 1;
  }
  if (bme.readTemperature() <= max_temp && last_state != 2)
  {
    Display.show("Shut");
    Serial.println("Shut windows");
    while (received != '\n')
    {
      received = Serial.read();
    }
    last_state = 2;
  }
}