/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eig.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "eig.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "schur.h"
#include "anyNonFinite.h"
#include "xhseqr.h"
#include "xgehrd.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A_data[]
 *                const int A_size[2]
 *                creal_T V_data[]
 *                int V_size[1]
 * Return Type  : void
 */
void b_eig(const creal_T A_data[], const int A_size[2], creal_T V_data[], int
           V_size[1])
{
  boolean_T p;
  int n;
  int i;
  boolean_T exitg2;
  int b_A_size[2];
  signed char unnamed_idx_0;
  creal_T b_A_data[4];
  int exitg1;
  lapack_int info_t;
  creal_T vl;
  creal_T vr;
  if (b_anyNonFinite(A_data, A_size)) {
    if ((A_size[0] == 1) && (A_size[1] == 1)) {
      V_size[0] = 1;
      V_data[0].re = rtNaN;
      V_data[0].im = 0.0;
    } else {
      V_size[0] = A_size[0];
      n = A_size[0];
      for (i = 0; i < n; i++) {
        V_data[i].re = rtNaN;
        V_data[i].im = 0.0;
      }
    }
  } else if ((A_size[0] == 1) && (A_size[1] == 1)) {
    V_size[0] = 1;
    V_data[0] = A_data[0];
  } else {
    p = (A_size[0] == A_size[1]);
    if (p) {
      n = 0;
      exitg2 = false;
      while ((!exitg2) && (n <= A_size[1] - 1)) {
        i = 0;
        do {
          exitg1 = 0;
          if (i <= n) {
            if ((!(A_data[i + A_size[0] * n].re == A_data[n + A_size[0] * i].re))
                || (!(A_data[i + A_size[0] * n].im == -A_data[n + A_size[0] * i]
                      .im))) {
              p = false;
              exitg1 = 1;
            } else {
              i++;
            }
          } else {
            n++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }

    if (p) {
      if (b_anyNonFinite(A_data, A_size)) {
        unnamed_idx_0 = (signed char)A_size[0];
        b_A_size[0] = unnamed_idx_0;
        n = unnamed_idx_0 * (signed char)A_size[1];
        for (i = 0; i < n; i++) {
          b_A_data[i].re = rtNaN;
          b_A_data[i].im = 0.0;
        }

        if (1 < unnamed_idx_0) {
          for (i = 2; i < 3; i++) {
            b_A_data[1].re = 0.0;
            b_A_data[1].im = 0.0;
          }
        }
      } else {
        b_A_size[0] = A_size[0];
        b_A_size[1] = A_size[1];
        n = A_size[0] * A_size[1];
        if (0 <= n - 1) {
          memcpy(&b_A_data[0], &A_data[0], (unsigned int)(n * (int)sizeof
                  (creal_T)));
        }

        b_xgehrd(b_A_data, b_A_size);
        xhseqr(b_A_data, b_A_size);
      }

      n = b_A_size[0];
      V_size[0] = b_A_size[0];
      for (i = 0; i < n; i++) {
        V_data[i] = b_A_data[i + b_A_size[0] * i];
      }
    } else {
      n = A_size[0] * A_size[1];
      if (0 <= n - 1) {
        memcpy(&b_A_data[0], &A_data[0], (unsigned int)(n * (int)sizeof(creal_T)));
      }

      V_size[0] = A_size[1];
      info_t = LAPACKE_zgeev(LAPACK_COL_MAJOR, 'N', 'N', (lapack_int)A_size[1],
        (lapack_complex_double *)&b_A_data[0], (lapack_int)A_size[0],
        (lapack_complex_double *)&V_data[0], (lapack_complex_double *)&vl,
        (lapack_int)1, (lapack_complex_double *)&vr, (lapack_int)1);
      if ((int)info_t < 0) {
        n = A_size[1];
        V_size[0] = A_size[1];
        for (i = 0; i < n; i++) {
          V_data[i].re = rtNaN;
          V_data[i].im = 0.0;
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_creal_T *V
 *                emxArray_creal_T *D
 * Return Type  : void
 */
void eig(const emxArray_real_T *A, emxArray_creal_T *V, emxArray_creal_T *D)
{
  int n;
  int i19;
  boolean_T p;
  unsigned int unnamed_idx_0;
  signed char D_size_idx_0;
  unsigned int unnamed_idx_1;
  signed char D_size_idx_1;
  int j;
  boolean_T exitg2;
  emxArray_creal_T *b_A;
  double D_re;
  int i;
  int exitg1;
  emxArray_creal_T *W;
  lapack_int info_t;
  creal_T vl;
  int i20;
  n = A->size[0];
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    i19 = V->size[0] * V->size[1];
    V->size[0] = A->size[0];
    V->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(V, i19);
    j = A->size[0] * A->size[1];
    for (i19 = 0; i19 < j; i19++) {
      V->data[i19].re = A->data[i19];
      V->data[i19].im = 0.0;
    }

    i19 = D->size[0] * D->size[1];
    D->size[0] = A->size[0];
    D->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(D, i19);
    j = A->size[0] * A->size[1];
    for (i19 = 0; i19 < j; i19++) {
      D->data[i19].re = A->data[i19];
      D->data[i19].im = 0.0;
    }
  } else if (anyNonFinite(A)) {
    if ((A->size[0] == 1) && (A->size[1] == 1)) {
      D_size_idx_0 = (signed char)A->size[0];
      D_size_idx_1 = (signed char)A->size[1];
      i19 = V->size[0] * V->size[1];
      V->size[0] = 1;
      V->size[1] = 1;
      emxEnsureCapacity_creal_T(V, i19);
      for (i19 = 0; i19 < 1; i19++) {
        V->data[0].re = rtNaN;
        V->data[0].im = 0.0;
      }

      i19 = D->size[0] * D->size[1];
      D->size[0] = D_size_idx_0;
      D->size[1] = D_size_idx_1;
      emxEnsureCapacity_creal_T(D, i19);
      j = D_size_idx_0 * D_size_idx_1;
      for (i19 = 0; i19 < j; i19++) {
        D->data[i19].re = rtNaN;
        D->data[i19].im = 0.0;
      }
    } else {
      unnamed_idx_0 = (unsigned int)A->size[0];
      unnamed_idx_1 = (unsigned int)A->size[1];
      i19 = V->size[0] * V->size[1];
      V->size[0] = (int)unnamed_idx_0;
      V->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity_creal_T(V, i19);
      j = (int)unnamed_idx_0 * (int)unnamed_idx_1;
      for (i19 = 0; i19 < j; i19++) {
        V->data[i19].re = rtNaN;
        V->data[i19].im = 0.0;
      }

      unnamed_idx_0 = (unsigned int)A->size[0];
      unnamed_idx_1 = (unsigned int)A->size[1];
      i19 = D->size[0] * D->size[1];
      D->size[0] = (int)unnamed_idx_0;
      D->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity_creal_T(D, i19);
      j = (int)unnamed_idx_0 * (int)unnamed_idx_1;
      for (i19 = 0; i19 < j; i19++) {
        D->data[i19].re = 0.0;
        D->data[i19].im = 0.0;
      }

      i19 = (int)unnamed_idx_0;
      for (j = 0; j < i19; j++) {
        D->data[j + D->size[0] * j].re = rtNaN;
        D->data[j + D->size[0] * j].im = 0.0;
      }
    }
  } else if ((A->size[0] == 1) && (A->size[1] == 1)) {
    i19 = V->size[0] * V->size[1];
    V->size[0] = 1;
    V->size[1] = 1;
    emxEnsureCapacity_creal_T(V, i19);
    V->data[0].re = 1.0;
    V->data[0].im = 0.0;
    i19 = D->size[0] * D->size[1];
    D->size[0] = A->size[0];
    D->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(D, i19);
    j = A->size[0] * A->size[1];
    for (i19 = 0; i19 < j; i19++) {
      D->data[i19].re = A->data[i19];
      D->data[i19].im = 0.0;
    }
  } else {
    p = (A->size[0] == A->size[1]);
    if (p) {
      j = 0;
      exitg2 = false;
      while ((!exitg2) && (j <= A->size[1] - 1)) {
        i = 0;
        do {
          exitg1 = 0;
          if (i <= j) {
            if (!(A->data[i + A->size[0] * j] == A->data[j + A->size[0] * i])) {
              p = false;
              exitg1 = 1;
            } else {
              i++;
            }
          } else {
            j++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }

    if (p) {
      schur(A, V, D);
      n = D->size[0];
      D_re = D->data[0].re;
      D->data[0].re = D_re;
      D->data[0].im = 0.0;
      for (j = 2; j <= n; j++) {
        D_re = D->data[(j + D->size[0] * (j - 1)) - 1].re;
        D->data[(j + D->size[0] * (j - 1)) - 1].re = D_re;
        D->data[(j + D->size[0] * (j - 1)) - 1].im = 0.0;
        D->data[(j + D->size[0] * (j - 2)) - 1].re = 0.0;
        D->data[(j + D->size[0] * (j - 2)) - 1].im = 0.0;
        for (i = 0; i <= j - 2; i++) {
          D->data[i + D->size[0] * (j - 1)].re = 0.0;
          D->data[i + D->size[0] * (j - 1)].im = 0.0;
        }
      }
    } else {
      emxInit_creal_T(&b_A, 2);
      i19 = b_A->size[0] * b_A->size[1];
      b_A->size[0] = A->size[0];
      b_A->size[1] = A->size[1];
      emxEnsureCapacity_creal_T(b_A, i19);
      j = A->size[0] * A->size[1];
      for (i19 = 0; i19 < j; i19++) {
        b_A->data[i19].re = A->data[i19];
        b_A->data[i19].im = 0.0;
      }

      emxInit_creal_T(&W, 1);
      i19 = V->size[0] * V->size[1];
      V->size[0] = A->size[1];
      V->size[1] = A->size[1];
      emxEnsureCapacity_creal_T(V, i19);
      i19 = W->size[0];
      W->size[0] = A->size[1];
      emxEnsureCapacity_creal_T(W, i19);
      info_t = LAPACKE_zgeev(LAPACK_COL_MAJOR, 'N', 'V', (lapack_int)A->size[1],
        (lapack_complex_double *)&b_A->data[0], (lapack_int)A->size[0],
        (lapack_complex_double *)&W->data[0], (lapack_complex_double *)&vl,
        (lapack_int)1, (lapack_complex_double *)&V->data[0], (lapack_int)A->
        size[1]);
      emxFree_creal_T(&b_A);
      if ((int)info_t < 0) {
        j = W->size[0];
        i19 = W->size[0];
        W->size[0] = j;
        emxEnsureCapacity_creal_T(W, i19);
        for (i19 = 0; i19 < j; i19++) {
          W->data[i19].re = rtNaN;
          W->data[i19].im = 0.0;
        }

        i19 = V->size[0] * V->size[1];
        emxEnsureCapacity_creal_T(V, i19);
        j = V->size[1];
        for (i19 = 0; i19 < j; i19++) {
          i = V->size[0];
          for (i20 = 0; i20 < i; i20++) {
            V->data[i20 + V->size[0] * i19].re = rtNaN;
            V->data[i20 + V->size[0] * i19].im = 0.0;
          }
        }
      }

      i19 = D->size[0] * D->size[1];
      D->size[0] = A->size[0];
      D->size[1] = A->size[0];
      emxEnsureCapacity_creal_T(D, i19);
      j = A->size[0] * A->size[0];
      for (i19 = 0; i19 < j; i19++) {
        D->data[i19].re = 0.0;
        D->data[i19].im = 0.0;
      }

      for (j = 0; j < n; j++) {
        D->data[j + D->size[0] * j] = W->data[j];
      }

      emxFree_creal_T(&W);
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
