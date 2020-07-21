/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eig.c
 *
 * Code generation for function 'eig'
 *
 */

/* Include files */
#include "eig.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "ishermitian.h"
#include "lapacke.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void eig(const emxArray_real_T *A, emxArray_creal_T *V, emxArray_creal_T *D)
{
  int n;
  int nx;
  int i;
  boolean_T p;
  int istart;
  unsigned int unnamed_idx_0;
  signed char D_size_idx_0;
  emxArray_creal_T *b_A;
  unsigned int unnamed_idx_1;
  signed char D_size_idx_1;
  emxArray_real_T *b_V;
  emxArray_real_T *c_A;
  emxArray_creal_T *W;
  emxArray_real_T *tau;
  lapack_int info_t;
  creal_T vl;
  int j;
  emxArray_real_T *wr;
  emxArray_real_T *wi;
  n = A->size[0];
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    i = V->size[0] * V->size[1];
    V->size[0] = A->size[0];
    V->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(V, i);
    nx = A->size[0] * A->size[1];
    for (i = 0; i < nx; i++) {
      V->data[i].re = A->data[i];
      V->data[i].im = 0.0;
    }

    i = D->size[0] * D->size[1];
    D->size[0] = A->size[0];
    D->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(D, i);
    nx = A->size[0] * A->size[1];
    for (i = 0; i < nx; i++) {
      D->data[i].re = A->data[i];
      D->data[i].im = 0.0;
    }
  } else {
    nx = A->size[0] * A->size[1];
    p = true;
    for (istart = 0; istart < nx; istart++) {
      if ((!p) || (rtIsInf(A->data[istart]) || rtIsNaN(A->data[istart]))) {
        p = false;
      }
    }

    if (!p) {
      if ((A->size[0] == 1) && (A->size[1] == 1)) {
        D_size_idx_0 = (signed char)A->size[0];
        D_size_idx_1 = (signed char)A->size[1];
        i = V->size[0] * V->size[1];
        V->size[0] = 1;
        V->size[1] = 1;
        emxEnsureCapacity_creal_T(V, i);
        for (i = 0; i < 1; i++) {
          V->data[0].re = rtNaN;
          V->data[0].im = 0.0;
        }

        i = D->size[0] * D->size[1];
        D->size[0] = D_size_idx_0;
        D->size[1] = D_size_idx_1;
        emxEnsureCapacity_creal_T(D, i);
        nx = D_size_idx_0 * D_size_idx_1;
        for (i = 0; i < nx; i++) {
          D->data[i].re = rtNaN;
          D->data[i].im = 0.0;
        }
      } else {
        unnamed_idx_0 = (unsigned int)A->size[0];
        unnamed_idx_1 = (unsigned int)A->size[1];
        i = V->size[0] * V->size[1];
        V->size[0] = (int)unnamed_idx_0;
        V->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_creal_T(V, i);
        nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
        for (i = 0; i < nx; i++) {
          V->data[i].re = rtNaN;
          V->data[i].im = 0.0;
        }

        unnamed_idx_0 = (unsigned int)A->size[0];
        unnamed_idx_1 = (unsigned int)A->size[1];
        i = D->size[0] * D->size[1];
        D->size[0] = (int)unnamed_idx_0;
        D->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_creal_T(D, i);
        nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
        for (i = 0; i < nx; i++) {
          D->data[i].re = 0.0;
          D->data[i].im = 0.0;
        }

        i = (int)unnamed_idx_0;
        for (istart = 0; istart < i; istart++) {
          D->data[istart + D->size[0] * istart].re = rtNaN;
          D->data[istart + D->size[0] * istart].im = 0.0;
        }
      }
    } else if ((A->size[0] == 1) && (A->size[1] == 1)) {
      i = V->size[0] * V->size[1];
      V->size[0] = 1;
      V->size[1] = 1;
      emxEnsureCapacity_creal_T(V, i);
      V->data[0].re = 1.0;
      V->data[0].im = 0.0;
      i = D->size[0] * D->size[1];
      D->size[0] = A->size[0];
      D->size[1] = A->size[1];
      emxEnsureCapacity_creal_T(D, i);
      nx = A->size[0] * A->size[1];
      for (i = 0; i < nx; i++) {
        D->data[i].re = A->data[i];
        D->data[i].im = 0.0;
      }
    } else if (ishermitian(A)) {
      nx = A->size[0] * A->size[1];
      p = true;
      for (istart = 0; istart < nx; istart++) {
        if ((!p) || (rtIsInf(A->data[istart]) || rtIsNaN(A->data[istart]))) {
          p = false;
        }
      }

      emxInit_real_T(&b_V, 2);
      emxInit_real_T(&c_A, 2);
      if (!p) {
        unnamed_idx_0 = (unsigned int)A->size[0];
        unnamed_idx_1 = (unsigned int)A->size[1];
        i = b_V->size[0] * b_V->size[1];
        b_V->size[0] = (int)unnamed_idx_0;
        b_V->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_real_T(b_V, i);
        nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
        for (i = 0; i < nx; i++) {
          b_V->data[i] = rtNaN;
        }

        nx = b_V->size[0];
        if (1 < b_V->size[0]) {
          istart = 2;
          if (b_V->size[0] - 2 < b_V->size[1] - 1) {
            n = b_V->size[0] - 1;
          } else {
            n = b_V->size[1];
          }

          for (j = 0; j < n; j++) {
            for (i = istart; i <= nx; i++) {
              b_V->data[(i + b_V->size[0] * j) - 1] = 0.0;
            }

            istart++;
          }
        }

        unnamed_idx_0 = (unsigned int)A->size[0];
        unnamed_idx_1 = (unsigned int)A->size[1];
        i = c_A->size[0] * c_A->size[1];
        c_A->size[0] = (int)unnamed_idx_0;
        c_A->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_real_T(c_A, i);
        nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
        for (i = 0; i < nx; i++) {
          c_A->data[i] = rtNaN;
        }
      } else {
        i = c_A->size[0] * c_A->size[1];
        c_A->size[0] = A->size[0];
        c_A->size[1] = A->size[1];
        emxEnsureCapacity_real_T(c_A, i);
        nx = A->size[0] * A->size[1];
        for (i = 0; i < nx; i++) {
          c_A->data[i] = A->data[i];
        }

        emxInit_real_T(&tau, 1);
        i = tau->size[0];
        tau->size[0] = c_A->size[0] - 1;
        emxEnsureCapacity_real_T(tau, i);
        if (c_A->size[0] > 1) {
          info_t = LAPACKE_dgehrd(LAPACK_COL_MAJOR, (lapack_int)c_A->size[0],
            (lapack_int)1, (lapack_int)c_A->size[0], &c_A->data[0], (lapack_int)
            c_A->size[0], &tau->data[0]);
          if ((int)info_t != 0) {
            nx = c_A->size[1];
            for (i = 0; i < nx; i++) {
              istart = c_A->size[0];
              for (j = 0; j < istart; j++) {
                c_A->data[j + c_A->size[0] * i] = rtNaN;
              }
            }

            nx = tau->size[0];
            i = tau->size[0];
            tau->size[0] = nx;
            emxEnsureCapacity_real_T(tau, i);
            for (i = 0; i < nx; i++) {
              tau->data[i] = rtNaN;
            }
          }
        }

        i = b_V->size[0] * b_V->size[1];
        b_V->size[0] = c_A->size[0];
        b_V->size[1] = c_A->size[1];
        emxEnsureCapacity_real_T(b_V, i);
        nx = c_A->size[0] * c_A->size[1];
        for (i = 0; i < nx; i++) {
          b_V->data[i] = c_A->data[i];
        }

        info_t = LAPACKE_dorghr(LAPACK_COL_MAJOR, (lapack_int)A->size[0],
          (lapack_int)1, (lapack_int)A->size[0], &b_V->data[0], (lapack_int)
          A->size[0], &tau->data[0]);
        emxFree_real_T(&tau);
        if ((int)info_t != 0) {
          nx = b_V->size[1];
          for (i = 0; i < nx; i++) {
            istart = b_V->size[0];
            for (j = 0; j < istart; j++) {
              b_V->data[j + b_V->size[0] * i] = rtNaN;
            }
          }
        }

        emxInit_real_T(&wr, 2);
        emxInit_real_T(&wi, 2);
        info_t = (lapack_int)c_A->size[0];
        i = wr->size[0] * wr->size[1];
        wr->size[0] = 1;
        wr->size[1] = c_A->size[0];
        emxEnsureCapacity_real_T(wr, i);
        i = wi->size[0] * wi->size[1];
        wi->size[0] = 1;
        wi->size[1] = c_A->size[0];
        emxEnsureCapacity_real_T(wi, i);
        info_t = LAPACKE_dhseqr(LAPACK_COL_MAJOR, 'S', 'V', info_t, (lapack_int)
          1, (lapack_int)c_A->size[0], &c_A->data[0], info_t, &wr->data[0],
          &wi->data[0], &b_V->data[0], (lapack_int)c_A->size[0]);
        emxFree_real_T(&wi);
        emxFree_real_T(&wr);
        if ((int)info_t < 0) {
          nx = c_A->size[1];
          for (i = 0; i < nx; i++) {
            istart = c_A->size[0];
            for (j = 0; j < istart; j++) {
              c_A->data[j + c_A->size[0] * i] = rtNaN;
            }
          }

          nx = b_V->size[1];
          for (i = 0; i < nx; i++) {
            istart = b_V->size[0];
            for (j = 0; j < istart; j++) {
              b_V->data[j + b_V->size[0] * i] = rtNaN;
            }
          }
        }
      }

      i = V->size[0] * V->size[1];
      V->size[0] = b_V->size[0];
      V->size[1] = b_V->size[1];
      emxEnsureCapacity_creal_T(V, i);
      nx = b_V->size[0] * b_V->size[1];
      for (i = 0; i < nx; i++) {
        V->data[i].re = b_V->data[i];
        V->data[i].im = 0.0;
      }

      emxFree_real_T(&b_V);
      n = c_A->size[0];
      for (j = 2; j <= n; j++) {
        c_A->data[(j + c_A->size[0] * (j - 2)) - 1] = 0.0;
        for (i = 0; i <= j - 2; i++) {
          c_A->data[i + c_A->size[0] * (j - 1)] = 0.0;
        }
      }

      i = D->size[0] * D->size[1];
      D->size[0] = c_A->size[0];
      D->size[1] = c_A->size[1];
      emxEnsureCapacity_creal_T(D, i);
      nx = c_A->size[0] * c_A->size[1];
      for (i = 0; i < nx; i++) {
        D->data[i].re = c_A->data[i];
        D->data[i].im = 0.0;
      }

      emxFree_real_T(&c_A);
    } else {
      emxInit_creal_T(&b_A, 2);
      i = b_A->size[0] * b_A->size[1];
      b_A->size[0] = A->size[0];
      b_A->size[1] = A->size[1];
      emxEnsureCapacity_creal_T(b_A, i);
      nx = A->size[0] * A->size[1];
      for (i = 0; i < nx; i++) {
        b_A->data[i].re = A->data[i];
        b_A->data[i].im = 0.0;
      }

      emxInit_creal_T(&W, 1);
      i = V->size[0] * V->size[1];
      V->size[0] = A->size[1];
      V->size[1] = A->size[1];
      emxEnsureCapacity_creal_T(V, i);
      i = W->size[0];
      W->size[0] = A->size[1];
      emxEnsureCapacity_creal_T(W, i);
      info_t = LAPACKE_zgeev(LAPACK_COL_MAJOR, 'N', 'V', (lapack_int)A->size[1],
        (lapack_complex_double *)&b_A->data[0], (lapack_int)A->size[0],
        (lapack_complex_double *)&W->data[0], (lapack_complex_double *)&vl,
        (lapack_int)1, (lapack_complex_double *)&V->data[0], (lapack_int)A->
        size[1]);
      emxFree_creal_T(&b_A);
      if ((int)info_t < 0) {
        nx = W->size[0];
        i = W->size[0];
        W->size[0] = nx;
        emxEnsureCapacity_creal_T(W, i);
        for (i = 0; i < nx; i++) {
          W->data[i].re = rtNaN;
          W->data[i].im = 0.0;
        }

        nx = V->size[1];
        for (i = 0; i < nx; i++) {
          istart = V->size[0];
          for (j = 0; j < istart; j++) {
            V->data[j + V->size[0] * i].re = rtNaN;
            V->data[j + V->size[0] * i].im = 0.0;
          }
        }
      }

      i = D->size[0] * D->size[1];
      D->size[0] = A->size[0];
      D->size[1] = A->size[0];
      emxEnsureCapacity_creal_T(D, i);
      nx = A->size[0] * A->size[0];
      for (i = 0; i < nx; i++) {
        D->data[i].re = 0.0;
        D->data[i].im = 0.0;
      }

      for (istart = 0; istart < n; istart++) {
        D->data[istart + D->size[0] * istart] = W->data[istart];
      }

      emxFree_creal_T(&W);
    }
  }
}

/* End of code generation (eig.c) */
