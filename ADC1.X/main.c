/*
 * File:   main.c
 * Author: swticher
 *
 * Created on 25 de julio de 2019, 08:08 PM
 */

#include <pic18f4550.h>
#include<xc.h>

#include"config.h"
#include"lcd.h"
#include"ADC.h"
#include"stdio.h"

int Value;
float voltage;
char datos[20];



void main(void) {
    
  //PUERTO DE SALIDA PARA LA LCD bit 0y1 son entradas
    TRISD = 0x03;  //se declara aca para que la LCD no tenga conflictos al tomar el puerto
    TRISA = 0xFF;   //Se declara antes de ADCInit para que los puertos sean entradada
    Lcd_Init();
    ADCInit();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("********ADC********");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("By: Switcher");
    __delay_ms(1000);
    Lcd_Clear();
    
    while(1){
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("EL Valor ES");
        __delay_ms(500);

        Value = ADC_Read(0);
        voltage = Value*5.0/1023;
        sprintf(datos,"%.3f",voltage);   //redondea a 2 decimales

        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(datos);
        __delay_ms(500);
        
    }
}

/*
 * TRISA = 1; // PORTA -> Entrada
    TRISD = 0; // portd -> SALIDA
    ADCON1bits.PCFG = 0; // Todos los puertos Analogicos
    ADCON1bits.VCFG = 0;
    ADCON0 = 0;
    ADCON2bits.ACQT = 3;
    ADCON2bits.ADCS = 5;
    ADCON2bits.ADFM = 1;
    ADCON0bits.ADON = 1;
    while(1){
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE == 1);
        PORTD = ADRESL;
    }
 */