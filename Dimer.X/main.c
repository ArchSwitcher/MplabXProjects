/*
 * File:   main.c
 * Author: swticher
 *
 * Created on 6 de agosto de 2019, 06:09 PM
 */
#include"config.h"
#include "USART_Header_File.h"
#include "B_interrupt.h"
#include "timer0.h"

#include <xc.h>
#include <stdlib.h>


int frecuency=0;
char Show[3];
int Counter=0;

int delay;
int comp=0;

void transform(int value){
    
    itoa(Show, value, 10);//conviertiendo valores enteros a decimales base 10 (base 16 hex, base 2 binarios)
    USART_SendString(Show); /* send LED ON status to terminal */
}


void main()
{
    OSCCON=0x72;              /* use internal oscillator frequency
                                 which is set to * MHz */
    char data_in;
    TRISD = 0x00;                /* set PORT as output port */
    PORTD=0;
    
    USART_Init(9600);         /* initialize USART operation with 9600 baud rate */ 
    __delay_ms(50);
    
     InitInterruptRB();          /*iniciando la interrupcion RB1 para que 
    //                       se active con un timer0 un tiempo determinado el trica bt136*/
  //  Timer0_Init();
    
    while(1)
    {
        data_in=USART_ReceiveChar();
        
        if(data_in=='1')  //DESARROLAR UN CONERTIDOR DE STRING A INT PARA VARIAR EL DELAY
        {   
            USART_SendString("delay1"); // send LED ON status to terminal 
            delay=1;
        }
        else if(data_in=='2')
                
        {
            USART_SendString("delay2");// send LED ON status to terminal 
            transform(Counter);
            delay=2;
        }
        else if(data_in=='3')
        {
            USART_SendString("delay3");// send msg to select proper option 
            delay=3;
        }
        else if(data_in=='4')
        {
            USART_SendString(" delay4"); // send msg to select proper option 
            delay=4;
        }
        else if(data_in=='5')
        {
            USART_SendString(" delay4"); // send msg to select proper option 
            delay=5;
            Counter=0;
        }
        else{
           USART_SendString("select 1, 2 or 3 or 4"); // send msg to select proper option 
        }
        
         /*if(comp <=4){
                PORTDbits.RD0 =0;
                T0CONbits.TMR0ON = 0;           // tmr0 apagado
        }
            else if(comp >= 5){  
                PORTDbits.RD0 =1;   
        }*/
        
        
    }
    
}

void __interrupt(high_priority) interruptRB(void){
     
     if(INT1E && INT1IF){
            Counter++;              //solo cuenta los pulsos de cada cruce por cero
            INTCON3bits.INT1IF=0;
            if(delay==1){
            PORTDbits.RD0 =0;
            __delay_ms(6);
            PORTDbits.RD0 =1;
            __delay_ms(2);
            }
            else if(delay==2){
            PORTDbits.RD0 =0;
            __delay_ms(4);
            PORTDbits.RD0 =1;
            __delay_ms(4);
            }
            else if(delay==3){
            PORTDbits.RD0 =0;
            __delay_ms(3);
            PORTDbits.RD0 =1;
            __delay_ms(5);
            }
            else if(delay==4){
            PORTDbits.RD0 =0;
            __delay_ms(1);
            PORTDbits.RD0 =1;
            __delay_ms(7);
            }
            else if(delay==5){
            PORTDbits.RD0 =0;
            
            }

/*            T0CONbits.TMR0ON = 1; // Tmr0 empieza
            TMR0 = 0xFF07;     //1mS*/
        }
        
            if(TMR0IE && TMR0IF){
                if(comp>=6){
                    comp=0;
                }
                comp++;
                INTCONbits.TMR0IF=0;
                TMR0 = 0xFF07;     //1mS
                
        }
            
      INTCONbits.RBIF=0;
     }