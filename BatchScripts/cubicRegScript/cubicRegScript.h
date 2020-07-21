/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

#ifndef CUBICREGSCRIPT_H
#define CUBICREGSCRIPT_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScript_types.h"

/* Function Declarations */
extern double __anon_fcn(const double U_tunableEnvironment[1], const double
  V_tunableEnvironment[1], const double W_tunableEnvironment[1], const
  emxArray_real_T *x);
extern void b___anon_fcn(const double U_tunableEnvironment[1], const double
  V_tunableEnvironment[1], const double W_tunableEnvironment[1], const
  emxArray_real_T *x, emxArray_real_T *varargout_1);
extern void c___anon_fcn(const double U_tunableEnvironment[1], const double
  V_tunableEnvironment[1], const double W_tunableEnvironment[1], const
  emxArray_real_T *x, emxArray_real_T *varargout_1);
extern void cubicRegScript(double i, double num, double rank, double k, double
  errThd, double maxIts, const char outputDir[10]);

#endif

/*
 * File trailer for cubicRegScript.h
 *
 * [EOF]
 */