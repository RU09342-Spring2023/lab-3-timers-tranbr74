/*
 * Part3.c
 *
 *  Created on: Feb 12, 2023
 *      Author: Brandon Tran
 *
 *       *Got helped/Referenced from Dylan Wyss*
 *
 *      YOU NEED TO FILL IN THIS AUTHOR BLOCK
 */


#include <msp430.h>
#include "GPIO_Driver.h"

unsigned long press_time = 0;             // Used to know the button press time from 2.3

unsigned int counting = 0;                  // Used to see if LED will blink by 10000 or value of LED time pressed
                                            // 0 = timer not counting, 1 = timer counting

unsigned int RISING = 1;
unsigned int FALLING = 0;


void timerInit();

void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    gpioInit(1,0,1);                // Initializes Pin 1.0 as an output
    gpioWrite(1,0,0);               // Sets Pin 1.0 to low

    gpioInit(6,6,1);                // Initializes Pin 6.6 as an output
    gpioWrite(6,6,0);               // Sets Pin 6.6 to low

    gpioInit(4,1,0);                // Initializes Pin 4.1 as an input with pull-up resistor
    P4IES |= BIT1;                  // P4.1 High --> Low edge
    P4IE |= BIT1;                   // P4.1 interrupt enabled

    gpioInit(2,3,0);                // Initializes Pin 2.3 as an input with pull-up resistor
    P2IES |= BIT3;                  // P2.3 High --> Low edge
    P2IE |= BIT3;                   // P2.3 interrupt enabled

    timerInit();

    press_time = 10000;
    counting = 0;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);
    __enable_interrupt();
}


void timerInit(){
    // Initializing timer for the time P2.3 (the button) is pressed (Timer B0)
    TB0CCTL0 |= CCIE;                       // Enable TB0 CCR0 Overflow IRQ
    TB0CCR0 = 1;
    TB0CTL = TBSSEL_1 | MC_2 | ID_3;               // ACLK, continuous mode

    // Initializing timer for blinking RED LED (Timer B1)
    TB1CCTL0 |= CCIE;                       // Enable TB1 CCR0 Overflow IRQ
    TB1CCR0 = 10000;
    TB1CTL = TBSSEL_1 | MC_2 | ID_3;               // ACLK, continuous mode
}


/*
 * INTERRUPT ROUTINES
 */

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;                            // Clear P2.3 interrupt flag

    if (RISING)                           //If P2.3 is held down (or if rising edge is high)
    {
        RISING = 0;                       // Set rising edge to 1
        FALLING = 1;                      // Set falling to 1 to look for falling edge

        P6OUT |= BIT6;              // Pin 6.6 (green led) is set to high
        P1OUT &= ~BIT0;             // Pin 1.0 (red led) is set to low

        P2IES &= ~BIT3;                        // P2.3 Low --> High edge
        counting = 1;                          // Counting is set to one and counting starts
        press_time = 0;
    }
    else if (FALLING)                     //if P2.3 is not held down
    {
        RISING = 1;                       //Set rising edge to 1 to look for rising edge
        FALLING = 0;                      //Set falling edge to 0.

        P2IES |= BIT3;                         // P2.3 High --> Low edge
        P6OUT &= ~BIT6;                        // Pin 6.6 (green led) is set to low
        counting = 0;                          // Counting is set to 0 and counting stops
    }
}

// Port 4 interrupt service routine (FOR P4.1 TO RESET THE TIMER)
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT1;                         // Clear P4.1 interrupt flag
    press_time = 10000;                     // Reset timer value to initialized value 10000
    counting = 0;
}

// Timer B0 interrupt service routine (FOR HOLDING THE BUTTON)
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    if (counting == 1){
        press_time++;                      // If the button is pressed, initiate timer to count by 1 (counting starts)
    }
    else {
        press_time = press_time;          // When button is not pressed, press timer = press timer (counting stops)
    }
    TB0CCR0 += 1;                         // Add Offset to TB0CRRO
}

// Timer B1 interrupt service routine (FOR BLINKING LED)
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    P1OUT ^= BIT0;                          // Toggle P1.0 (RED LED)
    TB1CCR0 += press_time;                 // ADD Offset to TB1CRRO
}
