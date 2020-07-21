/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ARCSubproblem.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

#ifndef ARCSUBPROBLEM_H
#define ARCSUBPROBLEM_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScript4Coder_types.h"

/* Function Declarations */
extern void ARCSubproblem(const emxArray_real_T *gx, const emxArray_real_T *B,
  const emxArray_real_T *v1, double lambda1, double sigma, double maxIts,
  emxArray_real_T *p);

#endif

/*
 * File trailer for ARCSubproblem.h
 *
 * [EOF]
 */
