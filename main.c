#pragma config FOSC = INTRC_NOCLKOUT    // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF  // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON   // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF    // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit 

#include <pic16f886.h>

#include "DRY.h" 
char buf[5], a[5];

void main() {
    OSCCON = 0x77;
    ANSELH = 0;
    ANSEL = 0x01;
    TRISB = 0;
    PORTB = 0;
    OPTION_REG = 0b01010000; // configure timer0( pre-scaler 1:1 )
    INTCON = 0b10100000; // enable interrupt of timer0

    ADC_Init();
//    PWM_Init();
    initLCD();
    LcdStart();
    TRISAbits.TRISA6 = 1;
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA3 = 1;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    while (1) {
        float curTemp = readTemperature();
        Float_to_String(buf,curTemp , 0, 0, 1);
        Float_to_String(a, desiredTemperature, 0, 0, 1);
        simulateButtonInput();
        
        TempCntr(curTemp,desiredTemperature);
        Led();
        displayData(buf, isSettingTimer, timeInSeconds, a);
        __delay_ms(100);
    }

}
