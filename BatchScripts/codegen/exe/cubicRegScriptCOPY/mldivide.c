/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mldivide.c
 *
 * Code generation for function 'mldivide'
 *
 */

/* Include files */
#include "mldivide.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "lapacke.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void mldiv(const emxArray_real_T *A, emxArray_creal_T *B)
{
  emxArray_real_T *b_A;
  emxArray_int32_T *jpvt;
  emxArray_real_T *tau;
  emxArray_lapack_int *jpvt_t;
  emxArray_creal_T *b_B;
  int i;
  int u0;
  int na;
  int mn;
  int minmn;
  int ma;
  int minmana;
  lapack_int info_t;
  int k;
  int b_i;
  double wj_re;
  double wj_im;
  double tol;
  double br;
  emxInit_real_T(&b_A, 2);
  emxInit_int32_T(&jpvt, 2);
  emxInit_real_T(&tau, 1);
  emxInit_lapack_int(&jpvt_t, 1);
  emxInit_creal_T(&b_B, 1);
  if ((A->size[0] == 0) || (A->size[1] == 0) || (B->size[0] == 0)) {
    i = B->size[0];
    B->size[0] = A->size[1];
    emxEnsureCapacity_creal_T(B, i);
    mn = A->size[1];
    for (i = 0; i < mn; i++) {
      B->data[i].re = 0.0;
      B->data[i].im = 0.0;
    }
  } else if (A->size[0] == A->size[1]) {
    u0 = A->size[0];
    na = A->size[1];
    if (u0 < na) {
      na = u0;
    }

    u0 = B->size[0];
    if (u0 < na) {
      na = u0;
    }

    i = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, i);
    mn = A->size[0] * A->size[1];
    for (i = 0; i < mn; i++) {
      b_A->data[i] = A->data[i];
    }

    i = jpvt_t->size[0];
    if (na > 1) {
      ma = na;
    } else {
      ma = 1;
    }

    jpvt_t->size[0] = ma;
    emxEnsureCapacity_lapack_int(jpvt_t, i);
    info_t = LAPACKE_dgetrf_work(LAPACK_COL_MAJOR, (lapack_int)na, (lapack_int)
      na, &b_A->data[0], (lapack_int)A->size[0], &jpvt_t->data[0]);
    i = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = jpvt_t->size[0];
    emxEnsureCapacity_int32_T(jpvt, i);
    if ((int)info_t < 0) {
      mn = b_A->size[1];
      for (i = 0; i < mn; i++) {
        ma = b_A->size[0];
        for (u0 = 0; u0 < ma; u0++) {
          b_A->data[u0 + b_A->size[0] * i] = rtNaN;
        }
      }

      i = jpvt_t->size[0] - 1;
      for (k = 0; k <= i; k++) {
        jpvt->data[k] = k + 1;
      }
    } else {
      i = jpvt_t->size[0] - 1;
      for (k = 0; k <= i; k++) {
        jpvt->data[k] = (int)jpvt_t->data[k];
      }
    }

    ma = b_A->size[0];
    for (b_i = 0; b_i <= na - 2; b_i++) {
      i = jpvt->data[b_i];
      if (i != b_i + 1) {
        wj_re = B->data[b_i].re;
        wj_im = B->data[b_i].im;
        B->data[b_i] = B->data[i - 1];
        B->data[i - 1].re = wj_re;
        B->data[i - 1].im = wj_im;
      }
    }

    for (k = 0; k < na; k++) {
      mn = ma * k;
      if ((B->data[k].re != 0.0) || (B->data[k].im != 0.0)) {
        i = k + 2;
        for (b_i = i; b_i <= na; b_i++) {
          u0 = (b_i + mn) - 1;
          B->data[b_i - 1].re -= B->data[k].re * b_A->data[u0];
          B->data[b_i - 1].im -= B->data[k].im * b_A->data[u0];
        }
      }
    }

    for (k = na; k >= 1; k--) {
      mn = ma * (k - 1);
      if ((B->data[k - 1].re != 0.0) || (B->data[k - 1].im != 0.0)) {
        tol = B->data[k - 1].re;
        wj_im = B->data[k - 1].im;
        br = b_A->data[(k + mn) - 1];
        if (wj_im == 0.0) {
          wj_re = tol / br;
          tol = 0.0;
        } else if (tol == 0.0) {
          wj_re = 0.0;
          tol = wj_im / br;
        } else {
          wj_re = tol / br;
          tol = wj_im / br;
        }

        B->data[k - 1].re = wj_re;
        B->data[k - 1].im = tol;
        for (b_i = 0; b_i <= k - 2; b_i++) {
          i = b_i + mn;
          B->data[b_i].re -= B->data[k - 1].re * b_A->data[i];
          B->data[b_i].im -= B->data[k - 1].im * b_A->data[i];
        }
      }
    }
  } else {
    i = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, i);
    mn = A->size[0] * A->size[1];
    for (i = 0; i < mn; i++) {
      b_A->data[i] = A->data[i];
    }

    minmn = b_A->size[0];
    na = b_A->size[1];
    i = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = b_A->size[1];
    emxEnsureCapacity_int32_T(jpvt, i);
    mn = b_A->size[1];
    for (i = 0; i < mn; i++) {
      jpvt->data[i] = 0;
    }

    ma = b_A->size[0];
    u0 = b_A->size[0];
    minmana = b_A->size[1];
    if (u0 < minmana) {
      minmana = u0;
    }

    i = tau->size[0];
    tau->size[0] = minmana;
    emxEnsureCapacity_real_T(tau, i);
    i = jpvt_t->size[0];
    jpvt_t->size[0] = b_A->size[1];
    emxEnsureCapacity_lapack_int(jpvt_t, i);
    mn = b_A->size[1];
    for (i = 0; i < mn; i++) {
      jpvt_t->data[i] = (lapack_int)0;
    }

    info_t = LAPACKE_dgeqp3(LAPACK_COL_MAJOR, (lapack_int)b_A->size[0],
      (lapack_int)b_A->size[1], &b_A->data[0], (lapack_int)b_A->size[0],
      &jpvt_t->data[0], &tau->data[0]);
    if ((int)info_t != 0) {
      for (u0 = 0; u0 < na; u0++) {
        for (b_i = 0; b_i < minmn; b_i++) {
          b_A->data[u0 * ma + b_i] = rtNaN;
        }
      }

      if (minmn >= na) {
        minmn = na;
      }

      for (k = 0; k < minmn; k++) {
        tau->data[k] = rtNaN;
      }

      i = minmn + 1;
      for (k = i; k <= minmana; k++) {
        tau->data[k - 1] = 0.0;
      }

      for (k = 0; k < na; k++) {
        jpvt->data[k] = k + 1;
      }
    } else {
      for (k = 0; k < na; k++) {
        jpvt->data[k] = (int)jpvt_t->data[k];
      }
    }

    na = 0;
    if (b_A->size[0] < b_A->size[1]) {
      minmn = b_A->size[0];
      ma = b_A->size[1];
    } else {
      minmn = b_A->size[1];
      ma = b_A->size[0];
    }

    tol = 2.2204460492503131E-15 * (double)ma;
    if (1.4901161193847656E-8 < tol) {
      tol = 1.4901161193847656E-8;
    }

    tol *= fabs(b_A->data[0]);
    while ((na < minmn) && (!(fabs(b_A->data[na + b_A->size[0] * na]) <= tol)))
    {
      na++;
    }

    i = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity_creal_T(b_B, i);
    mn = B->size[0];
    for (i = 0; i < mn; i++) {
      b_B->data[i] = B->data[i];
    }

    i = B->size[0];
    B->size[0] = b_A->size[1];
    emxEnsureCapacity_creal_T(B, i);
    mn = b_A->size[1];
    for (i = 0; i < mn; i++) {
      B->data[i].re = 0.0;
      B->data[i].im = 0.0;
    }

    ma = b_A->size[0];
    u0 = b_A->size[0];
    mn = b_A->size[1];
    if (u0 < mn) {
      mn = u0;
    }

    for (u0 = 0; u0 < mn; u0++) {
      if (tau->data[u0] != 0.0) {
        wj_re = b_B->data[u0].re;
        wj_im = b_B->data[u0].im;
        i = u0 + 2;
        for (b_i = i; b_i <= ma; b_i++) {
          tol = b_A->data[(b_i + b_A->size[0] * u0) - 1];
          wj_re += tol * b_B->data[b_i - 1].re;
          wj_im += tol * b_B->data[b_i - 1].im;
        }

        wj_re *= tau->data[u0];
        wj_im *= tau->data[u0];
        if ((wj_re != 0.0) || (wj_im != 0.0)) {
          b_B->data[u0].re -= wj_re;
          b_B->data[u0].im -= wj_im;
          i = u0 + 2;
          for (b_i = i; b_i <= ma; b_i++) {
            tol = b_A->data[(b_i + b_A->size[0] * u0) - 1];
            b_B->data[b_i - 1].re -= tol * wj_re;
            b_B->data[b_i - 1].im -= tol * wj_im;
          }
        }
      }
    }

    for (b_i = 0; b_i < na; b_i++) {
      B->data[jpvt->data[b_i] - 1] = b_B->data[b_i];
    }

    for (u0 = na; u0 >= 1; u0--) {
      i = jpvt->data[u0 - 1];
      tol = B->data[i - 1].re;
      wj_im = B->data[i - 1].im;
      br = b_A->data[(u0 + b_A->size[0] * (u0 - 1)) - 1];
      if (wj_im == 0.0) {
        wj_re = tol / br;
        tol = 0.0;
      } else if (tol == 0.0) {
        wj_re = 0.0;
        tol = wj_im / br;
      } else {
        wj_re = tol / br;
        tol = wj_im / br;
      }

      B->data[i - 1].re = wj_re;
      B->data[i - 1].im = tol;
      for (b_i = 0; b_i <= u0 - 2; b_i++) {
        tol = b_A->data[b_i + b_A->size[0] * (u0 - 1)];
        B->data[jpvt->data[b_i] - 1].re -= B->data[jpvt->data[u0 - 1] - 1].re *
          tol;
        B->data[jpvt->data[b_i] - 1].im -= B->data[jpvt->data[u0 - 1] - 1].im *
          tol;
      }
    }
  }

  emxFree_creal_T(&b_B);
  emxFree_lapack_int(&jpvt_t);
  emxFree_real_T(&tau);
  emxFree_int32_T(&jpvt);
  emxFree_real_T(&b_A);
}

/* End of code generation (mldivide.c) */
