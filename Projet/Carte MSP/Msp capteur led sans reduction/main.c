#include <msp430.h>
#include <stdint.h>

#define ledPin BIT0            // P1.0
#define pinCapteurTactile BIT2  // P1.2

volatile int capteurActive = 0;

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop the watchdog timer

    // Configure ports
    P1DIR |= ledPin;
    P1OUT &= ~ledPin;

    // Configure Timer A1
    TA1CTL = TASSEL_1 + MC_1; // ACLK, Up mode
    TA1CCR0 = 12000;           // Set a time interval for wake-up (adjust as needed)
    TA1CCTL0 |= CCIE;          // Enable Timer A1 interrupt

    while (1) {
        if (capteurActive) {
            // Check sensor value
            if (P1IN & pinCapteurTactile) {
                P1OUT |= ledPin;         // Turn on LED
                __delay_cycles(1000000); // Delay for demonstration purposes
                P1OUT &= ~ledPin;        // Turn off LED
            }
            capteurActive = 0;
        }
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void) {
    capteurActive = 1;
}
