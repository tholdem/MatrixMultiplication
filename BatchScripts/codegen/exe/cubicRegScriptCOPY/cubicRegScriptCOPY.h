/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cubicRegScriptCOPY.h
 *
 * Code generation for function 'cubicRegScriptCOPY'
 *
 */

#ifndef CUBICREGSCRIPTCOPY_H
#define CUBICREGSCRIPTCOPY_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScriptCOPY_types.h"

/* Function Declarations */
extern double __anon_fcn(const double U_tunableEnvironment[1], const double
  V_tunableEnvironment[1], const emxArray_real_T *x);
extern void cubicRegScriptCOPY(double i, double num, double rank, double t,
  double R, double k, double errThd, double maxIts);
extern void d___anon_fcn(const emxArray_real_T *x, emxArray_creal_T *varargout_1);
extern void e___anon_fcn(const double U_tunableEnvironment[1], const double
  V_tunableEnvironment[1], const double W_tunableEnvironment[1], const
  emxArray_real_T *x, emxArray_real_T *varargout_1);

#endif

/* End of code generation (cubicRegScriptCOPY.h) */
