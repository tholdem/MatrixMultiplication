/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mldivide.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "mldivide.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "xgetrf.h"
#include "xgeqp3.h"
#include "mkl_cblas.h"
#include "mkl_lapacke.h"

/* Type Definitions */

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *B
 * Return Type  : void
 */
void mldivide(const emxArray_real_T *A, emxArray_real_T *B)
{
  emxArray_real_T *b_A;
  emxArray_real_T *tau;
  emxArray_int32_T *jpvt;
  emxArray_real_T *b_B;
  unsigned int unnamed_idx_0;
  int maxmn;
  int minmn;
  int rankR;
  CBLAS_SIDE t;
  double tol;
  CBLAS_UPLO b_t;
  CBLAS_TRANSPOSE c_t;
  CBLAS_DIAG d_t;
  lapack_int nrc_t;
  lapack_int info_t;
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&tau, 1);
  emxInit_int32_T(&jpvt, 2);
  emxInit_real_T(&b_B, 1);
  if ((A->size[0] == 0) || (A->size[1] == 0) || (B->size[0] == 0)) {
    unnamed_idx_0 = (unsigned int)A->size[1];
    maxmn = B->size[0];
    B->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity_real_T(B, maxmn);
    minmn = (int)unnamed_idx_0;
    for (maxmn = 0; maxmn < minmn; maxmn++) {
      B->data[maxmn] = 0.0;
    }
  } else if (A->size[0] == A->size[1]) {
    maxmn = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, maxmn);
    minmn = A->size[0] * A->size[1];
    for (maxmn = 0; maxmn < minmn; maxmn++) {
      b_A->data[maxmn] = A->data[maxmn];
    }

    xgetrf(A->size[1], A->size[1], b_A, A->size[1], jpvt, &minmn);
    maxmn = A->size[1];
    for (minmn = 0; minmn <= maxmn - 2; minmn++) {
      if (jpvt->data[minmn] != minmn + 1) {
        tol = B->data[minmn];
        B->data[minmn] = B->data[jpvt->data[minmn] - 1];
        B->data[jpvt->data[minmn] - 1] = tol;
      }
    }

    t = CblasLeft;
    b_t = CblasLower;
    c_t = CblasNoTrans;
    d_t = CblasUnit;
    cblas_dtrsm(CblasColMajor, t, b_t, c_t, d_t, (MKL_INT)A->size[1], (MKL_INT)1,
                1.0, &b_A->data[0], (MKL_INT)A->size[1], &B->data[0], (MKL_INT)
                A->size[1]);
    t = CblasLeft;
    b_t = CblasUpper;
    c_t = CblasNoTrans;
    d_t = CblasNonUnit;
    cblas_dtrsm(CblasColMajor, t, b_t, c_t, d_t, (MKL_INT)A->size[1], (MKL_INT)1,
                1.0, &b_A->data[0], (MKL_INT)A->size[1], &B->data[0], (MKL_INT)
                A->size[1]);
  } else {
    maxmn = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, maxmn);
    minmn = A->size[0] * A->size[1];
    for (maxmn = 0; maxmn < minmn; maxmn++) {
      b_A->data[maxmn] = A->data[maxmn];
    }

    xgeqp3(b_A, tau, jpvt);
    rankR = 0;
    if (b_A->size[0] < b_A->size[1]) {
      minmn = b_A->size[0];
      maxmn = b_A->size[1];
    } else {
      minmn = b_A->size[1];
      maxmn = b_A->size[0];
    }

    if (minmn > 0) {
      tol = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (double)maxmn) *
        fabs(b_A->data[0]);
      while ((rankR < minmn) && (!(fabs(b_A->data[rankR + b_A->size[0] * rankR])
               <= tol))) {
        rankR++;
      }
    }

    maxmn = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity_real_T(b_B, maxmn);
    minmn = B->size[0];
    for (maxmn = 0; maxmn < minmn; maxmn++) {
      b_B->data[maxmn] = B->data[maxmn];
    }

    minmn = b_A->size[1];
    maxmn = B->size[0];
    B->size[0] = minmn;
    emxEnsureCapacity_real_T(B, maxmn);
    for (maxmn = 0; maxmn < minmn; maxmn++) {
      B->data[maxmn] = 0.0;
    }

    minmn = b_A->size[0];
    maxmn = b_A->size[1];
    if (minmn < maxmn) {
      maxmn = minmn;
    }

    if ((b_A->size[0] != 0) && (b_A->size[1] != 0)) {
      nrc_t = (lapack_int)b_B->size[0];
      info_t = LAPACKE_dormqr(LAPACK_COL_MAJOR, 'L', 'T', nrc_t, (lapack_int)1,
        (lapack_int)maxmn, &b_A->data[0], (lapack_int)b_A->size[0], &tau->data[0],
        &b_B->data[0], nrc_t);
      if ((int)info_t != 0) {
        minmn = b_B->size[0];
        maxmn = b_B->size[0];
        b_B->size[0] = minmn;
        emxEnsureCapacity_real_T(b_B, maxmn);
        for (maxmn = 0; maxmn < minmn; maxmn++) {
          b_B->data[maxmn] = rtNaN;
        }
      }
    }

    for (minmn = 0; minmn < rankR; minmn++) {
      B->data[jpvt->data[minmn] - 1] = b_B->data[minmn];
    }

    for (maxmn = rankR; maxmn >= 1; maxmn--) {
      B->data[jpvt->data[maxmn - 1] - 1] /= b_A->data[(maxmn + b_A->size[0] *
        (maxmn - 1)) - 1];
      for (minmn = 0; minmn <= maxmn - 2; minmn++) {
        B->data[jpvt->data[minmn] - 1] -= B->data[jpvt->data[maxmn - 1] - 1] *
          b_A->data[minmn + b_A->size[0] * (maxmn - 1)];
      }
    }
  }

  emxFree_real_T(&b_B);
  emxFree_int32_T(&jpvt);
  emxFree_real_T(&tau);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
