
//#include "p18f452.h"

///* 
// * File:   menu.c
// * Author: quintus
// *
// * Created on October 22, 2017, 3:02 PM
// */
//
#include <p18f452.h>
#include "ConfigRegs.h"
#include <lcd.h>
//
//#define B_SLCT PORTBbits.RB0
//
//int lastslctstate = 0;
//int lastbackstate = 0;
//int lastleftstate = 0;
//int lastritestate = 0;
//char buttonpressed = 0;
//
//const char scrcount = 3;
//
//void MODE_MANUAL(void);
//void mode0(void);
//unsigned char on[] = "on";
//unsigned char off[] = "off";
//
//#pragma code hipri = 0x0008
//void hiprint(void){
//    if(INTCONbits.INT0IF == 1){
//        _asm goto mode0 _endasm
//    }
//}
//
//#pragma interrupt mode0
//void mode0(void){
//    if(PORTBbits.RB0 == 1){
//        LCD_Delay(100);
//        if(PORTBbits.RB0 == 1){
//            INTCONbits.INT0IF = 0;              // clear flag
//            MODE_MANUAL();
//        }
//    }
//}
//// button external interrupt
//void mode_button_setup(void){
//    
//    INTCONbits.GIEH = 0;
//    RCONbits.IPEN = 1;
//    /*external interrupt enable bits*/
//    INTCONbits.INT0IE = 1;
//
//    /*external interrupt edge select bits*/
//    INTCON2bits.INTEDG0 = 1;
//    
//    INTCONbits.GIEH = 1;
//}
//
//
//
///*read button input, which key is pressed*/
//void readbutton(){
//    if(B_SLCT != lastslctstate){
//        LCD_Delay(1);
//        if(B_SLCT == 1){
//            lastslctstate = 1;
//        }        
//    }
//    
//    if( lastslctstate == 1){
//        buttonpressed = 1;
//    }
//    else{
//        buttonpressed = 0;
//    } 
//}
//
//void MENU_NAV(void){
//    if(lastslctstate == 1){
//        
//    }else if(lastbackstate == 1){
//        
//    }else if(lastritestate == 1){
//        
//    }
//}
//
//void main (void){
//    LCD_init();
//    mode_button_setup();
//    TRISBbits.RB3 = 0;
//    TRISBbits.RB0 = 1;
//    PORTBbits.RB0 = 0;
//    
//    /*set port b<1> = interrupt trigger source*/
//    TRISBbits.RB0 = 1;
//    TRISBbits.RB1 = 1;
//    TRISBbits.RB2 = 1;
//    /*PORTE allocated to buttons*/
//    TRISE = 1;  
//    TRISDbits.TRISD7 = 1;   // for button
//    TRISBbits.RB3 = 0;
//    LCDLine1();
//    LCD_puts("whattt");
//    
//    LCD_puts("ert");
//    while(1){
//        LCDLine1();
//        if(PORTBbits.RB0 == 1){
//            LCD_putc('l');
//            LCD_Delay(3);
//            PORTBbits.RB3 = 1;
//        }
//        else{
//            LCD_putc('-');
//            LCD_Delay(3);
//            PORTBbits.RB3 = 0;
//        }
//        DisplayClr();
//    }
//    MODE_MANUAL();          // default in manual
//    while(1);
//}
//
//
//void MODE_MANUAL(void){
//    LCDLine1();
//    LCD_puts("MODE:MANUAL"); 
//    /*Default to motor off*/
//    LCDLine2();
//    LCD_puts("SET:MTR _OF");
//    /*check if select is pressed
//     stay in this loop if not pressed*/
//    while(B_SLCT == 1);
//    LCDLine2();
//    LCD_puts("SET:MTR _ON");
//    while(1);
//    /*motor on function*/
//    
//    /*user menu navigation*/
//    LCDLine2();
//    LCD_puts("SET:MAX_SPD");
//
//    
//    while(1);
//}








/*LCD screen transition with button test*/

unsigned char str[3][6] = {"mode1","mode2","mode3"};
unsigned char str2[3][4] = {"m11","m12","m13"};
unsigned char str3[3][4] = {"m21","m22","m23"};
unsigned char str4[3][4] = {"m31","m32","m33"};

unsigned char str5[3][3][4] = {{"m11","m12","m13"},{"m21","m22","m23"},{"m31","m32","m33"}};
unsigned char num[10] = {'0','1','2','3','4','5','6','7','8','9'};
unsigned char num2[10][2] = {"0","1","2","3","4","5","6","7","8","9"};
//int countm = 0;
//int counts = 0;
int digit = 0;
int n=0;
int tina=0; //single digit
int tina1=0; //tens digit
int tina2=0; //double-digit
int speed, yaw, kp, ki, kd,IRsamplerate;
char transformer=0;     //mode transition(3 modes)


void delay(void){
    int x=0;
    while(x++<30000);
}


