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
    OPTION_REG = 0b11101000; // pullups disabled, T0CKI is input for TMR0, prescaler 1:2 applied to WDT
    VRCON = 0b10111111; // Vref settings: C1=2.1v,C2=0.6v
    SRCON = 0b11110000; // SR Latch settings: enabled, C1 sets, C2 resets
    
    /* Setup analog functionality and port direction */
    ANSEL = 0b10100000; // Select AN5/AN7 as analog inputs
    ANSELH = 0;
    
    TRISA = 0b00000000; // All A ports are outputs
    PORTA = 0;

    TRISB = 0b10110000; //RB7, RB5, RB4 are inputs, other are outputs
    PORTB = 0;
    
    TRISC = 0b00001010; //RC1,RC3 are inputs
    PORTC = 0;
    
    /* Initialize peripherals */
    CM1CON0 = 0b10100111;   // C1: pulse if AN7 > Vref=2.1v
    CM2CON0 = 0b10110111;   // C2: pulse if AN7 < Vref=0.6v
    CM2CON1 = 0b00110010; //0b00000001;   // C2Out from SR Latch, C1Out from C1, 
    
    /* Enable interrupts */
    INTCON = 0b10100000; // Enable interrupts, enable TMR0 interrupt
    T1CON = 0b00111000;     // use internal clock for Timer1, do not use TMR1 Gate
}

