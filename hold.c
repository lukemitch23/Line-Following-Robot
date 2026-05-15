void MOTOR_CONTROL__Initttt() {
 /* Set PORT C pin 3, PORTD pin 0 and PORTB to output */
 TRISB = 0;

 /* Set ports to digital */
 ANSELB = 0;
 ANSELD = 0;
 ANSELC = 0;

 TRISCbits.TRISC3 = 1;
 TRISDbits.TRISD0 = 1;

 /* Turn the motors off */
 // Enable_Left(MOTOR_OFF);
 // Enable_Right(MOTOR_OFF);

 /* Configure the timer */
 T2CONbits.TMR2ON = 0; // Stop timer during configuration
 T2CLKCON = 0x01;  // Select FOSC/4 as Timer2 clock source
 T2PR = T2PR_VALUE; // Set period register for 1kHz
 TMR2 = 0; // Clear timer count
 PIR4bits.TMR2IF = 0; // Clear Timer2 interrupt flag

 /* Configure PWM 3 */
 PWM3DCH = 0; // Zero duty cycle until motor enabled
 PWM3DCL = 0; // Set lower 6 bits to 0 as not needed
 PWM3CON = 0b10000000; // Enable PWM3, active-high output (bit7=EN, bit4=POL=0)

 /* Configure PWM 4 */
 PWM4DCH = 0; // Zero duty cycle until motor enabled
 PWM4DCL = 0; // Set lower 6 bits to 0 as not needed
 PWM4CON = 0b10000000; // Enable PWM4, active-high output

 /* Route the PWM to the correct output pins on the PIC */
 RC3PPS = PPS_PWM3OUT; // PWM3 output - RC3
 RD0PPS = PPS_PWM4OUT; // PWM4 output - RD0

 /* Start the timer used */

 T2CON = T2CON_VALUE; // Set prescaler and turn timer on

 /* Set the ports to output */
 TRISCbits.TRISC3 = 0;
 TRISDbits.TRISD0 = 0;
}

void MOTOR_CONTROL__Iniiiiit() {
 /* Step 1 - Disable PWM pins (set as input) */
 TRISCbits.TRISC3 = 1;
 TRISDbits.TRISD0 = 1;

 /* Step 2 - Clear PWMxCON */
 PWM3CON = 0;
 PWM4CON = 0;

 /* Step 3 - Load period register */
 T2PR = T2PR_VALUE;

 /* Step 4 - Load duty cycle registers */
 PWM3DCH = 0;
 PWM3DCL = 0;
 PWM4DCH = 0;
 PWM4DCL = 0;

 /* Step 5 - Configure and start Timer2 */
 PIR4bits.TMR2IF = 0;
 T2CLKCON = 0x01;        // FOSC/4 — required for PWM, was missing
 T2CON = T2CON_VALUE;    // Set prescaler and enable timer

 /* Step 6 - Wait for Timer2 overflow */
 while (!PIR4bits.TMR2IF);
 PIR4bits.TMR2IF = 0;

 /* Step 7 - Enable PWM pins and route via PPS */
 TRISCbits.TRISC3 = 0;
 TRISDbits.TRISD0 = 0;
 RC3PPS = PPS_PWM3OUT;
 RD0PPS = PPS_PWM4OUT;

 /* Step 8 - Enable PWM modules */
 PWM3CON = 0b10000000;
 PWM4CON = 0b10000000;
}

void MOTOR_CONTROL__Init(void) {
 /* Make PWM pins inputs while configuring */
 TRISCbits.TRISC3 = 1;
 TRISDbits.TRISD0 = 1;

 /* Make sure the pins are digital */
 ANSELC = 0;
 ANSELD = 0;

 /* Stop PWM modules during setup */
 PWM3CON = 0x00;
 PWM4CON = 0x00;

 /* Timer2 / PWM period */
 T2CLKCON = 0x01;      /* Fosc/4 */
 T2PR = T2PR_VALUE;    /* PWM period */

 /* Start with 0% duty */
 PWM3DCH = 0x00;
 PWM3DCL = 0x00;
 PWM4DCH = 0x00;
 PWM4DCL = 0x00;

 /* Clear Timer2 flag and start Timer2 */
 PIR4bits.TMR2IF = 0;
 T2CON = T2CON_VALUE;

 /* Wait for Timer2 to roll over once */
 while (!PIR4bits.TMR2IF) {
  ;
 }
 PIR4bits.TMR2IF = 0;

 /* Route PWM outputs to pins */
 RC3PPS = PPS_PWM3OUT;
 RD0PPS = PPS_PWM4OUT;

 /* Enable the PWM outputs */
 PWM3CON = 0b10000000;
 PWM4CON = 0b10000000;

 /* Release pins to peripheral control */
 TRISCbits.TRISC3 = 0;
 TRISDbits.TRISD0 = 0;
}












/* sflkjdl */

TRISDbits.TRISD1 = 1; // Temporarily set RD1 as input
RD1PPS = 0x07; // Map PWM3 output to pin RD1

// Configure timer
T2CLKCON = 0x01; // Select Timer2 clock source (Fosc/4)
T2PR = 0xFF; // Set Timer2 period register (defines PWM frequency)

// Configure PWM values
// Set PWM3 duty cycle (10-bit value split across two registers)
// Higher values = higher duty cycle (near 100% here)
PWM3DCH = 0xF5;
PWM3DCL = 0xC3;

// Timer 2 configuration
PIR4bits.TMR2IF = 0; // Clear Timer2 interrupt flag before starting
T2CONbits.T2CKPS = 0; // Set Timer2 prescaler to 1:1
T2CONbits.T2ON = 1; // Turn Timer2 ON (starts PWM time base)

// Ensure it is ready
while (!PIR4bits.TMR2IF);

// PWM Config
PWM3CONbits.POL = 0; // Set PWM polarity to active-high
PWM3CONbits.OUT = 0; // Allow PWM module to control the output pin
PWM3CONbits.EN = 1; // Enable PWM3 module

// Renable the motor
TRISDbits.TRISD1 = 0; // Set RD1 as output so PWM signal appears on the pin
TRISDbits.TRISD0 = 0; // Configure RD0 as output (motor driver enable pin)
LATD0 = 1; // Drive RD0 HIGH to enable the motor driver
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