nclude<iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "BigInteger.h"

    using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
  // Tests for constructors
  BigInteger *zero = new BigInteger();
  BigInteger *pos = new BigInteger("+123456789101112131415");
  BigInteger *pos_copy = new BigInteger(*pos);
  BigInteger *neg = new BigInteger("-345154896344488481285");

  // Tests for sign()
  cout << "sign() Tests: " << endl << endl;
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << zero->sign() << endl;

  cout << "Expected: 1" << endl;
  cout << "Actual:   " << pos->sign() << endl;

  cout << "Expected: -1" << endl;
  cout << "Actual:   " << neg->sign() << endl;

  // Tests for to_string()
  cout << endl << "to_string() Tests: " << endl << endl;
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << *zero << endl;

  cout << "Expected: 123456789101112131415" << endl;
  cout << "Actual:   " << *pos << endl;

  cout << "Expected: -345154896344488481285" << endl;
  cout << "Actual:   " << *neg << endl;

  cout << "Expected: 123456789101112131415" << endl;
  cout << "Actual:   " << *pos_copy << endl;

  // Test for negate()
  cout << endl << "negate() Tests: " << endl << endl;
  cout << "Before negate(): " << pos->sign() << endl;
  pos->negate();
  cout << "After negate():  " << pos->sign() << endl;
  pos->negate();

  // TESTS for compare()
  // Equality
  cout << endl << "compare() Tests: " << endl << endl;
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << zero->compare(*zero) << endl;

  cout << "Expected: 0" << endl;
  cout << "Actual:   " << pos->compare(*pos_copy) << endl;

  cout << "Expected: 0" << endl;
  cout << "Actual:   " << neg->compare(*neg) << endl;

  // Less than
  cout << "Expected: -1" << endl;
  cout << "Actual:   " << zero->compare(*pos) << endl;

  cout << "Expected: -1" << endl;
  cout << "Actual:   " << neg->compare(*zero) << endl;

  cout << "Expected: -1" << endl;
  cout << "Actual:   " << neg->compare(*pos) << endl;

  // Greater than
  cout << "Expected: 1" << endl;
  cout << "Actual:   " << pos->compare(*zero) << endl;

  cout << "Expected: 1" << endl;
  cout << "Actual:   " << pos->compare(*neg) << endl;

  cout << "Expected: 1" << endl;
  cout << "Actual:   " << zero->compare(*neg) << endl;

  // TESTS for add()
  cout << endl << "add() Tests: " << endl << endl;
  // 0 + 0
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << (*zero) + (*zero) << endl;

  // 0 + Positive
  cout << "Expected: 123456789101112131415" << endl;
  cout << "Actual:   " << (*zero) + (*pos) << endl;

  // 0 + Negative
  cout << "Expected: -345154896344488481285" << endl;
  cout << "Actual:   " << (*zero) + (*neg) << endl;

  // Positive + Negative
  cout << "Expected: -221698107243376349870" << endl;
  cout << "Actual:   " << (*pos) + (*neg) << endl;

  // Positive + Positive
  neg->negate();
  cout << "Expected: 468611685445600612700" << endl;
  cout << "Actual:   " << (*pos) + (*neg) << endl;
  neg->negate();

  // Negative + Negative
  pos->negate();
  cout << "Expected: -468611685445600612700" << endl;
  cout << "Actual:   " << (*pos) + (*neg) << endl;
  pos->negate();

  // TESTS for sub()
  cout << endl << "sub() Tests: " << endl << endl;
  // 0 - 0
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << (*zero) - (*zero) << endl;

  // 0 - Positive
  cout << "Expected: -123456789101112131415" << endl;
  cout << "Actual:   " << (*zero) - (*pos) << endl;

  // 0 - Negative
  cout << "Expected: 345154896344488481285" << endl;
  cout << "Actual:   " << (*zero) - (*neg) << endl;

  // Positive - Negative
  cout << "Expected: 468611685445600612700" << endl;
  cout << "Actual:   " << (*pos) - (*neg) << endl;

  // Positive - Positive
  neg->negate();
  cout << "Expected: -221698107243376349870" << endl;
  cout << "Actual:   " << (*pos) - (*neg) << endl;
  neg->negate();

  // Negative - Negative
  pos->negate();
  cout << "Expected: 221698107243376349870" << endl;
  cout << "Actual:   " << (*pos) - (*neg) << endl;
  pos->negate();

  // TESTS for mult()
  cout << endl << "mult() Tests: " << endl << endl;
  // 0 * 0
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << (*zero) * (*zero) << endl;

  // 0 * Positive
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << (*zero) * (*pos) << endl;

  // 0 * Negative
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << (*zero) * (*neg) << endl;

  // Positive * Negative
  cout << "Expected: -42611715245217732984647316295642688068275" << endl;
  cout << "Actual:   " << (*pos) * (*neg) << endl;

  // Positive * Positive
  neg->negate();
  cout << "Expected: 42611715245217732984647316295642688068275" << endl;
  cout << "Actual:   " << (*pos) * (*neg) << endl;
  neg->negate();

  // Negative * Negative
  pos->negate();
  cout << "Expected: 42611715245217732984647316295642688068275" << endl;
  cout << "Actual:   " << (*pos) * (*neg) << endl;
  pos->negate();

  // Test for makeZero()
  cout << endl << "makeZero() Tests: " << endl << endl;
  cout << "Before makeZero(): " << *pos << endl;
  pos->makeZero();
  cout << "After makeZero():  " << *pos << endl;
  cout << "Sign after makeZero(): " << pos->sign() << endl;

  delete pos;
  delete neg;
  delete zero;
  delete pos_copy;

  return 0;
}
