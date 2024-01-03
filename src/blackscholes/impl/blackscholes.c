/* Standard C includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Function to compute the cumulative normal distribution
static double normalCDF(double value) {
    return 0.5 * erfc(-value * M_SQRT1_2);
}

static double D1(double s, double k, double r, double v, double t) {
    double sqrtT = sqrt(t);
    return (log(s / k) + (r + 0.5 * v * v) * t) / (v * sqrtT);
}


static double D2(double s, double k, double r, double v, double t) {
    double sqrtT = sqrt(t);
    return D1(s, k, r, v, t) - (v * sqrtT);
}


static double CALL(double s, double k, double r, double v, double t) {
    double d1 = D1(s, k, r, v, t);
    double d2 = D2(s, k, r, v, t);
    return (s * normalCDF(d1)) - (k * exp(-r * t) * normalCDF(d2));
}



static double PUT(double s, double k, double r, double v, double t) {
    double d1 = D1(s, k, r, v, t);
    double d2 = D1(s, k, r, v, t);
    return (k * exp(-r * t) * normalCDF(-d2)) - (s * normalCDF(-d1));
}

double blackScholes(double s, double k, double r, double v, double t, char optionType) {
    return (optionType == 'C') ? CALL(s, k, r, v, t) : PUT(s, k, r, v, t);
}