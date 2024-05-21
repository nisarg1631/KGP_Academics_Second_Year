#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Fraction.hxx"
using namespace std;

/*
 *  CONSTANTS OF THE DATATYPE
 * 
 *  Initialization of static constants
 */

//constant representing unity fraction 1 / 1
const Fraction Fraction::sc_fUnity = Fraction();
//constant representing zero fraction 0 / 1
const Fraction Fraction::sc_fZero = Fraction(0);
//constant representing precision value used to construct fraction from double
const unsigned int Fraction::_precision = 1000000;

/*
 *  UTILITY FUNCTIONS
 */

//normalize function
//normalizes the fraction by ensuring gcd(num, den)=1, used the utility gcd function for the same
//also sets denominator to 1 if the numerator is 0 (ensures a uniform representation for the zero fraction)
void Fraction::normalize(){
    if(num==0){
        den=1;
        return;
    }
    int common = gcd(num,den);
    num/=common;
    den/=common;
}

//gcd function
//uses the euclidean algorithm to compute greatest common divisor of a and b
int Fraction::gcd(int a, int b){
    while(b){
        a%=b;
        swap(a, b);
    }
    return a;
}

/*
 *  CONSTRUCTORS AND DESTRUCTOR
 */

//construction from integers m and n, exits if n==0
//if n is negative it constructs using -m and -n
//for negative fraction first it normalizes fraction |m| / n and then sets the negative sign on numerator
Fraction::Fraction(int m, int n){
    if(n==0)
        exit(1);
    if(n<0)
        m=-m, n=-n;    
    bool isNegative=false;
    if(m<0)
        isNegative=true, m=abs(m);
    num=m, den=n;
    normalize();
    if(isNegative)
        num=-num;
}

//construction from double d
//if d is negative it constructs the fraction from |d| and then sets the negative sign on numerator
//first the double d is broken into integral and fractional parts
//the numerator is set to floor(fractional * precision) and denominator to precision
//after normalization the integral part is added
Fraction::Fraction(double d){
    bool isNegative=false;
    if(d<0)
        isNegative=true, d=abs(d);
    int integral = d;
    double fractional = d-integral;
    num=(fractional*_precision);
    den=_precision;
    normalize();
    num=num+(den*integral);
    if(isNegative)
        num=-num;
}

//copy constructor
//simply copies the values of numerator and denominator
Fraction::Fraction(const Fraction& f) : num(f.num), den(f.den) {}

//destructor
//as we are not dynamically allocating any memory there is no need for any deallocation
//the object also doesn't require any other actions at the end of lifetime hence default destructor does the work
Fraction::~Fraction(){}

/*
 *  COPY ASSIGNMENT OPERATOR
 */

//although we don't necessarily need to check for self copy it has been followed as a good design principle
Fraction& Fraction::operator=(const Fraction& f){
    if(this != &f){
        this->num=f.num;
        this->den=f.den;
    }
    return *this;
}

/*
 *  UNARY OPERATORS ++ and --
 */

// (p / q) + 1 = (p + q) / q
// (p / q) - 1 = (p - q) / q

//adds one and returns reference to obejct
Fraction& Fraction::operator++(){
    num+=den;
    return *this;
}

//creates a copy of object, adds one and returns the copy
Fraction Fraction::operator++(int){
    Fraction temp(*this);
    num+=den;
    return temp;
}

//subtracts one and returns reference to obejct
Fraction& Fraction::operator--(){
    num-=den;
    return *this;
}

//creates a copy of object, subtracts one and returns the copy
Fraction Fraction::operator--(int){
    Fraction temp(*this);
    num-=den;
    return temp;
}

/*
 *  BINARY ARITHMETIC OPERATORS
 */

//addition
//for p1 / q1 and p2 / q2 addition returns the fraction (p1*q2 + p2*q1) / (q1*q2)
//to avoid overflow we use the lcm of q1 and q2 as denominator and calculate numerator accordingly
Fraction operator+(const Fraction& f1, const Fraction& f2){
    int lcm=Fraction::lcm(f1.den, f2.den);
    int num1=f1.num*(lcm/f1.den);
    int num2=f2.num*(lcm/f2.den);
    return Fraction(num1+num2,lcm);
}

//subtraction
//defined as the addition of f1 with the negation (unary minus) of f2
Fraction operator-(const Fraction& f1, const Fraction& f2){
    return f1+(-f2);
}

//multiplication
//for p1 / q1 and p2 / q2 multiplication returns the fraction (p1*p2) / (q1*q2)
Fraction operator*(const Fraction& f1, const Fraction& f2){
    return Fraction(f1.num*f2.num, f1.den*f2.den);
}

//division
//defined as the multiplication of f1 with the inverse of f2
//exits the program if f2 is zero fraction (see implementation of inverse operator)
Fraction operator/(const Fraction& f1, const Fraction& f2){
    return f1*!f2;
}

//remainder
//if f' is the fractional part of f1 / f2, then remainder is defined as f'*f2
//the fractional part of p / q is equal to p%q / q
Fraction operator%(const Fraction& f1, const Fraction& f2){
    Fraction temp=f1/f2;
    temp.num%=temp.den;
    return temp*f2;
}

/*
 *  SPECIAL OPERATORS
 */

//inverse operator
//returns q / p for input p / q if p!=0, otherwise exits the program
Fraction Fraction::operator!() const{
    if(*this==Fraction::sc_fZero)
        exit(1);
    return Fraction(this->den, this->num);
}

/*
 *  I/O OPERATORS
 */

//output operator
//outputs "p / q" if q!=1 and "p" if q==1
ostream& operator<<(ostream& os, const Fraction& f){
    os<<f.num;
    if(f.den!=1)
        os<<" / "<<f.den;
    return os;
}

//input operator
//read two integers into numerator and denominator of fraction, calls normalize to reduce the fraction
istream& operator>>(istream& is, Fraction& f){
    is>>f.num>>f.den;
    f.normalize(); 
    return is;
}
