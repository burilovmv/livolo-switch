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
    OPTION_REG = 0b00101000; // pullups disabled, T0CKI is input for TMR0, prescaler applied to WDT
    
    /* Setup analog functionality and port direction */
    ANSEL = 0b10100000; // Select AN5/AN7 as analog inputs
    ANSELH = 0;
    
    TRISA = 0b00000110; // All A ports are outputs
    PORTA = 0;

    TRISB = 0b10110000; //RB7, RB5, RB4 are inputs, other are outputs
    PORTB = 0;
    
    TRISC = 0b00000000; // All C ports are outputs
    PORTC = 0;
    
    /* Initialize peripherals */
    CM1CON0 = 0b10100111;
    CM2CON0 = 0b10100100;   // C2 is enabled and output to C2OUT, input=AN1/RA1/pin18
    CM2CON1 = 0b00000011;   // C2 uses Timer1, both comparator outputs enabled, C2 synchronized with TMR1
    
    /* Enable interrupts */
    INTCON = 0b10100000; // Enable interrupts, enable TMR0 interrupt
    T1CON = 0b00000000;     // use internal clock for Timer1    
}

