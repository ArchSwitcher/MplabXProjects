/*
 * File:   main.c
 * Author: swticher
 *Timer 1 como temporizador de 5 segundos
 * Created on 9 de junio de 2019, 04:49 PM
 * timer 1 configurado como temporizado de 5 segundos 
 */
 
#define _XTAL_FREQ 16000000
#include"config.h"

void __interrupt(high_priority) MY_ISR_TIMER_1(void);
 int cont=0;
 
void Timer1_init(void){
    INTCONbits.GIE = 1; //set this for what the bit IPEN init whit 0  PAGE 127
    T1CONbits.RD16 = 1; //set 16bits r/w 
    //T1CONbits.T1RUN = 1; //clock another source
    T1CONbits.T1CKPS = 0x03;  //0b11  1:8 prescale
    //T1CONbits.TMR1CS = 0; //Internal Clock
    PIE1bits.TMR1IE = 1;  //enable timer1_overflow
    PIR1bits.TMR1IF = 0;   //flag timer1_overflow init_0
    INTCONbits.PEIE =1;     //enable peripheral interrupts
    T1CONbits.TMR1ON =1;   //ON timer1
    TMR1L =  3035 >> 8;
    
}

void Init_ports(void){
    ADCON1bits.PCFG=0xF;   //0b1111 set all portsB digitals
    //7|6|5|4|3|2|1|0
    TRISB=0x0F; //set output 0-4 inputs 0b00001111
    TRISA=0x00; //set all PORTA outputS
    LATBbits.LB0=1; //set portRB0.RB0 for pull-up    
    LATA=0x00;   //init all PORTA=0
}

void main(void) {
    Init_ports();
    Timer1_init();
    while(1){
        /*if (PORTBbits.RB0==0){
            __delay_ms(50);
            PORTA=0x01; //0b00000001
            //TMR1H = 62500;
            //TMR1L = (62500)>>8;
        }*/
         if (cont<=20){
            PORTA=0x01;
         }
    }
}

void __interrupt(low_priority) TIMER_1(void){
    if (PIR1bits.TMR1IF){
        //__delay_ms(1000);
        PIR1bits.TMR1IF=0;
        TMR1L = 3035 >> 8;
        if((cont >=20) && (cont<=50)){
            PORTA=0x00;
            if(cont>=49){
                cont=0;
            }
                
        }
        cont++;
    }
    
}


     /*Calculus in seconds for the timer1 in mode timer
       
       
      */

        