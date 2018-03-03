#include<Servo.h>
int echopin = 5;
int trigpin = 4;
int buzzer = 7;
int LeftMotorForward = 10; // Pin 10 has Left Motor connected on Arduino boards.
int LeftMotorReverse = 9; // Pin 9 has Left Motor connected on Arduino boards.
Servo servo;
int RightMotorForward = 12; // Pin 12 has Right Motor connected on Arduino boards.
int RightMotorReverse = 13; // Pin 13 has Right Motor connected on Arduino boards.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(3);
  pinMode(LeftMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(LeftMotorReverse, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorReverse, OUTPUT);  // initialize the  pin as an output.
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzer, OUTPUT);
}
void straight()
{
  digitalWrite(RightMotorForward, HIGH);
  analogWrite(RightMotorReverse, 0);
  digitalWrite(LeftMotorForward, HIGH);
  analogWrite(LeftMotorReverse, 0);
}

void right()
{
  digitalWrite(RightMotorForward, HIGH);
  analogWrite(RightMotorReverse, 0);
  digitalWrite(LeftMotorForward, 0);
  analogWrite(LeftMotorReverse, 0);
}

int  observe()
{
  long duration = 0, distance = 0;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  delay(500);
  distance = (duration * .033 / 2);
  Serial.print(distance);
  Serial.println("cm");
  return distance;
}

void left()
{
  digitalWrite(RightMotorForward, LOW);
  analogWrite(RightMotorReverse, 0);
  digitalWrite(LeftMotorForward, 150);
  analogWrite(LeftMotorReverse, 0);
}
void reverse()
{
  digitalWrite(buzzer, HIGH);
  analogWrite(RightMotorForward, 0);
  analogWrite(RightMotorReverse, 150);
  analogWrite(LeftMotorForward, 0);
  digitalWrite(LeftMotorReverse, HIGH);
  delay(2000);
  analogWrite(RightMotorForward, 0);
  analogWrite(RightMotorReverse, 0);
  analogWrite(LeftMotorForward, 0);
  digitalWrite(LeftMotorReverse, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance1 =  0,distance2 = 0;
  distance1 = observe();
  if (distance1 >= 10)
  {
    //Serial.println(distance1);
    straight();}
  else
  {
    reverse();
    servo.write(30);
    delay(500);
    distance1 = observe();
    //Serial.println("right dis\t\t");
    //Serial.println(distance1);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(160);
    delay(500);
    distance2  = observe();
    //Serial.println("left dis\t\t");
    //Serial.println(distance2);
    delay(1000);
    servo.write(90);
    if(distance1 > distance2)
          {right();
          delay(1000);}
    else
          {left();
           delay(1000);}
    straight();
  }
}

