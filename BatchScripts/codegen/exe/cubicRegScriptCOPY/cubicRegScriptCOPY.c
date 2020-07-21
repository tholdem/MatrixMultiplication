/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cubicRegScriptCOPY.c
 *
 * Code generation for function 'cubicRegScriptCOPY'
 *
 */

/* Include files */
#include "cubicRegScriptCOPY.h"
#include "cat.h"
#include "cubicRegCOPY.h"
#include "cubicRegScriptCOPY_data.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "cubicRegScriptCOPY_initialize.h"
#include "eye.h"
#include "ishermitian.h"
#include "kron.h"
#include "lapacke.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "tensorHessianOptimized.h"
#include "triu.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void b___anon_fcn(double r, const emxArray_real_T *x, emxArray_real_T
  *varargout_1);
static void c___anon_fcn(double r, const emxArray_real_T *x, emxArray_real_T
  *varargout_1);

/* Function Definitions */
static void b___anon_fcn(double r, const emxArray_real_T *x, emxArray_real_T
  *varargout_1)
{
  double d;
  int i;
  int i1;
  int loop_ub;
  d = 9.0 * r + 1.0;
  if (d > r * 18.0) {
    i = 1;
  } else {
    i = (int)d;
  }

  i1 = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = 9;
  loop_ub = (int)r;
  varargout_1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(varargout_1, i1);
  loop_ub *= 9;
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargout_1->data[i1] = x->data[(i + i1) - 1];
  }
}

static void c___anon_fcn(double r, const emxArray_real_T *x, emxArray_real_T
  *varargout_1)
{
  double d;
  int i;
  int i1;
  int loop_ub;
  d = r * 18.0 + 1.0;
  if (d > x->size[0]) {
    i = 1;
  } else {
    i = (int)d;
  }

  i1 = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = 9;
  loop_ub = (int)r;
  varargout_1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(varargout_1, i1);
  loop_ub *= 9;
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargout_1->data[i1] = x->data[(i + i1) - 1];
  }
}

double __anon_fcn(const double U_tunableEnvironment[1], const double
                  V_tunableEnvironment[1], const emxArray_real_T *x)
{
  double varargout_1;
  emxArray_real_T *b_varargout_1;
  double bkj;
  int i;
  int i1;
  int inner;
  int coffset;
  int j;
  double y_data[81];
  int k;
  int b_i;
  int aoffset;
  lapack_int info_t;
  double s_data[9];
  double superb_data[8];
  emxInit_real_T(&b_varargout_1, 2);
  bkj = 9.0 * V_tunableEnvironment[0] + 1.0;
  if (bkj > V_tunableEnvironment[0] * 18.0) {
    i = 0;
  } else {
    i = (int)bkj - 1;
  }

  i1 = b_varargout_1->size[0] * b_varargout_1->size[1];
  b_varargout_1->size[0] = 9;
  inner = (int)U_tunableEnvironment[0];
  b_varargout_1->size[1] = inner;
  emxEnsureCapacity_real_T(b_varargout_1, i1);
  coffset = 9 * inner;
  for (i1 = 0; i1 < coffset; i1++) {
    b_varargout_1->data[i1] = x->data[i1];
  }

  for (j = 0; j < 9; j++) {
    coffset = j * 9;
    memset(&y_data[coffset], 0, 9U * sizeof(double));
    for (k = 0; k < inner; k++) {
      aoffset = k * 9;
      bkj = x->data[(i + k * 9) + j];
      for (b_i = 0; b_i < 9; b_i++) {
        i1 = coffset + b_i;
        y_data[i1] += b_varargout_1->data[aoffset + b_i] * bkj;
      }
    }
  }

  emxFree_real_T(&b_varargout_1);
  varargout_1 = 0.0;
  for (j = 0; j < 9; j++) {
    for (b_i = 0; b_i < 9; b_i++) {
      bkj = fabs(y_data[b_i + 9 * j]);
      if (rtIsNaN(bkj) || (bkj > varargout_1)) {
        varargout_1 = bkj;
      }
    }
  }

  if ((!rtIsInf(varargout_1)) && (!rtIsNaN(varargout_1))) {
    info_t = LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'N', (lapack_int)9,
      (lapack_int)9, &y_data[0], (lapack_int)9, &s_data[0], NULL, (lapack_int)1,
      NULL, (lapack_int)1, &superb_data[0]);
    if ((int)info_t < 0) {
      for (i = 0; i < 9; i++) {
        s_data[i] = rtNaN;
      }
    }

    varargout_1 = s_data[0];
  }

  return varargout_1;
}

