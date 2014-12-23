#include "random_number.h"

//call constructor
RandomNumber::RandomNumber() {
}

double RandomNumber::ran0(long *idum) {
    /* function for uniform random number */
    const int a = 16807, m = 2147483647, q = 127773;
    const int r = 2836, MASK = 123459876;
    const double am = 1./m;
    long k; double ans;
   
    *idum ^= MASK;
    k = (*idum)/q;
    *idum = a*(*idum - k*q) - r*k;
    if(*idum < 0) {
        *idum += m;
    }

    ans = am*(*idum);
    *idum ^= MASK;

    return ans;
} //end function ran0
