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


unsigned char read_Temp(void);
unsigned char read_I(void);
unsigned char read_U(void);

char temp[5];

unsigned int high_i,low_i,high_u,low_u,high_t,low_t;
unsigned int esantion_curent_u,esantion_curent_i,esantion_curent_t;


unsigned int esantioane_u[4] = {0x00,0x00,0x00,0x00};      
unsigned int esantioane_i[4] = {0x00,0x00,0x00,0x00};    
unsigned int esantioane_t[4] = {0x00,0x00,0x00,0x00};  


float temperature;
float current;
float voltage;

float buffer;
unsigned char sst_button;


void main(void) {
    config(); 
    pwm_config();
    adc_config();
   
    PWM = 0;//60 min, 97 max
    IN1 = 0;
    IN2 = 1;
    
    Lcd_Clear();
    
    // medieaza intrarile
    for(int i=0;i<30;i++){
        read_Temp();
        read_I();
        read_U();
    }

    
    while(1){
        // ((raw_value_from_adc * resolution )/ 10mv/k) - 273.5
        temperature = (float)((read_Temp() * 0.01953)/0.01) - 273.5;
        
        current = ((read_I() * 0.01953)/11)/0.11;
     
        voltage = (read_U() *0.01953)/0.25;
        
        Lcd_Set_Cursor(1,1);
        sprintf(temp, "%2.1f",voltage);
        Lcd_Write_String(temp);
        Lcd_Write_String(" V");
        
        Lcd_Set_Cursor(1,12);
        sprintf(temp, "%2.1f",current);
        Lcd_Write_String(temp);
        Lcd_Write_String(" A");
        
        Lcd_Set_Cursor(2,1);
        sprintf(temp, "%2.1f",temperature);  
        Lcd_Write_String(temp);  
        Lcd_Write_String(" C");
        

        __delay_ms(100);
        if(SST == PUSHED){
            if(sst_button == 0){
                PWM = 80;
                sst_button = 1;
                __delay_ms(1000);  
            }
            else{
                PWM = 0;
                sst_button = 0;
                __delay_ms(1000);  
            }
            
            
        }
        else if(MINUS == PUSHED){
              PWM = PWM - 10;
            __delay_ms(100);   
        }
        else if(PLUS == PUSHED){  
            PWM= PWM + 10;
            __delay_ms(100);


        }
        else{
            __delay_ms(100);
        }
        
        if(voltage>17){
            PWM=0;
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Overvoltage");
            __delay_ms(5000);
            break;
        }
        if(temperature>55){
            PWM=0;
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Overtemperature");
            __delay_ms(5000);
            break;
        }
        
         if(current>1){
            PWM=0;
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Overcurrent");
            __delay_ms(5000);
            break;
        }
        
    }
    
}

unsigned char read_Temp(void)
{
    ADCON0=0b00001101;//RA4
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    esantion_curent_t=ADRESH;
    esantioane_t[0]=(esantion_curent_t+esantioane_t[1]+esantioane_t[2]+esantioane_t[3])/4;
    esantioane_t[3]=esantioane_t[2];
    esantioane_t[2]=esantioane_t[1];
    esantioane_t[1]=esantioane_t[0];
         
    return esantioane_t[0];
}

unsigned char read_U(void)
{
    ADCON0=0b00011001;//RC2
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    esantion_curent_u=ADRESH;
    esantioane_u[0]=(esantion_curent_u+esantioane_u[1]+esantioane_u[2]+esantioane_u[3])/4;
    esantioane_u[3]=esantioane_u[2];
    esantioane_u[2]=esantioane_u[1];
    esantioane_u[1]=esantioane_u[0];
         
    return esantioane_u[0];
}

unsigned char read_I(void)
{
    ADCON0=0b00011101;//RC3
    __delay_us(100);
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1){};
    esantion_curent_i=ADRESH;
    esantioane_i[0]=(esantion_curent_i+esantioane_i[1]+esantioane_i[2]+esantioane_i[3])/4;
    esantioane_i[3]=esantioane_i[2];
    esantioane_i[2]=esantioane_i[1];
    esantioane_i[1]=esantioane_i[0];
         
    return esantioane_i[0];
}
