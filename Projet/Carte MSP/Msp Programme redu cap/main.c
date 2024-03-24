#include <msp430.h>

const int ledPin = BIT0;            // P1.0
const int pinCapteurTactile = BIT2;  // P1.2
volatile int capteurActive = 0;

void configureLowPowerMode(void) {
    // Configure clock sources
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;

    // Configure Timer A1 for wake-up from LPM4 after a certain period
    TA1CTL = TASSEL_1 + MC_1;   // ACLK, Up mode
    TA1CCR0 = 12000;            // Set a time interval for wake-up (adjust as needed)
    TA1CCTL0 |= CCIE;           // Enable Timer A1 interrupt
}

void enterLowPowerMode(void) {
    __bis_SR_register(LPM4_bits + GIE);  // Enter LPM4 with interrupts enabled
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop the watchdog timer

    // Configure ports
    P1DIR |= ledPin;
    P1OUT &= ~ledPin;

    // Configure low-power mode and timers
    configureLowPowerMode();

    while (1) {
        enterLowPowerMode();  // Enter LPM4 and enable interrupts
        if (capteurActive) {
            // Check sensor value
            if (P1IN & pinCapteurTactile) {
                P1OUT |= ledPin;           // Turn on LED
                __delay_cycles(1000000);   // Delay for demonstration purposes
                P1OUT &= ~ledPin;          // Turn off LED
            }
            capteurActive = 0;
        }
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void) {
    capteurActive = 1;
}
