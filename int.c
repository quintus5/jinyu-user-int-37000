/* 
 * File:   interface.c
 * Author: twan8752
 *
 * Created on 19 October 2017, 12:17 PM
 * 
 * 
 * modified 21/10/17    6pm
 * add new functions for different mode
 * 
 */


#include <p18f452.h>
#include "ConfigRegs.h"
#include <lcd.h>

/*MACRO, VARIABLES*/
#define B_SLCT PORTDbits.RD7    //PORTD PIN7 for SELECT button
#define B_BACK PORTEbits.RE0    //PORTE PIN0 for BACK button
#define B_LEFT PORTEbits.RE1    //PORTE PIN1 for LEFT button
#define B_RITE PORTEbits.RE2    //PORTE PIN2 for RIGHT button

int lastslctstate = 0;
int lastbackstate = 0;
int lastleftstate = 0;
int lastritestate = 0;
char buttonpressed = 0;

const char scrcount = 3;
//char screen[scrcount][] = {"scr1","scr2","scr3"};

/*MACRO PROTOTYPE*/
void mode0(void);
void mode1(void);
void mode2(void);

void MODE_AUTO(void);
void MODE_ASSIST(void);
void MODE_MANUAL(void);


/*External Interrupt*/
#pragma code hipri = 0x0008     //HIGH PRIOPITY
void hiprint(void){
    if(INTCONbits.INT0IF == 1){   //INT0 External Interrupt Flag occurred
        _asm goto mode0 _endasm
    }
    if(INTCON3bits.INT1IF == 1){
        _asm goto mode1 _endasm
    }
    if(INTCON3bits.INT2IF == 1){
        _asm goto mode2 _endasm
    }
}

/*mode interrupt triggered via AUTO button*/
#pragma interrupt mode0
void mode0(void){
    if(PORTBbits.RB0 == 1){
        LCD_Delay(100);
        if(PORTBbits.RB0 == 1){
            INTCONbits.INT0IF = 0;              // clear flag
            MODE_AUTO();
        }
    }
}
/*mode interrupt triggered via Assist button*/
#pragma interrupt mode1
void mode1(void){
    if(PORTBbits.RB1 == 1){
        LCD_Delay(100);
        if(PORTBbits.RB1 == 1){
            INTCON3bits.INT1IF = 0;            // clear flag    
            MODE_ASSIST();
        }
    }
    
}
/*mode interrupt triggered via AUTO button*/
#pragma interrupt mode2
void mode2(void){
    if(PORTBbits.RB2 == 1){
        LCD_Delay(100);
        if(PORTBbits.RB1 == 1){
            INTCON3bits.INT2IF = 0;             // clear flag
            MODE_MANUAL();
        }
    }
}

/* button external interrupt*/
void mode_button_setup(void){
    
    INTCONbits.GIEH = 0;    //disables all interrupts
    RCONbits.IPEN = 1;      //Enables priority levels on interrupts
    
    /*external interrupt enable bits*/
    INTCONbits.INT0IE = 1;     //Enables the INT0 external interrupt
    INTCON3bits.INT1IE = 1;    //Enables the INT1 external interrupt
    INTCON3bits.INT2IE = 1;    //Enables the INT2 external interrupt
    
    /*external interrupt(x) edge select bits,x=0,1,2*/
    INTCON2bits.INTEDG0 = 1;   //interrupt on RISING EDGE
    INTCON2bits.INTEDG1 = 1;
    INTCON2bits.INTEDG2 = 1;
 
    
    /*external interrupt priority select, INT0 auto HIGH*/
    INTCON3bits.INT1IP = 1;   //HIGH PRIORITY
    INTCON3bits.INT2IP = 1;
    
    INTCONbits.GIEH = 1;    //Enables all HIGH priority interrupts
}

void main (void){
    LCD_init();
    mode_button_setup();
    
    /*set port b<1> = interrupt trigger source*/
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    /*PORTE allocated to buttons*/
    TRISE = 1;  //PORT E all for buttons
    TRISDbits.TRISD7 = 1;   // for button
    TRISBbits.RB3 = 0;
    
    MODE_MANUAL();          // default in MANUAL mode
}
    
