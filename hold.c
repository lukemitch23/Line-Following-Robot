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