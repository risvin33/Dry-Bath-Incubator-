#include "DRY.h"

int timeShift = 60;
// Simulated button flags

char cnt;

void simulateButtonInput() {
    if (UP) {
        // Logic for incrementing temperature or timer
        if (isSettingTimer) {
            // Logic for incrementing timer 
            timeInSeconds += timeShift;
            if (timeInSeconds > 61200)timeInSeconds = 0;
        } else {
            // Logic for incrementing temperature 
            desiredTemperature += 1.0;
        }
        __delay_ms(8);
    }

    if (DOWN) {
        // Logic for decrementing temperature or timer
        if (isSettingTimer) {
            // Logic for decrementing timer 
            if (timeInSeconds >= timeShift) {
                timeInSeconds -= timeShift; // Decrement timer by 60 seconds 
            }
        } else {
            // Logic for decrementing temperature 
            desiredTemperature -= 1.0;
        }
        __delay_ms(8);
    }


    if (MODE) {
        // Logic for toggling between temperature adjustment and timer setting
        while (MODE) {
            cnt++;
            __delay_ms(50);
        }

        if (cnt < 20) {
            isSettingTimer = ~isSettingTimer;
            if (~isSettingTimer) {
                //                isStart = ~isStart;
                timeInSeconds = 0;
                timeShift = 60;
            } 
            
        } else {
            if (timeShift == 60) {
                timeShift = 3600;

            } else
                timeShift = 60;


        }
        cnt = 0;

    }
    if (START) {
        if (!isSettingTimer) {

            isStart = ~isStart;
            switchIsPressed = 1;
            __delay_ms(8);
        } else {
            isTimer = ~isTimer;
            __delay_ms(8);
        }
    }

}
