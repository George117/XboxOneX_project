/*
 * File:   main.c
 * Author: 
 *
 * Created on June 16, 2020, 4:30 PM
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "bit_settings.h"
#include "config.h"
#include "i2c_display.h"


unsigned char read_Temp(void);//citire valoare tensinue de iesire

char duty[3];
char temp[3];

void main(void) {
    config(); 
    pwm_config();
    adc_config();
   
    PWM = 0;//60 min, 97 max
    IN1 = 0;
    IN2 = 1;
    
    Lcd_Clear();
    
    unsigned char res;
    while(1){
                // ((raw_value_from_adc * resolution )/ 10mv/k) - 273.5
        res = (unsigned char)((read_Temp() * 0.01953)/0.01) - 273.5;
        
        sprintf(temp, "%d    ",res );
        //sprintf(duty, "%d", PWM);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(temp);
        
        __delay_ms(100);
        if(SST == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("SST == PUSHED");
            PWM = 0;

        }
        else if(MINUS == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("MINUS == PUSHED");  
            PWM--;
            __delay_ms(100);
//            IN1 = 1;
//            IN2 = 0;
    
        }
        else if(PLUS == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("PLUS == PUSHED");          
  
            PWM++;
            __delay_ms(100);
//            IN1 = 0;
//            IN2 = 1;

        }
        else{
            __delay_ms(100);
        }
            
    }
    
}

unsigned char read_Temp(void)
{
    ADCON0=0b00001101;//RA4
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    return ADRESH;
}

unsigned char read_U(void)
{
    ADCON0=0b00011001;//RC2
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    return ADRESH;
}

unsigned char read_I(void)
{
    ADCON0=0b00011101;//RC3
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    return ADRESH;
}
