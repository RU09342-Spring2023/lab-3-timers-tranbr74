**What is this?**
The GPIO_Driver.c file is a file that contains functions to initialize, read, and write pins. The GPIO_Driver.h file is a header file that contains the functions from the c file.

**How to use it?**
When a pin is being initialized, it can be initialized as an input or an output. To do so, here is an example:

gpioInit(1,0,0); means that P1.0 is initialized an output
gpioInit(6,6,1); means that P6.6 is initialized an input

When a pin is an output, the write function can be used to set or clear using a 1 or 0. To do so, here is an example

 gpioWrite(1,0,0);  means that the output P1.0 is cleared 
 gpioWrite(6,6,1);  means that the output P6.6 is set

When a pin is an input, the read function can be used to read a pin. A pin can only  be read if the bit is on. To write the read function:

 gpioRead(1,0); means that the P1.0 is being read/not read.

**Dependencies:**
The header file depends on the c file, therefore, if the GPIO driver ever needs to be utilized. Both files should be in the same project folder.

**How to install and use the files for your project:** 
Download or add the header file and the c file into the desired project folder in code composer
Put in #include “GPIO_Driver.h” before your main. Doing this so, pulls the functions from the headers into your project.
Use functions from above to initialize, read, and write your pins.