/*
 * SET_PASS_GO
SET_PASS_ABORT
SET_MODE_USER_MANUAL
SET_MODE_USER_ASSIST */
void MODE_AUTO(void){  
    LCDLine1();
    LCD_puts("MODE:AUTO  ");        // don't delete space
    
    /*SET_PASS_GO*/
    while(1){
        if(B_SLCT == 1){
            /*initiate auto mode*/
        }
        else if(B_SLCT == 1){
            break;
        }
    }
    /*SET_PASS_ABORT*/
    MODE_MANUAL(); // transition to manual after abort auto
    
}
/*SET_MODE_USER_MANUAL
SET_MODE_USER_AUTO */
void MODE_ASSIST(void){
    LCDLine1();
    LCD_puts("MODE:ASSIST");
    while(1);
}

/*Full joystick control*/
/*SET_MOTORS_ON
SET_MOTORS_OFF
SET_SPEED_MAX
SET_MODE_USER_ASSIST
SET_MODE_USER_AUTO
SET_MODE_FACTORY
*/
void MODE_MANUAL(void){
    LCDLine1();
    LCD_puts("MODE:MANUAL"); 
    /*Default to motor off*/
    LCDLine2();
    LCD_puts("SET:MTR _OF");
    /*check if select is pressed
     stay in this loop if not pressed*/
    while(B_SLCT == 0);
    LCDLine2();
    LCD_puts("SET:MTR _ON");
    /*motor on function*/
    
    /*user menu navigation*/
    LCDLine2();
    LCD_puts("SET:MAX_SPD");

    
    while(1);
}
/*SET_PID_GAINS
SET_SPEED_MAX
SET_YAW_RATE_MAX
SET_IR_SAMPLES_PER_ESTIMATE
SET_IR_SAMPLE_RATE
SHOW_RAW_READINGS
SHOW_STATISTICS    
*/    
void MODE_FACTORY(void){
    LCDLine1();
    LCD_puts("MODE:FCTORY"); 
    
    /*user menu navigation*/
}

/*read button input, which key is pressed*/
void readbutton(){
    if(B_SLCT != lastslctstate){
        LCD_Delay(1);
        if(B_SLCT == 1){
            lastslctstate = 1;
        }        
    }
    if(B_BACK != lastbackstate){
        LCD_Delay(1);
        if(B_BACK == 1){
            lastbackstate = 1;
        } 
    }
    if(B_LEFT != lastleftstate){
        LCD_Delay(1);
        if(B_LEFT == 1){
            lastleftstate = 1;
        }        
    }
    if(B_RITE != lastritestate){
        LCD_Delay(1);
        if(B_RITE == 1){
            lastritestate = 1;
        }        
    }
    
    if(lastritestate == 1 || lastslctstate == 1|| lastleftstate == 1|| lastbackstate == 1){
        buttonpressed = 1;
    }
    else{
        buttonpressed = 0;
    } 
}

void MENU_NAV(void){
    if(lastslctstate == 1){
        
    }else if(lastbackstate == 1){
        
    }else if(lastritestate == 1){
        
    }
}
//     TRISAbits.RA0 = 1;
//     TRISAbits.RA4 = 1;
//     TRISD = 1;
//     TRISBbits.RB1 = 0;
//     while(1){
//     if(PORTDbits.RD4 == 1){
//         PORTBbits.RB1 = 1;
//     }
//     else{
//         PORTBbits.RB1 = 0;
//     }
//     LCD_init();
//     LCDLine1();
//     LCD_puts("welcom");
//     LCDLine2();
//     LCD_puts("press to start");
     
     
     
