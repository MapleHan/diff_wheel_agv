
#define MOTOR_COUNT 5
#define RM  "rm"
#define UM  "um"
#define LM  "lm"
#define ZM  "zm"
#define SM  "sm"
#define RUN "run"
#define EN   59
int pluae_pin[MOTOR_COUNT]={6,30,32,34,60};
int dir_pin[MOTOR_COUNT]={7,31,33,54,58};
bool ccw_dir[MOTOR_COUNT]={LOW,LOW,LOW,LOW,LOW};

void setup()
{
  // put your setup code here, to run once:
  delay(100);
  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  for(int i=0;i<MOTOR_COUNT;i++)
  {
    pinMode(pluae_pin[i],OUTPUT);
    pinMode(dir_pin[i],OUTPUT);
  }
  Serial.begin(115200);
  Serial.println("Calibration begin ... ...");
  String command = "ready";
  int n_step =0;
  while(command!=RUN)
  {
    command=""; 
    while(Serial.available())
    {
      command+=(char)Serial.read();
      delay(5);
    }
    int index = command.indexOf(' ');
    if(index!=-1)
    {
      n_step = command.substring(index+1).toInt();
      command = command.substring(0,index);
      Serial.print(command);
      Serial.print('\t');
      Serial.println(n_step);
    }

    if(command==RM){
      Serial.println("Motor1...");
      motorRotate(1,n_step);
    }
    else if(command==UM){
      Serial.println("Motor2...");
      motorRotate(2,n_step);
    }
    else if(command==LM){
      Serial.println("Motor3...");
      motorRotate(3,n_step);
    }
    else if(command==ZM){
      Serial.println("Motor4..");
      motorRotate(4,n_step);
    } 
    else if(command==SM){
      Serial.println("Motor5...");
      motorRotate(5,n_step);
    }   
  }
  //#Serial.println("Calibration Finish!!! begin CCW CW Rotate");
  //#motorRotate(0,40000);
  //#delay(1000);
  //#Serial.println("Calibration Finish!!! begin CCW CW Rotate");
}

void loop() 
{
  Serial.println("All Motor CW");
  motorRotate(0,-80000);
  delay(1000);
  Serial.println("All Motor CCW");
  motorRotate(0,80000);
  delay(1000);
}

//warning: id==0 all motor rotate
void motorRotate(int id,int n_step)
{
  if( (id>MOTOR_COUNT)||(id<0) )
    return;
  int id1=id;
  if(id==0)
  {
    id1=MOTOR_COUNT;
  }
  else
    id-=1;
  for( int i=id;i<id1;i++ )
  {
    if(n_step>0)
      digitalWrite(dir_pin[i],ccw_dir[i]);
    else
      digitalWrite(dir_pin[i],!ccw_dir[i]);
  }

  for(int j=0;j<abs(n_step);j++)
  {
    for( int k=id;k<id1;k++ )
    {
      digitalWrite(pluae_pin[k],HIGH);
    }
    delayMicroseconds(50);
    for( int l=id;l<id1;l++ )
    {
      digitalWrite(pluae_pin[l],LOW);
    }
    delayMicroseconds(50);
  }
}
