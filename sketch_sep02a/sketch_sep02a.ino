
int prevError = 0;
int currError;
float P = 0;
float I = 0;
float D = 0;
int currPos;
float correction;
const float Kp = 0;
const float Kd = 0;
const float Ki = 0;
const int normalSpeed = 133;
int speed1;
int speed2;
int M1 = 10;
int M2 = 11;
const int targetPos = 4;
int Mm1 = 9;
int Mm2 = 12;
//end global variable declaration

void setup()
{
        for(int i=2;i<9;i++)
                {
                        pinMode(i, INPUT);
                }
        pinMode(M1, OUTPUT);
        pinMode(M2, OUTPUT);
        pinMode(Mm1, OUTPUT);
        pinMode(Mm2, OUTPUT);

        digitalWrite(Mm1, LOW);
        digitalWrite(Mm2, LOW);

}

void loop()
{
        currPos = getCurrentPos();
        correction = calcPID(currPos);
        speed1 = normalSpeed - correction;
        speed2 = normalSpeed + correction;
        analogWrite(M1, speed1);
        analogWrite(M2, speed2);
}

int getCurrentPos()
{
        for(int i=2;i<9;i++)
                {
                        int j = digitalRead(i);
                        if(j==HIGH)
                                return i;
                 }
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