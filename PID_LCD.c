#include "DRY.h"

unsigned int i;


#define RW_DIR    TRISBbits.TRISB1 
#define RS_DIR    TRISBbits.TRISB2 
#define EN_DIR    TRISBbits.TRISB3 
#define D4_DIR    TRISBbits.TRISB4 

#define D5_DIR    TRISBbits.TRISB5 

#define D6_DIR    TRISBbits.TRISB6 

#define D7_DIR    TRISBbits.TRISB7 

void send_command_byte(unsigned char byte) {
    unsigned char nibble = byte;
    Drive_LCD((byte & 0xF0) | 0x08);
    __delay_us(200);
    Drive_LCD(byte & 0xF7);
    __delay_us(400);

    byte = nibble << 4;

    Drive_LCD((byte & 0xF0) | 0x08);
    __delay_us(200);
    Drive_LCD(byte & 0xF7);
    __delay_us(400);
}
// Send a data byte (i.e. with pin RS high)

void send_data_byte(unsigned char byte) {
    unsigned char nibble = byte;
    Drive_LCD((byte & 0xF0) | 0x0C);
    __delay_us(200);
    Drive_LCD(byte & 0xF7);
    __delay_us(400);

    byte = nibble << 4;

    Drive_LCD((byte & 0xF0) | 0x0C);
    __delay_us(200);
    Drive_LCD(byte & 0xF7);
    __delay_us(400);
}

void Write_LCD(unsigned char *s, unsigned char address, unsigned char row_offset) {
    {
        address = address + row_offset - 1;
        send_command_byte(address); // Go to start of line 1
        do {
            send_data_byte(*s);
            s++;
        } while (*s);
        send_data_byte(' ');
    }

}

void initLCD(void) {

    LCD_RS = 0;
    LCD_EN = 1;
    __delay_ms(20);
    for (i = 1065244; i <= 0; i--)
        NOP();

    send_command_byte(0x03); // command 0x03 to LCD and wait 5 msecs for the instruction to complete
    __delay_ms(5);
    send_command_byte(0x03); // command 0x03 to LCD and wait 160 usecs for instruction to complete.
    __delay_ms(5);
    send_command_byte(0x03); // command 0x03 AGAIN to LCD and wait 160 usecs (or poll the Busy Flag)
    __delay_ms(5);
    send_command_byte(0x02); // Write 0x02 to the LCD to Enable 4-Bit Mode
    __delay_ms(5);
    send_command_byte(0x28);
    __delay_ms(5);
    send_command_byte(0x02);
    __delay_ms(5);
    send_command_byte(0x08); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    __delay_ms(5);
    send_command_byte(0x00); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    __delay_ms(5);
    send_command_byte(0x0C); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    __delay_ms(5);
    send_command_byte(0x00); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    __delay_ms(5);
    send_command_byte(0x06); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    __delay_ms(5);
}


void LcdStart(){

Write_LCD("   PROMINENT    ", 0x80, 1);

Write_LCD(" Model: PTC100 ", 0xC0, 1);

__delay_ms(4000);

send_command_byte(0x01);
Write_LCD("    PRECISION   ", 0x80, 1);
Write_LCD("TEMP.CONTROLLER", 0xC0, 1);
__delay_ms(3000);
send_command_byte(0x01);
}


