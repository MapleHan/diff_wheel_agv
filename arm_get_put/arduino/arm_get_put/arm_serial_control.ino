//#include <Servo.h>
#include<Servo.h>
#define MOTOR_COUNT 4
#define servoPin 55
#define RM  "rm"
#define UM  "um"
#define LM  "lm"
#define ZM  "zm"
#define RUN "run"
int pluae_pin[MOTOR_COUNT]={6,30,32,34};
int dir_pin[MOTOR_COUNT]={7,31,33,54};
bool ccw_dir[MOTOR_COUNT]={LOW,LOW,LOW,LOW};
Servo gripper;

void armSetup()
{
  delay(100);
  gripper.attach(servoPin);
  gripper.write(145);
  for(int i=0;i<MOTOR_COUNT;i++)
  {
    pinMode(pluae_pin[i],OUTPUT);
    pinMode(dir_pin[i],OUTPUT);
  }
}

void getObject()
{
  servo_move(145,100,1500);
  motorRotate(3,-30000);
  //motorRotate(1,-56000);
  motorRotate(2,42000);
  motorRotate(3,15000);
  servo_move(100,145,1500);
  motorRotate(3,-45000);
  motorRotate(2,-10000);
  //motorRotate(1,56000);
  two_move(30000);delay(500);
  motorRotate(2,-2000);
  motorRotate(3,30000);delay(500);
}

void putObject()
{
  numbers++;
  if(numbers%2 == 0)
  {
  motorRotate(3,500);   
  rm_lm(1,3,0,-40000);//motorRotate(3,-40000);  motorRotate(1,96500);
  //motorRotate(1,51000);
  motorRotate(2,-6000);
  motorRotate(3,23000);
  servo_move(150,100,2000);
  motorRotate_quickly(4,35000);
  motorRotate(3,-23000);

  //motorRotate(1,-91000);
  motorRotate(3,40000);
  motorRotate_quickly(4,-35000);
  motorRotate(2,6000);
  }
  /*else
  {
  motorRotate(3,-500);   
  rm_lm(1,3,40000,-40000);//motorRotate(3,-40000);  motorRotate(1,96500);
  motorRotate(1,51000);
  motorRotate(2,-6000);
  motorRotate(3,23000);
  servo_move(150,100,2000);
  motorRotate_quickly(4,35000);
  motorRotate(3,-23000);

  motorRotate(1,-91000);
  motorRotate(3,40000);
  motorRotate_quickly(4,-35000);
  motorRotate(2,6000); 
  }
  */
}

void rm_lm(int rm_pin,int lm_pin,int rm_steps,int lm_steps)
{
    if(rm_steps>0)
      digitalWrite(dir_pin[rm_pin-1],ccw_dir[rm_pin-1]);
    else
      digitalWrite(dir_pin[rm_pin-1],!ccw_dir[rm_pin-1]);
    if(lm_steps>0)
      digitalWrite(dir_pin[lm_pin-1],ccw_dir[lm_pin-1]);
    else
      digitalWrite(dir_pin[lm_pin-1],!ccw_dir[lm_pin-1]);      
      
  for(int j=0;j<abs(lm_steps);j++)
  {
      digitalWrite(pluae_pin[rm_pin-1],HIGH);
      digitalWrite(pluae_pin[lm_pin-1],HIGH);
    delayMicroseconds(70);
      digitalWrite(pluae_pin[rm_pin-1],LOW);
      digitalWrite(pluae_pin[lm_pin-1],LOW);
    delayMicroseconds(70);
  }  
}

void um_lm(int um_pin,int lm_pin,int um_steps,int lm_steps)
{
    if(um_steps>0)
      digitalWrite(dir_pin[um_pin-1],ccw_dir[um_pin-1]);
    else
      digitalWrite(dir_pin[um_pin-1],!ccw_dir[um_pin-1]);

    if(lm_steps>0)
      digitalWrite(dir_pin[lm_pin-1],ccw_dir[lm_pin-1]);
    else
      digitalWrite(dir_pin[lm_pin-1],!ccw_dir[lm_pin-1]);      
      

  for(int j=0;j<abs(um_steps);j++)
  {
    for( int k=um_pin-1;k<lm_pin;k++ )
    {
      digitalWrite(pluae_pin[k],HIGH);
    }
    delayMicroseconds(50);
    for( int l=um_pin-1;l<lm_pin;l++ )
    {
      digitalWrite(pluae_pin[l],LOW);
    }
    delayMicroseconds(50);
  }  
}

void serialControl(String command)
{
  int n_step =0;
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
}

//warning: id==0 all motor rotate
void motorRotate(int id,long n_step)
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

  for(long j=0;j<abs(n_step);j++)
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


void servo_move(int start,int finish,int TIME)
{
  int flag=0;
  if(start-finish<0) { flag = 1; }
  else { flag = -1; }
  for(int i=0;i<abs(start-finish);i++){
    gripper.write(start + flag*(i));
    delay( TIME / (abs(start-finish)) );
  }
}

void motorRotate_quickly(int id,int n_step)
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
    delayMicroseconds(15);
    for( int l=id;l<id1;l++ )
    {
      digitalWrite(pluae_pin[l],LOW);
    }
    delayMicroseconds(15);
  }
}
void two_move(int n_steps)
{
   digitalWrite(dir_pin[1],!ccw_dir[1]);
   digitalWrite(dir_pin[2],ccw_dir[2]);
   for(int j=0;j<abs(n_steps);j++)
   {
     for( int k=1;k<3;k++ ){
       digitalWrite(pluae_pin[k],HIGH);
     }
     delayMicroseconds(50);
     for( int l=1;l<3;l++ ){
       digitalWrite(pluae_pin[l],LOW);
     }
     delayMicroseconds(50);
   }
}