void cubicRegScriptCOPY(double i, double num, double rank, double t, double R,
  double k, double errThd, double maxIts)
{
  double a;
  double U_tunableEnvironment[1];
  d_coder_internal_anonymous_func errFcn_tunableEnvironment[1];
  int b_i;
  cell_6 expl_temp;
  emxArray_real_T *errorHistory;
  emxArray_real_T *b;
  int j;
  double d;
  unsigned int seed;
  int mti;
  int i1;
  if (!isInitialized_cubicRegScriptCOPY) {
    cubicRegScriptCOPY_initialize();
  }

  /*  USAGE: cubicRegScript(i,num,rank,t,R,k,errThd,maxIts,outputDir) */
  a = (i - 1.0) * num + 1.0;

  /*  This script reproduces the tensor indices on page 30 of Tammy's tensor */
  /*  tutorial slides.  */
  /* r = 1; */
  /* sanity check */
  /* D = zeros(9,1); */
  /*  for k=1:9 */
  /*      D(k) =a'*X(:,:,k)*b; */
  /*  end */
  /* matricize u, v, w */
  U_tunableEnvironment[0] = rank;
  errFcn_tunableEnvironment[0].tunableEnvironment.f1.tunableEnvironment[0] =
    rank;
  errFcn_tunableEnvironment[0].tunableEnvironment.f2.tunableEnvironment[0] =
    rank;
  b_i = (int)(i * num + (1.0 - a));
  if (0 <= b_i - 1) {
    expl_temp.f6.tunableEnvironment[0] = rank;
    expl_temp.f5.tunableEnvironment[0] = rank;
    expl_temp.f4.tunableEnvironment[0] = rank;
    expl_temp.f3 = R;
    expl_temp.f2 = t;
    expl_temp.f1.tunableEnvironment.f1.tunableEnvironment[0] = rank;
    expl_temp.f1.tunableEnvironment.f2.tunableEnvironment[0] = rank;
    expl_temp.f1.tunableEnvironment.f3.tunableEnvironment[0] = rank;
  }

  emxInit_real_T(&errorHistory, 1);
  emxInit_real_T(&b, 1);
  for (j = 0; j < b_i; j++) {
    d = a + (double)j;
    if (d < 4.294967296E+9) {
      if (d >= 0.0) {
        seed = (unsigned int)d;
      } else {
        seed = 0U;
      }
    } else if (d >= 4.294967296E+9) {
      seed = MAX_uint32_T;
    } else {
      seed = 0U;
    }

    if (seed == 0U) {
      seed = 5489U;
    }

    state[0] = seed;
    for (mti = 0; mti < 623; mti++) {
      seed = ((seed ^ seed >> 30U) * 1812433253U + mti) + 1U;
      state[mti + 1] = seed;
    }

    state[624] = 624U;

    /* each subjob has a unique ID j and is used as seed */
    randn(27.0 * rank, b);
    mti = b->size[0];
    for (i1 = 0; i1 < mti; i1++) {
      b->data[i1] *= k;
    }

    cubicRegCOPY(U_tunableEnvironment, U_tunableEnvironment, t, R,
                 U_tunableEnvironment, U_tunableEnvironment,
                 U_tunableEnvironment, t, R, U_tunableEnvironment,
                 U_tunableEnvironment, U_tunableEnvironment, expl_temp, b,
                 errThd, maxIts, errFcn_tunableEnvironment, errorHistory);
    printf("The last entry of errorHistory is %f.\n", errorHistory->
           data[errorHistory->size[0] - 1]);
    fflush(stdout);
  }

  emxFree_real_T(&b);
  emxFree_real_T(&errorHistory);
}

