#ifndef DRY_H
#define	DRY_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define _XTAL_FREQ 4000000

// Global variables

void __interrupt() INTERRUPT_InterruptManager(void);
char temperatureMode = 'C' ,tempCounter2;
float currentTemperature;
float desiredTemperature = 30;
float previousError, integral;

#define TEMP_LED PORTCbits.RC4
#define TIME_LED PORTCbits.RC5
// Define necessary constants


// PWM configuration parameters
#define PWM_PERIOD 1024    // PWM period for the desired frequency
#define PWM_MAX_DUTY 255// Maximum duty cycle value for PWM (8-bit resolution)

#define UP PORTAbits.RA4
#define DOWN PORTAbits.RA5
#define MODE PORTAbits.RA3
#define START PORTAbits.RA6
#define TEMP PORTCbits.RC2

// LCD pins connection to PIC16F886
#define LCD_RW PORTBbits.RB1
#define LCD_RS PORTBbits.RB2
#define LCD_EN PORTBbits.RB3
#define LCD_D4 PORTBbits.RB4
#define LCD_D5 PORTBbits.RB5
#define LCD_D6 PORTBbits.RB6
#define LCD_D7 PORTBbits.RB7

#define LCD_DATA_PORT PORTB
#define OUTPUT 0
#define INPUT 1

// Global variables

float calculatePID(float desiredTemp, float currentTemp);
void TempCntr(float curTemp ,float setTemp);
void displayData(int Temp, bool isSettingTimer, int timeInSeconds, int desTemp);


void updateHeatingPWM(float currentTemp, float targetTemp);
float convertToTemperature();
float readTemperature();
// Function to initialize LCD
Drive_LCD(unsigned char byte);
void send_command_byte(unsigned char byte);
void send_data_byte(unsigned char byte);
void Write_LCD(unsigned char *s, unsigned char address, unsigned char row_offset);
void initLCD(void);
// Function to initialize ADC
void ADC_Init();

// Function to read temperature
unsigned int ADC_Read(unsigned char channel);


void PWM_Init();
void Led();
void simulateButtonInput();
int updateTimer(int elapsedSeconds);
void readSwitches();
bool isSettingTimer =0;    // Initially, not in timer setting mode
bool isStart =0;
bool isTimer =0;
bool switchIsPressed;
bool warmFlag;
void LcdStart();

int timerSetButton = 0;    // Button state for setting timer
unsigned int timeInSeconds = 0;     // Initially, timer set to 0 seconds
int elapsedSeconds = 0;    // Elapsed time counter
unsigned char RS;
unsigned char Float_to_String(unsigned char *str, float f, char NumberOfdecimalPlaces, unsigned char character, unsigned char position);
void printTimer(unsigned char hours, unsigned char minutes, unsigned char seconds);

#endif   // DBIn_H



