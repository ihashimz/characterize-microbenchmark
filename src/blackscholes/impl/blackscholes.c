/* Standard C includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Function to compute the cumulative normal distribution
static double normalCDF(double value) {
    return 0.5 * erfc(-value * M_SQRT1_2);
}

static double getD1(double s, double k, double r, double v, double t) {
    double sqrtT = sqrt(t);
    return (log(s / k) + (r + 0.5 * v * v) * t) / (v * sqrtT);
}


static double getD2(double s, double k, double r, double v, double t) {
    double sqrtT = sqrt(t);
    return getD1(s, k, r, v, t) - (v * sqrtT);
}


static double getCall(double s, double k, double r, double v, double t) {
    double d1 = getD1(s, k, r, v, t);
    double d2 = getD2(s, k, r, v, t);
    return (s * normalCDF(d1)) - (k * exp(-r * t) * normalCDF(d2));
}



static double getPut(double s, double k, double r, double v, double t) {
    double d1 = getD1(s, k, r, v, t);
    double d2 = getD2(s, k, r, v, t);
    return (k * exp(-r * t) * normalCDF(-d2)) - (s * normalCDF(-d1));
}

double blackScholes(double s, double k, double r, double v, double t, char optionType) {
    return (optionType == 'C') ? getCall(s, k, r, v, t) : getPut(s, k, r, v, t);
}