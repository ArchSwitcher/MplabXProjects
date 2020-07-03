/*
 * File:   main.c
 * Author: swticher
 *
 * Created on 26 de junio de 2019, 12:43 AM
 */

#include"timer0.h"
#include"config.h"
#include"lcd.h"
#include"B_interrupt.h"
#include"stdlib.h"

//entero para contar el numero de pulsos
    int Counter=0;
    char Show[3];
    int b,i;
    int delay;
    int flagEntry;
    
    
    
    
void InitALL(void){
   
    TRISA=0x00;   //all porta output
    LATA=0x0;   //all porta init 0
    b=0;
    Counter=0;
    delay=0;
    flagEntry=0;
}
void transform(int value){
    
    itoa(Show, value, 10);//conviertiendo valores enteros a decimales base 10 (base 16 hex, base 2 binarios)
    Lcd_Set_Cursor(2,7);
    Lcd_Write_String(Show);
    __delay_ms(1000);

}

void main(void) {
    
   
    //PUERTO DE SALIDA PARA LA LCD bit 0y1 son entradas
    TRISD = 0x03;  //se declara aca para que la LCD no tenga conflictos al tomar el puerto
    InitALL();
    Lcd_Init();
    Lcd_Clear();
    
    /*for(b=0;b<4;b++)
        {
            LATAbits.LA0 = ~LATAbits.LA0;
            __delay_ms(700); // UN TIEMPO DE ESPERA.

        }*/
    
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("LCD CONTADOR");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("POR 5 Segundos");
        __delay_ms(3000);
        Lcd_Clear();
        
        
    

    while(1)
    {
        if(flagEntry==0){
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Preparados!!!!!");
            __delay_ms(500);
            flagEntry=1;
        }
        
        if((PORTDbits.RD0)&&(flagEntry==1)){
            
            Lcd_Clear();
            
            Lcd_Write_String("CONTANDO");
            __delay_ms(500);
            for(i=3; i>-1; i--){
                transform(i);
            }
            flagEntry=5;
            delay=0;
            Timer0_Init();
            InitInterruptRB();
        }
        
        
    }
}


void __interrupt(high_priority) interruptRB(void){
     
    if(TMR0IE && TMR0IF){
            if(delay >= 100){  //1segundo 10ms *100
                //delay=0;
                INTCONbits.TMR0IE = 0;
                INTCON3bits.INT1E = 0;           //disable external interrupt for RB1
                INTCON3bits.INT1IF = 0;
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("RESULTADOS!!!!!");
                
                transform(Counter);
               
                __delay_ms(3000);
                flagEntry=0;
                Counter=0;
            }
        delay++;
        INTCONbits.TMR0IF=0;
        TMR0 = 0xEC77;     //10mS
    }
    
   // if(INTCONbits.RBIF){
            //if(INTCON3bits.INT1IF){
    if(INT1E && INT1IF){
            //__delay_ms(1);
            Counter++;
            INTCON3bits.INT1IF=0;
        }
        INTCONbits.RBIF=0;
   //     }
     
     
     }