//     while(1){
//            
//         while(PORTAbits.RA0 == 1);     // wait for press
//         DisplayClr();
//         LCDLine1();
//         LCD_puts("SET yoyoyo");
//         while(PORTAbits.RA0 == 0);     // wait for release
//         
//         while(PORTAbits.RA0 == 1 && PORTAbits.RA4 == 1);
//         if(PORTAbits.RA4 == 1){
//             LCDLine2();
//             LCD_putc('r');
//         }
//         else {
//            DisplayClr();
//            LCDLine1();
//            LCD_puts("SET ki");
//         }
////         while(PORTBbits.RB0 == 1);     
//         while(PORTAbits.RA0 == 0 || PORTAbits.RA4 == 0);  
         
//         while(PORTDbits.RD4 == 1);
//         DisplayClr();
//         LCDLine2();
//         LCD_puts("SET kp");
//         while(PORTDbits.RD4 == 0);   
         
         //}
         

//
//
///*include header filer*/
//
///*configuration bits*/
//
//
///*some command*/
//
//
///*macro prototype*/
//void init(void);
//void MANUAL_MODE(void);
//void ASSIST_MODE(void);
//void AUTO_MODE(void);
//void FACTORY_MODE(void);
//
//void highPriorityIsr(void); //Interrupt Service Routines-highPriority
//
//
///*Installing Interrupt Service Routines*/
//#pragma code highISR = 0x0008
//void goToHighIsr( void )
//{
//    _asm
//    goto highPriorityIsr
//    _endasm
//}
//
//
//void main() {
//    init();    //initialize
//    
//    //if (MANUAL Button is pressed){
//    MANUAL(); //manual mode
//    //}
//    
//    //if (ASSIST Button is pressed){
//    ASSIST(); //assist mode
//    //}
//    
//    //if (AUTO Button is pressed){
//    AUTO();   //auto mode
//    //}
//    
//    // Once factory button is pressed, if statement (check),polling/interrupt
//    //if (FACTORY Button is pressed){
//    FACTORY(); //factory mode
//    //}
//    
//    while(1);
//}
//
///*initialization*/
//void init(void){
//    LCD(); //initialize LCD
//}
//
///*MANUAL MODE*/
//void MANUAL(void){
//    //check motor status & 'select' button pressed or not.
//    //If(select && motor-off), then motor on. 
//    //If(select && motor-on),  then motor off
//   
//    /************CODE************/
//    
//    //when motor is on, it would turn off when 'select' button is pressed 
//    //and vice versa. After that, set Max Speed on left/right.
//    
//    /************CODE************/
//    
//    
//}
//
///*ASSIST MODE*/
//void ASSIST(void){
//    /*similar to MANUAL mode*/
//}
//
///*AUTO MODE*/
//void AUTO(void){
//    //AUTO Mode(waiting)
//   
//    /****************************************/
//    /****************CHECKING****************/
//    //if('select' is pressed){
//    //running AUTO Pass -> /************CODE************/
//    //}
//    
//    //if('back' is pressed){
//    // AUTO Mode(waiting) -> /************CODE************/
//    //}
//} 
//
///*FACTORY MODE*/
//void FACTORY(void){
//    //set PID gains -> press 'right' to set Speed Max -> press 'right' to set
//    //YAW rate MAX -> press 'right' to set IR Samples -> press 'right' to show
//    //RAW Readings...
//    //If press 'left' then returns to the previous page.
//}
//
//int maxspeed(void){
//    //blink/underline to show selected digit, using 'left' and 'right' button 
//    //to move underline and press 'select' to select digit
//    //add that digit to current number so far, after pressing 'select', the 
//    //underline returns to digit 0. (e.g.Max Speed: 524)
//    
//    /************CODE************/
//    
//    //check 'select' is pressed on 'tick'. If press 'select' on 'tick', 
//    //then Max speed is set. Or press 'select' on last allowable digit to set 
//    //Max speed
//    
//    /************CODE************/
//}
//
////interrupt
//#pragma interrupt highPriorityIsr // or interruptlow
//void highPriorityIsr(void)
//{ 
//    if(PIR1bits.RCIF==1){   //UART Rc Buffer Full
//        rx232Isr();       
//    }
//}

