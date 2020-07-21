/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: schur.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "schur.h"
#include "cubicRegScript_emxutil.h"
#include "xdlanv2.h"
#include "xgehrd.h"
#include "anyNonFinite.h"
#include "cubicRegScript_rtwutil.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_creal_T *V
 *                emxArray_creal_T *T
 * Return Type  : void
 */
void schur(const emxArray_real_T *A, emxArray_creal_T *V, emxArray_creal_T *T)
{
  emxArray_real_T *b_A;
  unsigned int unnamed_idx_0;
  int m;
  unsigned int unnamed_idx_1;
  int ldz;
  emxArray_real_T *Vr;
  emxArray_real_T *tau;
  int jend;
  int j;
  int i;
  lapack_int info_t;
  lapack_int n_t;
  emxArray_real_T *wr;
  emxArray_real_T *wi;
  int n;
  double r;
  double b;
  double c;
  double d;
  double s;
  double rt1i;
  double t1_re;
  double t1_im;
  double mu1_im;
  double mu1_re;
  if (anyNonFinite(A)) {
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)A->size[1];
    m = V->size[0] * V->size[1];
    V->size[0] = (int)unnamed_idx_0;
    V->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_creal_T(V, m);
    ldz = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (m = 0; m < ldz; m++) {
      V->data[m].re = rtNaN;
      V->data[m].im = 0.0;
    }

    m = V->size[0];
    if ((V->size[0] == 0) || (V->size[1] == 0) || (2 >= V->size[0])) {
    } else {
      ldz = 3;
      if (V->size[0] - 3 < V->size[1] - 1) {
        jend = V->size[0] - 2;
      } else {
        jend = V->size[1];
      }

      for (j = 0; j < jend; j++) {
        for (i = ldz; i <= m; i++) {
          V->data[(i + V->size[0] * j) - 1].re = 0.0;
          V->data[(i + V->size[0] * j) - 1].im = 0.0;
        }

        ldz++;
      }
    }

    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)A->size[1];
    m = T->size[0] * T->size[1];
    T->size[0] = (int)unnamed_idx_0;
    T->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_creal_T(T, m);
    ldz = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (m = 0; m < ldz; m++) {
      T->data[m].re = rtNaN;
      T->data[m].im = 0.0;
    }
  } else {
    emxInit_real_T(&b_A, 2);
    m = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, m);
    ldz = A->size[0] * A->size[1];
    for (m = 0; m < ldz; m++) {
      b_A->data[m] = A->data[m];
    }

    emxInit_real_T(&Vr, 2);
    emxInit_real_T(&tau, 1);
    xgehrd(b_A, tau);
    m = Vr->size[0] * Vr->size[1];
    Vr->size[0] = b_A->size[0];
    Vr->size[1] = b_A->size[1];
    emxEnsureCapacity_real_T(Vr, m);
    ldz = b_A->size[0] * b_A->size[1];
    for (m = 0; m < ldz; m++) {
      Vr->data[m] = b_A->data[m];
    }

    if ((Vr->size[0] != 0) && (Vr->size[1] != 0)) {
      info_t = LAPACKE_dorghr(LAPACK_COL_MAJOR, (lapack_int)A->size[0],
        (lapack_int)1, (lapack_int)A->size[0], &Vr->data[0], (lapack_int)A->
        size[0], &tau->data[0]);
      if ((int)info_t != 0) {
        m = Vr->size[0] * Vr->size[1];
        emxEnsureCapacity_real_T(Vr, m);
        ldz = Vr->size[1];
        for (m = 0; m < ldz; m++) {
          jend = Vr->size[0];
          for (n = 0; n < jend; n++) {
            Vr->data[n + Vr->size[0] * m] = rtNaN;
          }
        }
      }
    }

    emxFree_real_T(&tau);
    ldz = b_A->size[0];
    if (1 > ldz) {
      ldz = 1;
    }

    n_t = (lapack_int)b_A->size[0];
    if ((b_A->size[0] != 0) && (b_A->size[1] != 0)) {
      emxInit_real_T(&wr, 2);
      emxInit_real_T(&wi, 2);
      m = wr->size[0] * wr->size[1];
      wr->size[0] = 1;
      wr->size[1] = b_A->size[0];
      emxEnsureCapacity_real_T(wr, m);
      m = wi->size[0] * wi->size[1];
      wi->size[0] = 1;
      wi->size[1] = b_A->size[0];
      emxEnsureCapacity_real_T(wi, m);
      info_t = LAPACKE_dhseqr(LAPACK_COL_MAJOR, 'S', 'V', n_t, (lapack_int)1,
        (lapack_int)b_A->size[0], &b_A->data[0], n_t, &wr->data[0], &wi->data[0],
        &Vr->data[0], (lapack_int)ldz);
      emxFree_real_T(&wi);
      emxFree_real_T(&wr);
      if ((int)info_t < 0) {
        m = b_A->size[0] * b_A->size[1];
        emxEnsureCapacity_real_T(b_A, m);
        ldz = b_A->size[1];
        for (m = 0; m < ldz; m++) {
          jend = b_A->size[0];
          for (n = 0; n < jend; n++) {
            b_A->data[n + b_A->size[0] * m] = rtNaN;
          }
        }

        m = Vr->size[0] * Vr->size[1];
        emxEnsureCapacity_real_T(Vr, m);
        ldz = Vr->size[1];
        for (m = 0; m < ldz; m++) {
          jend = Vr->size[0];
          for (n = 0; n < jend; n++) {
            Vr->data[n + Vr->size[0] * m] = rtNaN;
          }
        }
      }
    }

    m = T->size[0] * T->size[1];
    T->size[0] = b_A->size[0];
    T->size[1] = b_A->size[1];
    emxEnsureCapacity_creal_T(T, m);
    ldz = b_A->size[0] * b_A->size[1];
    for (m = 0; m < ldz; m++) {
      T->data[m].re = b_A->data[m];
      T->data[m].im = 0.0;
    }

    m = V->size[0] * V->size[1];
    V->size[0] = Vr->size[0];
    V->size[1] = Vr->size[1];
    emxEnsureCapacity_creal_T(V, m);
    ldz = Vr->size[0] * Vr->size[1];
    for (m = 0; m < ldz; m++) {
      V->data[m].re = Vr->data[m];
      V->data[m].im = 0.0;
    }

    ldz = b_A->size[0];
    jend = b_A->size[1];
    if (ldz < jend) {
      jend = ldz;
    }

    ldz = Vr->size[0];
    n = Vr->size[1];
    if (ldz < n) {
      n = ldz;
    }

    emxFree_real_T(&Vr);
    if (jend < n) {
      n = jend;
    }

    if (n != 0) {
      for (m = n - 1; m + 1 >= 2; m--) {
        if (b_A->data[m + b_A->size[0] * (m - 1)] != 0.0) {
          r = b_A->data[(m + b_A->size[0] * (m - 1)) - 1];
          b = b_A->data[(m + b_A->size[0] * m) - 1];
          c = b_A->data[m + b_A->size[0] * (m - 1)];
          d = b_A->data[m + b_A->size[0] * m];
          xdlanv2(&r, &b, &c, &d, &s, &rt1i, &t1_re, &t1_im, &mu1_im, &mu1_re);
          mu1_re = s - b_A->data[m + b_A->size[0] * m];
          r = rt_hypotd_snf(rt_hypotd_snf(mu1_re, rt1i), b_A->data[m + b_A->
                            size[0] * (m - 1)]);
          if (rt1i == 0.0) {
            mu1_re /= r;
            mu1_im = 0.0;
          } else if (mu1_re == 0.0) {
            mu1_re = 0.0;
            mu1_im = rt1i / r;
          } else {
            mu1_re /= r;
            mu1_im = rt1i / r;
          }

          s = b_A->data[m + b_A->size[0] * (m - 1)] / r;
          for (j = m; j <= n; j++) {
            t1_re = T->data[(m + T->size[0] * (j - 1)) - 1].re;
            t1_im = T->data[(m + T->size[0] * (j - 1)) - 1].im;
            c = T->data[(m + T->size[0] * (j - 1)) - 1].re;
            d = T->data[(m + T->size[0] * (j - 1)) - 1].im;
            r = T->data[(m + T->size[0] * (j - 1)) - 1].im;
            b = T->data[(m + T->size[0] * (j - 1)) - 1].re;
            T->data[(m + T->size[0] * (j - 1)) - 1].re = (mu1_re * c + mu1_im *
              d) + s * T->data[m + T->size[0] * (j - 1)].re;
            T->data[(m + T->size[0] * (j - 1)) - 1].im = (mu1_re * r - mu1_im *
              b) + s * T->data[m + T->size[0] * (j - 1)].im;
            r = mu1_re * T->data[m + T->size[0] * (j - 1)].re - mu1_im * T->
              data[m + T->size[0] * (j - 1)].im;
            b = mu1_re * T->data[m + T->size[0] * (j - 1)].im + mu1_im * T->
              data[m + T->size[0] * (j - 1)].re;
            T->data[m + T->size[0] * (j - 1)].re = r - s * t1_re;
            T->data[m + T->size[0] * (j - 1)].im = b - s * t1_im;
          }

          for (i = 0; i <= m; i++) {
            t1_re = T->data[i + T->size[0] * (m - 1)].re;
            t1_im = T->data[i + T->size[0] * (m - 1)].im;
            r = mu1_re * T->data[i + T->size[0] * (m - 1)].re - mu1_im * T->
              data[i + T->size[0] * (m - 1)].im;
            b = mu1_re * T->data[i + T->size[0] * (m - 1)].im + mu1_im * T->
              data[i + T->size[0] * (m - 1)].re;
            c = T->data[i + T->size[0] * m].re;
            d = T->data[i + T->size[0] * m].im;
            T->data[i + T->size[0] * (m - 1)].re = r + s * c;
            T->data[i + T->size[0] * (m - 1)].im = b + s * d;
            c = T->data[i + T->size[0] * m].re;
            d = T->data[i + T->size[0] * m].im;
            r = T->data[i + T->size[0] * m].im;
            b = T->data[i + T->size[0] * m].re;
            T->data[i + T->size[0] * m].re = (mu1_re * c + mu1_im * d) - s *
              t1_re;
            T->data[i + T->size[0] * m].im = (mu1_re * r - mu1_im * b) - s *
              t1_im;
          }

          for (i = 0; i < n; i++) {
            t1_re = V->data[i + V->size[0] * (m - 1)].re;
            t1_im = V->data[i + V->size[0] * (m - 1)].im;
            r = mu1_re * V->data[i + V->size[0] * (m - 1)].re - mu1_im * V->
              data[i + V->size[0] * (m - 1)].im;
            b = mu1_re * V->data[i + V->size[0] * (m - 1)].im + mu1_im * V->
              data[i + V->size[0] * (m - 1)].re;
            c = V->data[i + V->size[0] * m].re;
            d = V->data[i + V->size[0] * m].im;
            V->data[i + V->size[0] * (m - 1)].re = r + s * c;
            V->data[i + V->size[0] * (m - 1)].im = b + s * d;
            c = V->data[i + V->size[0] * m].re;
            d = V->data[i + V->size[0] * m].im;
            r = V->data[i + V->size[0] * m].im;
            b = V->data[i + V->size[0] * m].re;
            V->data[i + V->size[0] * m].re = (mu1_re * c + mu1_im * d) - s *
              t1_re;
            V->data[i + V->size[0] * m].im = (mu1_re * r - mu1_im * b) - s *
              t1_im;
          }

          T->data[m + T->size[0] * (m - 1)].re = 0.0;
          T->data[m + T->size[0] * (m - 1)].im = 0.0;
        }
      }
    }

    emxFree_real_T(&b_A);
  }
}

/*
 * File trailer for schur.c
 *
 * [EOF]
 */
