/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ARCSubproblem.h
 *
 * Code generation for function 'ARCSubproblem'
 *
 */

#ifndef ARCSUBPROBLEM_H
#define ARCSUBPROBLEM_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScriptCOPY_types.h"

/* Function Declarations */
extern void ARCSubproblem(const emxArray_creal_T *gx, const emxArray_real_T *B,
  const emxArray_creal_T *v1, const creal_T lambda1, double sigma, double maxIts,
  emxArray_creal_T *p);

#endif

/* End of code generation (ARCSubproblem.h) */
