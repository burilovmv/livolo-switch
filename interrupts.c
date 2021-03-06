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

#include "user.h"

#define DEPTH	64L

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

unsigned long avtemp;
int diff = 0;
extern int min_diff;

extern bool debug3;

void interrupt isr(void)
{
    if(T0IF) { // Timer0 overflow
        TMR1ON = 0; // Stop Timer1
        
        debug3 = true;
        
        uint16_t freq = TMR1H << 8 | TMR1L;
        
        if(freq<300) {
            DEBUG1 = 0;
        } else {
            DEBUG1 = 1; //Yellow
        }
        
        if(calibrating) {
            if(calibrate_step==0) {
                avg1 = freq;
            } else {
                avg1 = (avg1 + freq)/2;
            }            
            calibrate_step++;
            if(calibrate_step>100) {
                min_diff = avg1 / 10;
                if(min_diff<=0) {
                    min_diff = 5;
                }
                calibrating = false;
            }
        } else {
      		/*avtemp = (unsigned long)avg1*(DEPTH-1) + freq;
            avg1 = avtemp/DEPTH;
            
            if(avg1<freq) {
                avg1 = freq;
            }
            
            diff = avg1 - freq;
         
            if(diff<100) {
                DEBUG2 = 0;
            } else {
                DEBUG2 = 1;
            }*/
            
/*            if(avg1<freq) {
                avg1 = freq;
            } else {
                diff = avg1 - freq;        
                
                if(freq>50000) {
                    sw1_on = true;
                } else {
                    sw1_on = false;
                }                
            }*/
            
            if(freq>100) {
                sw1_on = false;
            } else {
                sw1_on = true;
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


