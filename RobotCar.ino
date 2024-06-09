#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <IRremote.h>

int RECV_PIN = A0;
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

#define POWER 16736925
#define A 16720605
#define B 16712445
#define C 16761405
#define UP 16750695
#define DOWN 16726215
#define LEFT 16724175
#define RIGHT 16743045
#define SELECT 16718055
decode_results results;

IRrecv irrecv(RECV_PIN);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("IR Receiver Ready");
  motorShield.begin();
  SetSpeed(150);
  RunForward();
  Stop();
  Serial.println("Adafruit Motorshield v2 Ready");
  Serial.println("-- All Components Ready --");
}

void loop()
{
  if (irrecv.decode(&results))   {
    if (results.value == UP)
    {
      RunForward();
    }
    else if (results.value == DOWN)
    {
      RunBackward();
    }
    else if (results.value == SELECT)
    {
      Stop();
    }
    else if (results.value == RIGHT)
    {
      TurnRight();
    }
    else if (results.value == LEFT)
    {
      TurnLeft();
    }
    irrecv.resume();
  }
}

void SetSpeed(int speed)
{
  for (int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->setSpeed(speed);
  }
}

void RunForward()
{
  for (int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(FORWARD);
  }
}

void TurnRight()
{
  motorShield.getMotor(1)->run(RELEASE);
  motorShield.getMotor(2)->run(FORWARD);
  motorShield.getMotor(3)->run(FORWARD);
  motorShield.getMotor(1)->run(RELEASE);
}

void TurnLeft()
{
  motorShield.getMotor(1)->run(FORWARD);
  motorShield.getMotor(2)->run(RELEASE);
  motorShield.getMotor(3)->run(RELEASE);
  motorShield.getMotor(4)->run(FORWARD);

}

void RunBackward()
{
  for (int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(BACKWARD);
  }
}

void Stop()
{
  for (int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(RELEASE);
  }
}
