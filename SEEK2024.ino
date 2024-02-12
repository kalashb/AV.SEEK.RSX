#include <Servo.h>

#define threshold 10

const int M1 = 7; // Left 1
const int M2 = 8; // Left 2
const int M3 = 10;  // Right 1
const int M4 = 9;  // Right 2
const int PWM1 = 6;
const int PWM2 = 5;

const int IR = 2; // IR Output

const int Trig = 13; // Ultrasound Sensor Trigger Pin
const int Echo = 11; // Ultrasound Sensor Echo Pin

double distance;
long duration;

Servo myServo; // Servo Control Pin

void forward();
void backward();
void left();
void right();
void stop();

int IRinput(void);

double getDistance(void);

void Sweep(void);

void setup() {
  // put your setup code here, to run once:
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(M3, OUTPUT);
pinMode(M4, OUTPUT);

pinMode(PWM1, OUTPUT);
pinMode(PWM2, OUTPUT);

pinMode(IR, INPUT);

pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);

myServo.attach(3);

Serial.begin(9600);
}

void loop() { // SUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
myServo.write(90);
forward();
delay(1000);
right();
delay(1000);
forward();
delay(1000);
left();
delay(1000);
for (int i = 0; i <= 7; i++){
  right();
   myServo.write(150);
  delay(150);
  left();
   myServo.write(30);
  delay(150);
}
back();
delay(300);
for (int i = 0; i <= 7; i++){
  forward();
  myServo.write(150);
  delay(250);
  back();
   myServo.write(30);
  delay(250);
}
}

void forward(){
  digitalWrite(M1, 1);
  digitalWrite(M2, 0);
  digitalWrite(M3, 0);
  digitalWrite(M4, 1);
  analogWrite(PWM1, 200);
  analogWrite(PWM2, 200);
}
void back(){
  digitalWrite(M1, 0);
  digitalWrite(M2, 1);
  digitalWrite(M3, 1);
  digitalWrite(M4, 0);
  analogWrite(PWM1, 200);
  analogWrite(PWM2, 200);
}
void left(){
  digitalWrite(M1, 0);
  digitalWrite(M2, 1);
  digitalWrite(M3, 0);
  digitalWrite(M4, 1);
  analogWrite(PWM1, 200);
  analogWrite(PWM2, 200);
}
void right(){
  digitalWrite(M1, 1);
  digitalWrite(M2, 0);
  digitalWrite(M3, 1);
  digitalWrite(M4, 0);
  analogWrite(PWM1, 200);
  analogWrite(PWM2, 200);
}

void stop(){
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);
  digitalWrite(M3, 0);
  digitalWrite(M4, 0);
  analogWrite(PWM1, 200);
  analogWrite(PWM2, 200);
}

int IRinput(void){
  return digitalRead(IR);
}


double getDistance(void){
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration*0.0343/2;
  return distance;
}

void Sweep(void){
  for (int pos = 0; pos <= 165; pos += 10){
    // in steps of 1 degree
    myServo.write(pos);
    getDistance();
    Serial.println(distance);
    Serial.println(pos);
    delay(100);        
  }
  delay(100);
  for (int pos = 165; pos >= 0; pos -= 10){ 
    myServo.write(pos);              
    getDistance();
    Serial.println(distance);
    Serial.println(pos);
    delay(100);         
}
  delay(100);
}

double SweepScan(void){
  double max = 0;
    stop();
    for (int pos = 15; pos <= 165; pos += 5){
    myServo.write(pos);
    delay(25);
    getDistance();
      if (distance > max){
      max = pos;
      }
      else { 
      max = max;
      }
    Serial.println(max);
    Serial.println(distance);
    Serial.println(pos);
    delay(25);        
  }
    for (int pos = 165; pos >= 90; pos -= 5){
    myServo.write(pos);
    delay(25);
    getDistance();
      if (distance > max){
      max = pos;
      }
      else { 
      max = max;
      }
    Serial.println(max);
    Serial.println(distance);
    Serial.println(pos);
    delay(25);        
  }

  stop();
return max;
delay(100);
}
