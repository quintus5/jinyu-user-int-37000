
#include <button.h>
#include "p18f452.h"
#include "global.h"
#include "header/lcd.h" 


#pragma code hipri = 0x0008
void hipri(void){
    if(INTCONbits.INT0IF == 1){
        _asm goto mode0 _endasm
    }
//    if(INTCON3bits.INT2IF == 1){
//        _asm goto mode1 _endasm
//    }
//    if(INTCON3bits.INT1IF == 1){
//        _asm goto mode2 _endasm
//    }
}

#pragma code lopri = 0x0018
void lopri(void){
    if(INTCON3bits.INT2IF == 1){
        _asm goto mode2 _endasm
    }
    if(INTCON3bits.INT1IF == 1){
        _asm goto mode1 _endasm
    }
}

#pragma interrupt mode0
void mode0(void){
//    if(B1 == 1){mode = 0;}
//    else if(B2 == 1){mode == 1;}
//    else if(B3 == 1){mode == 2;}
 
//    PORTAbits.RA3 = 0;
//    PORTAbits.RA5 = 0;
//    PORTAbits.RA4 = 1;
    mode = 0;
  //  modechange = 1;
    INTCONbits.INT0IF = 0;
}
//#pragma interrupt mode1
#pragma interruptlow mode1
void mode1(void){


    mode = 1;
 //   modechange = 1;
    INTCON3bits.INT1IF = 0;
}

//#pragma interrupt mode2
#pragma interruptlow mode2
void mode2(void){


            
//    PORTAbits.RA4 = 0;
//    PORTAbits.RA5 = 0;
//    PORTAbits.RA3 = 1;
    mode = 2;
   // modechange = 1;
    INTCON3bits.INT2IF = 0;
}

void SETUP_BUTTON(void){

    TRISBbits.TRISB0 = 1;   // input
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;

    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
    
    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    
    PORTBbits.RB3 = 0;
    PORTBbits.RB4 = 0;
    
    INTCONbits.INT0IF = 0;       // clr flag
    INTCON3bits.INT1IF = 0;      // clr flg
    INTCON3bits.INT2IF = 0;
    
    INTCONbits.INT0IE = 1;      // enable int0
    INTCON3bits.INT1IE = 1;     // enable int1
    INTCON3bits.INT2IE = 1;
    
    INTCON2bits.INTEDG1 = 1;    // rising edge
    INTCON2bits.INTEDG0 = 1;    // rising edge
    INTCON2bits.INTEDG2 = 1;
    
    
    
    INTCON3bits.INT1IP = 0;     // lopri
    INTCON3bits.INT2IP = 0;     // lopri
    //   INTCON2bits.RBPU = 0;       // pull up enable
}

