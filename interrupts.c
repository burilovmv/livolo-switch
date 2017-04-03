/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

extern int avg1;
extern int avg2;

extern bool sw1_on;
extern bool sw2_on;

extern int calibrate_step;
extern bool calibrating;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

int diff = 0;
extern int min_diff;

void interrupt isr(void)
{
    if(T0IF) { // Timer0 overflow
        TMR1ON = 0; // Stop Timer1
        
        uint16_t freq = TMR1H << 8 | TMR1L;
        
        if(calibrating) {
            if(calibrate_step==0) {
                avg1 = freq;
            } else {
                avg1 = (avg1 + freq)/2;
            }            
            calibrate_step++;
            if(calibrate_step>10) {
                min_diff = avg1 / 10;
                if(min_diff<=0) {
                    min_diff = 5;
                }
                calibrating = false;
            }
        } else {
            diff = avg1 - freq;
            
            if(diff>20) {
                sw1_on = !sw1_on;
            }
               //avg1 = (9*avg1 + freq)/10;
            
            
            /*if(diff>20) {
                sw1_on = !sw1_on;
            }*//* else {
                if(!sw1_on) {
                    sw1_on = true;
                }
            }*/           
            
        }
        
        TMR1L = 0; //Reset Timer1
        TMR1H = 0; 
        
        TMR1ON = 1; // Restart Timer1
        T0IF = 0;   // Reset Timer0
    }
}
#endif


