/* para.c
 *
 * Author:
 * Date  :
 *
 *  Description
 */

#define _GNU_SOURCE

/* Standard C includes */
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>


/* Include common headers */
#include "../common/types.h"
#include "../common/macros.h"


/* If we are on Darwin, include the compatibility header */
#if defined(__APPLE__)
#include "../common/mach_pthread_compatibility.h"
#endif

/* Include application-specific headers */
#include "../blackscholes/include/types.h"
#include "../impl/blackscholes.h"


typedef struct {
    size_t start;  // Start index for this thread's work
    size_t end;    // End index (exclusive) for this thread's work
    float *S;      // Array of spot prices
    float *K;      // Array of strike prices
    float *r;      // Array of risk-free interest rates
    float *v;      // Array of volatilities
    float *t;      // Array of times to maturity
    char *otype;   // Array of option types ('C' or 'P')
    float *output; // Output array to store the results
} thread_args_t;

/* Alternative Implementation */
void* worker(void* arg) {
    thread_args_t *p_args = (thread_args_t *)arg;

    for (size_t i = p_args->start; i < p_args->end; ++i) {
        p_args->output[i] = blackScholes(p_args->S[i], p_args->K[i], 
                                         p_args->r[i], p_args->v[i], 
                                         p_args->t[i], p_args->otype[i]);
    }

    return NULL;
}

void* impl_parallel(void* args) {
    args_t* p_args = (args_t*)args;
    size_t nthreads = p_args->nthreads;
    size_t size = p_args->num_stocks;

    // Create thread arguments
    thread_args_t targs[nthreads];
    pthread_t threads[nthreads];
    size_t size_per_thread = size / nthreads;
    size_t remaining = size % nthreads;

    for (size_t i = 0; i < nthreads; ++i) {
        targs[i].start = i * size_per_thread;
        targs[i].end = (i == nthreads - 1) ? size : (i + 1) * size_per_thread;
        targs[i].S = p_args->sptPrice;
        targs[i].K = p_args->strike;
        targs[i].r = p_args->rate;
        targs[i].v = p_args->volatility;
        targs[i].t = p_args->otime;
        targs[i].otype = p_args->otype;
        targs[i].output = p_args->output;

        if (i > 0) { // Main thread will also do work, so skip creating a thread for it
            pthread_create(&threads[i], NULL, worker, &targs[i]);
        }
    }

    // Main thread doing part of the work
    worker(&targs[0]);

    // Join threads
    for (size_t i = 1; i < nthreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return p_args->output;
}
