#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "GIE_init.h"
#include "UART_init.h"
#include "Motor_Init.h"
#include "timer_init.h"
#include "Ultrasonic_Init.h"
#include <util/delay.h>

#define MIN_ANGLE 10
#define DEFAULT_SERVO_ANGLE 110
#define RIGHT_SERVO_ANGLE 0
#define LEFT_SERVO_ANGLE 210
#define SAVE_DISTANCE 25
#define LOW_SPEED 35
#define HIGH_SPEED 65
#define MAX_SPEED 100
#define SPEEDFACTOR 10
#define USART_PORT Port_D
#define USART_RX_PIN PIN_0
#define USART_TX_PIN PIN_1

#define DC_MOTOR_PORT Port_A
#define DC_MOTOR_PIN0 PIN_0
#define DC_MOTOR_PIN1 PIN_1
#define DC_MOTOR_PIN2 PIN_2
#define DC_MOTOR_PIN3 PIN_3

#define SERVO_MOTOR_CONTROL_PORT PORT_D
#define SERVO_MOTOR_CONTROL_PIN PIN_4

#define ULTRASONIC_ECHO_PORT Port_D
#define ULTRASONIC_ECHO_PIN Pin_6
#define ULTRASONIC_TRIGGER_PORT Port_D
#define ULTRASONIC_TRIGGER_PIN Pin_5

#define IR_MID_PORT Port_C
#define IR_MID_PIN Pin_0
#define IR_MID_RIGHT_PORT Port_C
#define IR_MID_RIGHT_PIN Pin_2
#define IR_MID_LEFT_PORT Port_C
#define IR_MID_LEFT_PIN Pin_3
#define IR_RIGHT_PORT Port_C
#define IR_RIGHT_PIN Pin_4
#define IR_LEFT_PORT Port_C
#define IR_LEFT_PIN Pin_5

u16 Global_u16DistanceReading_Right = 0;
u16 Global_u16DistanceReading_Left = 0;
u8 Local_u8Mode = 0;
u8 Bug = 0;
static u16 RightMotorSpeed = 100;

void init();
void RobotCar_VoidControlMode();
void RobotCar_VoidLogic_Comparison(u16 Copy_u16Left, u16 Copy_u16Right);
u8 RobotCar_u8CalcDir(u8 MidIR, u8 MidLeftIR, u8 MidRightIR, u8 RightIR, u8 LeftIR);
void ISR(void);
void ISR(void)
{
    return;
}

int main()
{
    init();
    while (1)
    {
        /* Select mode  */
        u8 Local_u8Mode;
        USART_u8SendStringSynchronous("\n************************************************\n");
        USART_u8SendStringSynchronous("Choose your mode\n  a-For Control Mode\n  b-Avoiding and Random Search Mode\n  c-Line Follower Mode\n ");
        USART_u8SendStringSynchronous("*************************************************\n");
        USART_u8ReceiveDataSynchronous(&Local_u8Mode);
        switch (Local_u8Mode)
        {
        /*Calling Function For Control Mode */
        case 'a':
            RobotCar_VoidControlMode();
            break;
        /*Calling Function For Avoiding and Random Search Mode*/
        case 'b':
            RobotCar_VidAvoidingRandomSearchMode();
            break;
        /*Calling Function For Line Follower Mode */
        case 'c':
            RobotCar_VidALineFolloingMode();
            break;

            /*	  default: USART_VidSendString("*********** Worng_Input ***********\n");break;*/
        }
    }
}

void RobotCar_VoidControlMode()
{

    u8 Local_u8DataControl;
    USART_u8SendStringSynchronous("\n********* Welcome To Control Mode ************\n");
    RightMotorSpeed = 75;
    LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
    RightMotor_VoidControlledSpeed(RightMotorSpeed);
    while (1)
    {
        USART_u8ReceiveDataSynchronous(&Local_u8DataControl);

        switch (Local_u8DataControl)
        {
            /******************* Direction_Control  *******************************/
        case 'F':
            MOTOR_VoidForward();
            break;
        case 'B':
            MOTOR_VoidBackward();
            break;
        case 'R':
            MOTOR_VoidRight();
            break;
        case 'L':
            MOTOR_VoidLeft();
            break;
        case 'S':
            MOTOR_VoidStop();
            break;
        /*************************  Speed    *************************************/
        case '1':
            RightMotorSpeed = 10;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '2':
            RightMotorSpeed = 20;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '3':
            RightMotorSpeed = 30;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '4':
            RightMotorSpeed = 40;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '5':
            RightMotorSpeed = 50;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '6':
            RightMotorSpeed = 60;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '7':
            RightMotorSpeed = 70;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '8':
            RightMotorSpeed = 80;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case '9':
            RightMotorSpeed = 90;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;
        case 'm':
            RightMotorSpeed = 100;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            break;

            /* default: USART_VidSendString("\n************** Wrong Input ****************\n");break;*/
        }
    }
}
void RobotCar_VidAvoidingRandomSearchMode(void)
{
    u8 Local_u8data = 0;

    USART_u8SendStringSynchronous("\n********* Welcome To Avoiding Mode ************\n");
    while (1)
    {
        Global_u16ReadingDistance = ULTRASONIC_u16EchoDistance();
        _delay_ms(25);

        USART_u8ReceiveDataAsynchronous(&Local_u8data, ISR);

        if ((Local_u8data == 's'))
        {
            MOTOR_VoidStop();
            break;
        }
        if (Global_u16ReadingDistance == 0)
        {
            Global_u16ReadingDistance = 255;
        }

        /*IF distance is less than save distance stop and look for save region
         */

        if (Global_u16ReadingDistance <= SAVE_DISTANCE)
        {

            /*
            In this condition the robot will execute the following instructions
                1- Make the servo move right and left
                2- Measure the distance at each side
                3- compare the distance and then move right or left
            */
            RightMotorSpeed = 100;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);

            MOTOR_VoidStop();
            _delay_ms(50);
            MOTOR_VoidBackward();
            _delay_ms(200);
            MOTOR_VoidStop();
            _delay_ms(50);

            TIMER1_VidSetServo_AngleWith_OCR1BL(LEFT_SERVO_ANGLE);
            _delay_ms(1000);
            Global_u16DistanceReading_Left = ULTRASONIC_u16EchoDistance();
            _delay_ms(200);

            TIMER1_VidSetServo_AngleWith_OCR1BL(RIGHT_SERVO_ANGLE);
            _delay_ms(1000);
            Global_u16DistanceReading_Right = ULTRASONIC_u16EchoDistance();
            _delay_ms(200);

            TIMER1_VidSetServo_AngleWith_OCR1BL(DEFAULT_SERVO_ANGLE);
            _delay_ms(500);
            RobotCar_VoidLogic_Comparison(Global_u16DistanceReading_Left, Global_u16DistanceReading_Right);
        }

        else
        {

            DIO_VoidSet_Pin_Value(Port_B, Pin_0, High);
            RightMotorSpeed = LOW_SPEED;
            LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
            RightMotor_VoidControlledSpeed(RightMotorSpeed);
            MOTOR_VoidForward();
        }
    }
}

