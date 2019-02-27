#include <SoftwareSerial.h>
#include <NewPing.h>

SoftwareSerial Genotronex(0, 1); // RX, TX

int ledpin=13; // led on D13 will show blink on / off
int rightFar = 11;
int leftFar = 10;
int leftStop = 9;
int rightStop = 12;
int rightSemnalPin = 3;
int leftSemnalPin = 5;
int BluetoothData; // the data given from Computer

const int LeftMotorForward = A0;
const int LeftMotorBackward = A1;
const int RightMotorForward = A2;
const int RightMotorBackward = A3;

void turnOnLights()
{
  digitalWrite(rightFar, HIGH);
  digitalWrite(leftFar, HIGH);
}

void turnOffLights()
{
  digitalWrite(leftFar, LOW);
  digitalWrite(rightFar, LOW);
}

void _mStop()
{
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);

  digitalWrite(leftStop, HIGH);
  digitalWrite(rightStop, HIGH);
  digitalWrite(leftSemnalPin, LOW);
  digitalWrite(rightSemnalPin, LOW);
  digitalWrite(leftFar, LOW);
  digitalWrite(rightFar, LOW);
}

void stop2()
{
  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 0);
}

void _mDance()
{
  stop2();
  delay(100);
  
  digitalWrite(leftSemnalPin, HIGH);
  digitalWrite(rightSemnalPin, HIGH);
  digitalWrite(leftStop, HIGH);
  digitalWrite(rightStop, HIGH);
  digitalWrite(leftFar, HIGH);
  digitalWrite(rightFar, HIGH);
  
  delay(100);
  
  digitalWrite(rightFar, LOW);
  digitalWrite(leftFar, LOW);
  
  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorForward, 0);
  
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 0);

  delay(200);

  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorForward, 255);
  
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 0);

  delay(2000);
  
  analogWrite(RightMotorForward, 255);
  analogWrite(LeftMotorForward, 0);
  
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 0);

  delay(2000);

  analogWrite(RightMotorForward, 255);
  analogWrite(LeftMotorForward, 0);
  
  analogWrite(RightMotorBackward, 0);
  analogWrite(LeftMotorBackward, 255);                                                                                                                                                                                                                                                                );

  delay(2000); 
  _mStop();
}

void _mForward()
{
  stop2();
  
  digitalWrite(leftSemnalPin, LOW);
  digitalWrite(rightSemnalPin, LOW);
  digitalWrite(leftFar, HIGH);
  digitalWrite(rightFar, HIGH);

  analogWrite(LeftMotorForward, 255);
  analogWrite(RightMotorForward, 255);
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);
}

void _mBack()
{
  stop2();

  digitalWrite(leftFar, LOW);
  digitalWrite(rightFar, LOW);
  digitalWrite(leftSemnalPin, LOW);
  digitalWrite(rightSemnalPin, LOW);
  digitalWrite(leftStop, HIGH);
  digitalWrite(rightStop, HIGH);
  
  analogWrite(LeftMotorForward, 0);
  analogWrite(RightMotorForward, 0);
  analogWrite(LeftMotorBackward, 200);
  analogWrite(RightMotorBackward, 200);
  
  Serial.println("go back!");
}

void _mLeft()
{
  digitalWrite(leftSemnalPin, HIGH);
  digitalWrite(rightSemnalPin, LOW);
  digitalWrite(leftStop, LOW);
  digitalWrite(rightStop, LOW);
  
  analogWrite(LeftMotorForward, 100);
  analogWrite(RightMotorForward, 255);
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);
  
  delay(20);
  
  _mForward();
  Serial.println("go left!");
}

void _mRight()
{
  digitalWrite(leftSemnalPin, LOW);
  digitalWrite(rightSemnalPin, HIGH);
  digitalWrite(rightStop, LOW);
  digitalWrite(leftStop, LOW);
  
  analogWrite(LeftMotorForward, 255);
  analogWrite(RightMotorForward, 100);
  analogWrite(LeftMotorBackward, 0);
  analogWrite(RightMotorBackward, 0);
  
  delay(20);

  _mForward();
}


void setup()
{
  Serial.begin(38400);
  Genotronex.begin(9600);

  pinMode(ledpin,OUTPUT);
  
  pinMode(leftFar, OUTPUT);
  pinMode(rightFar, OUTPUT);
  pinMode(leftStop, OUTPUT);
  pinMode(rightStop, OUTPUT);
  pinMode(leftSemnalPin, OUTPUT);
  pinMode(rightSemnalPin, OUTPUT);
  

  pinMode(LeftMotorForward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  digitalWrite(leftStop, HIGH);
  digitalWrite(rightStop, HIGH);
  digitalWrite(leftSemnalPin, HIGH);
  digitalWrite(rightSemnalPin, HIGH);
  digitalWrite(leftFar, HIGH);
  digitalWrite(rightFar, HIGH);
  
  delay(100);
}

void loop()
{
  
    if (Genotronex.available())
    {
        BluetoothData = Genotronex.read();
    }

    if (BluetoothData == 'F')
    {
        _mForward();
        Genotronex.println("Forward! ");
    }

    if(BluetoothData == 'L')
    {
        _mLeft();
        Genotronex.println("Go left!");
    }

    if(BluetoothData == 'R')
    {
        _mRight();
        Genotronex.println("Go right!");
    }

    if (BluetoothData == 'B')
    {
        _mBack();
        Genotronex.println("Go back! ");
    }

    if (BluetoothData == 'S')
    {
        _mStop();
        Genotronex.println("Stop! ");
    }

    if (BluetoothData == 'D')
    {
        _mDance();
        Genotronex.println("Dance! ");
    }
    
    if (BluetoothData == 'F')
    {
        turnOnLights();
    }
    
    if (BluetoothData == 'K')
    {
        turnOffLights();
    }
    
}
