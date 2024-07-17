# Assignment 3: 

##description:This C program aims to perform parallel matrix multiplication efficiently, specifically for squaring a square matrix using dynamic row allocation
techniques used - TAS, CAS, bounded CAS, atomic increment

## Instructions for Execution

This README provides instructions on how to compile and execute the submitted C++ program for efficient matrix squaring.


### Prerequisites

- Make sure you have a C compiler installed on your system (e.g., GCC).

## compilation
-Open a terminal
-Navigate to the directory containing the source code.
-complie the code using command :
			g++ Assgn3_Src-CO22BTECH11010_TAS.cpp ....for TAS method
			g++ Assgn3_Src-CO22BTECH11010_CAS.cpp ....for CAS method
			g++ Assgn3_Src-CO22BTECH11010_BOUNDED-CAS.cpp ....for Bounded CAS method
			g++ Assgn3_Src-CO22BTECH11010_Atomic.cpp ....for Atomic method

execution:
	type in ./a.out after compiling each file in terminal

## Input files:

	Input files will be given in a .txt format which will contain values of N and K and the matrix of size N.
	we will read the contents of the file using ifstream and store them in variables.


## Output file:
	The output file will contain the resultant matrix C and the time the code takes to execute.
