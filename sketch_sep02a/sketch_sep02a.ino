//Erros for PID
int prevError = 0;
int currError;

//P I D
float P = 0;
float I = 0;
float D = 0;

//PID stuff again
int currPos;
float correction;

//PID constants
const float Kp = 0;
const float Kd = 0;
const float Ki = 0;

//The normal speed is 255, we are taking normalSpeed instant
const int normalSpeed = 133;

//speeds for 2 motors
int speed1;
int speed2;

// connected to motor driver
int MH1 = A0;
int MH2 = A0;
int ML1 = A2;
int ML2 = A3;
int E1 = 9;
int E2 = 10;

//we get values from 7 IR sensor pairs into values
int values[6];
int count;

//target for PID
const int targetPos = 4;


//Setup for arduino
void setup()
{       //setup input IR sensor pairs.
        for(int i=2;i<9;i++)
                {
                        pinMode(i, INPUT);
                }
        //setup motor driver pins
        pinMode(E1, OUTPUT);
        pinMode(E2, OUTPUT);
        pinMode(MH1, OUTPUT);
        pinMode(MH2, OUTPUT);
        pinMode(ML1, OUTPUT);
        pinMode(ML2, OUTPUT);
        //keep one end of each motor HIGH, and other low. (through motor driver)
        digitalWrite(ML1, LOW);
        digitalWrite(ML1, LOW);
        digitalWrite(MH1, HIGH);
        digitalWrite(MH2, HIGH);
}

void loop()
{
        currPos = getCurrentPos();
        correction = calcPID(currPos);
        speed1 = normalSpeed - correction;
        speed2 = normalSpeed + correction;
        analogWrite(E1, speed1);
        analogWrite(E2, speed2);
}

int getCurrentPos()
{
        for(int i=2;i<9;i++)
                {       
                        values[i-2] = digitalRead(i);
                        if(values[i-2] == HIGH)
                            count++;
                }
        int j;
        j = returnInput(values, count);
        return j;
}//getting the current position as an integer

int calcPID(int c)
{
        currError = targetPos - c;
        P = currError*Kp;
        I = I + currError;
        I = I*Ki;
        D = currError - prevError;
        D = D*Kd;
        int corr = P+I+D;
        return (int)corr;
}//returns the correction in speed as an integer

int returnInput(int a[], int count)
{
    if(count == 0)
        return 4;
    else if(count >= 5)
        return 4;
    else{
        for(int i=0; i<4; i++)
            if(a[i] == HIGH)
                return i;
        
        for(int i=8; i>4; i--)
            if(a[i] == HIGH)
                return i;

    }
    return 4;
}
