# Lucas Ellenberger pa6 README

## List.h

This file contains the header for List.cpp and is required for the compilation of the code, as it has important include statements and function declarations.

## List.cpp

This file contains the implementation (function definitions) of the List ADT. It will construct, destruct, access, and manipulate the List ADT through the various fuinctions declared in List.h

## ListTest.cpp

This file is a simple test for our List ADT. It outputs the actual values from all functions to the command line which can be compared to the expected output. Although the tests are simple, it is a quick and easy way to make sure all the List ADT functions work for some cases. Helpful for early developement of the List ADT.

## BigInteger.h

This file contains the header for BigInteger.cpp and is required for the compilation of the code, as it has important include statements and function declarations.

## BigInteger.cpp

This file contains the implementation (function definitions) of the BigInteger ADT. It will construct, destruct, access, and manipulate the BigInteger ADT through the various fuinctions declared in BigInteger.h

## BigIntegerTest.cpp

This file is a simple test for our BigInteger ADT. It outputs the expected and actual values from all functions to the command line which can be compared to verify functionality. Although the tests are simple, it is a quick and easy way to make sure all the BigInteger ADT functions work for some cases. Helpful for early developement of the BigInteger ADT.

## Arithmetic.cpp

This is the file containing the main function and is the file to be compiled into an executable binary. This program takes two command line arguments, an infile and an outfile. First, the program reads from the infile two BigInteger numbers. Then, the program prints the following to the outfile: A, B, A + B, A - B, A - A, 3A - 2B, A^2, B^2, 9(A^4) + 16(B^5). Even computing these on incredibly large numbers (10000 digits+), can be done in a reasonable amount of time. Finally, the program will free all associated memory before terminating.

## Makefile

This file takes the .cpp files and .h file and creates the Arithmetic and testing executables.
Standard Makefile as provided on the website.

### make

makes Arithmetic

### make BigIntegerTest

makes BigIntegerTest

### make ListTest

makes ListTest

### make clean

removes all binaries

### make ArithmeticCheck

runs Arithmetic in valgrind on in4 junk4

### make BigIntegerCheck

runs BigIntegerTest in valgrind

### make ListCheck

runs ListTest in valgrind
            
### make format

formats all files to make them look better


## Note to the grader

Everything works and my program can now handle in5 on the timeshare relatively quickly.

## List.h

This file contains the header for List.cpp and is required for the compilation of the code, as it has important include statements and function declarations.

## List.cpp

This file contains the implementation (function definitions) of the List ADT. It will construct, destruct, access, and manipulate the List ADT through the various fuinctions declared in List.h

## ListTest.cpp

This file is a simple test for our List ADT. It outputs the actual values from all functions to the command line which can be compared to the expected output. Although the tests are simple, it is a quick and easy way to make sure all the List ADT functions work for some cases. Helpful for early developement of the List ADT.

## BigInteger.h

This file contains the header for BigInteger.cpp and is required for the compilation of the code, as it has important include statements and function declarations.

## BigInteger.cpp

This file contains the implementation (function definitions) of the BigInteger ADT. It will construct, destruct, access, and manipulate the BigInteger ADT through the various fuinctions declared in BigInteger.h

## BigIntegerTest.cpp

This file is a simple test for our BigInteger ADT. It outputs the expected and actual values from all functions to the command line which can be compared to verify functionality. Although the tests are simple, it is a quick and easy way to make sure all the BigInteger ADT functions work for some cases. Helpful for early developement of the BigInteger ADT.

## Arithmetic.cpp

This is the file containing the main function and is the file to be compiled into an executable binary. This program takes two command line arguments, an infile and an outfile. First, the program reads from the infile two BigInteger numbers. Then, the program prints the following to the outfile: A, B, A + B, A - B, A - A, 3A - 2B, A^2, B^2, 9(A^4) + 16(B^5). Even computing these on incredibly large numbers (10000 digits+), can be done in a reasonable amount of time. Finally, the program will free all associated memory before terminating.

## Makefile

This file takes the .cpp files and .h file and creates the Arithmetic and testing executables.
Standard Makefile as provided on the website.

### make

makes Arithmetic

### make BigIntegerTest

makes BigIntegerTest

### make ListTest

makes ListTest

### make clean

removes all binaries

### make ArithmeticCheck

runs Arithmetic in valgrind on in4 junk4

### make BigIntegerCheck

runs BigIntegerTest in valgrind

### make ListCheck

runs ListTest in valgrind
            
### make format

formats all files to make them look better

