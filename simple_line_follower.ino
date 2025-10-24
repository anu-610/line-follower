// C++ code


#define IR_LM 12
#define IR_L 11
#define IR_C 10
#define IR_R 9
#define IR_RM 8


#define EN1 6
#define EN2 5
#define INP1 2
#define INP2 3
#define INP3 4
#define INP4 7


int full_speed = 200;
int slight_turn_speed = 100;
int sharp_speed = 50;
int sharp_90_speed = 0;




void setMotors(int left_speed, int right_speed)
{
  digitalWrite(INP1, HIGH);
  digitalWrite(INP2, LOW);
  analogWrite(EN1, right_speed);
  
  digitalWrite(INP3, HIGH);
  digitalWrite(INP4, LOW);
  analogWrite(EN2, left_speed);
}

void goForward()
{
  setMotors(full_speed, full_speed);
  Serial.println("Going Forward");
}

void goLeftSlight()
{
  setMotors(slight_turn_speed, full_speed);
  Serial.println("Going slightly left");
}

void goRightSlight()
{
  setMotors(full_speed, slight_turn_speed);
  Serial.println("Going slighly right");
}
  
void goRightHard()
{
  setMotors(full_speed, sharp_speed);
  Serial.println("Going right quickly");
}

void goLeftHard()
{
  setMotors(sharp_speed, full_speed);
  Serial.println("Going left quickly");
}

void goRight90()
{
  setMotors(full_speed, sharp_90_speed);
  Serial.println("taking 90 degree turn to right");
}

void goLeft90()
{
  setMotors(sharp_90_speed, full_speed);
  Serial.println("taking 90 degree turn to left");
}


void stopMotor()
{
  setMotors(0,0);
  Serial.println("Stopped");
}
void setup()
{
  pinMode(IR_LM, INPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_C, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(IR_RM, INPUT);
  
  
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(INP1, OUTPUT);
  pinMode(INP2, OUTPUT);
  pinMode(INP3, OUTPUT);
  pinMode(INP4, OUTPUT);
  
  
  Serial.begin(9600);
  Serial.print("Begin");
}

void loop()
{
  int ir_lm = digitalRead(IR_LM);
  int ir_l = digitalRead(IR_L);
  int ir_c = digitalRead(IR_C);
  int ir_r = digitalRead(IR_R);
  int ir_rm = digitalRead(IR_RM);
  
  Serial.println("--------------------------------------");
  Serial.println(ir_lm);
  Serial.println(ir_l);
  Serial.println(ir_c);
  Serial.println(ir_r);
  Serial.println(ir_rm);
  Serial.println("---------------------------------------");
  if (ir_lm==1 && ir_l==1 && ir_c ==0 && ir_r==1 && ir_rm==1) //Go straight
  {
    //Serial.println("1");
    goForward();
  }
  else if (ir_lm==1 && ir_l==1 && ir_c ==1 && ir_r==0 && ir_rm==1) //If slighly on left of track
  {
    goRightSlight();
    //Serial.println("2");
  }
  else if (ir_lm==1 && ir_l==0 && ir_c ==1 && ir_r==1 && ir_rm==1)// If slightly on right of track
  {
    goLeftSlight();
    //Serial.println("3");
  }
  else if (ir_lm==1 && ir_l==1 && ir_c ==1 && ir_r==1 && ir_rm==0)// If greater part is on left of track
  {
    goRightHard();
    //Serial.println("4");
  }
  else if (ir_lm==0 && ir_l==1 && ir_c ==1 && ir_r==1 && ir_rm==1)// If greater part is on right of track
  {
    goLeftHard();
    //Serial.println("5");
  }
  else if (ir_lm==0 && ir_l==0 && ir_c ==0)//If there is a 90 degree turn to Left
  {
    goLeft90();
    //Serial.println("6");
  }
  else if (ir_c ==0 && ir_r==0 && ir_rm==0)//If there is a 90 degree turn to right
  {
    goRight90();
    //Serial.println("7");
  }
  else{
    stopMotor();
    //Serial.println("8");
  }
  
  
}