/* Comparison Function */
void RobotCar_VoidLogic_Comparison(u16 Copy_u16Left, u16 Copy_u16Right)
{
    if ((Copy_u16Right >= Copy_u16Left) && (Copy_u16Right >= SAVE_DISTANCE))
    {
        MOTOR_VoidRight90();
    }
    /* Apply following instructions if the save distance is in Left region*/
    else if ((Copy_u16Left >= Copy_u16Right) && (Copy_u16Left >= SAVE_DISTANCE))
    {
        MOTOR_VoidLeft90();
    }

    else if ((Copy_u16Right < SAVE_DISTANCE) && (Copy_u16Left < SAVE_DISTANCE))
    {
        MOTOR_VoidRevers();
    }
}

void RobotCar_VidALineFolloingMode(void)
{
    u8 MidIR = 0, MidLeftIR = 0, MidRightIR = 0, RightIR = 0, LeftIR = 0, Local_u8data;

    while (1)
    {
        USART_u8ReceiveDataAsynchronous(&Local_u8data, ISR);

        if ((Local_u8data == 's'))
        {
            MOTOR_VoidStop();
            break;
        }
        DIO_VoidGet_Pin_Value(IR_MID_PORT, IR_MID_PIN, &MidIR);
        DIO_VoidGet_Pin_Value(IR_MID_RIGHT_PORT, IR_MID_RIGHT_PIN, &MidRightIR);
        DIO_VoidGet_Pin_Value(IR_MID_LEFT_PORT, IR_MID_LEFT_PIN, &MidLeftIR);
        DIO_VoidGet_Pin_Value(IR_RIGHT_PORT, IR_RIGHT_PIN, &RightIR);
        DIO_VoidGet_Pin_Value(IR_LEFT_PORT, IR_LEFT_PIN, &LeftIR);
        u8 dir = RobotCar_u8CalcDir(MidIR, MidLeftIR, MidRightIR, RightIR, LeftIR);
        // car is good
        if (dir == 0)
        {
            MOTOR_VoidForward();
        }
        // no line stop the car
        else if (dir == 1)
        {
            MOTOR_VoidStop();
            MOTOR_VoidRevers();
        }
        // rotate left 10 degrees
        else if (dir == 2)
        {
            MOTOR_VoidLeft();
        } // rotage right 10 degrees
        else if (dir == 3)
        {
            MOTOR_VoidRight();
        }
        MOTOR_VoidStop();
    }
}

u8 RobotCar_u8CalcDir(u8 MidIR, u8 MidLeftIR, u8 MidRightIR, u8 RightIR, u8 LeftIR)
{
    if (MidLeftIR == 0 && MidRightIR == 0 && MidIR == 1)
        return 0;
    if (MidLeftIR == 0 && MidRightIR == 0 && MidIR == 0)
        return 1;
    if (MidLeftIR == 1 && MidIR == 0)
        return 2;
    if (MidRightIR == 1 && MidIR == 0)
        return 3;
}

void init()
{
    Timer0_VidInit();
    Timer2_VidInit();
    MOTOR_VoidInt();
    TIMER0_voidGenFastPWM(100);
    TIMER2_voidGenFastPWM(100);
    RightMotorSpeed = 100;
    LeftMotor_VoidControlledSpeed(RightMotorSpeed * (SPEEDFACTOR / 10));
    RightMotor_VoidControlledSpeed(RightMotorSpeed);
    Timer1_VidInit();
    DIO_VoidSet_Pin_Direction(Port_D, Pin_4, Output);
    TIMER1_VidSetServo_AngleWith_OCR1BL(DEFAULT_SERVO_ANGLE);
    USART_VidInit();
    GIE_VidEnable();
    ULTRASONIC_VidInit(Port_D, Pin_5);
    DIO_VoidSet_Pin_Direction(IR_MID_PORT, IR_MID_PIN, Input);
    DIO_VoidSet_Pin_Direction(IR_RIGHT_PORT, IR_RIGHT_PIN, Input);
    DIO_VoidSet_Pin_Direction(IR_LEFT_PORT, IR_LEFT_PIN, Input);
    DIO_VoidSet_Pin_Direction(IR_MID_RIGHT_PORT, IR_MID_RIGHT_PIN, Input);
    DIO_VoidSet_Pin_Direction(IR_MID_LEFT_PORT, IR_MID_LEFT_PIN, Input);
}