



#ifndef FUSES_H
#define	FUSES_H

#ifdef	__cplusplus
extern "C" {
#endif

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON        // Internal/External Oscillator Switchover bit (Oscillator Switchover mode enabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)
#include <xc.h>
    
/**Microcontrolador*/    
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
/**Frecuencia de 8MHz*/
#define _XTAL_FREQ 8000000 //Crystal Oscillator Frequency 8MHz
#include <time.h>
//MACROS QUE FACILITARAN LA DEFINICION DE LAS VARIABLES
/**Estado encendido*/
#define ON 1
/**Estado apagado*/    
#define OFF 0
/**Definir como salida*/    
#define OUTPUT 0
/**Definir como entrada*/          
#define INPUT 1
    
#define LED_R  TRISDbits.TRISD0 
#define LED_Y TRISDbits.TRISD1
#define LED_G TRISDbits.TRISD2
#define ALCOHOL TRISDbits.TRISD6
#define ALARMA TRISDbits.TRISD7
#define PIR TRISAbits.TRISA4
#define S_MAGNETICO TRISAbits.TRISA3
#define RS_ TRISBbits.TRISB7
#define EN_ TRISBbits.TRISB6
#define D4_ TRISBbits.TRISB5
#define D5_ TRISBbits.TRISB5
#define D6_ TRISBbits.TRISB3
#define D7_ TRISBbits.TRISB2
#define SENSOR_M TRISBbits.TRISB1
//PINES DE ENTRADA PARA LOS SENSORES
#define PIR_read PORTAbits.RA4 // Sensor pir conectado a RA4
#define SENSOR_MAG PORTBbits.RB1
#define S_MAGNETICO_read PORTAbits.RA3 // Sensor magnetico conectado a RA3
//PINES DE SALIDA PARA LOS LED Y PARA LA MOTOBOMBA
#define LED_RED PORTDbits.RD0 // LED rojo   conectado a RD0
#define LED_YELLOW PORTDbits.RD1 // LED amarillo conectado a RD1
#define LED_GREEN PORTDbits.RD2 // LED verde conectado a RD2
#define ALCOHOL_OUT PORTDbits.RD6 // Motobomba  conectado a RD6
#define ALARMA_OUT PORTDbits.RD7 // Alarma conectado a RD7
//PINES DE LA PANTALLA LCD    
#define RS PORTBbits.RB7 // Puerto RS del LCD conectado a RB7
#define EN PORTBbits.RB6 // Enable del LCD conectado a RB6
#define D4 PORTBbits.RB5 // Pin D4 del LCD conectado a RB5
#define D5 PORTBbits.RB4 // Pin D5 del LCD conectado a RB4
#define D6 PORTBbits.RB3 // Pin D6 del LCD conectado a RB3
#define D7 PORTBbits.RB2 // Pin d7 del LCD conectado a RB2

#ifdef	__cplusplus
}
#endif

#endif	/* FUSES_H */