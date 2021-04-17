#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <IRremote.h>

//const uint32_t buttonPower;
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
IRrecv irrecv(RECV_PIN); 

void setup() {
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

void loop() {

  if(irrecv.decode())
  {
    irrecv.stop();
    uint32_t value = IrReceiver.decodedIRData.decodedRawData;
    if(value != 0)
    {
      Serial.println("Code: " + value);
    }
  }
  irrecv.resume();
}

void SetSpeed(int speed)
{
  for(int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->setSpeed(speed);
  }
}

void RunForward()
{
  for(int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(FORWARD);
  }
}

void RunBackward()
{
  for(int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(BACKWARD);
  }
}

void Stop()
{
  for(int i = 1; i < 5; i++)
  {
    motorShield.getMotor(i)->run(RELEASE);
  }
}
