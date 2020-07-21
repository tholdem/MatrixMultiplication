/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cubicRegScriptCOPY_mex.c
 *
 * Code generation for function '_coder_cubicRegScriptCOPY_mex'
 *
 */

/* Include files */
#include "_coder_cubicRegScriptCOPY_mex.h"
#include "_coder_cubicRegScriptCOPY_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void cubicRegScriptCOPY_mexFunction(int32_T nlhs, int32_T
  nrhs, const mxArray *prhs[8]);

/* Function Definitions */
void cubicRegScriptCOPY_mexFunction(int32_T nlhs, int32_T nrhs, const mxArray
  *prhs[8])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 8) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 8, 4,
                        18, "cubicRegScriptCOPY");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "cubicRegScriptCOPY");
  }

  /* Call the function. */
  cubicRegScriptCOPY_api(prhs, nlhs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  (void)plhs;
  mexAtExit(&cubicRegScriptCOPY_atexit);

  /* Module initialization. */
  cubicRegScriptCOPY_initialize();

  /* Dispatch the entry-point. */
  cubicRegScriptCOPY_mexFunction(nlhs, nrhs, prhs);

  /* Module termination. */
  cubicRegScriptCOPY_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_cubicRegScriptCOPY_mex.c) */
