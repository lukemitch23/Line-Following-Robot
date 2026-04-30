/**********************************************************************************************************************************
 *
 *  File name: main.c
 *  Date: 18/03/2026
 *
 *  Description:
 *
**********************************************************************************************************************************/

// PIC18F45K40 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = ECH    // External Oscillator mode Selection bits (EC (external clock) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = HFINTOSC_1MHZ // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)

// CONFIG4H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config SCANE = ON       // Scanner Enable bit (Scanner module is available for use, SCANMD bit can control the module)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // UserNVM Program Memory Code Protection bit (UserNVM code protection disabled)
#pragma config CPD = OFF        // DataNVM Memory Code Protection bit (DataNVM code protection disabled)

// CONFIG5H

// CONFIG6L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG6H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.





#define _XTAL_FREQ 1000000

#include "COMMON.h"
#include "LIGHT_CONTROL.h"
#include "SENSOR.h"
#include "MOTOR_CONTROL.h"

/***************************************************************************
 *
 *  Interrupt service routine
 *
***************************************************************************/

void __interrupt() ISR(void){

    if (PIR0bits.TMR0IF){
        PIR0bits.TMR0IF = 0;

    }
}

// Set PWM3 (RD0) to a given duty cycle percentage (0?100)
/*
void PWM3_SetDuty_Percent(uint8_t percent)
{
    if (percent > 100) percent = 100;
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);
    PWM3DCH = steps;
    PWM3DCL = 0x00;
}

// Set PWM4 (RC3) to a given duty cycle percentage (0?100)
void PWM4_SetDuty_Percent(uint8_t percent)
{
    if (percent > 100) percent = 100;
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);
    PWM4DCH = steps;
    PWM4DCL = 0x00;
}
*/

void PWM_Init_1kHz(void)
{
    // --- Step 1: Disable output drivers on target pins ---
    TRISCbits.TRISC3 = 1;
    TRISDbits.TRISD0 = 1;

    // --- Ensure pins are digital (not analog) ---
    ANSELCbits.ANSELC3 = 0;
    ANSELDbits.ANSELD0 = 0;

    // --- Ensure PWM3, PWM4, and Timer2 peripherals are not power-gated ---
    PMD3bits.PWM3MD = 0;
    PMD3bits.PWM4MD = 0;
    PMD1bits.TMR2MD = 0;   // Enable Timer2

    // --- Step 2: Clear PWM control registers ---
    PWM3CON = 0x00;
    PWM4CON = 0x00;

    // --- Step 3: Set PWM period ---
    // Period = (T2PR + 1) * 4 * Tosc * Prescaler
    // 1ms   = (249 + 1)  * 4 * (1/4MHz) * 4
    // 1ms   = 250 * 1us * 4 = 1000us ?
    T2PR = 249;

    // --- Step 4: Set initial duty cycles (50%) ---
    // 50% of 250 steps = 125. Write to DCH; DCL bits[7:6] = 0
    PWM3DCH = 125;
    PWM3DCL = 0x00;
    PWM4DCH = 125;
    PWM4DCL = 0x00;

    // --- Step 5: Configure Timer2 ---
    PIR4bits.TMR2IF = 0;    // Clear overflow flag before starting

    T2CLKCON = 0x01;        // Clock source = FOSC/4 (CS[3:0] = 0001)
                            // Required for correct PWM operation

    // CKPS[2:0] = 010 ? 1:4 prescaler
    // OUTPS[3:0] = 0000 ? 1:1 postscaler (postscaler unused for PWM freq)
    // ON = 1 ? start timer
    T2CON = 0b10100000;     // ON=1, CKPS=010, OUTPS=0000

    // --- Step 6: Wait for first Timer2 overflow ---
    // Ensures the first PWM output starts as a complete cycle
    while (!PIR4bits.TMR2IF);

    // --- Step 7: Route PWM outputs to pins via PPS ---
    RD0PPS = 0x07;          // PWM3 output ? RD0
    RC3PPS = 0x08;          // PWM4 output ? RC3

    // Enable output drivers
    TRISDbits.TRISD0 = 0;
    TRISCbits.TRISC3 = 0;

    // --- Step 8: Enable PWM modules ---
    PWM3CON = 0x80;         // EN=1, OUT=0(read-only), POL=0 (normal)
    PWM4CON = 0x80;
}

void main(void) {
    // Assuming oscillator config bits already set to your FOSC in config words
    
    // PWM_Init_1kHz();
    SENSOR__Init();
    LIGHT_CONTROL__Init();
    MOTOR_CONTROL__Init();
    
    TRISB = 0x00;
    ANSELB = 0x00;
    LATB = 0x00;

    while (1){
        //PWM3_SetDuty_Percent(90);
        //PWM4_SetDuty_Percent(20);  // Complementary on RC3
        MOTOR_CONTROL__Set_Duty(70);
       
        SENSOR__Read_Sensor();
        SENSOR__Process_Sensor();
        __delay_ms(10);
    }
    
}
