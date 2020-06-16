/*
 * File:   config.c
 * Author: georg
 *
 * Created on January 1, 2017, 1:37 PM
 */

#include <xc.h>
#include "bit_settings.h"
#include "config.h"
#include "i2c_display.h"

void config()
{  
    OSCCONbits.IRCF0=0;
    OSCCONbits.IRCF1=1;//8Mhz
    OSCCONbits.IRCF2=1;
    OSCCONbits.IRCF3=1;
    
    INTCONbits.GIE = 0;
    INTCONbits.INTE = 0;
    INTCONbits.PEIE = 0;

    ANSELA=0X00;
    ANSELC=0X00;
    TRISA=0X00;
    TRISC=0X00;
    PORTA=0X00;
    PORTC=0X00;
    LATA=0X00;
    LATC=0X00;
        
    //Butoane
    TRISAbits.TRISA0 = 1; // SST
    TRISAbits.TRISA1 = 1; // PLUS
    TRISAbits.TRISA2 = 1; // MINUS
    
    // l298
    TRISCbits.TRISC4 = 0; // IN1
    TRISCbits.TRISC5 = 0; // IN2
    TRISAbits.TRISA5 = 0; // ENA
    
    
    //Feedback
    TRISAbits.TRISA4 = 1; // TEMP_SENSE
    TRISCbits.TRISC2 = 0; // U_SENSE
    TRISCbits.TRISC3 = 0; // I_SENSE
    
    //Display
    TRISCbits.TRISC0=1;//i2c
    TRISCbits.TRISC1=1;//i2c
    I2C_Master_Init(100000);
    __delay_ms(100);
    Lcd_Init();
    Lcd_Clear();
    Cursor_Off();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Paul Iorga");
    __delay_ms(2000);
    

    
    

}


