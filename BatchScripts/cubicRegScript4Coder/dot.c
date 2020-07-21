/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: dot.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "dot.h"
#include "mkl_cblas.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                const emxArray_real_T *b
 * Return Type  : double
 */
double dot(const emxArray_real_T *a, const emxArray_real_T *b)
{
  double c;
  if (a->size[0] < 1) {
    c = 0.0;
  } else {
    c = cblas_ddot((MKL_INT)a->size[0], &a->data[0], (MKL_INT)1, &b->data[0],
                   (MKL_INT)1);
  }

  return c;
}

/*
 * File trailer for dot.c
 *
 * [EOF]
 */
