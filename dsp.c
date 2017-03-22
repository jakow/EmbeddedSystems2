#include "dsp.h"

#include <stdlib.h> // For malloc/free
#include <string.h> // For memset

// The micromodeler DSP code was changed so that it can use the
// float arrays below as parameters. This takes advantage of the fact that
// the bandpass filters have the same topology and the same number
// of coefficients. To use a particular filter, it is enough to point
// the modified code to which coefficient array it should use. This is done
// by passing extra parameter to flt_filterBlock

float coeff_0k5_1k0[20] =
{
  // b0, b1, b2, a1, a2
  0.9559025796657589, -1.9118051593315177, 0.9559025796657589,
  1.527635591369355, -0.7253280429895612,
  // b0, b1, b2, a1, a2
  0.25, -0.5, 0.25, 1.7479956457420662, -0.8993446739158173,
  // b0, b1, b2, a1, a2
  0.0625, 0.125, 0.0625, 1.325173051363978, -0.6584500002289182,
  // b0, b1, b2, a1, a2
  0.0625, 0.125, 0.0625, 1.3138787406673829, -0.8278481652242764
};


float coeff_1k5_1k75[20] =
{
  // b0, b1, b2, a1, a2
  0.14903818094588128, -0.29807636189176256, 0.14903818094588128,
  0.6009532423247502, -0.835172813291451,
  // b0, b1, b2, a1, a2
  0.0625, -0.125, 0.0625, 0.7257577382283413, -0.9298543567377061,
  // b0, b1, b2, a1, a2
  0.125, 0.25, 0.125, 0.4672156621466492, -0.8316490295746326,
  // b0, b1, b2, a1, a2
  0.0625, 0.125, 0.0625, 0.39004046713368923, -0.9260132764830762
};

float coeff_2k0_2k5[20] =
{
  // b0, b1, b2, a1, a2
  0.23897564491644038, -0.47795128983288077, 0.23897564491644038,
  -0.20582187469403773, -0.6869973849561894,
  // b0, b1, b2, a1, a2
  0.125, -0.25, 0.125, -0.027172519467246737, -0.8581727302742403,
  // b0, b1, b2, a1, a2
  0.25, 0.5, 0.25, -0.46354156147532416, -0.695187871934875,
  // b0, b1, b2, a1, a2
  0.125, 0.25, 0.125, -0.6912446676183592, -0.8675652487437044
};

float coeff_3k0_3k75[20] =
{
  // b0, b1, b2, a1, a2
  0.1238245861926606, -0.2476491723853212, 0.1238245861926606,
  -1.2220875221654894, -0.46223724401245486,
  // b0, b1, b2, a1, a2
  0.0625, -0.125, 0.0625, -1.237981840349054, -0.7151285708936009,
  // b0, b1, b2, a1, a2
  1, 2, 1, -1.6338725584832217, -0.6958169496025528,
  // b0, b1, b2, a1, a2
  0.5, 1, 0.5, -1.8690948366571372, -0.9080021415622019
};

float test_coeff[20] = {
 1, 0, 0, 0, 0,
 1, 0, 0, 0, 0,
 1, 0, 0, 0, 0,
 1, 0, 0, 0, 0
};

float* flt_coeffs[4]  = {
	coeff_0k5_1k0, coeff_1k5_1k75, coeff_2k0_2k5, coeff_3k0_3k75
};

fltType *flt_create(void) {
  // Allocate memory for the object
  fltType *result = (fltType*) malloc(sizeof(fltType));
  flt_init(result);
  return result;
}

void flt_destroy(fltType *pObject) {
  free(pObject);
}

void flt_init(fltType * pThis) {
  flt_reset(pThis);
}

void flt_reset(fltType * pThis) {
  memset( &pThis->state, 0, sizeof( pThis->state ) ); // Reset state to 0
  pThis->output = 0; // Reset output

}
/*
flt_coefficients is the pointer to array which dictates which set of filter
coefficients to use. This takes advantage of the fact that
the bandpass filters have the same topology and the same number
of coefficients. (Don't Repeat Yourself!)
*/
int flt_filterBlock(fltType * pThis, float * pInput, float * pOutput,
  unsigned int count, float* flt_coefficients)
{
  // The executionState structure holds call data, minimizing stack reads
  // and writes
  flt_executionState executionState;
  // If there are no input samples, return immediately
  if( ! count ) return 0;
// Pointers to the input and output buffers that each call to filterBiquad()
// will use. pInput and pOutput can be equal, allowing reuse of the same memory
  executionState.pInput = pInput;
  executionState.pOutput = pOutput;
  // The number of samples to be processed
  executionState.count = count;
   // Pointer to the biquad's internal state and coefficients.
  executionState.pState = pThis->state;
  // Each call to filterBiquad() will advance pState and pCoefficients
  // to the next biquad
  // use the coefficients supplied with the input parameter
  executionState.pCoefficients = flt_coefficients;

  // The 1st call to flt_filterBiquad() reads from the caller supplied input
  // buffer and writes to the output buffer. The remaining calls to
  // filterBiquad() recycle the same output buffer, so that multiple
  // intermediate buffers are not required.

  flt_filterBiquad(&executionState);		// Run biquad #0
  // The remaining biquads will now re-use the same output buffer.
  executionState.pInput = executionState.pOutput;
  flt_filterBiquad(&executionState);		// Run biquad #1
  flt_filterBiquad(&executionState);		// Run biquad #2
  flt_filterBiquad(&executionState);		// Run biquad #3

  // At this point, the caller-supplied output buffer will contain the filtered
  // samples and the input buffer will contain the unmodified input samples.
  return count;		// Return the number of samples processed

}

void flt_filterBiquad( flt_executionState * pExecState )
{
  // Read state variables
  float w0, x0;
  float w1 = pExecState->pState[0];
  float w2 = pExecState->pState[1];

  // Read coefficients into work registers
  float b0 = *(pExecState->pCoefficients++);
  float b1 = *(pExecState->pCoefficients++);
  float b2 = *(pExecState->pCoefficients++);
  float a1 = *(pExecState->pCoefficients++);
  float a2 = *(pExecState->pCoefficients++);

  // Read source and target pointers
  float *pInput  = pExecState->pInput;
  float *pOutput = pExecState->pOutput;
  short count = pExecState->count;
  float accumulator;

  // Loop for all samples in the input buffer
  while(count--)
  {
    // Read input sample
    x0 = *(pInput++);

    // Run feedback part of filter
    accumulator  = w2 * a2;
    accumulator += w1 * a1;
    accumulator += x0 ;

    w0 = accumulator ;

    // Run feedforward part of filter
    accumulator  = w0 * b0;
    accumulator += w1 * b1;
    accumulator += w2 * b2;

    w2 = w1;		// Shuffle history buffer
    w1 = w0;

    // Write output
    *(pOutput++) = accumulator;
  }

  // Write state variables
  *(pExecState->pState++) = w1;
  *(pExecState->pState++) = w2;

}
