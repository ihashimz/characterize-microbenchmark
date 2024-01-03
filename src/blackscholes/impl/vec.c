/* vec.c
 *
 * Author:
 * Date  :
 *
 *  Description
 */

/* Standard C includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*  -> SIMD header file  */
#if defined(__amd64__) || defined(__x86_64__)
#include <immintrin.h>
#elif defined(__aarch__) || defined(__aarch64__) || defined(__arm64__)
#include <arm_neon.h>
#endif


/* Include common headers */
#include "../common/types.h"
#include "../common/macros.h"

/* Include application-specific headers */
#include "../../blackscholes/include/types.h"
#include "../impl/blackscholes_vec.h"


/* Alternative Implementation */
void* impl_vector(void* args) {
    args_t* arguments = (args_t*)args;
    size_t size = arguments->num_stocks;

    // Pointers to input arrays
    float *S = arguments->sptPrice;
    float *K = arguments->strike;
    float *r = arguments->rate;
    float *v = arguments->volatility;
    float *t = arguments->otime;
    char *type = arguments->otype;

    float *output = arguments->output;

    for (size_t i = 0; i < size; i += 4) {
        // Load 4 elements from each input array into NEON registers
        float32x4_t SVec = vld1q_f32(&S[i]);
        float32x4_t KVec = vld1q_f32(&K[i]);
        float32x4_t rVec = vld1q_f32(&r[i]);
        float32x4_t vVec = vld1q_f32(&v[i]);
        float32x4_t tVec = vld1q_f32(&t[i]);
        char *typeVec = &type[i];

        // Vectorized Black-Scholes calculations (placeholder)
        // You will need to implement vectorized versions of the required math functions
        // and adapt the Black-Scholes formula for SIMD
        float32x4_t resultVec = blackScholesVectorized(SVec, KVec, rVec, vVec, tVec,typeVec); 

        // Store the result back to the output array
        vst1q_f32(&output[i], resultVec);
    }

    return arguments->output;
}
