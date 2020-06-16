#include <xc.h> // include processor files - each processor file is guarded.  


//butoane
#define SST PORTAbits.RA0
#define PLUS PORTAbits.RA1
#define MINUS PORTAbits.RA2

// control L298
#define ENA LATAbits.LATA5
#define IN1 LATCbits.LATC4
#define IN2 LATCbits.LATC5


void config(void);

