#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Ultrasonic_Init.h"
#include "DIO_init.h"
#include "timer_init.h"
#include <util/delay.h>

u16 ULTRASONIC_u16TimeON = 0;

u16 Global_u16ReadingDistance = 0;

void ULTRASONIC_VidInit(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin)
{ /* Initialize ICU */
    TIMER1_Vid_ICU_Init();
    /*Call ICU Callback Function */
    Timer1_u8SetCallBackForCaptureEvent(&ULTRASONIC_VidSetup);

    /* Set Port Direction Of trigger pin and echo pin */
    DIO_VoidSet_Pin_Direction(Copy_u8TriggerPort, Copy_u8TriggerPin, Output);
    DIO_VoidSet_Pin_Value(Copy_u8TriggerPort, Copy_u8TriggerPin, Low);
    /*Set Pin6 in PortD(ICR1L Pin) AS  Input */
    DIO_VoidSet_Pin_Direction(Port_D, Pin_6, Input);
}

/*Trigger function that initializes sound signal of ultrasonic sensor*/
void ULTRASONIC_VidIniti_Trigger(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin)
{
    DIO_VoidSet_Pin_Value(Copy_u8TriggerPort, Copy_u8TriggerPin, High);
    _delay_us(20);
    DIO_VoidSet_Pin_Value(Copy_u8TriggerPort, Copy_u8TriggerPin, Low);
}

/*This function calculate the distance of object depending on echo signal on_period*/
u16 ULTRASONIC_u16EchoDistance(void)
{
    u16 Local_u16Distance = 0;

    for (u8 Local_u8Couter = 0; Local_u8Couter < 16; Local_u8Couter++)
    {
        /* Initialize Ultrasonic Trigger */
        ULTRASONIC_VidIniti_Trigger(Port_D, Pin_5);
        Local_u16Distance = (34300 * ULTRASONIC_u16TimeON) / (2 * FRE_CPU);
    }
    return Local_u16Distance;
}

/*Set The properties of ultrasonic */

void ULTRASONIC_VidSetup(void)
{
    static u8 Local_u8Counter = 0;
    Local_u8Counter++;

    if (Local_u8Counter == 1)
    {
        TIMER1_voidSetPreLoadValue(0);
        Timer1_VoidICUSetTriggerEdge(TIMER_1_INPUTCAPTURE_FALLINGEDGE);
    }
    else if (Local_u8Counter == 2)
    {
        ULTRASONIC_u16TimeON = Timer1_u16ReadInputCaptureUnit();
        TIMER1_voidSetPreLoadValue(0);
        Local_u8Counter = 0;
        Timer1_VoidICUSetTriggerEdge(TIMER_1_INPUTCAPTURE_RISINGEDGE);
    }
}
