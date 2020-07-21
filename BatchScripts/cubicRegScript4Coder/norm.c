/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: norm.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "norm.h"
#include "mkl_cblas.h"

/* Function Definitions */

/*
 * Arguments    : const double x[729]
 * Return Type  : double
 */
double b_norm(const double x[729])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 729; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double c_norm(const emxArray_real_T *x)
{
  double y;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = cblas_dnrm2((MKL_INT)x->size[0], &x->data[0], (MKL_INT)1);
  }

  return y;
}

/*
 * File trailer for norm.c
 *
 * [EOF]
 */
