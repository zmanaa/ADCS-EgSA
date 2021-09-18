#define dataSize 12
#define CONTAINER_SIZE 3 // 0 reqSpdValue, 1 motorStopFlag, 2 CW flag, 3 CCW flag

#define rightIS 2
#define leftIS 3
#define rightEnable 4
#define leftEnable 5
#define rightPWM 6
#define leftPWM 7
#define debug 0 // to hide serial monitor info for the motor driver
#define CW 1
#define CCW 0

// objects
MPU6050 mpu;
RobojaxBTS7960 motor(rightEnable,rightPWM,rightIS, leftEnable,leftPWM,leftIS,debug);

int dirFlag = 1;
int stopMotorFlag = 0;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float yaw       = 0;
float angularSpeed  = 0;

// Union
typedef union {
   struct{
    float y;
    float spd;
    float timeValue;
   }data;
   byte dataStream[dataSize] ;
}dataUnion;

uint8_t  reqSpdValue = 0; float kp_spd = 1.1, ki_spd = 1.5, kd_spd=0.3, e_spd = 0, ePrev_spd = 0, E_spd = 0, dE_spd = 0;
uint8_t reqAngValue = 0;  float kp_ang = 1, kd_ang = 0.3, ki_ang = 1.1, e_ang = 0, ePrev_ang = 0, E_ang = 0, dE_ang = 0;

dataUnion ypr;
byte startCommFlag = 0;
byte programStatus = 0;   // speed mode, angle mode.
