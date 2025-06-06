#ifndef MOTOR_INIT_H
#define MOTOR_INIT_H

/*Description:
 * we need to build 6 function to control the motor movement:
 *  1-Motor Initialization of DIO Pins
 *  2-Motor Forward  Movement
 *  3-Motor Backward Movement
 *  4-Motor Right    Movement
 *  5-Motor Left     Movement
 *  6-Motor Stop     Movement
 */

/* Motor Initialization function of DIO Pins */
void MOTOR_VoidInt(void);

/* Motor Forward  Movement prototype of func*/
void MOTOR_VoidForward(void);

/* Motor Backward  Movement prototype of func*/
void MOTOR_VoidBackward(void);

/* Motor Right    Movement prototype of func*/
void MOTOR_VoidRight(void);

/* Motor Left  Movement prototype of func*/
void MOTOR_VoidLeft(void);

/* Motor Stop  Movement prototype of func*/
void MOTOR_VoidStop(void);

#endif
