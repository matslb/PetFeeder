#include <Stepper.h>
#include <String.h>

const int rep = 2050;
const int turn = rep/4;
const long hour = 60UL * 60UL * 1000UL;
int dir = -1;
Stepper stepper = Stepper(rep,9, 11, 10, 12); //make sure this matches your setup

/**
 * 
 * ARDUINO PET FEEDER 
 * 
 * REQUIRES AN ARDUINO AND COMPATIBLE STEPPER MOTOR
 * 
 * 
 * 
 ****************** CUSTOMIZABLE SETTINGS **************************

 * The standard Arduino Uno cant tell time without power, so set clockHour to the closest hour to when it powers on.
 */
long clockHour = 16; //24h

/**
 * Set the interval to how many hours you want between each dispensing
 */
const int interval = 3;

/**
 * Set the desired dosage of each dispensing
 */
const int dosage = 2;



/********************* CODE *****************/

void setup() {
  
  stepper.setSpeed(10);
  stepper.step(turn*dir*-1);
  delay(5000);
}

void loop() {
  Serial.begin(9600);

  delay(hour*interval);
  
  //delay(1000); //for testing
  
  clockHour += interval;
  
  if( clockHour > 24 ){
    clockHour = clockHour-24;
  }
  Serial.print("the time is: ");
  Serial.println(clockHour);

}

void wiggle (int times){
  for (int i = 0; i<times; i++){
    stepper.step(-70);
    delay(10);
    stepper.step(70);
  }
}

void dispense (int times){
    for (int i = 0; i<times; i++){
      Serial.println("Dispensing");
      wiggle(2);
      stepper.step(turn*dir);
      wiggle(2);
      dir= dir*-1;
    }
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);  
    Serial.println("done");
}
