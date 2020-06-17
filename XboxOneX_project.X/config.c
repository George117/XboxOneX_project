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
    
    
    
    //Feedback
    TRISAbits.TRISA4 = 1; // TEMP_SENSE
    TRISCbits.TRISC2 = 1; // U_SENSE
    TRISCbits.TRISC3 = 1; // I_SENSE
    
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


void pwm_config(void)
{  
    TRISAbits.TRISA5 = 1; // ENA
    PIR1bits.TMR2IF = 0;
    APFCON1bits.CCP2SEL = 1;
    CCP2CON=0b00001100; 
    CCPTMRS = 0b00000000;
    CCP2AS=0b00000000; 
    PR2=0x65; 
    CCPR2L=0;  
    T2CON=0b00000100; 
    TRISAbits.TRISA5 = 0; 
}

void adc_config(void)
{
    TRISAbits.TRISA4 = 1; // AN3:Temp
    TRISCbits.TRISC2 = 1; // AN6:U
    TRISCbits.TRISC3 = 1; // AN7: I
    
    ANSELAbits.ANSA4 = 1;
    ANSELCbits.ANSC2 = 1;
    ANSELCbits.ANSC3 = 1;
    
    
    ADCON0=0b00001101;// AN3
    ADCON1=0b0101000;
    
}