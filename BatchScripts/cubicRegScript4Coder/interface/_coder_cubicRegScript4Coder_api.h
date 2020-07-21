/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_cubicRegScript4Coder_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

#ifndef _CODER_CUBICREGSCRIPT4CODER_API_H
#define _CODER_CUBICREGSCRIPT4CODER_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_cubicRegScript4Coder_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void cubicRegScript4Coder(real_T i, real_T num, real_T rank, real_T k,
  real_T errThd, real_T maxIts, char_T outputDir[10]);
extern void cubicRegScript4Coder_api(const mxArray * const prhs[7], int32_T nlhs);
extern void cubicRegScript4Coder_atexit(void);
extern void cubicRegScript4Coder_initialize(void);
extern void cubicRegScript4Coder_terminate(void);
extern void cubicRegScript4Coder_xil_terminate(void);

#endif

/*
 * File trailer for _coder_cubicRegScript4Coder_api.h
 *
 * [EOF]
 */
