/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgetrf.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "xgetrf.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                emxArray_real_T *A
 *                int lda
 *                emxArray_int32_T *ipiv
 *                int *info
 * Return Type  : void
 */
void xgetrf(int m, int n, emxArray_real_T *A, int lda, emxArray_int32_T *ipiv,
            int *info)
{
  emxArray_lapack_int *ipiv_t;
  int i25;
  int u0;
  lapack_int info_t;
  int loop_ub;
  int i26;
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    ipiv->size[0] = 1;
    ipiv->size[1] = 0;
    *info = 0;
  } else {
    emxInit_lapack_int(&ipiv_t, 1);
    i25 = ipiv_t->size[0];
    if (m < n) {
      u0 = m;
    } else {
      u0 = n;
    }

    if (u0 <= 1) {
      u0 = 1;
    }

    ipiv_t->size[0] = u0;
    emxEnsureCapacity_lapack_int(ipiv_t, i25);
    info_t = LAPACKE_dgetrf_work(LAPACK_COL_MAJOR, (lapack_int)m, (lapack_int)n,
      &A->data[0], (lapack_int)lda, &ipiv_t->data[0]);
    *info = (int)info_t;
    i25 = ipiv->size[0] * ipiv->size[1];
    ipiv->size[0] = 1;
    ipiv->size[1] = ipiv_t->size[0];
    emxEnsureCapacity_int32_T(ipiv, i25);
    if (*info < 0) {
      i25 = A->size[0] * A->size[1];
      emxEnsureCapacity_real_T(A, i25);
      u0 = A->size[1];
      for (i25 = 0; i25 < u0; i25++) {
        loop_ub = A->size[0];
        for (i26 = 0; i26 < loop_ub; i26++) {
          A->data[i26 + A->size[0] * i25] = rtNaN;
        }
      }

      i25 = ipiv->size[1] - 1;
      for (u0 = 0; u0 <= i25; u0++) {
        ipiv->data[u0] = u0 + 1;
      }
    } else {
      i25 = ipiv->size[1] - 1;
      for (u0 = 0; u0 <= i25; u0++) {
        ipiv->data[u0] = (int)ipiv_t->data[u0];
      }
    }

    emxFree_lapack_int(&ipiv_t);
  }
}

/*
 * File trailer for xgetrf.c
 *
 * [EOF]
 */
