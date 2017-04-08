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
int min_diff = 20;

int avg1 = 0;
int avg2 = 0;

int calibrate_step = 0;
bool calibrating = true;

bool sw1_on = true;
bool sw2_on = false;

bool sw1_prev = false;
bool sw2_prev = false;

bool debug3 = false;

void delay(uint8_t time);

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    
    delay(100); // wait for oscillator settings to be in effect

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    //RA1 = 0; // This is our VRef for C2.
    
    delay(50); // wait a little
    
    T0IF = 0; // Start timers
    TMR1ON = 1;

    DEBUG1 = 0;
    DEBUG2 = 0;
    DEBUG3 = 1;
    
    while(1)
    {
        if(calibrating) {
            if(LED1==0) {
                LED1 = 1;
            } else {
                LED1 = 0;
            }
            delay(50);
        } else {
            if(debug3) {
                DEBUG3 = !DEBUG3;
            } else {
                PULSR = 1;
            }
            debug3 = false;
            
            if(sw1_on!=sw1_prev) {
                LED1 = sw1_on;
                //RELAY1 = sw1_on;
                
                sw1_prev = sw1_on;
            }
            delay(20);
        }
    }
}

void delay (uint8_t time) {
  uint8_t temp1, temp2;
  
  temp1 = time;
  while(temp1--) {
     temp2 = 249;
     while(temp2--) {
        NOP();
        NOP();
        NOP();
        NOP();
     }
   }
}