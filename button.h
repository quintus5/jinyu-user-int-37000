/* 
 * File:   button.h
 * Author: twan8752
 *
 * Created on 26 October 2017, 2:15 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif
#define B_SLCT PORTBbits.RB3
#define B_NEXT PORTBbits.RB4
    
void SETUP_BUTTON(void);
void mode0(void);
void mode1(void);
void mode2(void);
void lopri(void);
void hipri(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

