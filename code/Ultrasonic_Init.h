

#ifndef ULTRASONIC_INIT_H_
#define ULTRASONIC_INIT_H_

#define FRE_CPU 1000000UL

extern u16 Global_u16ReadingDistance;

void ULTRASONIC_VidInit(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin);

/*Trigger function that initializes sound signal of Ultrasonic sensor*/
void ULTRASONIC_VidIniti_Trigger(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin);

/*This function calculate the distance of object depending on echo signal on_period*/
u16 ULTRASONIC_u16EchoDistance(void);

/* Set The properties of ultrasonic */
void ULTRASONIC_VidSetup(void);

#endif
