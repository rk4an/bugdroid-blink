#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX, TX

String command = "";
int ledRight = 3;
int ledLeft = 4;

int blinkMode = false;
int toggleMode = false;
int flashMode = false;
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

long intervalOn = 0;
long intervalOff = 0;
int times = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ledRight, OUTPUT); 
  pinMode(ledLeft, OUTPUT); 
  
  mySerial.begin(9600);
}

void loop() {
  // Read device output if available.
  if (mySerial.available()) {
    while(mySerial.available()) { // While there is more to be read, keep reading.
      command += (char)mySerial.read();
    }
    
    Serial.println(command);
    command.trim();
    command.toLowerCase();
    
    //on all leds
    if(command == "on") {
      digitalWrite(ledRight, HIGH);
      digitalWrite(ledLeft, HIGH);
    }
    
    //off all leds
    if(command == "off") {
      digitalWrite(ledRight, LOW);
      digitalWrite(ledLeft, LOW);
      blinkMode = false;
      toggleMode = false;
      flashMode = false;
    }
    
    //toggle rigth
    if(command == "right") {
        digitalWrite(ledRight, !digitalRead(ledRight));
    }
    
    //toggle left
    if(command == "left") {
        digitalWrite(ledLeft, !digitalRead(ledLeft));
    }
    
    //blink
    if(command == "b1000") {
        blinkMode = true;
        interval = 1000;
    }
    
    if(command == "b500") {
        blinkMode = true;
        interval = 500;
    }
    
    if(command == "b200") {
        blinkMode = true;
        interval = 200;
    }
    
    //toogle
    if(command == "t1000") {
        toggleMode = true;
        interval = 500;
    }
    
    if(command == "t500") {
        toggleMode = true;
        interval = 500;
    }
    
    if(command == "t200") {
        toggleMode = true;
        interval = 200;
    }
    
    if(command == "flash") {
        flashMode = true;
        times = 0;
        intervalOn = 200;
        intervalOff = 1000;
        interval = intervalOn;
    }
    
    command = ""; // No repeats
  }//if
  
  if(blinkMode) {
      unsigned long currentMillis = millis();
     
      if(currentMillis - previousMillis > interval) {

        previousMillis = currentMillis;   
    
        if (ledState == LOW) {
          ledState = HIGH;
        }
        else {
          ledState = LOW;
        }

        digitalWrite(ledRight, ledState);
        digitalWrite(ledLeft, ledState);
    }
  }
  
    if(toggleMode) {
      unsigned long currentMillis = millis();
     
      if(currentMillis - previousMillis > interval) {

        previousMillis = currentMillis;   
    
        if (ledState == LOW) {
          ledState = HIGH;
        }
        else {
          ledState = LOW;
        }

        digitalWrite(ledRight, ledState);
        digitalWrite(ledLeft, !ledState);
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
        }
        else {
          times = times +1;
          interval = intervalOn;
          if (ledState == LOW) {
            ledState = HIGH;
          }
          else {
            ledState = LOW;
          }
        }
       
        digitalWrite(ledRight, ledState);
        digitalWrite(ledLeft, ledState);
      }
  }
  
  
  // Read user input if available.
  if (Serial.available()){
    delay(10); // The delay is necessary to get this working!
    mySerial.write(Serial.read());
  }

}

