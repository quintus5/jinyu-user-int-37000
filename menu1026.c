/* 
 * File:   menu1026.c
 * Author: twan8752
 *
 * Created on 26 October 2017, 7:19 PM
 */
/*27/10 6.30pm
 try to fix port e not acting as select button
 port ra6 is timer output, outputing pwmish stuff*/
/*7.07pm
 gonna test one interrupt for all mode multiplexed with other port*/

#include <p18f452.h>
#include "ConfigRegs.h"
#include "header/lcd.h"
#include "header/menu.h"
#include "header/button.h"
#include "header/global.h"

/*variable initialization*/
volatile unsigned char mode = 0;


void main(void){
    which_setting = 0;
    ADCON1 = 0b00001110;
    LCD_init();
    SETUP_INTERRUPT();
    /*configure LEDs*/
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    PORTCbits.RC2 = 0;
//    TRISAbits.RA3 = 0;
//    TRISAbits.RA4 = 0;
//    TRISAbits.RA5 = 0;
 //   TRISAbits.RA2 = 1;

//    PORTAbits.RA3 = 0;
//    PORTAbits.RA4 = 0;
//    PORTAbits.RA5 = 0;
//    PORTAbits.RA2 = 0;
    /*next and slect button*/


    /*initial value for testing*/
    IR_VAL.IR_RAW = 2653;
    IR_VAL.IR_VARIANCE = 4096;
    IR_VAL.IR_MEAN = 4998;
    speed_max = 1;
    PID_GAIN.kp = 125;
    PID_GAIN.ki = 452;
    PID_GAIN.kd = 560;
    yaw_max = 1;
    IRsamplerate = 0;
    
//    TRISE = 0b111;
//    TRISEbits.TRISE0 = 1;
//    TRISEbits.TRISE1 = 1;
//    PORTE = 0;
    MODE_MANUAL();
    while(1);
}

/**/
void SETUP_INTERRUPT(void){
    INTCONbits.GIEH = 0;
    
    SETUP_BUTTON();
    
    RCONbits.IPEN = 1;          // enable priority
    INTCONbits.GIE = 1;         // enable int
    INTCONbits.PEIE = 1;

    return;
}

/*manual mode*/
void MODE_MANUAL(void){
    LCDLine1();
    LCD_puts(MODE_SLCT[mode]);
//    PORTAbits.RA3 = 0;
//    PORTAbits.RA5 = 0;
//    PORTAbits.RA4 = 1;
    LED_MAN = 1;
    LED_AUT = 0;
    LED_FAC = 0;
    LCDLine2();
     LCD_puts(SETTING_MAN[which_setting]);
    /*setting select*/
    if(B_NEXT == 1){
        LCD_Delay(20);
        if(B_NEXT == 1){
            which_setting++;
        }
    }
    if(B_SLCT == 1){
        LCD_Delay(20);
        if(B_SLCT == 1){
            if(which_setting == 0){
                /*motor turn on*/
            }
            else if(which_setting == 1){
                /*motor turn off*/
            }
            else if(which_setting == 2){
                SET_SPD();
            }
        }
    }
    if(which_setting == 3){
        which_setting = 0;
    }
     
    /*mode check*/
    if(mode == 0)     {_asm goto MODE_MANUAL _endasm}
    else if(mode == 1){DisplayClr();which_setting = 0;_asm goto MODE_ROUGE _endasm }
    else if(mode == 2){DisplayClr();which_setting = 0;_asm goto MODE_FACTORY _endasm}
    else{errorstate();}
}
/*factory mode*/
void MODE_FACTORY(void){
    LCDLine1();
    LCD_puts(MODE_SLCT[mode]);
//    PORTAbits.RA3 = 0;
//    PORTAbits.RA4 = 0;
//    PORTAbits.RA5 = 1;
    LED_MAN = 0;
    LED_AUT = 0;
    LED_FAC = 1;
    LCDLine2();
    LCD_puts(SETTING_FCT[which_setting]);
    /*setting select*/
    if(B_NEXT == 1){
        LCD_Delay(20);
        if(B_NEXT == 1){
            which_setting++;
        }
    }
    if(B_SLCT == 1){
        LCD_Delay(20);
        if(B_SLCT == 1){
            if(which_setting == 0){
                /*motor turn on*/
            }
            else if(which_setting == 1){
                /*motor turn off*/
            }
            else if(which_setting == 2){
                SET_SPD();
            }
            else if(which_setting==3){
                SET_YAW();
            }
            else if(which_setting==4){
                SET_KP();
            }
            else if(which_setting==5){
                SET_KD();
            }
            else if(which_setting==6){
                SET_KI();
            }
            else if(which_setting==7){
                SET_IR_SAMPLE_RATE();
            }
//            else if(which_setting==8){
//                IR_VAL.IR_RAW = READ_IRRAW();
//            }
//            else if(which_setting==9){
//                IR_VAL.IR_MEAN = READ_IRMEAN();
//            }
//            else if(which_setting==10){
//                IR_VAL.IR_VARIANCE = READ_IRVAR();
//            }
        }
    }
    if(which_setting==8){
        Int_to_string(IR_VAL.IR_RAW);
    }
    else if(which_setting==9){
        Int_to_string(IR_VAL.IR_MEAN);
    }
    else if(which_setting==10){
        Int_to_string(IR_VAL.IR_VARIANCE);
    }
    if(which_setting == 11){
        DisplayClr();
        which_setting = 0;
    }
    
    
    /*mode check*/
    if(mode == 0)     {DisplayClr();which_setting = 0;_asm goto MODE_MANUAL _endasm}
    else if(mode == 1){DisplayClr();which_setting = 0;_asm goto MODE_ROUGE _endasm }
    else if(mode == 2){_asm goto MODE_FACTORY _endasm}
    else{errorstate();}
}

