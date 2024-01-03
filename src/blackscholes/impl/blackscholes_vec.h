// blackscholes_vec.h

#ifndef BLACKSCHOLES_VEC_H
#define BLACKSCHOLES_VEC_H

#include <arm_neon.h>

// Public function declarations
float32x4_t blackScholesVectorized(float32x4_t S, float32x4_t K, float32x4_t r, float32x4_t v, float32x4_t t, char optionType);
#endif // BLACKSCHOLES_VEC_H