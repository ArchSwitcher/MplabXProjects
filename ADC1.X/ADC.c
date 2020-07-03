/*
 * File:   ADC.c
 * Author: swticher
 *
 * Created on 30 de julio de 2019, 04:06 PM
 */

/*MAS INFO EN pag269 DATASHEET--> Este adc tiene un TAD=1us(ACQT=TAD*4)--> utiliza 4 microsegundos para el tiempo de cada bit a convertir
 * Esta configurado para un cristal de 16MHZ (ADCS)
 * */
#include "config.h"
#include<xc.h>
#include <pic18f4550.h>

//calculando TAD 
//Clock 16Mhz 
//TOSC 1/16Mhz = 62.5ns
//el minimo es 0.8 us y maximo es 25us TAD 16xTOSC 
// 16x62.5ns = 1us
// 1 TAD = 1us
//TACQ tiempo minimo de conversion  2.45us
//TACQ = TAD * 4 = 4us  pagina269

void ADCInit(void){


    ADCON1bits.PCFG = 0b1110;
    ADCON1bits.VCFG = 0b00;
    ADCON0 = 0x00;
    ADCON2bits.ACQT = 0b010;
    ADCON2bits.ADCS = 0b101;
    ADCON2bits.ADFM = 1;
    ADCON0bits.ADON = 1;
}
unsigned int ADC_Read(unsigned char ch){
    if(ch>13){
        return 0;
    }
    ADCON0=0;
    ADCON0 = (ch<<2);
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    ADCON0bits.ADON = 0;
    return ADRES;
}