// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Use loop since multiplying is basically adding 
// R1, R0 amount of times 

	@R2			// M = R2, where R2 stores the multiplication result
	M=0			// R2 = 0 -> initialize R2

	@R0			// R0 is the amount of times R1 needs to be added
	D=M 		// D = R0
	@i 			// i is the iterator that will be equal to R0		
	M=D 		// iterator = R0

// Start loop. Will basically subtract 1 from the iterator
// each time R1 is added to R2, until i = 0 to fully add
// R1, R0 amount of times
(LOOP)	
	// while i != 0
	@i
	D=M 		// D = i -> D now contains the iterator
	@END
	D;JEQ		// check if iterator = 0, if it is goto END

	// if iterator !=0 then decrement iterator
	D=D-1 		// iterator = iterator - 1 -> i--;
	@i 			// Now update iterator to the decremented value
	M=D

	//Now we will add R1 to the result R2 
	@R1
	D=M 		// D = R1
	@R2			// M = R2
	M=D+M 		// R2 = R1 + R2

	// goto LOOP again
	@LOOP
	0;JMP

(END)			// infinite loop to end
	@END
	0;JMP