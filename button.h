/* 
 * File:   butint.c
 * Author: twan8752
 *
 * Created on 24 October 2017, 7:12 PM
 */
#include <p18f452.h>
#include "ConfigRegs.h"


void testint(void);
void mode1(void);
void mode2(void);
void lopri(void);
void hipri(void);

#pragma code hipri = 0x0008
void hipri(void){
//    if(INTCON3bits.INT1IF == 1){
//        mode1();
//    }
    if(INTCONbits.INT0IF == 1){
        testint();
    }
//    if(INTCON3bits.INT2IF == 1){
//        mode2();
//    }
}

#pragma code  lopri = 0x0018
void lopri(void){
    if(INTCON3bits.INT2IF == 1){
        mode2();
    }
    if(INTCON3bits.INT1IF == 1){
        mode1();
    }
}
/****************************************************************************
NAME	 :  button_setup()
 
Include	 : 	button.h
 
Description : 	configure external interrupt on portb<0-2>
 
Arguments   : 	None
 
Return Value: 	None
 
Remarks     : 	Enable interrupts, Rising edge trigger, INT0 hi priority, INT1,2
                low priority, can change if needed
*******************************************************************************/
void button_setup(void){
 /******************************************************************
 external interrupt setting, for use in mode changing
 all button require a pull down resistor to pull down the pins
 INT0 is hi priority by default
 ******************************************************************/
    TRISBbits.TRISB0 = 1;   // input
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;

    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    
    INTCONbits.INT0IF = 0;       // clr flag
    INTCON3bits.INT1IF = 0;      // clr flg
    INTCON3bits.INT2IF = 0;
    
    INTCONbits.INT0IE = 1;      // enable int0
    INTCON3bits.INT1IE = 1;     // enable int1
    INTCON3bits.INT2IE = 1;
    
    INTCON2bits.INTEDG1 = 1;    // rising edge
    INTCON2bits.INTEDG0 = 1;    // rising edge
    INTCON2bits.INTEDG2 = 1;
    
    INTCON3bits.INT1IP = 0;     // hipri
    INTCON3bits.INT2IP = 0;     // hipri
    //   INTCON2bits.RBPU = 0;       // pull up enable

}

#pragma code
void main(void){
    
    INTCONbits.GIEH = 0;
    button_setup();
    RCONbits.IPEN = 1;          // prio

    INTCONbits.GIE = 1;         // enable int
    INTCONbits.PEIE = 1;
    
    
    
    while(1){
//        PORTBbits.RB3 = 0;
//        PORTDbits.RD3 = 0;
//        PORTDbits.RD4 = 0;
    /*code here*/
    
    }
    
}

/****************************************************************************
NAME	 :  
 
Include	 : 	portb.h
 
Description : 	Subroutine for mode 1
 
Arguments   : 	None
 
Return Value: 	None
 
Remarks     : 	This Macro disables the interrupt on INT pin.
*******************************************************************************/
#pragma interrupt testint
void testint(void){
//    int x = 0;
//    PORTBbits.RB3 = 1;
//    while(x++<20000);x=0;
    /*code here
     set flag only, do not do complex algorithm here*/
    INTCONbits.INT0IF = 0;
//    }
}
//#pragma interrupt mode1
#pragma interruptlow mode1
void mode1(void){
//    int y= 0;
//    PORTDbits.RD3 = 1;
//    while(y++<20000);y=0;
    
    /*code here
     set flag only, do not do complex algorithm here*/
    INTCON3bits.INT1IF = 0;
}

//#pragma interrupt mode2
#pragma interruptlow mode2
void mode2(void){
//    int z = 0;
//    PORTDbits.RD4 = 1;
//    while(z++<20000);z=0;  
    /*code here
     set flag only, do not do complex algorithm here*/
    INTCON3bits.INT2IF = 0;
}