/*auto mode*/
void MODE_ROUGE(void){
    LCDLine1();
    LCD_puts(MODE_SLCT[mode]);
//    PORTAbits.RA4 = 0;
//    PORTAbits.RA5 = 0;
//    PORTAbits.RA3 = 1;
    LED_MAN = 0;
    LED_AUT = 1;
    LED_FAC = 0;
    LCDLine2();
    LCD_puts(SETTING_AUT[which_setting]);
    /*setting select*/
    if(B_NEXT == 1){
        LCD_Delay(20);
        if(B_NEXT == 1){
            if(which_setting == 1){which_setting = 0;}
            else{which_setting = 1;}
        }
    }
    if(B_SLCT == 1){
        LCD_Delay(20);
        if(B_SLCT == 1){
            if(which_setting == 0){
                /*goto auto mode*/
            }
            else if(which_setting == 1){
                /*goto assist mode*/
            }
        }
    }

    
    /*mode check*/
    if(mode == 0)     {DisplayClr();which_setting = 0;_asm goto MODE_MANUAL _endasm}
    else if(mode == 1){_asm goto MODE_ROUGE _endasm }
    else if(mode == 2){DisplayClr();which_setting = 0;_asm goto MODE_FACTORY _endasm}
    else{errorstate();}
}

void errorstate(void){
    LCDLine2();
    LCD_putc('e');
    PORTAbits.RA3 = 1;
    while(1);

}


void SET_SPD(void){
    
//    LCD_CMD_WRT(LCD_CURSOR_ON); 
    LCD_CMD_WRT(0xCF);
    LCD_putc(DATA_VALUE[speed_max]);
    while(1){
        
        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){
                LCD_CMD_WRT(0xCF);
                speed_max++;        
                if(speed_max == 10){speed_max = 0;}
                LCD_putc(DATA_VALUE[speed_max]);
//                LCD_CMD_WRT(0xCF);
//                LCD_putc(DATA_VALUE[++unitdig]);
//                unitdig++;
            }
        }
        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
//                LCD_CMD_WRT(LCD_CURSOR_OFF);
                DisplayClr();
                break;
//                return unitdig;
            }
        }
        /*keep range in 1-9*/
//        if(unitdig == 9){
//            unitdig = 0;
//        }
//        LCD_CMD_WRT(0xCF);
//        LCD_putc(DATA_VALUE[which_number]);
//        
//        if(B_NEXT == 1){
//            LCD_Delay(100);
//            if(B_NEXT == 1){
//                unitdig = DATA_VALUE[which_number]-48;
//                which_number++;
//            }
//        }
//        if(B_SLCT == 1){
//            LCD_Delay(100);
//            if(B_SLCT == 1){
//                LCD_CMD_WRT(LCD_CURSOR_OFF);
//                DisplayClr();
//                return unitdig;
//            }
//        }
//        if(which_number == 10){
//            which_number = 0;
//        }
    }

}


void SET_YAW(void){
    
//    unitdig = yaw_max;
//    LCD_CMD_WRT(LCD_CURSOR_ON); 
    LCD_CMD_WRT(0xCF);
//    LCD_putc(DATA_VALUE[unitdig]);
    LCD_putc(DATA_VALUE[yaw_max]);
    while(1){
        
//        LCD_CMD_WRT(0xCF);
//       LCD_putc(DATA_VALUE[unitdig]);
        
        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){
                LCD_CMD_WRT(0xCF);
                yaw_max++;        
                if(yaw_max == 10){yaw_max = 0;}
                LCD_putc(DATA_VALUE[yaw_max]);
//                LCD_CMD_WRT(0xCF);
//                LCD_putc(DATA_VALUE[++unitdig]);
//                unitdig++;
            }
        }
        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
