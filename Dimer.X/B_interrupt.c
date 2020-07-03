/*
 * File:   B_interrupt.c
 * Author: swticher
 *
 * Created on 21 de junio de 2019, 10:28 AM
 */


#include <xc.h>
#include <pic18f4550.h>
#include"B_interrupt.h"

/*how to works?
 * define in the page 100 datasheet
 */
void InitInterruptRB(void){
    /*digital pins RB0-4 digital other pins B567 
     * are PGM PGC PGD define in TRIS.*/
    ADCON1bits.PCFG = 0x0F;    
    TRISB=0xFF;                //define inputs all TRISB
   // LATB=0xFF;                  //define all LATB 1
    INTCONbits.GIE=1;           //enable Global Interrupts
   // INTCONbits.RBIE=1;          //Enable Interrupt PORTB
   // INTCONbits.RBIF=0;          //FLAG change on portB init 0
    
    //INTCON2bits.RBIP=0;         //LOW priority for RB interrupt
    INTCON2bits.RBPU=0;         //Pull up enable by individual port latch values
    
    
    //INTCON2bits.INTEDG0=1;      //rb0 external interrupt enable
    INTCON2bits.INTEDG1=1;      //rb1 external interrupt enable
    //INTCON2bits.INTEDG2=1;      //rb2 external interrupt enable
    
    INTCON3bits.INT1E=1;           //enable external interrupt for RB1
    //INTCON3bits.INT2E=1;
    INTCON3bits.INT1IF=0;
    //INTCON3bits.INT2IF=0;
    
    

}