/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "xgehrd.h"
#include "cubicRegScript_emxutil.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : creal_T a_data[]
 *                int a_size[2]
 * Return Type  : void
 */
void b_xgehrd(creal_T a_data[], int a_size[2])
{
  lapack_int info_t;
  creal_T tau_data[1];
  int loop_ub;
  int i28;
  int b_loop_ub;
  int i29;
  int i30;
  if (a_size[0] > 1) {
    info_t = LAPACKE_zgehrd(LAPACK_COL_MAJOR, (lapack_int)a_size[0], (lapack_int)
      1, (lapack_int)a_size[0], (lapack_complex_double *)&a_data[0], (lapack_int)
      a_size[0], (lapack_complex_double *)&tau_data[0]);
    if ((int)info_t != 0) {
      loop_ub = a_size[1];
      for (i28 = 0; i28 < loop_ub; i28++) {
        b_loop_ub = a_size[0];
        for (i29 = 0; i29 < b_loop_ub; i29++) {
          i30 = i29 + a_size[0] * i28;
          a_data[i30].re = rtNaN;
          a_data[i30].im = 0.0;
        }
      }
    }
  }
}

/*
 * Arguments    : emxArray_real_T *a
 *                emxArray_real_T *tau
 * Return Type  : void
 */
void xgehrd(emxArray_real_T *a, emxArray_real_T *tau)
{
  int lda;
  int ntau;
  int i22;
  lapack_int info_t;
  int i23;
  lda = a->size[0];
  if (1 > lda) {
    lda = 1;
  }

  if (a->size[0] < 1) {
    ntau = 0;
  } else {
    ntau = a->size[0] - 1;
  }

  i22 = tau->size[0];
  tau->size[0] = ntau;
  emxEnsureCapacity_real_T(tau, i22);
  if (a->size[0] > 1) {
    info_t = LAPACKE_dgehrd(LAPACK_COL_MAJOR, (lapack_int)a->size[0],
      (lapack_int)1, (lapack_int)a->size[0], &a->data[0], (lapack_int)lda,
      &tau->data[0]);
    if ((int)info_t != 0) {
      i22 = a->size[0] * a->size[1];
      emxEnsureCapacity_real_T(a, i22);
      lda = a->size[1];
      for (i22 = 0; i22 < lda; i22++) {
        ntau = a->size[0];
        for (i23 = 0; i23 < ntau; i23++) {
          a->data[i23 + a->size[0] * i22] = rtNaN;
        }
      }

      lda = tau->size[0];
      i22 = tau->size[0];
      tau->size[0] = lda;
      emxEnsureCapacity_real_T(tau, i22);
      for (i22 = 0; i22 < lda; i22++) {
        tau->data[i22] = rtNaN;
      }
    }
  }
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
