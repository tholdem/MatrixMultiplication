/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eig.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

#ifndef EIG_H
#define EIG_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScript4Coder_types.h"

/* Function Declarations */
extern void b_eig(const creal_T A_data[], const int A_size[2], creal_T V_data[],
                  int V_size[1]);
extern void eig(const emxArray_real_T *A, emxArray_creal_T *V, emxArray_creal_T *
                D);

#endif

/*
 * File trailer for eig.h
 *
 * [EOF]
 */
