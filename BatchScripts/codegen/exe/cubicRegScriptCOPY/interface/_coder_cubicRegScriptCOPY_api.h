/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cubicRegScriptCOPY_api.h
 *
 * Code generation for function '_coder_cubicRegScriptCOPY_api'
 *
 */

#ifndef _CODER_CUBICREGSCRIPTCOPY_API_H
#define _CODER_CUBICREGSCRIPTCOPY_API_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void cubicRegScriptCOPY(real_T i, real_T num, real_T rank, real_T t,
  real_T R, real_T k, real_T errThd, real_T maxIts);
extern void cubicRegScriptCOPY_api(const mxArray * const prhs[8], int32_T nlhs);
extern void cubicRegScriptCOPY_atexit(void);
extern void cubicRegScriptCOPY_initialize(void);
extern void cubicRegScriptCOPY_terminate(void);
extern void cubicRegScriptCOPY_xil_shutdown(void);
extern void cubicRegScriptCOPY_xil_terminate(void);

#endif

/* End of code generation (_coder_cubicRegScriptCOPY_api.h) */
