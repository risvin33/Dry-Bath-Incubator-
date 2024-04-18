#include <pic16f886.h>

#include "DRY.h"
 int tempCounter;
 extern unsigned int timeInSeconds;
 char RunningState =0;

void __interrupt() INTERRUPT_InterruptManager(void) {
    if (INTCONbits.T0IF) {
        
        if (tempCounter > 4100) {
            if (timeInSeconds > 0)
                if(isSettingTimer){
               if(isTimer) {
                timeInSeconds--;
               __delay_ms(8); }}
            tempCounter = 0;
        } else tempCounter++;
        
        INTCONbits.T0IF = 0;

    }
}