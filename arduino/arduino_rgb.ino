
/*************************************
Bugdroid blink with RGB LED and API:

command: off, temp or RrGrBrRlGlBlM

Rr = 000 (on) to 255 (off) for right red
Gr = 000 (on) to 255 (off) for right green
Br = 000 (on) to 255 (off) for right blue
Rl = 000 (on) to 255 (off) for left red
Gl = 000 (on) to 255 (off) for left green
Bl = 000 (on) to 255 (off) for left blue
M = a (blink) or b (flash)
*************************************/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

SoftwareSerial mySerial(7, 6); // RX, TX

String command = "";

//PWM
int Rg = 5;
int Rd = 9;
int Bg = 11;
int Bd = 10;
int Gd = 3;
int Gg = 6;

int blinkMode = false;
int toggleMode = false;
int flashMode = false;
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

long intervalOn = 0;
long intervalOff = 0;
int times = 0;
int cmdReady = 0;

String request = "";

void setup()
{
    Serial.begin(9600);

    pinMode(Rg, OUTPUT);
    pinMode(Rd, OUTPUT);
    pinMode(Bg, OUTPUT);
    pinMode(Bd, OUTPUT);
    pinMode(Gg, OUTPUT);
    pinMode(Gd, OUTPUT);

    off();
    
    sensors.begin();
}

void stopAll() {
  off();
  blinkMode = false;
  flashMode = false;
}

void off() {
    analogWrite(Rg, 255);
    analogWrite(Rd, 255);
    analogWrite(Bg, 255);
    analogWrite(Bd, 255);
    analogWrite(Gg, 255);
    analogWrite(Gd, 255);
}

void color() {
  analogWrite(Rg,request.substring(0,3).toInt());
  analogWrite(Gg,request.substring(3,6).toInt());
  analogWrite(Bg,request.substring(6,9).toInt());
  
  analogWrite(Rd,request.substring(9,12).toInt());
  analogWrite(Gd,request.substring(12,15).toInt());
  analogWrite(Bd,request.substring(15,18).toInt());
}

void loop()
{
    if (mySerial.available()) {
      while(mySerial.available()) {
          command += (char)mySerial.read();
      }
      cmdReady = 1;
    }
  
    if (Serial.available()) {
      delay(20);
      while(Serial.available()) {
          command += (char)Serial.read();
      }
      cmdReady = 1;
    }


    if(cmdReady == 1) {
        command.trim();
        command.toLowerCase();
        

        if(command == "temp") {
            sensors.requestTemperatures();
            Serial.println(sensors.getTempCByIndex(0));
            mySerial.println(sensors.getTempCByIndex(0));
        }
        else if(command == "off") {
            stopAll();
            Serial.println("ok");
            mySerial.println("ok");
        }
        else {
           request = command;
           stopAll();
           color();
           
           if(command.substring(18) == "a") {
              interval = 1000;
              blinkMode = true;
           }
           else if(command.substring(18) == "b") {
              flashMode = true;
              times = 0;
              intervalOn = 200;
              intervalOff = 1000;
              interval = intervalOn;
           }
           
           Serial.println("ok");
           mySerial.println("ok");
        }


    
        command = ""; // No repeats
        cmdReady = 0;

    }

    if(blinkMode) {
        unsigned long currentMillis = millis();

        if(currentMillis - previousMillis > interval) {
            previousMillis = currentMillis;

            if (ledState == LOW) {
                ledState = HIGH;
                off();
            }
            else {
              color();
                ledState = LOW;
            }

        }
    }

    if(flashMode) {
        unsigned long currentMillis = millis();

        if(currentMillis - previousMillis > interval) {

            previousMillis = currentMillis;

            if(times == 3) {
                times = 0;
                interval = intervalOff;
                ledState = LOW;
                off();
            }
            else {
                times = times +1;
                interval = intervalOn;
                if (ledState == LOW) {
                    ledState = HIGH;
                    color();
                }
                else {
                    ledState = LOW;
                    off();
                }
            }
        }
    }
}


