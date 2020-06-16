#include <xc.h> // include processor files - each processor file is guarded.  


//butoane
#define SST PORTAbits.RA0
#define PLUS PORTAbits.RA1
#define MINUS PORTAbits.RA2

#define PUSHED      1
#define NOT_PUSHED  0

// control L298
#define IN1 LATCbits.LATC4
#define IN2 LATCbits.LATC5
#define PWM CCPR2L


void config(void);
void pwm_config(void);