int SET_SPD(void);
int SET_YAW(void);
int SET_ki(void);
void main(void){
    LCD_init();

    TRISBbits.RB0 = 1;  //configure as input
    TRISBbits.RB1 = 1;  
    PORTBbits.RB0 = 0;  //connect to ground
    PORTBbits.RB1 = 0;
    TRISD = 0;
    
    LCD_CMD_WRT(LCD_BLINK_ON); //blink on 
    
    while(1){
        LCDLine1();
        LCD_puts(str[transformer]);
        if(PORTBbits.RB0==1){
            delay();
            if(PORTBbits.RB0==1){
                transformer++;
            }
        }
        else if(PORTBbits.RB1==1){
            delay();
            if(PORTBbits.RB1==1){
                if(transformer==0){
                    speed=SET_SPD();
                }
                else if(transformer==1){
                    yaw=SET_YAW();
                }
                else if(transformer==2){
                    ki=SET_ki();                }
            }
        }
        if(transformer==3){
            transformer=0;
        }
        
        
//        
//        if(PORTBbits.RB0 == 1){
//            delay();
//            if(PORTBbits.RB0 == 1){
//                LCD_putc(num[n]);
//                tina=num[n]-48;
//                n++;
//            }
//        }
//        if(PORTBbits.RB1 == 1){
//            delay();
//            if(PORTBbits.RB1 == 1){
//                digit=digit+1;
//                if(digit==1){
//                    tina1=tina*10;
//                }
//                else if(digit==2){
//                    tina2=tina1+tina;
//                    break;
//                }
//                n=0;
//            }
//        }
//        if(digit==1){
//            LCD_CMD_WRT(0x88);
//            
//        }
//        else if(digit==0){  
//            LCD_CMD_WRT(0x87);
//            
//        }
//
//        if(n == 10){
//            n=0;
//        }
//        
//        
//        if(PORTBbits.RB0 == 1){
//            if(digit == 1){
//                LCD_CMD_WRT(0x85);
//                LCD_putc('1');
//                
//                                
//            }
//            else if(digit == 2){
//                
//                LCD_CMD_WRT(0x85);
//                LCD_putc('2');
//            }
//        }
//        if(PORTBbits.RB1 == 1){
//            if(digit == 1){
//                digit = 2;
//                                
//            }
//            else if(digit == 2){
//                digit = 1;
//            }
//        
//        }

    }

    
    
//    while(1){
//        LCDLine1();
//        LCD_puts(str[0]);
//        LCD_CMD_WRT(0x87);
//        LCD_puts(str5[countm][counts]);
//        if(PORTBbits.RB1 == 1){
//            delay();
//            if(PORTBbits.RB1 == 1){
//                countm++;
//            }
//        }
//        else if(PORTBbits.RB0 == 1){
//            delay();
//            if(PORTBbits.RB0 == 1){
//                counts++;
//            }
//        }
//
//        if(countm == 3){
//            countm = 0;
//        }
//        if(counts == 3){
//            counts = 0;
//        }
//      
//    }
//    while(1){
//        LCD_CMD_WRT(0x87);
//        LCD_puts(str2[count]);
//        if(PORTBbits.RB0 == 1){
//            delay();
//            if(PORTBbits.RB0 == 1){
//                count++;
//            }
//        }
//        if(count == 3){
//            count = 0;
//        }
//    }
}


int SET_SPD(void){
    while(1){

    if(PORTBbits.RB0 == 1){
            delay();
            if(PORTBbits.RB0 == 1){
                LCD_putc(num[n]);
                tina=num[n]-48;
                n++;
            }
        }
        if(PORTBbits.RB1 == 1){
            delay();
            if(PORTBbits.RB1 == 1){
                digit=digit+1;
                if(digit==1){
                    tina1=tina*10;
                }
                else if(digit==2){
                    tina2=tina1+tina;
                    LCD_CMD_WRT(LCD_BLINK_OFF);
                    digit=0;
                    return tina2;
                }
                n=0;
            }
        }
        if(digit==1){
            LCD_CMD_WRT(0xC8);
            
        }
        else if(digit==0){  
            LCD_CMD_WRT(0xC7);
            
        }

        if(n == 10){
            n=0;
        }
    
            
    }
    
}

int SET_YAW(void){
    while(1){

    if(PORTBbits.RB0 == 1){
            delay();
            if(PORTBbits.RB0 == 1){
                LCD_putc(num[n]);
                tina=num[n]-48;
                n++;
            }
        }
        if(PORTBbits.RB1 == 1){
            delay();
            if(PORTBbits.RB1 == 1){
                digit=digit+1;
                if(digit==1){
                    tina1=tina*10;
                }
                else if(digit==2){
                    tina2=tina1+tina;
                    LCD_CMD_WRT(LCD_BLINK_OFF);
                    digit=0;
                    return tina2;
                }
                n=0;
            }
        }
        if(digit==1){
            LCD_CMD_WRT(0xC8);
            
        }
        else if(digit==0){  
            LCD_CMD_WRT(0xC7);
            
        }

        if(n == 10){
            n=0;
        }
    
            
    }
    
}
int SET_ki(void){
    while(1){

    if(PORTBbits.RB0 == 1){
            delay();
            if(PORTBbits.RB0 == 1){
                LCD_putc(num[n]);
                tina=num[n]-48;
                n++;
            }
        }
        if(PORTBbits.RB1 == 1){
            delay();
            if(PORTBbits.RB1 == 1){
                digit=digit+1;
                if(digit==1){
                    tina1=tina*10;
                }
                else if(digit==2){
                    tina2=tina1+tina;
                    LCD_CMD_WRT(LCD_BLINK_OFF);
                    digit=0;
                    return tina2;
                }
                n=0;
            }
        }
        if(digit==1){
            LCD_CMD_WRT(0xC8);
            
        }
        else if(digit==0){  
            LCD_CMD_WRT(0xC7);
            
        }

        if(n == 10){
            n=0;
        }
    
            
    }
    
}
