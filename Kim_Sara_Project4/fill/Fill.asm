// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Keyboard no key press = 0

(LOOP)
// Get keyboard RAM to see if key is pressed
@KBD
D=M
@WHITE 			// if key is not pressed, KBD = 0, so goto WHITE loop
D;JEQ
@BLACK 			// if key is pressed, KBD != 0, so goto BLACK loop
D;JNE

(WHITE)
@color
M=0					// White in pixel	
@INCREMENT			// jump to INCREMENT loop
0;JMP

(BLACK)
@color
M=-1					// Black in pixel
@INCREMENT			// jump to INCREMENT loop
0;JMP

// INCREMENT loop will increment through the screen pixels
// coloring it in accordingly
(INCREMENT)
	@SCREEN
	D=A
	@pixel
	M=D			// current pixel position being colored in

	@8192	// count will first contain the total number SCREEN pixels
	D=A
	@count 		
	M=D			// count = how many more pixels to color in

	(INCLOOP)
		// First need to check the whether count = 0
		// if it is, SCREEN is all colored, so return to LOOP start
		@count
		D=M
		@LOOP
		D;JEQ

		@color 		// color contains 0 or 1 depending on where it jumped from
		D=M 		// D = either 0 or 1 
		@pixel
		A=M 		// Access pixel that's on SCREEN
		M=D 		// Color in the pixel with either 0 (white) or 1 (black)

		// Decrement the count similar to the iterator in mult.asm
		@pixel 		// Now we need to move pixel pointer to next pixel
		M=M+1 		// pixel = pixel + 1 -> pixel++;
		@count 		// M now contains the new decremented count
		M=M-1 		// count = count - 1 -> count--;

	@INCLOOP
	0;JMP