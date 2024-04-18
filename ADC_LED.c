#include "DRY.h"
char cnt1,cnt2=0,cnt3=1;

void ADC_Init() {
    ADCON0 = 0b01000001; // ADC ON, Fosc/8, AN0 selected
    ADCON1 = 0b10000000; // Right justify result, VDD as Vref
}

// Function to read ADC
unsigned int ADC_Read(unsigned char channel) {
    ADCON0bits.CHS = channel; // Select ADC channel
      ADCON0bits.GO = 1; // Start ADC conversion
    while(ADCON0bits.GO); // Wait for conversion to complete
       return (unsigned int) (ADRESL | (ADRESH << 8));
}



void Led(){

if (readTemperature() < desiredTemperature && isStart)
{
    
    if(cnt1>7){
    TEMP_LED = ~TEMP_LED;
        cnt1 =0;
    }
    else  cnt1++;
}
else if(readTemperature() == ((desiredTemperature) || (desiredTemperature+1) || (desiredTemperature-1)) ) TEMP_LED = 0;

else if (readTemperature() <desiredTemperature && ~isStart)
{
       if(cnt3>0 && cnt3<20){ TEMP_LED = 1;
    cnt3++;
    }
    else if(cnt3>=20 && cnt3<22){ TEMP_LED = 0;
    cnt3++;}
    else cnt3=1;

}


if (timeInSeconds>0 && isTimer)
{  
     if(cnt2>10){
         TIME_LED =~TIME_LED;
         
     } else cnt2++;
}
else TIME_LED = 1;

}

