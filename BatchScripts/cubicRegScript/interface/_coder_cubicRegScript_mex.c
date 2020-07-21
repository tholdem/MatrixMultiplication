/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_cubicRegScript_mex.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "_coder_cubicRegScript_api.h"
#include "_coder_cubicRegScript_mex.h"

/* Function Declarations */
static void cubicRegScript_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray
  *prhs[7]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                int32_T nrhs
 *                const mxArray *prhs[7]
 * Return Type  : void
 */
static void cubicRegScript_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray
  *prhs[7])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 7) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 7, 4,
                        14, "cubicRegScript");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "cubicRegScript");
  }

  /* Call the function. */
  cubicRegScript_api(prhs, nlhs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  (void)plhs;
  mexAtExit(cubicRegScript_atexit);

  /* Module initialization. */
  cubicRegScript_initialize();

  /* Dispatch the entry-point. */
  cubicRegScript_mexFunction(nlhs, nrhs, prhs);

  /* Module termination. */
  cubicRegScript_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_cubicRegScript_mex.c
 *
 * [EOF]
 */
