/*!
\file   fuses.h
\date   2020-12-14
\author Juan Andrés Salazar Gonzalez- Andrés Felipe Perez Perez - Gersain Galindez Buitrón < juanandress@unicauca.edu.co afepepe@unicauca.edu.co gersaing@unicauca.edu.co>
\brief  configuration bits pic18f4550.
\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.
\par
Copyright (c) unicauca 2020. All rights reserved.
\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include "FUSES.h"
#include<ctype.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pic18f4550.h"
#include <ctype.h> 
#include <time.h>

// FUNCIONES DE LOS SENSORES
unsigned int Leer_S_Magnetic(int aux2);
unsigned int Leer_Pir(int aux2);

unsigned int Dips_Alcohol(int aux2);
void Alarma_ON(void);
// FUNCIONES DE LA PANTALLA LCD
void Lcd_Init();  
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Init(void);
void Lcd_Clear(void);
void Lcd_Port(char a);
void Lcd_Set_Cursor(char a, char b);
void Estado_Sis(int count);



/**\brief Main del algoritmo*/
int main() {
    /** 
        \details
     Algoritmo para la automatizacion la desinfeccion de manos de personas
     */
    int count=0;
    //OSCCON=0x72; 
  //Configura los pines RD7-RD6-RD5-RD4 como salida digital
    LED_R = OUTPUT;
    LED_Y = OUTPUT;
    LED_G = OUTPUT;
    ALARMA = OUTPUT;
    ALCOHOL= OUTPUT;
    TRISB=OUTPUT;
    SENSOR_MAG=OUTPUT;
    //Configura los pines RB7-RB6-RB5-RB4 como entrada digital
    PIR=INPUT;
    S_MAGNETICO=INPUT;
    
    
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Analógica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisición 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversión Fosc/8.
    ADCON2bits.ADFM = 0; //  Justificación Izquierda (modo-8bits).
    ADCON0bits.ADON = 1; //  Habilita el Módulo AD.
    
    
    while(PORTEbits.RE3==1){// Ciclo que solo acabará con el reset
    count=Leer_Pir(count);// Analisa los sensores del sistema
    Estado_Sis(count);// Muestra en pantalla informacion referente al sistema
    
    }
}

/*F**************************************************************************
* NAME: Leer_Pir
*----------------------------------------------------------------------------
* PARAMS:
* val: numero de personas 
* return:   numero actual de personas 
*----------------------------------------------------------------------------
* PURPOSE:
* Deacuerdo a la activacion del sensor Pir y el sensor magnectico desinfecta
 * las manos de las personas , en caso contrario suena una alarma por 500ms
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Funcion leer sensor PIR*/
unsigned int Leer_Pir(int count) {// Lee el sensor de presensia PIR 
      /** 
        \details
       Analizar con el sensor PIR si hay presencia de una persona 
     */
    if(PIR_read==ON)// Si hay una persona enciende el amarillo y lee otro sensor 
    {
        SENSOR_MAG=ON;
        LED_RED=OFF;
        LED_YELLOW=ON;
        
        __delay_ms(500);
        count=Leer_S_Magnetic(count);// Se lee el sensor magnetico
    }
    else{// Sino enciende el led rojo
          LED_RED=OFF;
          LED_YELLOW=OFF;
    }
   return(count); 
}

/*F**************************************************************************
* NAME: Leer_S_Magnectic
*----------------------------------------------------------------------------
* PARAMS:
* val: numero de personas 
* return:   count, numero de personas desinfectadas actual
*----------------------------------------------------------------------------
* PURPOSE:
* Leer el sensor magnectico y si se activa prende una motobomba para desinfectar
 * las manos de las personas, caso contrario hace sonar una alarma por 500ms
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/

/**\brief Analizar sensor magnectico*/
unsigned int Leer_S_Magnetic(int count) {
      /** 
        \details
       Analiza las manos de la persona estan enfrente del sensor 
     */
    if(S_MAGNETICO_read==ON){
        count=Dips_Alcohol(count);//Se dispensa alcohol 
    }
    else{
        SENSOR_MAG=OFF;
        LED_RED=ON;
        Alarma_ON();// Enciende una alamar si no hay desinfeccion
    }
    return(count);
}


/*F**************************************************************************
* NAME: Dips_Alcohol
*----------------------------------------------------------------------------
* PARAMS:
* val: count,numero de personas
* return:   count, nuevo numero de personas
*----------------------------------------------------------------------------
* PURPOSE:
* Dispensa alcohol activando una motobomba y suma 1 el numero de personas
 * desinfectadas
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Dispensar alcohol*/
unsigned int Dips_Alcohol(int count) { // Dispensa mientra
      /** 
        \details
       Dispensa alcohol activando el pin donde se conecta la motobomba
     */

    while(S_MAGNETICO_read==ON){
     LED_YELLOW=OFF;
     LED_GREEN=ON;
     ALCOHOL_OUT=ON;//Enciende la motobomba de alcohol
    }
    ALCOHOL_OUT=OFF;
    LED_GREEN=OFF;
    count=count+1;
    SENSOR_MAG=OFF;
    return(count);
}


