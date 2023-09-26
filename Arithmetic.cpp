/*****************************************************
 * Arithmetic.cpp
 * Implementation file Client interface with BigInteger ADT
 * Lucas Ellenberger
 * lmellenb
 * pa6
 ****************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>

#include "BigInteger.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main (int argc, char** argv) {
    // check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " invalid number of arguments " << endl;
        return(EXIT_FAILURE);
    }

    std::ifstream infile;
    infile.open(argv[1]);
    std::ofstream outfile;
    outfile.open(argv[2]);
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Usage: " << argv[0] << " unable to open files " << endl;
        return(EXIT_FAILURE);
    }
    std::string line = "";
    getline(infile, line); // A
    BigInteger * A = new BigInteger(line);
    getline(infile, line); // newline character
    getline(infile, line); // B
    BigInteger * B = new BigInteger(line);

    outfile << *A << endl << endl; // A
    outfile << *B << endl << endl; // B

    outfile << (*A) + (*B) << endl << endl; // A + B
    outfile << (*A) - (*B) << endl << endl; // A - B
    outfile << (*A) - (*A) << endl << endl; // A - A

    BigInteger * three = new BigInteger("3");
    BigInteger * two = new BigInteger("2");

    outfile << (((*three) * (*A)) - ((*two) * (*B))) << endl << endl; // 3A - 2B
    outfile << ((*A) * (*B)) << endl << endl; // AB

    BigInteger A_pow_2 = ((*A) * (*A));

    outfile << A_pow_2 << endl << endl; // A^2

    BigInteger B_pow_2 = ((*B) * (*B));

    outfile << B_pow_2 << endl << endl; // B^2

    BigInteger * nine = new BigInteger("9");
    BigInteger * sixteen = new BigInteger("16");
    BigInteger A_pow_4 = (A_pow_2 * A_pow_2);
    BigInteger B_pow_5 = ((B_pow_2 * B_pow_2) * (*B));

    outfile << (((*nine) * A_pow_4) + ((*sixteen) * B_pow_5)) << endl; // 9(𝐴^4) + 16(𝐵^5)

    delete A;
    delete B;
    delete three;
    delete two;
    delete nine;
    delete sixteen;

    infile.close();
    outfile.close();

    return 0;
}
