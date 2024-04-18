#include "DRY.h"

float voltage,voltageAvg;
char tmpCounter2;
float readTemperature() {
    if(tmpCounter2<9)
    {
      voltageAvg += (ADC_Read(0) - 179); // Convert ADC value to voltage (assuming Vref = 5V)
     tmpCounter2++;
    }
    else
    {
       voltage = voltageAvg;
       tmpCounter2=0;
       voltageAvg =0;
    }
     
    return (voltage * 0.185);
}




unsigned char Float_to_String(unsigned char *str, float f, char NumberOfdecimalPlaces, unsigned char character, unsigned char position)
{
    unsigned char p, k, o, flag = 0;
    unsigned char i;
    unsigned long t, d;
    unsigned int z = 1;
    for (i = 0; i < NumberOfdecimalPlaces; i++)
    {
        z = z * 10;
    }
    t = f*z; //default 10                                                //                          1234567  234567   34567   4567   567   67   7   
    //             1                         2                                  3                                           4                                               5                                                        6                                                          7                               
    d = (((t / 1000000) << 24) |
            (((t % 1000000) / 100000) << 20) |
            ((((t % 1000000) % 100000) / 10000) << 16) |
            ((((t % 1000000) % 100000) % 10000) / 1000 << 12) |
            (((((t % 1000000) % 100000) % 10000) % 1000) / 100 << 8) |
            ((((((t % 1000000) % 100000) % 10000) % 1000) % 100) / 10 << 4) |
            (((((((t % 1000000) % 100000) % 10000) % 1000) % 100) % 10) / 1 << 0));


    for (o = 1; o < position; o++)
    {
        if (*str == '\0')
            *str = ' ';
        str++;
    }

    flag = 0;
    for (k = 28; k >= 0; k = k - 4)
    {
        p = d>>k;
        p = p & 0x0F;
        if ((p && !flag) || ((character == 'V' || character == 'W') && !p && !flag && (k == ((4 * (NumberOfdecimalPlaces - 1)) + 8))) || (!p && !flag && (k == ((4 * (NumberOfdecimalPlaces - 1)) + 4))) || (!p && flag) || p || (k == 8) || (k == 4))
        {



            if ((character == 'V' || character == 'W') && !p && !flag && (k == ((4 * (NumberOfdecimalPlaces - 1)) + 8)))
            {
                *str = ' ';
            }

            else if (k == (4 * (NumberOfdecimalPlaces - 1)))
            {
                *str = ' ';
                str++;
                *str = p + '0';
            }
            else
            {
                *str = p + '0';
            }
            str++;

            if (k == 0)
            {
                *str = '\0';
                break;
            }
            flag = 1;
        }
    }


    flag = 0;
    *str = '\0';
}