/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include <pic.h>
#include <pic16f690.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

bool sw1_on = false;
bool sw2_on = false;

bool sw1_prev = false;
bool sw2_prev = false;

bool check_switch(int num);

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    for(int i=0;i<9;i++) {
        LED1 = !LED1;
        __delay_ms(100);
    }
    //TODO: calibrate!
    
    LED1 = 1;
    LED2 = 0;
#ifdef S1_ENABLE
    RELAY1 = 0;
#endif
#ifdef S2_ENABLE
    RELAY2 = 0;
#endif
    
    while(1)
    {
        bool sw1 = check_switch(1);
        if(sw1_prev!=sw1) {
            sw1_on=!sw1_on;
            LED1 = sw1_on;
            RELAY1 = sw1_on;
            
            sw1_prev = sw1;
        }        
    }
}

bool check_switch(int num) {
    TMR0 = 0;
    __delay_ms(20); //TODO: configurable!
    uint8_t raw = TMR0;
    
    if(raw<50) 
    { //TODO: calibrate!
        return true;
    }
    
    return false;
}