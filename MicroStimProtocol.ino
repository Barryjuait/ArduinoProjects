/*
author: Sebastian Barrientos
Protocol to send pulses to the stimulator MultiChannel.

*/
int pin1 = 7;
int pin2 = 8;
int pin3 = 9;
int pin4 = 10;
int pin5 = 11;
int pin6 = 13;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  }

void loop() {
  //put your main code here, to run repeatedly:
  SpeedVal = Serial.parseInt(); //reads only the numbers from the incoming string
  inByte = Serial.read(); //reads the rest of the characters from the incoming string that are not numbers
  int valR = 1500 + (SpeedVal*5);
  int valL = 1500 - (SpeedVal*5);
  //values of microseconds between 1000 and 1499 will turn the motor left; from 1501 to 2000 will turn it right. 1500 will stop;
  if (inByte == 'x')
  {
    manualMode = false;
    Serial.println("Manual Mode OFF");
    }
  else if (inByte == 'y')
  {
    manualMode = true;
    Serial.println("Manual Mode ON");
    }
    if (press_right == LOW && manualMode == true) {
    //servoCommutator.attach(servo_pin);
    Serial.println("right");
    digitalWrite(LED_control, HIGH);
    servoCommutator.writeMicroseconds(2000);
  }
  else if (press_left == LOW && manualMode == true) {
    //servoCommutator.attach(servo_pin);
    Serial.println("left");
    digitalWrite(LED_control, HIGH);
    servoCommutator.writeMicroseconds(1000);
  }
  else if (press_left == HIGH && press_right == HIGH && manualMode == true) {
    servoCommutator.writeMicroseconds(1500);
    digitalWrite(LED_control, LOW);
    Serial.println(" ");
  }
  else if (press_left == LOW && press_right == LOW && manualMode == true) {
    servoCommutator.writeMicroseconds(1500);
    digitalWrite(LED_control, LOW);
    Serial.println(" ");
  }
  else if (inByte == 'a' && manualMode == false) {
    servoCommutator.writeMicroseconds(valR);
    digitalWrite(LED_control, HIGH);
    Serial.println("Right");
  }
  else if (inByte == 'b' && manualMode == false) {
    servoCommutator.writeMicroseconds(valL);
    digitalWrite(LED_control, HIGH);
    Serial.println("Left");
  }  
  else if (inByte == 'c' && manualMode == false) {
    servoCommutator.writeMicroseconds(1500);
    digitalWrite(LED_control, LOW);
    Serial.println("Stop");
  }
                    
}
