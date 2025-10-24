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



void setMotors(int left_speed, int right_speed)
{
    digitalWrite(INP1, HIGH);
    digitalWrite(INP2, LOW);
    analogWrite(EN1, right_speed);
  
    digitalWrite(INP4, LOW);
    digitalWrite(INP3, HIGH);
    analogWrite(EN2, left_speed);
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



}


int base_speed = 150;


double kp = 1; 
double kd = 0;
double ki = 0;

int error;
double prop_term;
double der_term;
double integral_term = 0;
double prev_error = 0;

double correction;

void loop()
{
    int IR1 = digitalRead(IR_LM);
    int IR2 = digitalRead(IR_L);
    int IR3 = digitalRead(IR_C);
    int IR4 = digitalRead(IR_R);
    int IR5 = digitalRead(IR_RM);

    if((IR1==1 && IR2==1 & IR3==1 && IR4==1 && IR5==1) || IR1==0 && IR2==0 && IR3==0 && IR4==0 && IR5==0)
    {
        //Turn of the robot
        setMotors(0, 0);

    }
    else
    {
        error = IR1 * (-2) + IR2 * (-1) + IR4 * (1) + IR5 * (2);
        Serial.print("Error: ");
        Serial.println(error);

        prop_term = (kp * error);
        integral_term += (ki * error);
        der_term = kd * (error-prev_error) ;

        prev_error = error;

        correction = -1*(prop_term + integral_term + der_term);
        Serial.print("Correction: ");
        Serial.println(correction);


        int left_speed = base_speed - correction;
        int right_speed = base_speed + correction;


        left_speed = constrain(left_speed, 0, 255);
        right_speed = constrain(right_speed, 0, 255);

        setMotors(left_speed, right_speed);
    }

}