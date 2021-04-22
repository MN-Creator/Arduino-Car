#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <IRremote.h>

//const uint32_t buttonPower = ;
//const uint32_t buttonA;
//const uint32_t buttonB;
//const uint32_t buttonC;
//const uint32_t buttonUp;
//const uint32_t buttonDown;
//const uint32_t buttonLeft;
//const uint32_t buttonRight;
//const uint32_t buttonMid;

int RECV_PIN = A0;
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

//#define POWER 0x10EFD827
//#define A 0x10EFF807
//#define B 0x10EF7887
//#define C 0x10EF58A7
//#define UP 0x10EFA05F
//#define DOWN 0x10EF00FF
//#define LEFT 0x10EF10EF
//#define RIGHT 0x10EF807F
//#define SELECT 0x10EF20DF
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
    //    auto value = IrReceiver.decodedIRData.decodedRawData;
    //    Serial.println(value);
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
    //    Serial.println(value);
    irrecv.resume();
  }
}

//void loop() {
//
//  if (irrecv.decode())
//  {
//    //    uint32_t value = IrReceiver.decodedIRData.decodedRawData;
//    irrecv.printIRResultShort(&Serial);
//    Serial.println("Code: ");
//    Serial.println(irrecv.decodedIRData.command);
//    //    Serial.println(value);
//  }
//  irrecv.resume();
//}

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
