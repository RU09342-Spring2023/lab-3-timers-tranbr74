**WHAT IS THIS CODE?**

This code is about blinking a Red LED based on how long a button is pushed down for. The LED is blinked at an initial speed but its speed will change based on the length of the button it is pushed down for. A green LED will show that the button is held down vice versa when the button is not pressed. When the button is let go, the red LED blink speed will be based on how long the button was pushed down for.

**WHAT WAS USED?**

1.  P1.0 (a.k.a red LED) was set as an output toggled by the Timer B1 interrupt.
2.  P6.6 (a.k.a green LED) was set as an output toggled by the P2.3 interrupt.
3.  P2.3 (a.k.a Blinking Button) was set as input with a pullup resistor, interrupt enabled, and rising/falling changes.
4.  P4.1 (a.k.a reset button) was set as an input with a pullup resistor, interrupt enabled, and falling edge.
5.  Timer B0 was set to TB0CCRO, ACLK, continuous, and divided by a clock divider of 8. This is used to set the timer for       P2.3. 
6.  Timer B1 was set to TB1CCRO, ACLK, continuous, and divided by a clock divider of 8. This is used to set the timer for the   red LED.

**Why do we need a clock divider and ACLK (Design consideration):** 
A clock divider and an ACLK is needed to slow the clock down as using these will allow the user to hold down a button for a very long time. Using an ACLK will capture 2 seconds of time as it runs at 32,768 Hz. With the addition of Clock Dividers (ID), clocks can be slowed even further. A clock divider can only divide by factors of 2, 4, 8, 16. If needed, more can be used.

**How do you use the code?**
1. Place code into code composer.
2. Plug your MSP430 to your device using an USB
3. Debug and Run Code
4. Red LED should be blinking at an initial speed. Either tap or press the P2.3 for a set amount of time. A Green LED will light up with the Red LED off when P2.3 is pressed. 
5. Once P2.3 is let go, the Red LED's blinking speed will change based on how long the P2.3 was pressed. The Green LED is off at that time.
6. To reset blinking speed, press P4.1

