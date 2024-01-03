/* scalar.c
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

/* Include common headers */
#include "../common/types.h"
#include "../common/macros.h"

/* Include application-specific headers */
#include "../../blackscholes/include/types.h"
#include "../impl/blackscholes.h"

/* Naive Implementation */
void* impl_scalar(void* args)
{
    args_t* arguments = (args_t*)args;
    register size_t size = arguments->num_stocks;
    float *S = arguments->sptPrice;
    float *K = arguments->strike;
    float *r = arguments->rate;
    float *v = arguments->volatility;
    float *t = arguments->otime;
    char *type = arguments->otype;
    float *output = arguments->output;

    for (size_t i = 0; i < size; ++i) {
        output[i] = blackScholes(S[i], K[i], r[i], v[i], t[i], type[i]);
    }

    // Return a pointer to the output array
    return arguments->output;
}