void printTimer(unsigned char hours, unsigned char minutes, unsigned char seconds) {
    // Convert hours, minutes, and seconds into individual digits
    unsigned char hourTens = hours / 10;
    unsigned char hourOnes = hours % 10;
    unsigned char minTens = minutes / 10;
    unsigned char minOnes = minutes % 10;
    unsigned char secTens = seconds / 10;
    unsigned char secOnes = seconds % 10;

    // Display string "timer: " on LCD
    unsigned char timerString[] = " Timer: ";
    unsigned char *s = timerString;
    send_command_byte(0x80); // Move cursor to the start of the first line
    do {
        send_data_byte(*s);
        s++;
    } while (*s);

    // Display time on LCD
    send_data_byte(hourTens + '0'); // Display hour tens digit
    send_data_byte(hourOnes + '0'); // Display hour ones digit
    send_data_byte(':'); // Display colon (:)
    send_data_byte(minTens + '0'); // Display minute tens digit
    send_data_byte(minOnes + '0'); // Display minute ones digit
    send_data_byte(':'); // Display colon (:)
    send_data_byte(secTens + '0'); // Display second tens digit
    send_data_byte(secOnes + '0'); // Display second ones digit
}

Drive_LCD(unsigned char byte) {
    LCD_DATA_PORT = byte;
}

void displayData(int Temp, bool isSettingTimer, int timeInSeconds, int desTemp) {

    // Display temperature if timer is not set
    if (!isSettingTimer) {
        //        send_command_byte(0x01);  // Clear display
        
        if(readTemperature() < desiredTemperature && isStart) {
            
                if (switchIsPressed) {
                    switchIsPressed = 0;
                    warmFlag = 1;
                }
                if(isSettingTimer && isStart)warmFlag = 0;
                if (warmFlag == 1) {
//                    send_command_byte(0x01);
                      Write_LCD("  Warming Up...  ", 0x80, 1);
                      Write_LCD(" SV:", 0xC0, 1);
                      Write_LCD("C", 0xC0,8 );
                      Write_LCD(desTemp, 0xC0, 6);
                      Write_LCD(" PV:", 0xC0, 9);
                      Write_LCD("C", 0xC0, 16);
                      Write_LCD(Temp, 0xC0, 14);
                }
            
        } else {

            warmFlag = 0;
            Write_LCD(" Cur Temp:", 0x80, 1);
            Write_LCD("  ", 0x80, 11);
            Write_LCD(Temp, 0x80, 12);
            Write_LCD("C ", 0x80, 15);
            Write_LCD(" Set Temp:", 0xC0, 1);
            

            Write_LCD("  ", 0xC0, 11);
            Write_LCD(desTemp, 0xC0, 12);
            Write_LCD("C", 0xC0, 15);
          
        }



    } else {
        // Display timer if timer is set
        unsigned int remainingTime = timeInSeconds;
        int remainingHours = remainingTime / 3600;
        int remainingMinutes = (remainingTime % 3600) / 60;
        int remainingSeconds = remainingTime % 60;

        printTimer(remainingHours, remainingMinutes, remainingSeconds);
        Write_LCD(" SV:", 0xC0, 1);
        Write_LCD("C", 0xC0,8 );
        Write_LCD(desTemp, 0xC0, 5);
        Write_LCD(" PV:", 0xC0, 9);
        Write_LCD("C", 0xC0, 16);
        Write_LCD(Temp, 0xC0, 14);
    }
}

void TempCntr(float curTemp, float setTemp) {
    if (!isSettingTimer) {
//        float b;
        char cnT;
//        a=(setTemp - curTemp)*0.80;
        if(isTimer)isTimer=~isTimer;
        if (curTemp < setTemp && isStart){ 
//         a=(setTemp - curTemp)*0.80;
//         b=a*0.80;
//           if((setTemp - curTemp)>((setTemp - curTemp)*0.80))
//           {
//               if(cnT>10 && cnT<15){
               TEMP = 0;
//               cnT++;
//               }
//               else if (cnT>=15 && cnT<20)
//               {
//               TEMP = 1;
//               cnT=0;
//               }
//               else cnT++;
//           
//           }
//           else TEMP = 0;
        }
        else TEMP = 1;
    } else {
        
        if (timeInSeconds > 0) {
            if (curTemp < setTemp) TEMP = 0;
            else TEMP = 1;
        } else{ TEMP = 1;
        if(isTimer)isTimer=~isTimer;}
    }

}
