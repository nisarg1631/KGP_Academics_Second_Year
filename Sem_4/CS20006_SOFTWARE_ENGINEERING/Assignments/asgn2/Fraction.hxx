#ifndef FRACTION_HXX
#define FRACTION_HXX

#include <iostream>
using namespace std;

class Fraction{

    /*
     *  DATA MEMBERS
     * 
     *  num - numerator (signed, hence determines whether the fraction is positive or negative)
     *  den - denominator (unsigned)
     *  _precision - static constant used to convert double to fraction
     */

    int num;
    unsigned int den;
    static const unsigned int _precision;

    /*
     *  NORMALIZE FUNCTION
     * 
     *  When called it checks whether the fraction is in its reduced form
     *  If not it sets the value of "num" and "den" accordingly
     */

    void normalize();

    public:

        /*
         *  CONSTRUCTORS AND DESTRUCTOR
         * 
         *  Constructor with pair of int values, properly defaulted as asked, does not allow implicit conversion
         *  Constructor from double value, does not allow implicit conversion
         *  Copy constructor to construct from existing object, passed as a const reference so as to not allow any change in it
         *  Destructor with usual semantics
         */

        explicit Fraction(int = 1, int = 1);
        explicit Fraction(double);
        Fraction(const Fraction&);
        ~Fraction();

        /*
         *  COPY ASSIGNMENT OPERATOR
         * 
         *  Usual semantics
         *  Copies data from passed object (passed as a const reference so as to not allow any change in it)
         *  Returns reference to current object to allow chaining
         */

        Fraction& operator=(const Fraction&);
        
        /*
         *  UTILITY FUNCTIONS
         * 
         *  Static utility functions which help in arithmetics of fractions
         *  precision() and lcm() just return the relevant values, hence inlined to reduce overhead of call
         *  to avoid overflow in lcm() we first divide n2 by gcd of n1 and n2
         */

        inline static unsigned int precision(){
            return _precision;
        };
        static int gcd(int, int);
        inline static int lcm(int n1, int n2){
            return n1*(n2/gcd(n1,n2));
        };

        /*
         *  UNARY OPERATORS + and -
         * 
         *  Member functions to return +p/q and -p/q
         *  Object doesn't need to change hence defined as const functions
         *  Functions are just returning a constructed object, hence inlined to reduce overhead of call
         */
        
        inline Fraction operator+() const{
            return Fraction(+num, den);
        };
        inline Fraction operator-() const{
            return Fraction(-num, den);
        };

        /*
         *  UNARY OPERATORS ++ and --
         * 
         *  PRE-INCREMENT/DECREMENT:
         *      Increments or decrements the fraction by 1
         *      We return by reference the current object in accordance with the design guidelines
         *      Returns reference to object after increment/decrement
         * 
         *  POST-INCREMENT/DECREMENT:
         *      Increments or decrements the fraction by 1
         *      We return by value a copy of the current object (as object itself is changed) in accordance with the design guidelines
         *      Returns the previous value before increment/decrement
         */

        Fraction& operator++();
        Fraction operator++(int);
        Fraction& operator--();
        Fraction operator--(int);

        /*
         *  BINARY ARITHMETIC OPERATORS
         * 
         *  Friend functions to perform arithmetic operations on two fractions
         *  We return by value the constructed object after performing the operation on the operands
         *  Friend function as access to private data members is required to perform the necessary operations
         *  Operands don't need to change, hence passing UDT as const reference
         */

        friend Fraction operator+(const Fraction&, const Fraction&);
        friend Fraction operator-(const Fraction&, const Fraction&);
        friend Fraction operator*(const Fraction&, const Fraction&);
        friend Fraction operator/(const Fraction&, const Fraction&);
        friend Fraction operator%(const Fraction&, const Fraction&);

        /*
         *  BINARY RELATIONAL OPERATORS
         * 
         *  Member functions to compare two fractions
         *  Object doesn't need to change hence defined as const functions
         *  Object being compared to also doesn't need to change, hence passing UDT as const reference
         *  Functions are just comparing integers, hence inlined to reduce overhead of call
         * 
         *  Note: When multiplying an unsigned int and int, the int gets casted to unsigned int by default
         *        Hence, during comparisons the denominator which is an unsigned int has been explicitly casted to int
         */

        inline bool operator==(const Fraction& f) const{
            return ((this->num == f.num) && (this->den == f.den));
        };
        inline bool operator!=(const Fraction& f) const{
            return !(*this == f);
        }
        inline bool operator<(const Fraction& f) const{
            return ((this->num)*((int)f.den) < ((int)(this->den))*f.num);
        };
        inline bool operator<=(const Fraction& f) const{
            return ((this->num)*((int)f.den) <= ((int)(this->den))*f.num);
        }
        inline bool operator>(const Fraction& f) const{
            return ((this->num)*((int)f.den) > ((int)(this->den))*f.num);
        }
        inline bool operator>=(const Fraction& f) const{
            return ((this->num)*((int)f.den) >= ((int)(this->den))*f.num);
        }

        /*
         *  SPECIAL OPERATORS
         * 
         *  Member functions to compute inverse of a fraction
         *  Object doesn't need to change hence defined as const function
         *  We return by value the inverse of the calling fraction object, object itself doesn't change
         */

        Fraction operator!() const;

        /*
         *  I/O OPERATORS
         * 
         *  Friend functions to input/output fractions
         *  For the output operator, object doesn't need to change, hence passing UDT as const reference
         *  For the input operator, object needs to change, hence passing UDT as non-const reference
         *  Friend function as access to private data members is required to perform input/output operations
         */

        friend istream& operator>>(istream&, Fraction&);
        friend ostream& operator<<(ostream&, const Fraction&);

        /*
         *  CONSTANTS OF THE DATATYPE
         * 
         *  Static constants which represent the zero and unity fractions
         *  Declared constant to prevent any modification during runtime
         */

        static const Fraction sc_fUnity;
        static const Fraction sc_fZero;
};

#endif