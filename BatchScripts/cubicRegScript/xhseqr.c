/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "xhseqr.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : creal_T h_data[]
 *                int h_size[2]
 * Return Type  : int
 */
int xhseqr(creal_T h_data[], int h_size[2])
{
  int info;
  creal_T z;
  lapack_int n_t;
  lapack_int info_t;
  creal_T w_data[2];
  int loop_ub;
  int i31;
  int b_loop_ub;
  int i32;
  int i33;
  z.re = 0.0;
  z.im = 0.0;
  n_t = (lapack_int)h_size[0];
  info_t = LAPACKE_zhseqr(LAPACK_COL_MAJOR, 'S', 'N', n_t, (lapack_int)1,
    (lapack_int)h_size[0], (lapack_complex_double *)&h_data[0], n_t,
    (lapack_complex_double *)&w_data[0], (lapack_complex_double *)&z,
    (lapack_int)h_size[0]);
  info = (int)info_t;
  if (info < 0) {
    loop_ub = h_size[1];
    for (i31 = 0; i31 < loop_ub; i31++) {
      b_loop_ub = h_size[0];
      for (i32 = 0; i32 < b_loop_ub; i32++) {
        i33 = i32 + h_size[0] * i31;
        h_data[i33].re = rtNaN;
        h_data[i33].im = 0.0;
      }
    }
  }

  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
