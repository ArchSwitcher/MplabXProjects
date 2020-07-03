
#include <pic18f4550.h>
#include"timer0.h"
#include<xc.h>
#include"config.h"

int cont;

void InitPort(void){
    ADCON1bits.PCFG = 0xF; // Digitales
    TRISB = 1;
    TRISA = 0;
    LATB = 1;
    LATA = 0;
    cont=0;
}

void main(){
    Timer0_Init();
    InitPort();
    T0CONbits.TMR0ON = 1; // Tmr0 empieza
    while(1){
       
        if(cont <= 101){
        LATAbits.LA0=1;
        }
        
    }
}

void __interrupt(low_priority) ISR_TIMER(void){
    if(TMR0IE && TMR0IF){
                    
            if((cont >= 101) && (cont <= 200)){
                LATAbits.LA0 = 0;
            }
            if(cont >= 201){
                cont=0;
            }
        cont++;
        INTCONbits.TMR0IF=0;
        TMR0 = 0xEC77;     //100mS
        //TMR0L = 0x77;     //
    }
}


//Temporizador = (4/Fosc)*Pre-escaler*(x+1)
//        3s   = (4/16MHz)*256*(x+1)
//        x  = 46875

/*x=((Temp*Fosc)/(4*Prescaler))
 
 */
/*
 * File:   ProgramaPrincipal.c
 * Author: Wels modify by switcher
 *
 * Created on 8 de marzo de 2018, 09:29 PM
 */