void d___anon_fcn(const emxArray_real_T *x, emxArray_creal_T *varargout_1)
{
  emxArray_real_T *T;
  int j;
  int nx;
  int istart;
  int jend;
  boolean_T p;
  emxArray_creal_T *A;
  emxArray_real_T *tau;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  emxArray_real_T *wr;
  lapack_int info_t;
  emxArray_real_T *wi;
  double z;
  creal_T vl;
  creal_T vr;
  int i;
  emxInit_real_T(&T, 2);
  j = T->size[0] * T->size[1];
  T->size[0] = x->size[0];
  T->size[1] = x->size[0];
  emxEnsureCapacity_real_T(T, j);
  nx = x->size[0];
  for (j = 0; j < nx; j++) {
    istart = x->size[0];
    for (jend = 0; jend < istart; jend++) {
      T->data[jend + T->size[0] * j] = x->data[jend] * x->data[j];
    }
  }

  if ((T->size[0] == 0) || (T->size[1] == 0)) {
    j = varargout_1->size[0];
    varargout_1->size[0] = T->size[0];
    emxEnsureCapacity_creal_T(varargout_1, j);
    nx = T->size[0];
    for (j = 0; j < nx; j++) {
      varargout_1->data[j].re = 0.0;
      varargout_1->data[j].im = 0.0;
    }
  } else {
    nx = T->size[0] * T->size[1];
    p = true;
    for (istart = 0; istart < nx; istart++) {
      if ((!p) || (rtIsInf(T->data[istart]) || rtIsNaN(T->data[istart]))) {
        p = false;
      }
    }

    if (!p) {
      if ((T->size[0] == 1) && (T->size[1] == 1)) {
        j = varargout_1->size[0];
        varargout_1->size[0] = 1;
        emxEnsureCapacity_creal_T(varargout_1, j);
        for (j = 0; j < 1; j++) {
          varargout_1->data[0].re = rtNaN;
          varargout_1->data[0].im = 0.0;
        }
      } else {
        j = varargout_1->size[0];
        varargout_1->size[0] = T->size[0];
        emxEnsureCapacity_creal_T(varargout_1, j);
        nx = T->size[0];
        for (j = 0; j < nx; j++) {
          varargout_1->data[j].re = rtNaN;
          varargout_1->data[j].im = 0.0;
        }
      }
    } else if ((T->size[0] == 1) && (T->size[1] == 1)) {
      j = varargout_1->size[0];
      varargout_1->size[0] = 1;
      emxEnsureCapacity_creal_T(varargout_1, j);
      varargout_1->data[0].re = T->data[0];
      varargout_1->data[0].im = 0.0;
    } else if (ishermitian(T)) {
      nx = T->size[0] * T->size[1];
      p = true;
      for (istart = 0; istart < nx; istart++) {
        if ((!p) || (rtIsInf(T->data[istart]) || rtIsNaN(T->data[istart]))) {
          p = false;
        }
      }

      emxInit_real_T(&tau, 1);
      if (!p) {
        unnamed_idx_0 = (unsigned int)T->size[0];
        unnamed_idx_1 = (unsigned int)T->size[1];
        j = T->size[0] * T->size[1];
        T->size[0] = (int)unnamed_idx_0;
        T->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity_real_T(T, j);
        nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
        for (j = 0; j < nx; j++) {
          T->data[j] = rtNaN;
        }

        nx = T->size[0];
        if (1 < T->size[0]) {
          istart = 2;
          if (T->size[0] - 2 < T->size[1] - 1) {
            jend = T->size[0] - 1;
          } else {
            jend = T->size[1];
          }

          for (j = 0; j < jend; j++) {
            for (i = istart; i <= nx; i++) {
              T->data[(i + T->size[0] * j) - 1] = 0.0;
            }

            istart++;
          }
        }
      } else {
        j = tau->size[0];
        tau->size[0] = T->size[0] - 1;
        emxEnsureCapacity_real_T(tau, j);
        if (T->size[0] > 1) {
          info_t = LAPACKE_dgehrd(LAPACK_COL_MAJOR, (lapack_int)T->size[0],
            (lapack_int)1, (lapack_int)T->size[0], &T->data[0], (lapack_int)
            T->size[0], &tau->data[0]);
          if ((int)info_t != 0) {
            nx = T->size[1];
            for (j = 0; j < nx; j++) {
              istart = T->size[0];
              for (jend = 0; jend < istart; jend++) {
                T->data[jend + T->size[0] * j] = rtNaN;
              }
            }
          }
        }

        emxInit_real_T(&wr, 2);
        emxInit_real_T(&wi, 2);
        z = 0.0;
        info_t = (lapack_int)T->size[0];
        j = wr->size[0] * wr->size[1];
        wr->size[0] = 1;
        wr->size[1] = T->size[0];
        emxEnsureCapacity_real_T(wr, j);
        j = wi->size[0] * wi->size[1];
        wi->size[0] = 1;
        wi->size[1] = T->size[0];
        emxEnsureCapacity_real_T(wi, j);
        info_t = LAPACKE_dhseqr(LAPACK_COL_MAJOR, 'S', 'N', info_t, (lapack_int)
          1, (lapack_int)T->size[0], &T->data[0], info_t, &wr->data[0],
          &wi->data[0], &z, (lapack_int)T->size[0]);
        emxFree_real_T(&wi);
        emxFree_real_T(&wr);
        if ((int)info_t < 0) {
          nx = T->size[1];
          for (j = 0; j < nx; j++) {
            istart = T->size[0];
            for (jend = 0; jend < istart; jend++) {
              T->data[jend + T->size[0] * j] = rtNaN;
            }
          }
        }
      }

      nx = T->size[0];
      j = tau->size[0];
      tau->size[0] = T->size[0];
      emxEnsureCapacity_real_T(tau, j);
      for (istart = 0; istart < nx; istart++) {
        tau->data[istart] = T->data[istart + T->size[0] * istart];
      }

      j = varargout_1->size[0];
      varargout_1->size[0] = tau->size[0];
      emxEnsureCapacity_creal_T(varargout_1, j);
      nx = tau->size[0];
      for (j = 0; j < nx; j++) {
        varargout_1->data[j].re = tau->data[j];
        varargout_1->data[j].im = 0.0;
      }

      emxFree_real_T(&tau);
    } else {
      emxInit_creal_T(&A, 2);
      j = A->size[0] * A->size[1];
      A->size[0] = T->size[0];
      A->size[1] = T->size[1];
      emxEnsureCapacity_creal_T(A, j);
      nx = T->size[0] * T->size[1];
      for (j = 0; j < nx; j++) {
        A->data[j].re = T->data[j];
        A->data[j].im = 0.0;
      }

      j = varargout_1->size[0];
      varargout_1->size[0] = T->size[1];
      emxEnsureCapacity_creal_T(varargout_1, j);
      info_t = LAPACKE_zgeev(LAPACK_COL_MAJOR, 'N', 'N', (lapack_int)T->size[1],
        (lapack_complex_double *)&A->data[0], (lapack_int)T->size[0],
        (lapack_complex_double *)&varargout_1->data[0], (lapack_complex_double *)
        &vl, (lapack_int)1, (lapack_complex_double *)&vr, (lapack_int)1);
      emxFree_creal_T(&A);
      if ((int)info_t < 0) {
        nx = varargout_1->size[0];
        j = varargout_1->size[0];
        varargout_1->size[0] = nx;
        emxEnsureCapacity_creal_T(varargout_1, j);
        for (j = 0; j < nx; j++) {
          varargout_1->data[j].re = rtNaN;
          varargout_1->data[j].im = 0.0;
        }
      }
    }
  }

  emxFree_real_T(&T);
}

