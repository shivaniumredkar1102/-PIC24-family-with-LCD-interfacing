/*Author -- Shivani Umredkar
 * Date -- 19-11-018
 * Program to implement basic LCD interfacing with PIC24 as well blink LED. 
// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2

// PIC24FJ64GA010 Configuration Bit Settings

// 'C' source line config statements
*/
// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/*HERE pin connection
 LCD pin connection
 * VDD - +5V
 * VSS - GND
 * VEE - GND
 * RS  - RD0
 * E   - RD1
 * RW  - GND
 * D4  - RD2
 * D5  - RD3
 * D6  - RD4
 * D7  - RD5
 * 
 * RE0 - LED
 */
#define FCY 8000000UL  
#include <xc.h>
#include <p24FJ64GA010.h>
#include <string.h>
#include <stdio.h>
#include <libpic30.h>



#define RS_PIN LATDbits.LATD0 // RD0 --> RS
#define E_PIN LATDbits.LATD1  // RD1 --> E 
#define D4_PIN LATDbits.LATD2 // RD2 --> D4
#define D5_PIN LATDbits.LATD3 // RD3 --> D5
#define D6_PIN LATDbits.LATD4 // RD4 --> D6
#define D7_PIN LATDbits.LATD5 // RD5 --> D7

#define RS_TRIS TRISDbits.TRISD0
#define E_TRIS TRISDbits.TRISD1
#define D4_TRIS TRISDbits.TRISD2
#define D5_TRIS TRISDbits.TRISD3
#define D6_TRIS TRISDbits.TRISD4
#define D7_TRIS TRISDbits.TRISD5

#include "lcd_h.h"


void main()
{
    int count;
    count=0;
    TRISEbits.TRISE0 = 0;
    LATEbits.LATE0 = 1;
    lcd_init();
    
    lcd_cmd();
    lcd_print("Hello World :)");
    __delay_ms(10);
    
    while(1)
    {
       LATEbits.LATE0 = 1;   // LED - ON
       lcd_clr();
       lcd_print("count = ");
       __delay_ms(10);
       count++;   
       lcd_numXY(0,8,count); // (row,column,variable in int)print integer value
       __delay_ms(20);
       lcd_clr();
       LATEbits.LATE0 = 0;  // LED - OFF
       __delay_ms(100);
    }
}