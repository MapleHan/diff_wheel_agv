#define MOTOR_COUNT 1"
int pluae_pin=35;
int dir_pin=54;
bool ccw_dir=LOW;
String up_command = "liftingup";
String down_command = "liftingdown";
String reply = "ok";
String err = "er";

void setup()
{
  // put your setup code here, to run once:
  delay(100);
  Serial.begin(115200);
  pinMode(pluae_pin,OUTPUT);
  pinMode(dir_pin,OUTPUT);
      motorRotate(3500);
      delay(2000);
      motorRotate(-3500);
      delay(2000);
}

void loop() 
{
  if(Serial.available())
  {
    String str="";
    while(Serial.available())
    {
      str+=(char)Serial.read();
      delay(1);
    }
    if(str==up_command)
    {
      Serial.print(reply);
      motorRotate(3500);
      delay(2000);
      motorRotate(-3500);
      delay(2000);
    }
    else if(str==down_command)
    {
      Serial.print(reply);
      motorRotate(1500);
      delay(2000);
      motorRotate(-1500);
      delay(2000);
    }
    else
      Serial.print(err);
    //SerialUSB.println(str);
  }
}


void motorRotate(long n_step)
{
  if(n_step>0)
    digitalWrite(dir_pin,ccw_dir);
  else
    digitalWrite(dir_pin,!ccw_dir);
  for(long j=0;j<abs(n_step);j++)
  {
    digitalWrite(pluae_pin,HIGH);
    delayMicroseconds(15);
    digitalWrite(pluae_pin,LOW);
    delayMicroseconds(15);
  }
}