//                LCD_CMD_WRT(LCD_CURSOR_OFF);
                DisplayClr();
                break;
//                return unitdig;
            }
        }
//        if(unitdig == 9){
//            unitdig = 0;
//        }
    }
    
//    unitdig = 0;
//    which_number = yaw_max+1;
//    LCD_CMD_WRT(LCD_CURSOR_ON); 
//    
//    while(1){
//        LCD_CMD_WRT(0xCF);
//        LCD_putc(DATA_VALUE[which_number]);
//        
//        if(B_NEXT == 1){
//            LCD_Delay(100);
//            if(B_NEXT == 1){
//                unitdig = DATA_VALUE[which_number]-48;
//                which_number++;
//            }
//        }
//        if(B_SLCT == 1){
//            LCD_Delay(100);
//            if(B_SLCT == 1){
//                LCD_CMD_WRT(LCD_CURSOR_OFF);
//                DisplayClr();
//                return unitdig;
//            }
//        }
//        if(which_number == 10){
//            which_number = 0;
//        }
//    }
    return;
}

void SET_KP(void){
    /*seperate into each digit*/
    unitdig = PID_GAIN.kp%10; 
    tenthdig = (PID_GAIN.kp/10)%10;
    hundrethdig = PID_GAIN.kp/100;
    which_digit = 0;
    which_number = hundrethdig;
    LCD_CMD_WRT(0xCD);
    LCD_putc(DATA_VALUE[hundrethdig]);
    LCD_putc(DATA_VALUE[tenthdig]);
    LCD_putc(DATA_VALUE[unitdig]);
//    LCD_CMD_WRT(LCD_CURSOR_ON); 
    
    while(1){

        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){               
                if(which_digit == 0){     LCD_CMD_WRT(0xCD);}
                else if(which_digit == 1){LCD_CMD_WRT(0xCE);}
                else if(which_digit == 2){LCD_CMD_WRT(0xCF);} 
                which_number++;
                if(which_number == 10){which_number = 0;}
                LCD_putc(DATA_VALUE[which_number]);
            }
        }

        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
                if(which_digit == 0){
                    hundrethdig = (which_number)*100;
                    which_number = tenthdig;
                }
                else if(which_digit == 1){
                    tenthdig = which_number*10;
                    which_number = unitdig;
                }
                else if(which_digit == 2){
                    PID_GAIN.kp = hundrethdig+tenthdig+which_number;
//                    LCD_CMD_WRT(LCD_CURSOR_OFF); 
                    DisplayClr();
                    return;
                }   
            which_digit++;
            }
        }
    }
    
    
////    LCD_CMD_WRT(LCD_CURSOR_ON); 
//    while(1){
////    LCD_putc(DATA_VALUE[which_number]);
//    if(B_NEXT == 1){
//        LCD_Delay(100);
//        if(B_NEXT == 1){
//       //     LCD_putc(DATA_VALUE[which_number]);
//            unit=DATA_VALUE[which_number]-48;
//            which_number++;
//        }
//    }
//    if(B_SLCT == 1){
//        LCD_Delay(100);
//        if(B_SLCT == 1){
//            which_digit++;
////            if(which_digit==1){
////                ten=unit*10;
////            }
////            else if(which_digit==2){
////                input_val=ten+unit;
////                LCD_CMD_WRT(LCD_BLINK_OFF); 
////                which_digit=0;
////                return input_val;
////            }
////            which_number=0;
//        }
//    }
//    if(which_digit==1){
//        ten=unit*10;
//    }
//    else if(which_digit==2){
//        input_val=ten+unit;
//        LCD_CMD_WRT(LCD_CURSOR_OFF); 
//        which_digit=0;
//        return input_val;
//    }
//    //which_number=0;
//    if(which_digit==1){
//        LCD_CMD_WRT(LCD_CURSOR_OFF); 
//        LCD_CMD_WRT(0xCF);
//        LCD_CMD_WRT(LCD_CURSOR_ON); 
//        LCD_putc(DATA_VALUE[which_number]);
//        
//    }
//    else if(which_digit==0){  
//        LCD_CMD_WRT(0xCE);
//        LCD_CMD_WRT(LCD_CURSOR_ON); 
//        LCD_putc(DATA_VALUE[which_number]);
//        LCD_CMD_WRT(LCD_CURSOR_OFF);
//    }
//    if(which_number >= 10){
//        which_number=0;
//    }        
//    }

}
void SET_KD(void){
    unitdig = PID_GAIN.kd%10; 
    tenthdig = (PID_GAIN.kd/10)%10;
    hundrethdig = PID_GAIN.kd/100;
    which_digit = 0;
    which_number = hundrethdig;
    LCD_CMD_WRT(0xCD);
    LCD_putc(DATA_VALUE[hundrethdig]);
    LCD_putc(DATA_VALUE[tenthdig]);
    LCD_putc(DATA_VALUE[unitdig]);
//    LCD_CMD_WRT(LCD_CURSOR_ON); 
    
    while(1){

        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){
                if(which_digit == 0){     LCD_CMD_WRT(0xCD);}
                else if(which_digit == 1){LCD_CMD_WRT(0xCE);}
                else if(which_digit == 2){LCD_CMD_WRT(0xCF);} 
                which_number++;
                if(which_number == 10){which_number = 0;}
                LCD_putc(DATA_VALUE[which_number]);
            }
        }
        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
                if(which_digit == 0){
                    hundrethdig = (which_number)*100;
                    which_number = tenthdig;
                }
                else if(which_digit == 1){
                    tenthdig = (which_number)*10;
                    which_number = unitdig;
                }
                else if(which_digit == 2){
                    PID_GAIN.kd = hundrethdig+tenthdig+which_number;
//                    LCD_CMD_WRT(LCD_CURSOR_OFF); 
                    DisplayClr();
                    return;
                }   
            which_digit++;
            }
        }
    }
}