/*F**************************************************************************
* NAME: Alarma_ON
*----------------------------------------------------------------------------
* PARAMS:
* val: none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Enciende y apaga los led amarillo y verde. Hace sonar una alarma por 500ms
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Encender alarma*/
void Alarma_ON(void){//Enciende una alarma
      /** 
        \details
       Enciende una alarma durante 500ms cuando no hay desinfeccion 
     */
    ALARMA_OUT=ON;
    LED_YELLOW=ON;
    __delay_ms(500);//Duran 500ms se mantiene la alarma prendida
     ALARMA_OUT=OFF;
     LED_YELLOW=OFF;
     
}

/*F**************************************************************************
* NAME: Estados_Sis
*----------------------------------------------------------------------------
* PARAMS:
* val: count,numero actual de personas
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Imprimir lo valores actuales del sistema
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Actualizar pantalla*/
void Estado_Sis(int count){// Actualiza la pantalla LCD
      /** 
        \details
       Actualiza e imprime en pantalla #personas, nivel de alcohol y fecha 
     */
    char aux[5];
    Lcd_Init();  
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("#Per:");
    Lcd_Set_Cursor(1,6); 
    sprintf(aux,"%d",count);
    Lcd_Write_String(aux);// Imprime el numero de personas desinfectadas
    Lcd_Set_Cursor(1,10);
    Lcd_Write_String("Niv:");//Imprimi el nivel de alcohol
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("15/12/2020");//Imprimi fecha
   }
/*F**************************************************************************
* NAME: Lcd_Port
*----------------------------------------------------------------------------
* PARAMS:
* val: Caracter 
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Actualizar pines del LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Actualiza pines LCD*/
void Lcd_Port(char a){// Actualiza los pines de la pantalla LCD

      /** 
        \details
       Actualiza los pines conectados a la pantalla LCD
     */
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}
/*F**************************************************************************
* NAME: Lcd_Cmd
*----------------------------------------------------------------------------
* PARAMS:
* val: a, caracter 
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Manda comandos al LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Comandos LCD*/
void Lcd_Cmd(char a){// Envia un comando para la LCD

      /** 
        \details
       Envia comandos a la pantalla LCD
     */
	RS = 0;             // => RS = 0
	Lcd_Port(a);
	EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}
/*F**************************************************************************
* NAME: Lcd_Clear
*----------------------------------------------------------------------------
* PARAMS:
* val: none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Borra todo en la pantalla LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Clear del LCD*/
void Lcd_Clear(void){//Borra toda la pantalla LCD

      /** 
        \details
       Borra todo lo que hay en la LCD 
     */
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}
/*F**************************************************************************
* NAME: Lcd_Set_Cursor
*----------------------------------------------------------------------------
* PARAMS:
* val: x,y, coordenadas donde poner el cursor
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Actualiza las coordenadas del cursor LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Obtener cursor*/
void Lcd_Set_Cursor(char a, char b){//Obtiene la ubicación del cursor en LCD

      /** 
        \details
       Asigna las coordenadas del cursor en la pantalla LCD
     */
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}
/*F**************************************************************************
* NAME: Lcd_Init
*----------------------------------------------------------------------------
* PARAMS:
* val: none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Inicializa los valores del LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Incializacion del LCD*/
void Lcd_Init(void){// Inicializ la LCD

      /** 
        \details
       Pone los valores inciiales de la Pantalla LCD
     */
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(11);
  Lcd_Cmd(0x03);
 
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}
/*F**************************************************************************
* NAME: Lcd_Write_Char
*----------------------------------------------------------------------------
* PARAMS:
* val: a, caracter a escribir
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Escribe un caracter en la pantalla LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Escribir char*/
void Lcd_Write_Char(char a){// Escribe en la LCD un caracter 

      /** 
        \details
       Escribe en pantalla un caracter
     */
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}
/*F**************************************************************************
* NAME: Lcd_Write_String
*----------------------------------------------------------------------------
* PARAMS:
* val: primera posicion de la cadena
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Escribe una cadena de caracteres en la pantalla LCD
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
/**\brief Escribir cadena*/
void Lcd_Write_String(char *a){// Escribe en la LCD una palara

      /** 
        \details
       Escribe en la pantalla LCD una cadena 
     */
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}



