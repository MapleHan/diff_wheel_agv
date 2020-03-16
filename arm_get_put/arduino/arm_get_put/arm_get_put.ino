String get_command = "armget";
String put_command = "armput";
String reply = "ok";
String err = "er";
int numbers = 0;
void setup()
{
  // put your setup code here, to run once:
  delay(100);
  Serial.begin(115200);
  armSetup();
//  neoSetup();

}

void loop() 
{
  String str="";
  if(Serial.available())
  {
    while(Serial.available())
    {
      str+=(char)Serial.read();
      delay(5);
    }
    if(str==get_command)
    {
      Serial.print(reply);
      getObject();
    }
    else if(str==put_command)
    {
      Serial.print(reply);
      putObject();
    }
    else
    {
      serialControl(str);
    }
  }
}