void SET_KI(void){
    unitdig = PID_GAIN.ki%10; 
    tenthdig = (PID_GAIN.ki/10)%10;
    hundrethdig = PID_GAIN.ki/100;
    which_digit = 0;
    which_number = hundrethdig;
    LCD_CMD_WRT(0xCD);
    LCD_putc(DATA_VALUE[hundrethdig]);
    LCD_putc(DATA_VALUE[tenthdig]);
    LCD_putc(DATA_VALUE[unitdig]);
//    LCD_CMD_WRT(LCD_BLINK_ON); 
    
    while(1){
        if(which_number == 10){
            which_number = 0;
        }
        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){
                if(which_digit == 0){     LCD_CMD_WRT(0xCD);}
                else if(which_digit == 1){LCD_CMD_WRT(0xCE);}
                else if(which_digit == 2){LCD_CMD_WRT(0xCF);} 
                which_number++;
                if(which_number == 10){which_number = 0;}
                LCD_putc(DATA_VALUE[which_number]);
            }
        }
        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
                if(which_digit == 0){
                    hundrethdig = (which_number)*100;
                    which_number = tenthdig;
                }
                else if(which_digit == 1){
                    tenthdig = (which_number)*10;
                    which_number = unitdig;
                }
                else if(which_digit == 2){
                    PID_GAIN.ki = hundrethdig+tenthdig+which_number;
//                    LCD_CMD_WRT(LCD_BLINK_OFF); 
                    DisplayClr();
                    return;
                }   
            which_digit++;
            }
        }
    }
}

void SET_IR_SAMPLE_RATE(void){
    
//    unitdig = IRsamplerate;
    LCD_CMD_WRT(LCD_CURSOR_ON); 
    LCD_CMD_WRT(0xCF);
    LCD_putc(DATA_VALUE[IRsamplerate]);
    while(1){
        if(B_NEXT == 1){
            LCD_Delay(100);
            if(B_NEXT == 1){
                LCD_CMD_WRT(0xCF);
                IRsamplerate++;        
                if(IRsamplerate == 10){IRsamplerate = 0;}
                LCD_putc(DATA_VALUE[IRsamplerate]);
            }
        }
        if(B_SLCT == 1){
            LCD_Delay(100);
            if(B_SLCT == 1){
                LCD_CMD_WRT(LCD_CURSOR_OFF);
                DisplayClr();
                return;
            }
        }
    }
}



//convert int read from sensor to string form
void Int_to_string(int num){
        //read each digital of the num
        if(num >= 1000){
            value_string[0] = DATA_VALUE[num/1000];
            value_string[1] = DATA_VALUE[(num/100)%10];
            value_string[2] = DATA_VALUE[(num/10)%10];
            value_string[3] = DATA_VALUE[num%10];
            value_string[4] = 0x00;   //null character  
        } 
        else if(num >= 100){
            value_string[0] = ' ';
            value_string[1] = DATA_VALUE[num/100];
            value_string[2] = DATA_VALUE[(num/10)%10];
            value_string[3] = DATA_VALUE[num%10];
            value_string[4] = 0x00;         //null character
        }
        else if(num >= 10){
            value_string[0] = ' ';
            value_string[1] = ' ';
            value_string[2] = DATA_VALUE[num/10];
            value_string[3] = DATA_VALUE[num%10];
            value_string[4] = 0x00;         //null character
        }
        else{
            value_string[0] = ' ';
            value_string[1] = ' ';
            value_string[2] = ' ';
            value_string[3] = DATA_VALUE[num];
            value_string[4] = 0x00;         //null character
        }
        LCD_CMD_WRT(0xCC);
        LCD_puts(value_string);
}