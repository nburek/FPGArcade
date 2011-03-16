FPGArcade

To download this repository run the command:
git clone git@github.com:nburek/FPGArcade.git

The folder VGA_Driver contains a very simple VGA driver 
project implemented in ISE. All it does is read in the 
switches on the Nexys2 board, maps them as an 8 bit 
color and then displays that color on the VGA monitor.

The folder Simple_Video contains a ISE project that 
reads in the switches and push buttons on the Nexys2. 
It maps each of these to an X and Y coordinate and then
displays a block at those coordinates. 

The folder PmodJSTK_Module contains an ISE project that 
is designed to handle the SPI interface with the 
joystick boards. 

The Bouncing_Ball folder contains an EDK project that 
is being used as a starting point for using C code with 
Microblaze to control the VGA screen. It has been 
expanded from bouncing a simple ball around the screen 
to being used for a simple pong implementation.

The Reference Material folder contains a bunch of 
different files that contain useful information that 
we may need to reference. 