void e___anon_fcn(const double U_tunableEnvironment[1], const double
                  V_tunableEnvironment[1], const double W_tunableEnvironment[1],
                  const emxArray_real_T *x, emxArray_real_T *varargout_1)
{
  emxArray_real_T *Ux;
  int i;
  int i1;
  int loop_ub;
  emxArray_real_T *Vx;
  emxArray_real_T *Wx;
  emxArray_real_T *Gamma;
  emxArray_real_T *X;
  emxArray_real_T *H1;
  emxArray_real_T *r;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  int rank;
  int b_loop_ub;
  double tmp_data[81];
  int tmp_size[2];
  int n;
  emxArray_real_T *An;
  emxArray_real_T *Ap;
  emxArray_real_T *term3;
  unsigned int s;
  int c_loop_ub;
  int i2;
  double term1_data[81];
  double d;
  int d_loop_ub;
  double d1;
  int i3;
  int i4;
  double d2;
  double d3;
  double b_Wx;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  double d4;
  double d5;
  double a[9];
  emxInit_real_T(&Ux, 2);

  /* removed cell arrays to save time */
  /* implementation of Theorem 4.3 of Sandia 200dim1 Tech Report */
  /* Z is the tensor representing 3 by 3 matrix multiplication */
  /* U,V,W are matricization functions for the factor matrices */
  /*  for k = 1:10 */
  /*  tic */
  i = Ux->size[0] * Ux->size[1];
  Ux->size[0] = 9;
  i1 = (int)U_tunableEnvironment[0];
  Ux->size[1] = i1;
  emxEnsureCapacity_real_T(Ux, i);
  loop_ub = 9 * i1;
  for (i = 0; i < loop_ub; i++) {
    Ux->data[i] = x->data[i];
  }

  emxInit_real_T(&Vx, 2);
  emxInit_real_T(&Wx, 2);
  emxInit_real_T(&Gamma, 3);
  emxInit_real_T(&X, 3);
  emxInit_real_T(&H1, 2);
  emxInit_real_T(&r, 3);
  emxInit_real_T(&r1, 2);
  emxInit_real_T(&r2, 2);
  b___anon_fcn(V_tunableEnvironment[0], x, Vx);
  c___anon_fcn(W_tunableEnvironment[0], x, Wx);
  rank = Ux->size[1];

  /* each cell is the elementwise product of the Gram matrices of factor */
  /* matrices except for the factor matrix of cell index, also known as nth Gamma */
  f___anon_fcn(Vx, Wx, r1);
  f___anon_fcn(Ux, Wx, r2);
  f___anon_fcn(Ux, Vx, H1);
  cat(r1, r2, H1, Gamma);
  cat(Ux, Vx, Wx, r);
  i = X->size[0] * X->size[1] * X->size[2];
  X->size[0] = r->size[0];
  X->size[1] = r->size[1];
  X->size[2] = 3;
  emxEnsureCapacity_real_T(X, i);
  loop_ub = r->size[0] * r->size[1] * r->size[2];
  for (i = 0; i < loop_ub; i++) {
    X->data[i] = r->data[i];
  }

  emxFree_real_T(&r);
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = (int)((double)Ux->size[1] * 3.0 * 9.0);
  varargout_1->size[1] = (int)((double)Ux->size[1] * 3.0 * 9.0);
  emxEnsureCapacity_real_T(varargout_1, i);
  loop_ub = (int)((double)Ux->size[1] * 3.0 * 9.0) * (int)((double)Ux->size[1] *
    3.0 * 9.0);
  for (i = 0; i < loop_ub; i++) {
    varargout_1->data[i] = 0.0;
  }

  /* when n(matrix) is the same but r (columns) are different */
  /* block diagonal matrices on the diagonal of H */
  /* accomplished by expanding each entry of Gamma to 9 by 9 diagnal using */
  /* kronecker product */
  /* upper triangle to save computation */
  /* saved 1/3 time */
  loop_ub = Gamma->size[0];
  b_loop_ub = Gamma->size[1];
  eye(tmp_data, tmp_size);
  for (n = 0; n < 3; n++) {
    i = r1->size[0] * r1->size[1];
    r1->size[0] = loop_ub;
    r1->size[1] = b_loop_ub;
    emxEnsureCapacity_real_T(r1, i);
    for (i = 0; i < b_loop_ub; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        r1->data[i1 + r1->size[0] * i] = Gamma->data[(i1 + Gamma->size[0] * i) +
          Gamma->size[0] * Gamma->size[1] * n];
      }
    }

    triu(r1);
    kron(r1, tmp_data, H1);
    s = (unsigned int)n * H1->size[0] + 1U;
    if (s > ((double)n + 1.0) * (double)H1->size[0]) {
      i = 1;
    } else {
      i = (int)s;
    }

    s = (unsigned int)n * H1->size[0] + 1U;
    if (s > ((double)n + 1.0) * (double)H1->size[0]) {
      i1 = 1;
    } else {
      i1 = (int)s;
    }

    c_loop_ub = H1->size[1];
    for (i2 = 0; i2 < c_loop_ub; i2++) {
      d_loop_ub = H1->size[0];
      for (i3 = 0; i3 < d_loop_ub; i3++) {
        varargout_1->data[((i + i3) + varargout_1->size[0] * ((i1 + i2) - 1)) -
          1] = H1->data[i3 + H1->size[0] * i2];
      }
    }
  }

  emxFree_real_T(&H1);
  emxFree_real_T(&Gamma);

  /* for the next two cases we only find the upper triangle part to avoid error */
  /* when n are different and r is the same */
  i = Ux->size[1];
  emxInit_real_T(&An, 2);
  emxInit_real_T(&Ap, 2);
  emxInit_real_T(&term3, 3);
  for (n = 0; n < i; n++) {
    /* case 1 */
    loop_ub = X->size[1];
    i1 = An->size[0] * An->size[1];
    An->size[0] = 9;
    An->size[1] = X->size[1];
    emxEnsureCapacity_real_T(An, i1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < 9; i2++) {
        i3 = i2 + 9 * i1;
        An->data[i3] = X->data[i3];
      }
    }

    memset(&term1_data[0], 0, 81U * sizeof(double));
    i1 = term3->size[0] * term3->size[1] * term3->size[2];
    term3->size[0] = 9;
    term3->size[1] = 9;
    term3->size[2] = rank;
    emxEnsureCapacity_real_T(term3, i1);
    loop_ub = 81 * rank;
    for (i1 = 0; i1 < loop_ub; i1++) {
      term3->data[i1] = 0.0;
    }

    /* remaining matrix's rth column */
    /* term1 is I1 by I2 matrix, i is i1, j is i2 */
    /* term1 = ttv(Z,col_r,3); equivalent but slower */
    /*      for i = 1:dim1 */
    /*         term1(i,:) = reshape(Z(i,:,:),[dim2,dim3]) * col_r; */
    /*      end */
    /* hardcoded ttv(Z,col_r),saves 4x time */
    for (i1 = 0; i1 < 3; i1++) {
      d = Wx->data[3 * i1 + 9 * n];
      b_loop_ub = 3 * i1 + 1;
      d1 = Wx->data[b_loop_ub + 9 * n];
      c_loop_ub = 3 * i1 + 2;
      d2 = Wx->data[c_loop_ub + 9 * n];
      d_loop_ub = 9 * (3 * i1);
      term1_data[d_loop_ub] = d;
      term1_data[9 * b_loop_ub + 3] = d;
      term1_data[9 * c_loop_ub + 6] = d;
      term1_data[d_loop_ub + 1] = d1;
      term1_data[9 * b_loop_ub + 4] = d1;
      term1_data[9 * c_loop_ub + 7] = d1;
      term1_data[d_loop_ub + 2] = d2;
      term1_data[9 * b_loop_ub + 5] = d2;
      term1_data[9 * c_loop_ub + 8] = d2;
    }

    /* psi_rl is the inner product of rth,lth col of remaining matrix */
    /* combine half of 2nd term and 3rd term for simplicity                 */
    for (b_loop_ub = 0; b_loop_ub < rank; b_loop_ub++) {
      b_Wx = 0.0;
      for (i1 = 0; i1 < 9; i1++) {
        b_Wx += Wx->data[i1 + 9 * n] * Wx->data[i1 + 9 * b_loop_ub];
      }

      for (i1 = 0; i1 < 9; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          term3->data[(i2 + 9 * i1) + 81 * b_loop_ub] = b_Wx * An->data[i2 + 9 *
            b_loop_ub] * X->data[(i1 + 9 * b_loop_ub) + 9 * X->size[1]];
        }
      }
    }

    b_Wx = 0.0;
    for (i1 = 0; i1 < 9; i1++) {
      d = Wx->data[i1 + 9 * n];
      b_Wx += d * d;
    }

    d = (((double)n + 1.0) - 1.0) * 9.0 + 1.0;
    d1 = ((double)n + 1.0) * 9.0;
    if (d > d1) {
      i1 = 1;
    } else {
      i1 = (int)d;
    }

    d2 = ((unsigned int)n + rank) + 1U;
    d3 = (d2 - 1.0) * 9.0 + 1.0;
    d2 *= 9.0;
    if (d3 > d2) {
      i2 = 1;
    } else {
      i2 = (int)d3;
    }

    sum(term3, tmp_data, tmp_size);
    for (i3 = 0; i3 < 9; i3++) {
      for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
        b_loop_ub = c_loop_ub + 9 * i3;
        varargout_1->data[((i1 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
          - 1)) - 1] = (-term1_data[b_loop_ub] + b_Wx * X->data[c_loop_ub + 9 *
                        n] * X->data[(i3 + 9 * n) + 9 * X->size[1]]) +
          tmp_data[b_loop_ub];
      }
    }

    /* case 2 */
    /* n=1; */
    loop_ub = X->size[1];
    i1 = Ap->size[0] * Ap->size[1];
    Ap->size[0] = 9;
    Ap->size[1] = X->size[1];
    emxEnsureCapacity_real_T(Ap, i1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < 9; i2++) {
        i3 = i2 + 9 * i1;
        Ap->data[i3] = X->data[i3 + 9 * X->size[1] * 2];
      }
    }

    memset(&term1_data[0], 0, 81U * sizeof(double));

    /*      for j = 1:dim3 */
    /*         term1(:,j) = reshape(Z(:,:,j),[dim1,dim2]) * col_r; */
    /*      end */
    for (i1 = 0; i1 < 3; i1++) {
      d4 = Vx->data[3 * i1 + 9 * n];
      b_loop_ub = 3 * i1 + 1;
      b_Wx = Vx->data[b_loop_ub + 9 * n];
      c_loop_ub = 3 * i1 + 2;
      d5 = Vx->data[c_loop_ub + 9 * n];
      d_loop_ub = 9 * (3 * i1);
      term1_data[d_loop_ub] = d4;
      term1_data[9 * b_loop_ub + 1] = d4;
      term1_data[9 * c_loop_ub + 2] = d4;
      term1_data[d_loop_ub + 3] = b_Wx;
      term1_data[9 * b_loop_ub + 4] = b_Wx;
      term1_data[9 * c_loop_ub + 5] = b_Wx;
      term1_data[d_loop_ub + 6] = d5;
      term1_data[9 * b_loop_ub + 7] = d5;
      term1_data[9 * c_loop_ub + 8] = d5;
    }

    for (b_loop_ub = 0; b_loop_ub < rank; b_loop_ub++) {
      b_Wx = 0.0;
      for (i1 = 0; i1 < 9; i1++) {
        b_Wx += Vx->data[i1 + 9 * n] * Vx->data[i1 + 9 * b_loop_ub];
      }

      for (i1 = 0; i1 < 9; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          term3->data[(i2 + 9 * i1) + 81 * b_loop_ub] = b_Wx * An->data[i2 + 9 *
            b_loop_ub] * Ap->data[i1 + 9 * b_loop_ub];
        }
      }
    }

    b_Wx = 0.0;
    for (i1 = 0; i1 < 9; i1++) {
      d4 = Vx->data[i1 + 9 * n];
      b_Wx += d4 * d4;
    }

    if (d > d1) {
      i1 = 1;
    } else {
      i1 = (int)d;
    }

    d = ((double)n + 1.0) + (double)rank * 2.0;
    d1 = (d - 1.0) * 9.0 + 1.0;
    d *= 9.0;
    if (d1 > d) {
      i2 = 1;
    } else {
      i2 = (int)d1;
    }

    sum(term3, tmp_data, tmp_size);
    for (i3 = 0; i3 < 9; i3++) {
      for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
        b_loop_ub = c_loop_ub + 9 * i3;
        varargout_1->data[((i1 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
          - 1)) - 1] = (-term1_data[b_loop_ub] + b_Wx * X->data[c_loop_ub + 9 *
                        n] * X->data[(i3 + 9 * n) + 9 * X->size[1] * 2]) +
          tmp_data[b_loop_ub];
      }
    }

    /* case 3 */
    /* p=3; */
    memset(&term1_data[0], 0, 81U * sizeof(double));

    /*      for j = 1:dim3 */
    /*         term1(:,j) =  col_r.' * reshape(Z(:,:,j),[dim1,dim2]); */
    /*      end */
    a[0] = Ux->data[9 * n];
    a[3] = Ux->data[9 * n + 1];
    a[6] = Ux->data[9 * n + 2];
    a[1] = Ux->data[9 * n + 3];
    a[4] = Ux->data[9 * n + 4];
    a[7] = Ux->data[9 * n + 5];
    a[2] = Ux->data[9 * n + 6];
    a[5] = Ux->data[9 * n + 7];
    a[8] = Ux->data[9 * n + 8];
    for (i1 = 0; i1 < 3; i1++) {
      d4 = a[3 * i1];
      term1_data[9 * i1] = d4;
      d_loop_ub = 9 * (i1 + 3);
      term1_data[d_loop_ub + 3] = d4;
      b_loop_ub = 9 * (i1 + 6);
      term1_data[b_loop_ub + 6] = d4;
      d4 = a[3 * i1 + 1];
      term1_data[9 * i1 + 1] = d4;
      term1_data[d_loop_ub + 4] = d4;
      term1_data[b_loop_ub + 7] = d4;
      d4 = a[3 * i1 + 2];
      term1_data[9 * i1 + 2] = d4;
      term1_data[d_loop_ub + 5] = d4;
      term1_data[b_loop_ub + 8] = d4;
    }

    for (b_loop_ub = 0; b_loop_ub < rank; b_loop_ub++) {
      b_Wx = 0.0;
      for (i1 = 0; i1 < 9; i1++) {
        b_Wx += Ux->data[i1 + 9 * n] * Ux->data[i1 + 9 * b_loop_ub];
      }

      for (i1 = 0; i1 < 9; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          term3->data[(i2 + 9 * i1) + 81 * b_loop_ub] = b_Wx * X->data[(i2 + 9 *
            b_loop_ub) + 9 * X->size[1]] * Ap->data[i1 + 9 * b_loop_ub];
        }
      }
    }

    /* term2 = col_r.'*col_r*An(:,r)*Ap(:,r).' */
    /* each term is a nxn matrix, where n is dim1 */
    b_Wx = 0.0;
    for (i1 = 0; i1 < 9; i1++) {
      d4 = Ux->data[i1 + 9 * n];
      b_Wx += d4 * d4;
    }

    if (d3 > d2) {
      i1 = 1;
    } else {
      i1 = (int)d3;
    }

    if (d1 > d) {
      i2 = 1;
    } else {
      i2 = (int)d1;
    }

    sum(term3, tmp_data, tmp_size);
    for (i3 = 0; i3 < 9; i3++) {
      for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
        b_loop_ub = c_loop_ub + 9 * i3;
        varargout_1->data[((i1 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
          - 1)) - 1] = (-term1_data[b_loop_ub] + b_Wx * X->data[(c_loop_ub + 9 *
          n) + 9 * X->size[1]] * X->data[(i3 + 9 * n) + 9 * X->size[1] * 2]) +
          tmp_data[b_loop_ub];
      }
    }
  }

  emxFree_real_T(&term3);
  emxFree_real_T(&Ap);
  emxFree_real_T(&An);

  /* both n/p and r/s pairs are different */
  i = Ux->size[1];
  for (n = 0; n < i; n++) {
    i1 = rank - n;
    if (0 <= i1 - 2) {
      d = (((double)n + 1.0) - 1.0) * 9.0 + 1.0;
      d1 = ((double)n + 1.0) * 9.0;
      if (d > d1) {
        i4 = 1;
      } else {
        i4 = (int)d;
      }

      d2 = ((unsigned int)n + rank) + 1U;
      d3 = (d2 - 1.0) * 9.0 + 1.0;
      d2 *= 9.0;
      if (d3 > d2) {
        i5 = 1;
      } else {
        i5 = (int)d3;
      }

      if (d > d1) {
        i6 = 1;
      } else {
        i6 = (int)d;
      }

      d = ((double)n + 1.0) + (double)rank * 2.0;
      d1 = (d - 1.0) * 9.0 + 1.0;
      d *= 9.0;
      if (d1 > d) {
        i7 = 1;
      } else {
        i7 = (int)d1;
      }

      if (d3 > d2) {
        i8 = 1;
      } else {
        i8 = (int)d3;
      }

      if (d1 > d) {
        i9 = 1;
      } else {
        i9 = (int)d1;
      }
    }

    for (b_loop_ub = 0; b_loop_ub <= i1 - 2; b_loop_ub++) {
      s = ((unsigned int)n + b_loop_ub) + 2U;
      d = (double)s + (double)rank;
      d1 = (d - 1.0) * 9.0 + 1.0;
      if (d1 > d * 9.0) {
        i2 = 1;
      } else {
        i2 = (int)d1;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Wx->data[i3 + 9 * n] * Wx->data[i3 + 9 * ((int)s - 1)];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i4 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
            - 1)) - 1] = b_Wx * X->data[c_loop_ub + 9 * ((int)s - 1)] * X->data
            [(i3 + 9 * n) + 9 * X->size[1]];
        }
      }

      d = ((double)s - 1.0) * 9.0 + 1.0;
      d1 = (double)s * 9.0;
      if (d > d1) {
        i2 = 1;
      } else {
        i2 = (int)d;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Wx->data[i3 + 9 * ((int)s - 1)] * Wx->data[i3 + 9 * n];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i2 + c_loop_ub) + varargout_1->size[0] * ((i5 + i3)
            - 1)) - 1] = b_Wx * X->data[c_loop_ub + 9 * n] * X->data[(i3 + 9 *
            ((int)s - 1)) + 9 * X->size[1]];
        }
      }

      d2 = (double)s + (double)rank * 2.0;
      d3 = (d2 - 1.0) * 9.0 + 1.0;
      d2 *= 9.0;
      if (d3 > d2) {
        i2 = 1;
      } else {
        i2 = (int)d3;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Vx->data[i3 + 9 * n] * Vx->data[i3 + 9 * ((int)s - 1)];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i6 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
            - 1)) - 1] = b_Wx * X->data[c_loop_ub + 9 * ((int)s - 1)] * X->data
            [(i3 + 9 * n) + 9 * X->size[1] * 2];
        }
      }

      if (d > d1) {
        i2 = 1;
      } else {
        i2 = (int)d;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Vx->data[i3 + 9 * ((int)s - 1)] * Vx->data[i3 + 9 * n];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i2 + c_loop_ub) + varargout_1->size[0] * ((i7 + i3)
            - 1)) - 1] = b_Wx * X->data[c_loop_ub + 9 * n] * X->data[(i3 + 9 *
            ((int)s - 1)) + 9 * X->size[1] * 2];
        }
      }

      /* psi_rs is the inner product of rth,sth col of remaining matrix */
      if (d3 > d2) {
        i2 = 1;
      } else {
        i2 = (int)d3;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Ux->data[i3 + 9 * n] * Ux->data[i3 + 9 * ((int)s - 1)];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i8 + c_loop_ub) + varargout_1->size[0] * ((i2 + i3)
            - 1)) - 1] = b_Wx * X->data[(c_loop_ub + 9 * ((int)s - 1)) + 9 *
            X->size[1]] * X->data[(i3 + 9 * n) + 9 * X->size[1] * 2];
        }
      }

      d = s + rank;
      d1 = (d - 1.0) * 9.0 + 1.0;
      if (d1 > d * 9.0) {
        i2 = 1;
      } else {
        i2 = (int)d1;
      }

      b_Wx = 0.0;
      for (i3 = 0; i3 < 9; i3++) {
        b_Wx += Ux->data[i3 + 9 * ((int)s - 1)] * Ux->data[i3 + 9 * n];
      }

      for (i3 = 0; i3 < 9; i3++) {
        for (c_loop_ub = 0; c_loop_ub < 9; c_loop_ub++) {
          varargout_1->data[((i2 + c_loop_ub) + varargout_1->size[0] * ((i9 + i3)
            - 1)) - 1] = b_Wx * X->data[(c_loop_ub + 9 * n) + 9 * X->size[1]] *
            X->data[(i3 + 9 * ((int)s - 1)) + 9 * X->size[1] * 2];
        }
      }
    }
  }

  emxFree_real_T(&X);
  emxFree_real_T(&Wx);
  emxFree_real_T(&Vx);
  emxFree_real_T(&Ux);
  i = r1->size[0] * r1->size[1];
  r1->size[0] = varargout_1->size[0];
  r1->size[1] = varargout_1->size[1];
  emxEnsureCapacity_real_T(r1, i);
  loop_ub = varargout_1->size[0] * varargout_1->size[1];
  for (i = 0; i < loop_ub; i++) {
    r1->data[i] = varargout_1->data[i];
  }

  triu(r1);
  i = r2->size[0] * r2->size[1];
  r2->size[0] = varargout_1->size[0];
  r2->size[1] = varargout_1->size[1];
  emxEnsureCapacity_real_T(r2, i);
  loop_ub = varargout_1->size[0] * varargout_1->size[1];
  for (i = 0; i < loop_ub; i++) {
    r2->data[i] = varargout_1->data[i];
  }

  b_triu(r2);
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = r1->size[0];
  varargout_1->size[1] = r1->size[1];
  emxEnsureCapacity_real_T(varargout_1, i);
  loop_ub = r1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = r1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      varargout_1->data[i1 + varargout_1->size[0] * i] = r1->data[i1 + r1->size
        [0] * i] + r2->data[i + r2->size[0] * i1];
    }
  }

  emxFree_real_T(&r2);
  emxFree_real_T(&r1);

  /*  toc */
  /*  end */
}

/* End of code generation (cubicRegScriptCOPY.c) */
