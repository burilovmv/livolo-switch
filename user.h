/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define LED1 RB6
#define LED2 RC5
#define RELAY1 RC6
#define RELAY2 RC7

#define DATA1 RB4 // This is DATA in original circuit
#define DATA2 RB5 // This is DER in original circuit

#define S1_ENABLE 1
//#define S2_ENABLE 1 // Uncomment to enable switch 2

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
