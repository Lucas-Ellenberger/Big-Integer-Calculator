//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for the BigInteger ADT
// Lucas Ellenberger
// lmellenb
// pa6
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#include"BigInteger.h"

static const long base = 1000000000;
static const int power = 9;

using std::cerr;
using std::cout;
using std::cin;
using std::endl;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    this->signum = 0;
    this->digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() < 1) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    
    std::string new_string;
    if (s[0] == '-') { // Negative number
        this->signum = -1;
        new_string = s.substr(1);
    } else if (s[0] == '+') { // Positive number
        this->signum = 1;
        new_string = s.substr(1);
    } else { // Non-empty string precondition
        this->signum = 1; // Default is positive
        new_string = s;
    }
    if (new_string.length() < 1) { // Only a positive / negative sign
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    for (int i = 0; i < int(new_string.length()); i++) { // Check each character and make sure it's a digit
        if (!isdigit(new_string[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    std::string pow_str = "";
    List * curr = new List();
    while (new_string.length() >= power) {
        // Grab a string up to the base
        pow_str = new_string.substr(new_string.length()-power);
        // Continue with what's left
        new_string = new_string.substr(0, new_string.length()-power);
        curr->insertAfter(std::stol(pow_str));
    }
    if (new_string.length() > 0) {
        // If there is any leftover that can't fit a full power
        curr->insertAfter(std::stol(new_string));
    }
    this->digits = *curr;
    delete curr;
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    // Use List copy constructor
    this->digits = List(N.digits);
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return this->signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    // Trivial cases from signum
    if (this->signum < N.signum) {
        return -1;
    } else if (this->signum > N.signum) {
        return 1;
    } else { // Must have equal signum
        if (this->signum == 0 && N.signum == 0) {
            return 0;
        }
        // Trivial cases from signum
        if (this->digits.length() < N.digits.length()) {
            if (this->signum == -1) {
                return 1;
            } else {
                return -1;
            }
        } else if (this->digits.length() > N.digits.length()) {
            if (this->signum == -1) {
                return -1;
            } else {
                return 1;
            }
        } else {
            // Must walk the Lists until we find a difference
            List self = List(this->digits);
            List them = List(N.digits);
            self.moveFront();
            them.moveFront();
            int curr_self = 0;
            int curr_them = 0;
            for (int i = 0; i < this->digits.length(); i++) {
                curr_self = self.moveNext();
                curr_them = them.moveNext();
                if (curr_self < curr_them) {
                    if (this->signum == 1) {
                        return -1;
                    } else {
                        return 1;
                    }
                }
                if (curr_self > curr_them) {
                    if (this->signum == 1) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            }
            // Signum and every digit is the same
            return 0;
        }
    }
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    this->signum = 0;
    // Use List clear for ease
    this->digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    this->signum *= -1;
}


// BigInteger Arithmetic operations ----------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub()
static void negateList(List& L) {
    // Walk the List and flip the sign
    for (L.moveFront(); L.position() < L.length(); L.moveNext()) {
        L.setAfter(-1 * L.peekNext());
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
static void sumList(List& S, List A, List B, int sgn) {
    S.clear();
    S.moveBack();
    A.moveBack();
    B.moveBack();
    // Back is least signifacant digit, so we add from back to front
    // Ensures proper carrying
    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.movePrev() + (sgn * B.movePrev()));
    }
    // Check for leftovers from length differences
    while (A.position() > 0) {
        S.insertAfter(A.movePrev());
    }

    while (B.position() > 0) {
        S.insertAfter(sgn * B.movePrev());
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
static int normalizeList(List& L) {
    // Empty List
    if (L.length() == 0) {
        return 1;
    }
    // Continually remove leading 0's
    if(L.front() == 0) {
        while (L.length()) {
            if (L.front() == 0) {
                L.moveFront();
                L.eraseAfter();
            }
            else {
                break;
            }
        }
    }
    // If it was all 0's, check length again
    if (L.length() == 0) {
        return 0;
    }

    int sign = 0;
    // Ensure we have digits to borrow from if necessary
    if (L.front() < 0) { 
        negateList(L);
        sign = -1; // Set the flag to calling function
    } else {
        sign = 1;
    }

    // Again, back of list is least significant digit
    L.moveBack();

    ListElement carry = 0;
    ListElement val = 0;
    for (L.moveBack(); L.position() > 0; L.movePrev()) {
        val = L.peekPrev() + carry;
        if (val >= 0) { // Value is too large, need a carry
            carry = val / base;
        } else {
            if (val % base == 0) {
                // Value is negative but fits evenly into the base
                carry = val / base;
            } else {
                // Value is negative but needs a unique borrow
                carry = (val / base) - 1;
            }
        }
        // Adjust val based on the borrow / carry
        val = val - (carry * base);
        L.setBefore(val);
    }    
    // Leftover carry must be added as the most significant digit
    if (carry > 0) {
        L.moveFront();
        L.insertBefore(carry);
    }
    // This should never happen, because we negated earlier
    if (carry < 0) {
        // Internal (black box error)
        // No client can catch this
        cerr << "BigInteger: normalizeList: error" << endl;
    }

    return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, long p) {
    L.moveBack();
    // Add the 0's to the least significant digits
    // Back is the least significant
    for (long i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    // Walk the list and apply the scalar
    for (L.moveBack(); L.position() > 0; L.movePrev()) {
        L.setBefore(m * L.peekPrev());
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger result = BigInteger();
    // Trivial cases with adding a 0
    if (this->signum == 0 && N.signum == 0) {
        return result;
    }
    if (this->signum == 0) {
        result.signum = N.signum;
        result.digits = List(N.digits);
        return result;
    }
    if (N.signum == 0) {
        result.signum = this->signum;
        result.digits = List(this->digits);
        return result;
    }
    // Grab each List
    List this_list = List(this->digits);
    List N_list = List(N.digits);
    // Negate the List's with a negative signum
    if (this->signum == -1) {
        negateList(this_list);
    }
    if (N.signum == -1) {
        negateList(N_list);
    }
    // Sum them with the correct sign
    sumList(result.digits, this_list, N_list, 1);
    result.signum = normalizeList(result.digits);
    return result;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger result = BigInteger();
    // Trivial cases involving a 0
    if (this->signum == 0 && N.signum == 0) {
        return result;
    }
    if (this->signum == 0) {
        result.signum = N.signum * -1;
        result.digits = List(N.digits);
        return result;
    }
    if (N.signum == 0) {
        result.signum = this->signum;
        result.digits = List(this->digits);
        return result;
    }
    // Grab both List's
    List this_list = List(this->digits);
    List N_list = List(N.digits);
    // Negate only the first List 
    if (this->signum == -1) {
        negateList(this_list);
    }
    if (N.signum == -1) {
        sumList(result.digits, this_list, N_list, 1);
        // negateList(N_list);
    } else {
        sumList(result.digits, this_list, N_list, -1);
    }
    result.signum = normalizeList(result.digits);
    return result;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;
    // Trivial case of multiplying with a 0
    if (this->signum == 0 || N.signum == 0) {
        return result;
    }
    // Grab each List
    List this_digits = List(this->digits);
    List N_digits = List(N.digits);
    List temp = List();
    long i = 0;
    // Walk one list, and multiply each by the other List
    for (this_digits.moveBack(); this_digits.position() > 0; this_digits.movePrev()) {
        List curr = List(N_digits);
        scalarMultList(curr, this_digits.peekPrev());
        normalizeList(curr);
        // Account for the shift
        shiftList(curr, i);
        normalizeList(curr);
        // Sum to running total
        sumList(temp, result.digits, curr, 1);
        normalizeList(temp);
        result.digits = temp;
        i++;
    }
    // Determine signum
    result.signum = (this->signum * N.signum);
    return result;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    // Trivial 0 case
    if (this->signum == 0) {
        return "0";
    } else {
        std::string result = "";
        // Add a negative sign if necessary
        if (this->signum == -1) {
            result += "-";
        }
        // Walk the List, adding each power as we go to our resulting string
        for (this->digits.moveFront(); this->digits.position() < this->digits.length(); this->digits.moveNext()) {
            long curr = this->digits.peekNext();
            // Must add an entire power's worth of 0's instead of only 1
            if (curr == 0) {
                for (int i = 0; i < power; i++) {
                    result += "0";
                }
            } else {
                std::string curr_str = std::to_string(curr);
                // Add leading 0's if needed
                if (curr_str.length() < power) {
                    std::string zeros = "";
                    for (long unsigned int i = 0; i < power - curr_str.length(); i++) {
                        zeros += "0";
                    }
                    result += zeros + curr_str;
                } else {
                    result += curr_str;
                }
            }
        }
        // Remove unnecessary leading 0's
        while (result[0] == '0') {
            result.erase(0,1);
        }
        // Remove unnecessary leading 0's
        if (result[0] == '+' || result[0] == '-') {
            while (result[1] == '0') {
                result.erase(1,1);
            }
        }
        return result;
    }
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return (A.BigInteger::compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return (A.BigInteger::compare(B) < 0);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    return (A.BigInteger::compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    return (A.BigInteger::compare(B) > 0);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return (A.BigInteger::compare(B) >= 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    return A = A.BigInteger::add(B);
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    return A = A.BigInteger::sub(B);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    return A = A.BigInteger::mult(B);
}
