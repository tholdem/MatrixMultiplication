/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * evalPenaltyFcn_CP.h
 *
 * Code generation for function 'evalPenaltyFcn_CP'
 *
 */

#ifndef EVALPENALTYFCN_CP_H
#define EVALPENALTYFCN_CP_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScriptCOPY_types.h"

/* Function Declarations */
extern void b_evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R,
  const double U_tunableEnvironment[1], const double V_tunableEnvironment[1],
  const double W_tunableEnvironment[1], emxArray_real_T *outputFcn);
extern void c_evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R,
  const double U_tunableEnvironment[1], const double V_tunableEnvironment[1],
  const double W_tunableEnvironment[1], emxArray_real_T *outputFcn);
extern double evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R,
  const double U_tunableEnvironment[1], const double V_tunableEnvironment[1],
  const double W_tunableEnvironment[1]);

#endif

/* End of code generation (evalPenaltyFcn_CP.h) */
