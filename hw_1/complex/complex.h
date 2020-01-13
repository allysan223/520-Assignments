#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif complex object and method definitions
 *
 *  A complex object is a struct with the real part, denoted real, and
 *  the imaginary part, denoted im. Varions Methods that take complex numbers and returns
 *  arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first complex number
 *  \param b The second complex number
 */
Complex add ( Complex a, Complex b );

/*! Negates a complex number
 *  \param a The complex number
 */
Complex negate ( Complex a );

/*! multiply two complex numbers
 *  \param a The first complex number
 *  \param b The second complex number
 */
Complex multiply ( Complex a, Complex b );

/*! magnitude of complex number
 *  \param a The first complex number
 */
double magnitude ( Complex a );

#endif