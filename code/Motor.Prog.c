#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Motor_Config.h"
#include "DIO_init.h"
#include "timer_init.h"

#include <util/delay.h>
static u16 RightMotorSpeed;

/* Motor Initialization function of DIO Pins :
 * WE Control The Motors by L298N Module using 4 inputs pins
 * >>two pin(Int1,Int2)that control Left side motor set
 * >>two pin(Int3,Int4)that control Right side motor set */
void MOTOR_VoidInt(void)
{
    /*Set PortC Pin Direction as Output to initialize L298N*/
    DIO_VoidSet_Pin_Direction(DC_MOTOR_PORT, DC_MOTOR_PIN0, Output); // Int1  left
    DIO_VoidSet_Pin_Direction(DC_MOTOR_PORT, DC_MOTOR_PIN1, Output); // Int2  left
    DIO_VoidSet_Pin_Direction(DC_MOTOR_PORT, DC_MOTOR_PIN2, Output); // Int3  right
    DIO_VoidSet_Pin_Direction(DC_MOTOR_PORT, DC_MOTOR_PIN3, Output); // Int3  right
    DIO_VoidSet_Pin_Direction(OCR0_PORT, OCR0_PIN, Output);          // Int4  right
    DIO_VoidSet_Pin_Direction(OCR2_PORT, OCR2_PIN, Output);          // Int4  right
}

/* Motor Forward  Movement func*/
void MOTOR_VoidForward(void)
{
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, High); // Right Motor Set is Forward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, Low);

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, High); // Left Motor Set is Forward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, Low);
}
/* Motor Backward  Movement func*/
void MOTOR_VoidBackward(void)
{
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, Low); // Right Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, High);

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, Low); // Left Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, High);
}

/* Motor Right    Movement func*/
void MOTOR_VoidRight(void)
{

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, Low); // Right Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, High);

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, High);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, Low); // Left Motor Set is Forward
}

/* Motor Left  Movement func*/
void MOTOR_VoidLeft(void)
{
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, High);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, Low); // Right Motor Set is Forward

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, Low); // Left Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, High);
}

/* Motor Stop  Movement func*/
void MOTOR_VoidStop(void)
{
    RightMotorSpeed = 0;
    LeftMotor_VoidControlledSpeed(RightMotorSpeed * (1 / 10));
    RightMotor_VoidControlledSpeed(RightMotorSpeed);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, High); // Right Motors Set to low
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, High);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, High); // Left Motors Set to low
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, High);
}

void MOTOR_VoidRight90(void)
{

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, Low); // Right Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, High);

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, High);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, Low); // Left Motor Set is Forward
    _delay_ms(150);
    MOTOR_VoidStop();
    _delay_ms(150);
}

void MOTOR_VoidLeft90(void)
{
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN0, High); // Right Motor Set is Backward
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN1, Low);

    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN2, Low);
    DIO_VoidSet_Pin_Value(DC_MOTOR_PORT, DC_MOTOR_PIN3, High); // Left Motor Set is Forward
    _delay_ms(150);
    MOTOR_VoidStop();
    _delay_ms(150);
}
void MOTOR_VoidRevers()
{

    MOTOR_VoidLeft90();
    MOTOR_VoidLeft90();
}