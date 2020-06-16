/*
 * File:   main.c
 * Author: 
 *
 * Created on June 16, 2020, 4:30 PM
 */


#include <xc.h>
#include "bit_settings.h"
#include "config.h"
#include "i2c_display.h"

void main(void) {
    config(); 
    pwm_config();
   
    PWM = 0;
    IN1 = 0;
    IN2 = 1;
    
    while(1){
        if(SST == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("SST == PUSHED");
            PWM = 0;

        }
        else if(MINUS == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("MINUS == PUSHED");  
            PWM--;
            __delay_ms(500);
//            IN1 = 1;
//            IN2 = 0;
    
        }
        else if(PLUS == PUSHED){
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("PLUS == PUSHED");          
  
            PWM++;
            __delay_ms(500);
//            IN1 = 0;
//            IN2 = 1;

        }
        else{
            __delay_ms(100);
        }
            
    }
    
}
