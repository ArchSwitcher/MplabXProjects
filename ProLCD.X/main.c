/*
 * File:   main.c
 * Author: swticher
 *
 * Created on 25 de junio de 2019, 11:10 PM
 */


#include <xc.h>
#include"config.h"
#include"lcd.h"
#include"DELAY.h"
#include <stdio.h>


void main(void) {
    
    TRISA=0x00;
    
  unsigned int a;
  int b;
  TRISD = 0x00;
  Lcd_Init();
  
  
  
  for(b=0;b<4;b++){
      LATA=0x01<<b;
      __delay_ms(700);
  }
  
  while(1)
  {
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Curso PIC18F");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("PABLO_ZAPETA");
    MsDelay(2000); // UN TIEMPO DE ESPERA.
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("HOLA");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("MUNDO");
    MsDelay(2000); // UN TIEMPO DE ESPERA.
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("PAblo Zapeta");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("@GMAIL.COM");
    MsDelay(2000); // UN TIEMPO DE ESPERA.
    MsDelay(2000); // UN TIEMPO DE ESPERA.
    for(a=0;a<15;a++)
    {
        MsDelay(300); // UN TIEMPO DE ESPERA.
        Lcd_Shift_Left();
    }

    for(a=0;a<15;a++)
    {
        MsDelay(300); // UN TIEMPO DE ESPERA.
        Lcd_Shift_Right();
    }
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("TELF.:77720351");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char('O');
    Lcd_Write_Char('K');
    MsDelay(2000); // UN TIEMPO DE ESPERA.
  }
}
