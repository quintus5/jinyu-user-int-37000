/* 
 * File:   menu.h
 * Author: twan8752
 *
 * Created on 26 October 2017, 7:32 PM
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/*MACRO, VARIABLES*/
//#define B_SLCT PORTEbits.RE0
//#define B_NEXT PORTAbits.RA6
#define LED_MAN PORTCbits.RC0
#define LED_AUT PORTCbits.RC1
#define LED_FAC PORTCbits.RC2
    
const unsigned char SETTING_FCT[11][12] ={"SET:MTR_ON ","SET:MTR_OFF",
                                          "SET:MAX_SPD","SET:MAX_YAW",
                                          "SET:PID_KP ","SET:PID_KD ","SET:PID_KI ",
                                          "SET:IR_RATE",
                                          "READ:IR_RAW","READ:IRMEAN","READ:IR_VAR"};
const unsigned char MODE_SLCT[3][12]   = {"MODE:MANUAL","MODE:ROUGE ","MODE:FCTORY"};
const unsigned char DATA_VALUE[10] = {'0','1','2','3','4','5','6','7','8','9'};
const unsigned char SETTING_MAN[3][12] = {"SET:MTR_ON ","SET:MTR_OFF","SET:MAX_SPD"};
const unsigned char SETTING_AUT[2][12] = {"USER:AUTO  ","USER:ASSIST"};
unsigned char value_string[5];

int which_digit;  // which digit we on
int which_number;    // which number is now
int unitdig;
int tenthdig;
int hundrethdig;
int input_value; 
char speed_max, yaw_max, IRsamplerate;
char which_setting;     //mode transition(3 modes)
char modechange;

struct PIDGAIN{
    int kd;
    int kp;
    int ki;
}PID_GAIN;
struct IRVAL{
    int IR_RAW;
    int IR_MEAN;
    int IR_VARIANCE;
}IR_VAL;

void SETUP_INTERRUPT(void);
void Int_to_string(int num);
void SET_SPD(void);
void SET_YAW(void);
void SET_KP(void);
void SET_KD(void);
void SET_KI(void);
void SET_IR_SAMPLE_RATE(void);
//int READ_IRRAW(void);
//int READ_IRMEAN(void);
//int READ_IRVAR(void);


void MODE_MANUAL(void);
void MODE_FACTORY(void);
void MODE_ROUGE(void);


void errorstate(void);
#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

