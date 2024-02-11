#include <Servo.h>

const int M1 = 10; // Left 1
const int M2 = 9; // Left 2
const int M3 = 6;  // Right 1
const int M4 = 5;  // Right 2

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

pinMode(IR, INPUT);

pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);

myServo.attach(3);

Serial.begin(9600);
}

void loop() {
 Sweep();
}

void forward(){
  analogWrite(M1, 255);
  analogWrite(M2, 0);
  analogWrite(M3, 0);
  analogWrite(M4, 255);
}
void back(){
  analogWrite(M1, 0);
  analogWrite(M2, 255);
  analogWrite(M3, 255);
  analogWrite(M4, 0);
}
void left(){
  analogWrite(M1, 0);
  analogWrite(M2, 255);
  analogWrite(M3, 0);
  analogWrite(M4, 255);
}
void right(){
  analogWrite(M1, 255);
  analogWrite(M2, 0);
  analogWrite(M3, 255);
  analogWrite(M4, 0);
}

void stop(){
  analogWrite(M1, 0);
  analogWrite(M2, 0);
  analogWrite(M3, 0);
  analogWrite(M4, 0);
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
  for (int pos = 0; pos <= 180; pos += 1){
    // in steps of 1 degree
    myServo.write(pos);              
    delay(25);                       
  }
  delay(100);
  for (int pos = 180; pos >= 0; pos -= 1){ 
    myServo.write(pos);              
    delay(25);         
}
  delay(100);
}