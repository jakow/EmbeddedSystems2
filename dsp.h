#ifndef DSP_H_
#define DSP_H_

static const int flt_numStages = 4;
static const int flt_coefficientLength = 20;

extern float coeff_0k5_1k0[20];
extern float coeff_1k5_1k75[20];
extern float coeff_2k0_2k5[20];
extern float coeff_3k0_3k75[20];
float* flt_coeffs[4] = {
	coeff_0k5_1k0, coeff_1k5_1k75, coeff_2k0_2k5, coeff_3k0_3k75
};

typedef struct
{
	float state[16];
	float output;
} fltType;

typedef struct
{
	float *pInput;
	float *pOutput;
	float *pState;
	float *pCoefficients;
	short count;
} flt_executionState;

fltType *flt_create(void);

void flt_destroy(fltType *pObject);

void flt_init(fltType * pThis);

void flt_reset(fltType * pThis);

#define flt_writeInput(pThis, input)  \
	flt_filterBlock(pThis, &input, &pThis->output, 1);

#define flt_readOutput(pThis)  \
	pThis->output

 int flt_filterBlock(fltType* pThis, float* pInput, float* pOutput,
	 unsigned int count, float* flt_coefficients);

#define flt_outputToFloat(output)  \
	(output)

#define flt_inputFromFloat(input)  \
	(input)

 void flt_filterBiquad(flt_executionState * pExecState);
#endif // DSP_H_
