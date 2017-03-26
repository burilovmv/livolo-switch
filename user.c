/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic16f690.h>
#include <pic16f690.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    ANSEL = 0;
    ANSELH = 0; // Disable analog select
    WPUA = 0;
    WPUB = 0;   
    
    PORTA = 0;
    TRISA = 0x04;
    PORTB = 0;
    TRISB = 0x20;
    PORTC = 0;
    
    /* Initialize peripherals */
    OPTION_REG = 0xb1; //TODO: What is it?
    CM1CON0 = 0x95;
    CM2CON0 = 0xa5;
    CM2CON1 = 0;
    SRCON = 0xF0;
    VRCON = 0x87;    
    
    /* Enable interrupts */
    IOCA = 0;
    INTCON = 0;
}

