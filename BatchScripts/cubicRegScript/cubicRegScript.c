/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "cubicRegScript_emxutil.h"
#include "fclose.h"
#include "fwrite.h"
#include "fileManager.h"
#include "norm.h"
#include "ktensorOptimized.h"
#include "triu.h"
#include "sum.h"
#include "kron.h"
#include "eye.h"
#include "cat.h"
#include "tensorHessianOptimized.h"
#include "khatriraoOptimized.h"
#include "cubicReg4Coder.h"
#include "randn.h"
#include "cubicRegScript_rtwutil.h"
#include "cubicRegScript_data.h"
#include "mkl_cblas.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : const double U_tunableEnvironment[1]
 *                const double V_tunableEnvironment[1]
 *                const double W_tunableEnvironment[1]
 *                const emxArray_real_T *x
 * Return Type  : double
 */
double __anon_fcn(const double U_tunableEnvironment[1], const double
                  V_tunableEnvironment[1], const double W_tunableEnvironment[1],
                  const emxArray_real_T *x)
{
  double a;
  int i3;
  int i4;
  emxArray_real_T *b_x;
  int i5;
  int loop_ub;
  emxArray_real_T *c_x;
  emxArray_real_T *d_x;
  double X[729];
  double b_X[729];
  static const signed char iv0[729] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  /* FUNC_F     Returns function f. */
  /*    This is used with FASTA package. */
  /* edited by Jaden Wang 6/17/2020 */
  /*  for vectorized input */
  /* X = tensor(ktensor({U(x),V(x),W(x)})); */
  a = 9.0 * V_tunableEnvironment[0] + 1.0;
  if (a > V_tunableEnvironment[0] * 18.0) {
    i3 = 0;
  } else {
    i3 = (int)a - 1;
  }

  a = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (a > x->size[0]) {
    i4 = 0;
  } else {
    i4 = (int)a - 1;
  }

  emxInit_real_T(&b_x, 2);
  i5 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 9;
  loop_ub = (int)U_tunableEnvironment[0];
  b_x->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_x, i5);
  loop_ub *= 9;
  for (i5 = 0; i5 < loop_ub; i5++) {
    b_x->data[i5] = x->data[i5];
  }

  emxInit_real_T(&c_x, 2);
  i5 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 9;
  loop_ub = (int)V_tunableEnvironment[0];
  c_x->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_x, i5);
  loop_ub *= 9;
  for (i5 = 0; i5 < loop_ub; i5++) {
    c_x->data[i5] = x->data[i3 + i5];
  }

  emxInit_real_T(&d_x, 2);
  i3 = d_x->size[0] * d_x->size[1];
  d_x->size[0] = 9;
  i5 = (int)W_tunableEnvironment[0];
  d_x->size[1] = i5;
  emxEnsureCapacity_real_T(d_x, i3);
  loop_ub = 9 * i5;
  for (i3 = 0; i3 < loop_ub; i3++) {
    d_x->data[i3] = x->data[i4 + i3];
  }

  ktensorOptimized(b_x, c_x, d_x, X);

  /*  AA = cell(3,1); */
  /*  no_row = size(A,1)/3; */
  /*  for k = 1:3 */
  /*      AA{k} = A(1 + (k-1)*no_row : k*no_row, :); */
  /*  end */
  /* ret_val = 1/2 * norm(X - tensor(Z))^2; */
  emxFree_real_T(&d_x);
  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  for (i3 = 0; i3 < 729; i3++) {
    b_X[i3] = X[i3] - (double)iv0[i3];
  }

  a = b_norm(b_X);
  return 0.5 * (a * a);
}

/*
 * Arguments    : const double U_tunableEnvironment[1]
 *                const double V_tunableEnvironment[1]
 *                const double W_tunableEnvironment[1]
 *                const emxArray_real_T *x
 *                emxArray_real_T *varargout_1
 * Return Type  : void
 */
void b___anon_fcn(const double U_tunableEnvironment[1], const double
                  V_tunableEnvironment[1], const double W_tunableEnvironment[1],
                  const emxArray_real_T *x, emxArray_real_T *varargout_1)
{
  double d1;
  int i10;
  int i11;
  emxArray_real_T *b_x;
  int i12;
  int loop_ub;
  emxArray_real_T *c_x;
  emxArray_real_T *d_x;
  emxArray_real_T *X;
  emxArray_real_T *r1;
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *y;
  boolean_T guard1 = false;
  emxArray_real_T *r2;
  int b_loop_ub;
  emxArray_real_T *b_X;
  int c_loop_ub;
  emxArray_real_T *c_X;
  emxArray_real_T *b_b;
  emxArray_real_T *mat1;
  static const double A[729] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  emxArray_real_T *mat2;
  static const double b_A[729] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  emxArray_real_T *mat3;
  static const double c_A[729] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  /* GRAD_F     Returns gradient of function f. */
  /*    This is used with FASTA package. */
  /*  X = cell(3,1); */
  /*  ret_mat = zeros(siXe(A)); */
  /*  no_row = size(A,1)/3; */
  /*  for k = 1:3 */
  /*      X{k} = A(1 + (k-1)*no_row : k*no_row, :); */
  /*  end */
  /* see Corollary 4.2 from Sandia 2009 Tech Report */
  d1 = 9.0 * V_tunableEnvironment[0] + 1.0;
  if (d1 > V_tunableEnvironment[0] * 18.0) {
    i10 = 0;
  } else {
    i10 = (int)d1 - 1;
  }

  d1 = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (d1 > x->size[0]) {
    i11 = 0;
  } else {
    i11 = (int)d1 - 1;
  }

  emxInit_real_T(&b_x, 2);
  i12 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 9;
  loop_ub = (int)U_tunableEnvironment[0];
  b_x->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_x, i12);
  loop_ub *= 9;
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_x->data[i12] = x->data[i12];
  }

  emxInit_real_T(&c_x, 2);
  i12 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 9;
  loop_ub = (int)V_tunableEnvironment[0];
  c_x->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_x, i12);
  loop_ub *= 9;
  for (i12 = 0; i12 < loop_ub; i12++) {
    c_x->data[i12] = x->data[i10 + i12];
  }

  emxInit_real_T(&d_x, 2);
  i10 = d_x->size[0] * d_x->size[1];
  d_x->size[0] = 9;
  i12 = (int)W_tunableEnvironment[0];
  d_x->size[1] = i12;
  emxEnsureCapacity_real_T(d_x, i10);
  loop_ub = 9 * i12;
  for (i10 = 0; i10 < loop_ub; i10++) {
    d_x->data[i10] = x->data[i11 + i10];
  }

  emxInit_real_T(&X, 3);
  emxInit_real_T(&r1, 3);
  cat(b_x, c_x, d_x, r1);
  i10 = X->size[0] * X->size[1] * X->size[2];
  X->size[0] = r1->size[0];
  X->size[1] = r1->size[1];
  X->size[2] = 3;
  emxEnsureCapacity_real_T(X, i10);
  loop_ub = r1->size[0] * r1->size[1] * r1->size[2];
  emxFree_real_T(&d_x);
  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  for (i10 = 0; i10 < loop_ub; i10++) {
    X->data[i10] = r1->data[i10];
  }

  emxFree_real_T(&r1);
  emxInit_real_T(&a, 2);

  /*  1st factor matrix */
  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i10 + 9 * i11) + ((9 * X->size
        [1]) << 1)];
    }
  }

  emxInit_real_T(&b, 2);
  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[(i11 + 9 * i10) + ((9 * X->size
        [1]) << 1)];
    }
  }

  emxInit_real_T(&y, 2);
  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = y->size[0] * y->size[1];
      y->size[0] = a->size[0];
      y->size[1] = i10;
      emxEnsureCapacity_real_T(y, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &y->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = i10;
    emxEnsureCapacity_real_T(y, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      y->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i10 + 9 * i11) + 9 * X->size[1]];
    }
  }

  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[(i11 + 9 * i10) + 9 * X->size[1]];
    }
  }

  emxInit_real_T(&r2, 2);
  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = r2->size[0] * r2->size[1];
      r2->size[0] = a->size[0];
      r2->size[1] = i10;
      emxEnsureCapacity_real_T(r2, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &r2->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = r2->size[0] * r2->size[1];
    r2->size[0] = a->size[0];
    r2->size[1] = i10;
    emxEnsureCapacity_real_T(r2, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      r2->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = 9;
  a->size[1] = loop_ub;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[i11 + 9 * i10];
    }
  }

  i10 = b->size[0] * b->size[1];
  b->size[0] = y->size[1];
  b->size[1] = y->size[0];
  emxEnsureCapacity_real_T(b, i10);
  loop_ub = y->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    b_loop_ub = y->size[1];
    for (i11 = 0; i11 < b_loop_ub; i11++) {
      b->data[i11 + b->size[0] * i10] = y->data[i10 + y->size[0] * i11] *
        r2->data[i10 + r2->size[0] * i11];
    }
  }

  i10 = X->size[1];
  if ((i10 == 1) || (b->size[0] == 1)) {
    i10 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = b->size[1];
    emxEnsureCapacity_real_T(y, i10);
    loop_ub = a->size[0];
    for (i10 = 0; i10 < loop_ub; i10++) {
      b_loop_ub = b->size[1];
      for (i11 = 0; i11 < b_loop_ub; i11++) {
        y->data[i10 + y->size[0] * i11] = 0.0;
        c_loop_ub = a->size[1];
        for (i12 = 0; i12 < c_loop_ub; i12++) {
          y->data[i10 + y->size[0] * i11] += a->data[i10 + a->size[0] * i12] *
            b->data[i12 + b->size[0] * i11];
        }
      }
    }
  } else {
    i10 = X->size[1];
    i11 = X->size[1];
    if ((i11 == 0) || (b->size[0] == 0) || (b->size[1] == 0)) {
      i10 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i10);
      loop_ub = 9 * b->size[1];
      for (i10 = 0; i10 < loop_ub; i10++) {
        y->data[i10] = 0.0;
      }
    } else {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i11);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)b->size[1], (MKL_INT)i10, 1.0, &a->data[0], (MKL_INT)
                  9, &b->data[0], (MKL_INT)i10, 0.0, &y->data[0], (MKL_INT)9);
    }
  }

  emxInit_real_T(&b_X, 2);
  loop_ub = X->size[1];
  i10 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = 9;
  b_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      b_X->data[i12] = X->data[i12 + ((9 * X->size[1]) << 1)];
    }
  }

  emxInit_real_T(&c_X, 2);
  loop_ub = X->size[1];
  i10 = c_X->size[0] * c_X->size[1];
  c_X->size[0] = 9;
  c_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      c_X->data[i12] = X->data[i12 + 9 * X->size[1]];
    }
  }

  emxInit_real_T(&b_b, 2);
  khatriraoOptimized(b_X, c_X, b_b);
  emxInit_real_T(&mat1, 2);
  if (b_b->size[1] == 0) {
    mat1->size[0] = 9;
    mat1->size[1] = 0;
  } else {
    i10 = mat1->size[0] * mat1->size[1];
    mat1->size[0] = 9;
    mat1->size[1] = b_b->size[1];
    emxEnsureCapacity_real_T(mat1, i10);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9, (MKL_INT)
                b_b->size[1], (MKL_INT)81, 1.0, &A[0], (MKL_INT)9, &b_b->data[0],
                (MKL_INT)81, 0.0, &mat1->data[0], (MKL_INT)9);
  }

  i10 = y->size[0] * y->size[1];
  i11 = mat1->size[0] * mat1->size[1];
  mat1->size[0] = y->size[0];
  mat1->size[1] = y->size[1];
  emxEnsureCapacity_real_T(mat1, i11);
  loop_ub = i10 - 1;
  for (i10 = 0; i10 <= loop_ub; i10++) {
    mat1->data[i10] = y->data[i10] - mat1->data[i10];
  }

  /*  2nd factor matrix */
  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i10 + 9 * i11) + ((9 * X->size
        [1]) << 1)];
    }
  }

  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[(i11 + 9 * i10) + ((9 * X->size
        [1]) << 1)];
    }
  }

  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = y->size[0] * y->size[1];
      y->size[0] = a->size[0];
      y->size[1] = i10;
      emxEnsureCapacity_real_T(y, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &y->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = i10;
    emxEnsureCapacity_real_T(y, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      y->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[i10 + 9 * i11];
    }
  }

  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[i11 + 9 * i10];
    }
  }

  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = r2->size[0] * r2->size[1];
      r2->size[0] = a->size[0];
      r2->size[1] = i10;
      emxEnsureCapacity_real_T(r2, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &r2->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = r2->size[0] * r2->size[1];
    r2->size[0] = a->size[0];
    r2->size[1] = i10;
    emxEnsureCapacity_real_T(r2, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      r2->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = 9;
  a->size[1] = loop_ub;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i11 + 9 * i10) + 9 * X->size[1]];
    }
  }

  i10 = b->size[0] * b->size[1];
  b->size[0] = y->size[1];
  b->size[1] = y->size[0];
  emxEnsureCapacity_real_T(b, i10);
  loop_ub = y->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    b_loop_ub = y->size[1];
    for (i11 = 0; i11 < b_loop_ub; i11++) {
      b->data[i11 + b->size[0] * i10] = y->data[i10 + y->size[0] * i11] *
        r2->data[i10 + r2->size[0] * i11];
    }
  }

  i10 = X->size[1];
  if ((i10 == 1) || (b->size[0] == 1)) {
    i10 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = b->size[1];
    emxEnsureCapacity_real_T(y, i10);
    loop_ub = a->size[0];
    for (i10 = 0; i10 < loop_ub; i10++) {
      b_loop_ub = b->size[1];
      for (i11 = 0; i11 < b_loop_ub; i11++) {
        y->data[i10 + y->size[0] * i11] = 0.0;
        c_loop_ub = a->size[1];
        for (i12 = 0; i12 < c_loop_ub; i12++) {
          y->data[i10 + y->size[0] * i11] += a->data[i10 + a->size[0] * i12] *
            b->data[i12 + b->size[0] * i11];
        }
      }
    }
  } else {
    i10 = X->size[1];
    i11 = X->size[1];
    if ((i11 == 0) || (b->size[0] == 0) || (b->size[1] == 0)) {
      i10 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i10);
      loop_ub = 9 * b->size[1];
      for (i10 = 0; i10 < loop_ub; i10++) {
        y->data[i10] = 0.0;
      }
    } else {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i11);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)b->size[1], (MKL_INT)i10, 1.0, &a->data[0], (MKL_INT)
                  9, &b->data[0], (MKL_INT)i10, 0.0, &y->data[0], (MKL_INT)9);
    }
  }

  loop_ub = X->size[1];
  i10 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = 9;
  b_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      b_X->data[i12] = X->data[i12 + ((9 * X->size[1]) << 1)];
    }
  }

  loop_ub = X->size[1];
  i10 = c_X->size[0] * c_X->size[1];
  c_X->size[0] = 9;
  c_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      c_X->data[i12] = X->data[i12];
    }
  }

  khatriraoOptimized(b_X, c_X, b_b);
  emxInit_real_T(&mat2, 2);
  if (b_b->size[1] == 0) {
    mat2->size[0] = 9;
    mat2->size[1] = 0;
  } else {
    i10 = mat2->size[0] * mat2->size[1];
    mat2->size[0] = 9;
    mat2->size[1] = b_b->size[1];
    emxEnsureCapacity_real_T(mat2, i10);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9, (MKL_INT)
                b_b->size[1], (MKL_INT)81, 1.0, &b_A[0], (MKL_INT)9, &b_b->data
                [0], (MKL_INT)81, 0.0, &mat2->data[0], (MKL_INT)9);
  }

  i10 = y->size[0] * y->size[1];
  i11 = mat2->size[0] * mat2->size[1];
  mat2->size[0] = y->size[0];
  mat2->size[1] = y->size[1];
  emxEnsureCapacity_real_T(mat2, i11);
  loop_ub = i10 - 1;
  for (i10 = 0; i10 <= loop_ub; i10++) {
    mat2->data[i10] = y->data[i10] - mat2->data[i10];
  }

  /*  3rd factor matrix */
  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i10 + 9 * i11) + 9 * X->size[1]];
    }
  }

  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[(i11 + 9 * i10) + 9 * X->size[1]];
    }
  }

  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = y->size[0] * y->size[1];
      y->size[0] = a->size[0];
      y->size[1] = i10;
      emxEnsureCapacity_real_T(y, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &y->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = i10;
    emxEnsureCapacity_real_T(y, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      y->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = loop_ub;
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < 9; i10++) {
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[i10 + 9 * i11];
    }
  }

  loop_ub = X->size[1];
  i10 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      b->data[i11 + b->size[0] * i10] = X->data[i11 + 9 * i10];
    }
  }

  guard1 = false;
  if (a->size[0] == 0) {
    guard1 = true;
  } else {
    i10 = X->size[1];
    if (i10 == 0) {
      guard1 = true;
    } else {
      i10 = X->size[1];
      i11 = r2->size[0] * r2->size[1];
      r2->size[0] = a->size[0];
      r2->size[1] = i10;
      emxEnsureCapacity_real_T(r2, i11);
      i10 = X->size[1];
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                  (MKL_INT)i10, (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)a->size[0],
                  &b->data[0], (MKL_INT)9, 0.0, &r2->data[0], (MKL_INT)a->size[0]);
    }
  }

  if (guard1) {
    i10 = X->size[1];
    i11 = r2->size[0] * r2->size[1];
    r2->size[0] = a->size[0];
    r2->size[1] = i10;
    emxEnsureCapacity_real_T(r2, i11);
    loop_ub = a->size[0] * i10;
    for (i10 = 0; i10 < loop_ub; i10++) {
      r2->data[i10] = 0.0;
    }
  }

  loop_ub = X->size[1];
  i10 = a->size[0] * a->size[1];
  a->size[0] = 9;
  a->size[1] = loop_ub;
  emxEnsureCapacity_real_T(a, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      a->data[i11 + a->size[0] * i10] = X->data[(i11 + 9 * i10) + ((9 * X->size
        [1]) << 1)];
    }
  }

  i10 = b->size[0] * b->size[1];
  b->size[0] = y->size[1];
  b->size[1] = y->size[0];
  emxEnsureCapacity_real_T(b, i10);
  loop_ub = y->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    b_loop_ub = y->size[1];
    for (i11 = 0; i11 < b_loop_ub; i11++) {
      b->data[i11 + b->size[0] * i10] = y->data[i10 + y->size[0] * i11] *
        r2->data[i10 + r2->size[0] * i11];
    }
  }

  emxFree_real_T(&r2);
  i10 = X->size[1];
  if ((i10 == 1) || (b->size[0] == 1)) {
    i10 = y->size[0] * y->size[1];
    y->size[0] = a->size[0];
    y->size[1] = b->size[1];
    emxEnsureCapacity_real_T(y, i10);
    loop_ub = a->size[0];
    for (i10 = 0; i10 < loop_ub; i10++) {
      b_loop_ub = b->size[1];
      for (i11 = 0; i11 < b_loop_ub; i11++) {
        y->data[i10 + y->size[0] * i11] = 0.0;
        c_loop_ub = a->size[1];
        for (i12 = 0; i12 < c_loop_ub; i12++) {
          y->data[i10 + y->size[0] * i11] += a->data[i10 + a->size[0] * i12] *
            b->data[i12 + b->size[0] * i11];
        }
      }
    }
  } else {
    i10 = X->size[1];
    i11 = X->size[1];
    if ((i11 == 0) || (b->size[0] == 0) || (b->size[1] == 0)) {
      i10 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i10);
      loop_ub = 9 * b->size[1];
      for (i10 = 0; i10 < loop_ub; i10++) {
        y->data[i10] = 0.0;
      }
    } else {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i11);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)b->size[1], (MKL_INT)i10, 1.0, &a->data[0], (MKL_INT)
                  9, &b->data[0], (MKL_INT)i10, 0.0, &y->data[0], (MKL_INT)9);
    }
  }

  emxFree_real_T(&b);
  emxFree_real_T(&a);
  loop_ub = X->size[1];
  i10 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = 9;
  b_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      b_X->data[i12] = X->data[i12 + 9 * X->size[1]];
    }
  }

  loop_ub = X->size[1];
  i10 = c_X->size[0] * c_X->size[1];
  c_X->size[0] = 9;
  c_X->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_X, i10);
  for (i10 = 0; i10 < loop_ub; i10++) {
    for (i11 = 0; i11 < 9; i11++) {
      i12 = i11 + 9 * i10;
      c_X->data[i12] = X->data[i12];
    }
  }

  emxFree_real_T(&X);
  khatriraoOptimized(b_X, c_X, b_b);
  emxFree_real_T(&c_X);
  emxFree_real_T(&b_X);
  emxInit_real_T(&mat3, 2);
  if (b_b->size[1] == 0) {
    mat3->size[0] = 9;
    mat3->size[1] = 0;
  } else {
    i10 = mat3->size[0] * mat3->size[1];
    mat3->size[0] = 9;
    mat3->size[1] = b_b->size[1];
    emxEnsureCapacity_real_T(mat3, i10);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9, (MKL_INT)
                b_b->size[1], (MKL_INT)81, 1.0, &c_A[0], (MKL_INT)9, &b_b->data
                [0], (MKL_INT)81, 0.0, &mat3->data[0], (MKL_INT)9);
  }

  emxFree_real_T(&b_b);
  i10 = y->size[0] * y->size[1];
  i11 = mat3->size[0] * mat3->size[1];
  mat3->size[0] = y->size[0];
  mat3->size[1] = y->size[1];
  emxEnsureCapacity_real_T(mat3, i11);
  loop_ub = i10 - 1;
  for (i10 = 0; i10 <= loop_ub; i10++) {
    mat3->data[i10] = y->data[i10] - mat3->data[i10];
  }

  emxFree_real_T(&y);
  i10 = varargout_1->size[0];
  varargout_1->size[0] = (9 * mat1->size[1] + 9 * mat2->size[1]) + 9 *
    mat3->size[1];
  emxEnsureCapacity_real_T(varargout_1, i10);
  loop_ub = 9 * mat1->size[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10] = mat1->data[i10];
  }

  loop_ub = 9 * mat2->size[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10 + 9 * mat1->size[1]] = mat2->data[i10];
  }

  loop_ub = 9 * mat3->size[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[(i10 + 9 * mat1->size[1]) + 9 * mat2->size[1]] =
      mat3->data[i10];
  }

  emxFree_real_T(&mat3);
  emxFree_real_T(&mat2);
  emxFree_real_T(&mat1);
}

/*
 * Arguments    : const double U_tunableEnvironment[1]
 *                const double V_tunableEnvironment[1]
 *                const double W_tunableEnvironment[1]
 *                const emxArray_real_T *x
 *                emxArray_real_T *varargout_1
 * Return Type  : void
 */
void c___anon_fcn(const double U_tunableEnvironment[1], const double
                  V_tunableEnvironment[1], const double W_tunableEnvironment[1],
                  const emxArray_real_T *x, emxArray_real_T *varargout_1)
{
  double d2;
  int loop_ub;
  emxArray_real_T *b_x;
  int i14;
  int num_idx_1;
  double d3;
  int i15;
  emxArray_real_T *c_x;
  int term1_data_tmp;
  emxArray_real_T *d_x;
  emxArray_real_T *Gamma;
  emxArray_real_T *X;
  emxArray_real_T *H1;
  emxArray_real_T *r3;
  emxArray_real_T *r4;
  emxArray_real_T *r5;
  emxArray_real_T e_x;
  int iv1[2];
  emxArray_real_T f_x;
  int iv2[2];
  int iv3[2];
  int iv4[2];
  int iv5[2];
  int iv6[2];
  int iv7[2];
  int iv8[2];
  emxArray_real_T g_x;
  int iv9[2];
  int n;
  int b_loop_ub;
  emxArray_real_T *An;
  emxArray_real_T *Ap;
  emxArray_real_T *term3;
  int unnamed_idx_2;
  double tmp_data[81];
  int tmp_size[2];
  int r;
  unsigned int s;
  int b_term1_data_tmp;
  double term1_data[81];
  double col_r_data[9];
  double a[9];
  double a_data[9];
  double b_a;
  double b_data[9];
  double d4;

  /* removed cell arrays to save time */
  /* implementation of Theorem 4.3 of Sandia 200dim1 Tech Report */
  /* Z is the tensor representing 3 by 3 matrix multiplication */
  /* U,V,W are matricization functions for the factor matrices */
  /*  for k = 1:10 */
  /*  tic */
  d2 = 9.0 * U_tunableEnvironment[0];
  if (1.0 > d2) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d2;
  }

  emxInit_real_T(&b_x, 1);
  i14 = b_x->size[0];
  b_x->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_x, i14);
  for (i14 = 0; i14 < loop_ub; i14++) {
    b_x->data[i14] = x->data[i14];
  }

  num_idx_1 = (int)U_tunableEnvironment[0];
  d2 = 9.0 * V_tunableEnvironment[0] + 1.0;
  d3 = V_tunableEnvironment[0] * 18.0;
  if (d2 > d3) {
    i14 = 0;
    i15 = 0;
  } else {
    i14 = (int)d2 - 1;
    i15 = (int)d3;
  }

  emxInit_real_T(&c_x, 1);
  term1_data_tmp = c_x->size[0];
  loop_ub = i15 - i14;
  c_x->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c_x, term1_data_tmp);
  for (i15 = 0; i15 < loop_ub; i15++) {
    c_x->data[i15] = x->data[i14 + i15];
  }

  d2 = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (d2 > x->size[0]) {
    i14 = 0;
    i15 = 0;
  } else {
    i14 = (int)d2 - 1;
    i15 = x->size[0];
  }

  emxInit_real_T(&d_x, 1);
  term1_data_tmp = d_x->size[0];
  loop_ub = i15 - i14;
  d_x->size[0] = loop_ub;
  emxEnsureCapacity_real_T(d_x, term1_data_tmp);
  for (i15 = 0; i15 < loop_ub; i15++) {
    d_x->data[i15] = x->data[i14 + i15];
  }

  emxInit_real_T(&Gamma, 3);
  emxInit_real_T(&X, 3);
  emxInit_real_T(&H1, 2);
  emxInit_real_T(&r3, 2);
  emxInit_real_T(&r4, 2);
  emxInit_real_T(&r5, 3);

  /* each cell is the elementwise product of the Gram matrices of factor */
  /* matrices except for the factor matrix of cell index, also known as nth Gamma */
  e_x = *c_x;
  iv1[0] = 9;
  i14 = (int)V_tunableEnvironment[0];
  iv1[1] = i14;
  e_x.size = &iv1[0];
  e_x.numDimensions = 1;
  f_x = *d_x;
  iv2[0] = 9;
  i15 = (int)W_tunableEnvironment[0];
  iv2[1] = i15;
  f_x.size = &iv2[0];
  f_x.numDimensions = 1;
  d___anon_fcn(&e_x, &f_x, r3);
  e_x = *b_x;
  iv3[0] = 9;
  iv3[1] = num_idx_1;
  e_x.size = &iv3[0];
  e_x.numDimensions = 1;
  f_x = *d_x;
  iv4[0] = 9;
  iv4[1] = i15;
  f_x.size = &iv4[0];
  f_x.numDimensions = 1;
  d___anon_fcn(&e_x, &f_x, r4);
  e_x = *b_x;
  iv5[0] = 9;
  iv5[1] = num_idx_1;
  e_x.size = &iv5[0];
  e_x.numDimensions = 1;
  f_x = *c_x;
  iv6[0] = 9;
  iv6[1] = i14;
  f_x.size = &iv6[0];
  f_x.numDimensions = 1;
  d___anon_fcn(&e_x, &f_x, H1);
  cat(r3, r4, H1, Gamma);
  e_x = *b_x;
  iv7[0] = 9;
  iv7[1] = num_idx_1;
  e_x.size = &iv7[0];
  e_x.numDimensions = 1;
  f_x = *c_x;
  iv8[0] = 9;
  iv8[1] = i14;
  f_x.size = &iv8[0];
  f_x.numDimensions = 1;
  g_x = *d_x;
  iv9[0] = 9;
  iv9[1] = i15;
  g_x.size = &iv9[0];
  g_x.numDimensions = 1;
  cat(&e_x, &f_x, &g_x, r5);
  i14 = X->size[0] * X->size[1] * X->size[2];
  X->size[0] = r5->size[0];
  X->size[1] = r5->size[1];
  X->size[2] = 3;
  emxEnsureCapacity_real_T(X, i14);
  loop_ub = r5->size[0] * r5->size[1] * r5->size[2];
  for (i14 = 0; i14 < loop_ub; i14++) {
    X->data[i14] = r5->data[i14];
  }

  emxFree_real_T(&r5);
  i14 = varargout_1->size[0] * varargout_1->size[1];
  i15 = (int)U_tunableEnvironment[0] * 3 * 9;
  varargout_1->size[0] = i15;
  varargout_1->size[1] = i15;
  emxEnsureCapacity_real_T(varargout_1, i14);
  loop_ub = i15 * i15;
  for (i14 = 0; i14 < loop_ub; i14++) {
    varargout_1->data[i14] = 0.0;
  }

  /* when n(matrix) is the same but r (columns) are different */
  /* block diagonal matrices on the diagonal of H */
  /* accomplished by expanding each entry of Gamma to 9 by 9 diagnal using */
  /* kronecker product */
  /* upper triangle to save computation */
  /* saved 1/3 time */
  for (n = 0; n < 3; n++) {
    loop_ub = Gamma->size[0];
    b_loop_ub = Gamma->size[1];
    i14 = r3->size[0] * r3->size[1];
    r3->size[0] = loop_ub;
    r3->size[1] = b_loop_ub;
    emxEnsureCapacity_real_T(r3, i14);
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        r3->data[i15 + r3->size[0] * i14] = Gamma->data[(i15 + Gamma->size[0] *
          i14) + Gamma->size[0] * Gamma->size[1] * n];
      }
    }

    triu(r3);
    eye(tmp_data, tmp_size);
    kron(r3, tmp_data, H1);
    s = 1U + (unsigned int)n * H1->size[0];
    d2 = (1.0 + (double)n) * (double)H1->size[0];
    if (s > d2) {
      i14 = 0;
    } else {
      i14 = (int)s - 1;
    }

    s = 1U + (unsigned int)n * H1->size[0];
    d2 = (1.0 + (double)n) * (double)H1->size[0];
    if (s > d2) {
      i15 = 0;
    } else {
      i15 = (int)s - 1;
    }

    loop_ub = H1->size[1];
    for (term1_data_tmp = 0; term1_data_tmp < loop_ub; term1_data_tmp++) {
      b_loop_ub = H1->size[0];
      for (b_term1_data_tmp = 0; b_term1_data_tmp < b_loop_ub; b_term1_data_tmp
           ++) {
        varargout_1->data[(i14 + b_term1_data_tmp) + varargout_1->size[0] * (i15
          + term1_data_tmp)] = H1->data[b_term1_data_tmp + H1->size[0] *
          term1_data_tmp];
      }
    }
  }

  emxFree_real_T(&H1);
  emxFree_real_T(&Gamma);

  /* for the next two cases we only find the upper triangle part to avoid error */
  /* when n are different and r is the same */
  i14 = (int)U_tunableEnvironment[0];
  emxInit_real_T(&An, 2);
  emxInit_real_T(&Ap, 2);
  emxInit_real_T(&term3, 3);
  if (0 <= (int)U_tunableEnvironment[0] - 1) {
    unnamed_idx_2 = num_idx_1;
  }

  for (r = 0; r < i14; r++) {
    /* case 1 */
    loop_ub = X->size[1];
    i15 = An->size[0] * An->size[1];
    An->size[0] = 9;
    An->size[1] = loop_ub;
    emxEnsureCapacity_real_T(An, i15);
    for (i15 = 0; i15 < loop_ub; i15++) {
      for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
        b_term1_data_tmp = term1_data_tmp + 9 * i15;
        An->data[b_term1_data_tmp] = X->data[b_term1_data_tmp];
      }
    }

    loop_ub = X->size[1];
    i15 = Ap->size[0] * Ap->size[1];
    Ap->size[0] = 9;
    Ap->size[1] = loop_ub;
    emxEnsureCapacity_real_T(Ap, i15);
    for (i15 = 0; i15 < loop_ub; i15++) {
      for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
        b_term1_data_tmp = term1_data_tmp + 9 * i15;
        Ap->data[b_term1_data_tmp] = X->data[b_term1_data_tmp + 9 * X->size[1]];
      }
    }

    memset(&term1_data[0], 0, 81U * sizeof(double));

    /* remaining matrix's rth column */
    for (i15 = 0; i15 < 9; i15++) {
      col_r_data[i15] = d_x->data[i15 + 9 * r];
    }

    /* term1 is I1 by I2 matrix, i is i1, j is i2 */
    /* term1 = ttv(Z,col_r,3); equivalent but slower */
    /*      for i = 1:dim1 */
    /*         term1(i,:) = reshape(Z(i,:,:),[dim2,dim3]) * col_r; */
    /*      end */
    /* hardcoded ttv(Z,col_r),saves 4x time */
    for (i15 = 0; i15 < 3; i15++) {
      a[3 * i15] = col_r_data[3 * i15];
      n = 1 + 3 * i15;
      a[n] = col_r_data[n];
      b_loop_ub = 2 + 3 * i15;
      a[b_loop_ub] = col_r_data[b_loop_ub];
      term1_data_tmp = 9 * (3 * i15);
      term1_data[term1_data_tmp] = a[3 * i15];
      term1_data[1 + term1_data_tmp] = a[n];
      term1_data[2 + term1_data_tmp] = a[b_loop_ub];
    }

    for (i15 = 0; i15 < 3; i15++) {
      term1_data_tmp = 1 + 3 * i15;
      loop_ub = 9 * term1_data_tmp;
      term1_data[loop_ub + 3] = a[3 * i15];
      term1_data[loop_ub + 4] = a[term1_data_tmp];
      term1_data[loop_ub + 5] = a[2 + 3 * i15];
    }

    for (i15 = 0; i15 < 3; i15++) {
      n = 2 + 3 * i15;
      term1_data_tmp = 9 * n;
      term1_data[term1_data_tmp + 6] = a[3 * i15];
      term1_data[term1_data_tmp + 7] = a[1 + 3 * i15];
      term1_data[term1_data_tmp + 8] = a[n];
    }

    /* psi_rl is the inner product of rth,lth col of remaining matrix */
    /* combine half of 2nd term and 3rd term for simplicity                 */
    i15 = term3->size[0] * term3->size[1] * term3->size[2];
    term3->size[0] = 9;
    term3->size[1] = 9;
    term3->size[2] = unnamed_idx_2;
    emxEnsureCapacity_real_T(term3, i15);
    for (n = 0; n < unnamed_idx_2; n++) {
      for (i15 = 0; i15 < 9; i15++) {
        a_data[i15] = col_r_data[i15];
        b_data[i15] = d_x->data[i15 + 9 * n];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (i15 = 0; i15 < 9; i15++) {
        b_loop_ub = i15 + 9 * n;
        b_data[i15] = b_a * An->data[b_loop_ub];
        a_data[i15] = Ap->data[b_loop_ub];
      }

      for (i15 = 0; i15 < 9; i15++) {
        for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
          term3->data[(i15 + 9 * term1_data_tmp) + 81 * n] = b_data[i15] *
            a_data[term1_data_tmp];
        }
      }
    }

    memcpy(&a_data[0], &col_r_data[0], 9U * sizeof(double));
    b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &col_r_data[0],
                     (MKL_INT)1);
    d2 = ((1.0 + (double)r) - 1.0) * 9.0 + 1.0;
    if (d2 > (1.0 + (double)r) * 9.0) {
      i15 = 0;
    } else {
      i15 = (int)d2 - 1;
    }

    d3 = ((double)(((unsigned int)r + num_idx_1) + 1U) - 1.0) * 9.0 + 1.0;
    if (d3 > (double)(((unsigned int)r + num_idx_1) + 1U) * 9.0) {
      term1_data_tmp = 0;
    } else {
      term1_data_tmp = (int)d3 - 1;
    }

    sum(term3, tmp_data, tmp_size);
    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      b_loop_ub = b_term1_data_tmp + 9 * r;
      b_data[b_term1_data_tmp] = b_a * An->data[b_loop_ub];
      a_data[b_term1_data_tmp] = Ap->data[b_loop_ub];
    }

    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
        n = b_term1_data_tmp + 9 * b_loop_ub;
        varargout_1->data[(i15 + b_term1_data_tmp) + varargout_1->size[0] *
          (term1_data_tmp + b_loop_ub)] = (-term1_data[n] +
          b_data[b_term1_data_tmp] * a_data[b_loop_ub]) + tmp_data[n];
      }
    }

    /* case 2 */
    /* n=1; */
    loop_ub = X->size[1];
    i15 = Ap->size[0] * Ap->size[1];
    Ap->size[0] = 9;
    Ap->size[1] = loop_ub;
    emxEnsureCapacity_real_T(Ap, i15);
    for (i15 = 0; i15 < loop_ub; i15++) {
      for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
        b_term1_data_tmp = term1_data_tmp + 9 * i15;
        Ap->data[b_term1_data_tmp] = X->data[b_term1_data_tmp + ((9 * X->size[1])
          << 1)];
      }
    }

    memset(&term1_data[0], 0, 81U * sizeof(double));
    for (i15 = 0; i15 < 9; i15++) {
      col_r_data[i15] = c_x->data[i15 + 9 * r];
    }

    /*      for j = 1:dim3 */
    /*         term1(:,j) = reshape(Z(:,:,j),[dim1,dim2]) * col_r; */
    /*      end */
    for (i15 = 0; i15 < 3; i15++) {
      a[3 * i15] = col_r_data[3 * i15];
      n = 1 + 3 * i15;
      a[n] = col_r_data[n];
      b_loop_ub = 2 + 3 * i15;
      a[b_loop_ub] = col_r_data[b_loop_ub];
      d4 = a[3 * i15];
      term1_data_tmp = 9 * (3 * i15);
      term1_data[term1_data_tmp] = d4;
      loop_ub = 9 * n;
      term1_data[loop_ub + 1] = d4;
      b_term1_data_tmp = 9 * b_loop_ub;
      term1_data[b_term1_data_tmp + 2] = d4;
      term1_data[3 + term1_data_tmp] = a[n];
      term1_data[loop_ub + 4] = a[n];
      term1_data[b_term1_data_tmp + 5] = a[n];
      term1_data[6 + term1_data_tmp] = a[b_loop_ub];
      term1_data[loop_ub + 7] = a[b_loop_ub];
      term1_data[b_term1_data_tmp + 8] = a[b_loop_ub];
    }

    i15 = term3->size[0] * term3->size[1] * term3->size[2];
    term3->size[0] = 9;
    term3->size[1] = 9;
    term3->size[2] = unnamed_idx_2;
    emxEnsureCapacity_real_T(term3, i15);
    for (n = 0; n < unnamed_idx_2; n++) {
      for (i15 = 0; i15 < 9; i15++) {
        a_data[i15] = col_r_data[i15];
        b_data[i15] = c_x->data[i15 + 9 * n];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (i15 = 0; i15 < 9; i15++) {
        b_loop_ub = i15 + 9 * n;
        b_data[i15] = b_a * An->data[b_loop_ub];
        a_data[i15] = Ap->data[b_loop_ub];
      }

      for (i15 = 0; i15 < 9; i15++) {
        for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
          term3->data[(i15 + 9 * term1_data_tmp) + 81 * n] = b_data[i15] *
            a_data[term1_data_tmp];
        }
      }
    }

    memcpy(&a_data[0], &col_r_data[0], 9U * sizeof(double));
    b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &col_r_data[0],
                     (MKL_INT)1);
    if (d2 > (1.0 + (double)r) * 9.0) {
      i15 = 0;
    } else {
      i15 = (int)d2 - 1;
    }

    d2 = (((1.0 + (double)r) + (double)num_idx_1 * 2.0) - 1.0) * 9.0 + 1.0;
    if (d2 > ((1.0 + (double)r) + (double)num_idx_1 * 2.0) * 9.0) {
      term1_data_tmp = 0;
    } else {
      term1_data_tmp = (int)d2 - 1;
    }

    sum(term3, tmp_data, tmp_size);
    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      b_loop_ub = b_term1_data_tmp + 9 * r;
      b_data[b_term1_data_tmp] = b_a * An->data[b_loop_ub];
      a_data[b_term1_data_tmp] = Ap->data[b_loop_ub];
    }

    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
        n = b_term1_data_tmp + 9 * b_loop_ub;
        varargout_1->data[(i15 + b_term1_data_tmp) + varargout_1->size[0] *
          (term1_data_tmp + b_loop_ub)] = (-term1_data[n] +
          b_data[b_term1_data_tmp] * a_data[b_loop_ub]) + tmp_data[n];
      }
    }

    /* case 3 */
    /* p=3; */
    loop_ub = X->size[1];
    i15 = An->size[0] * An->size[1];
    An->size[0] = 9;
    An->size[1] = loop_ub;
    emxEnsureCapacity_real_T(An, i15);
    for (i15 = 0; i15 < loop_ub; i15++) {
      for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
        b_term1_data_tmp = term1_data_tmp + 9 * i15;
        An->data[b_term1_data_tmp] = X->data[b_term1_data_tmp + 9 * X->size[1]];
      }
    }

    memset(&term1_data[0], 0, 81U * sizeof(double));
    for (i15 = 0; i15 < 9; i15++) {
      col_r_data[i15] = b_x->data[i15 + 9 * r];
    }

    /*      for j = 1:dim3 */
    /*         term1(:,j) =  col_r.' * reshape(Z(:,:,j),[dim1,dim2]); */
    /*      end */
    a[0] = col_r_data[0];
    a[3] = col_r_data[1];
    a[6] = col_r_data[2];
    a[1] = col_r_data[3];
    a[4] = col_r_data[4];
    a[7] = col_r_data[5];
    a[2] = col_r_data[6];
    a[5] = col_r_data[7];
    a[8] = col_r_data[8];
    for (i15 = 0; i15 < 3; i15++) {
      term1_data[9 * i15] = a[3 * i15];
      term1_data[1 + 9 * i15] = a[1 + 3 * i15];
      term1_data[2 + 9 * i15] = a[2 + 3 * i15];
    }

    for (i15 = 0; i15 < 3; i15++) {
      term1_data_tmp = 9 * (3 + i15);
      term1_data[term1_data_tmp + 3] = a[3 * i15];
      term1_data[term1_data_tmp + 4] = a[1 + 3 * i15];
      term1_data[term1_data_tmp + 5] = a[2 + 3 * i15];
    }

    for (i15 = 0; i15 < 3; i15++) {
      term1_data_tmp = 9 * (6 + i15);
      term1_data[term1_data_tmp + 6] = a[3 * i15];
      term1_data[term1_data_tmp + 7] = a[1 + 3 * i15];
      term1_data[term1_data_tmp + 8] = a[2 + 3 * i15];
    }

    i15 = term3->size[0] * term3->size[1] * term3->size[2];
    term3->size[0] = 9;
    term3->size[1] = 9;
    term3->size[2] = unnamed_idx_2;
    emxEnsureCapacity_real_T(term3, i15);
    for (n = 0; n < unnamed_idx_2; n++) {
      for (i15 = 0; i15 < 9; i15++) {
        a_data[i15] = col_r_data[i15];
        b_data[i15] = b_x->data[i15 + 9 * n];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (i15 = 0; i15 < 9; i15++) {
        b_loop_ub = i15 + 9 * n;
        b_data[i15] = b_a * An->data[b_loop_ub];
        a_data[i15] = Ap->data[b_loop_ub];
      }

      for (i15 = 0; i15 < 9; i15++) {
        for (term1_data_tmp = 0; term1_data_tmp < 9; term1_data_tmp++) {
          term3->data[(i15 + 9 * term1_data_tmp) + 81 * n] = b_data[i15] *
            a_data[term1_data_tmp];
        }
      }
    }

    /* term2 = col_r.'*col_r*An(:,r)*Ap(:,r).' */
    /* each term is a nxn matrix, where n is dim1 */
    memcpy(&a_data[0], &col_r_data[0], 9U * sizeof(double));
    b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &col_r_data[0],
                     (MKL_INT)1);
    if (d3 > (double)(((unsigned int)r + num_idx_1) + 1U) * 9.0) {
      i15 = 0;
    } else {
      i15 = (int)d3 - 1;
    }

    if (d2 > ((1.0 + (double)r) + (double)num_idx_1 * 2.0) * 9.0) {
      term1_data_tmp = 0;
    } else {
      term1_data_tmp = (int)d2 - 1;
    }

    sum(term3, tmp_data, tmp_size);
    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      b_loop_ub = b_term1_data_tmp + 9 * r;
      b_data[b_term1_data_tmp] = b_a * An->data[b_loop_ub];
      a_data[b_term1_data_tmp] = Ap->data[b_loop_ub];
    }

    for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
      for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
        n = b_term1_data_tmp + 9 * b_loop_ub;
        varargout_1->data[(i15 + b_term1_data_tmp) + varargout_1->size[0] *
          (term1_data_tmp + b_loop_ub)] = (-term1_data[n] +
          b_data[b_term1_data_tmp] * a_data[b_loop_ub]) + tmp_data[n];
      }
    }
  }

  emxFree_real_T(&term3);

  /* both n/p and r/s pairs are different */
  i14 = (int)U_tunableEnvironment[0];
  for (r = 0; r < i14; r++) {
    i15 = num_idx_1 - r;
    for (n = 0; n <= i15 - 2; n++) {
      s = ((unsigned int)r + n) + 2U;
      loop_ub = X->size[1];
      term1_data_tmp = An->size[0] * An->size[1];
      An->size[0] = 9;
      An->size[1] = loop_ub;
      emxEnsureCapacity_real_T(An, term1_data_tmp);
      for (term1_data_tmp = 0; term1_data_tmp < loop_ub; term1_data_tmp++) {
        for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
          unnamed_idx_2 = b_term1_data_tmp + 9 * term1_data_tmp;
          An->data[unnamed_idx_2] = X->data[unnamed_idx_2];
        }
      }

      loop_ub = X->size[1];
      term1_data_tmp = Ap->size[0] * Ap->size[1];
      Ap->size[0] = 9;
      Ap->size[1] = loop_ub;
      emxEnsureCapacity_real_T(Ap, term1_data_tmp);
      for (term1_data_tmp = 0; term1_data_tmp < loop_ub; term1_data_tmp++) {
        for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
          unnamed_idx_2 = b_term1_data_tmp + 9 * term1_data_tmp;
          Ap->data[unnamed_idx_2] = X->data[unnamed_idx_2 + 9 * X->size[1]];
        }
      }

      d2 = ((1.0 + (double)r) - 1.0) * 9.0 + 1.0;
      if (d2 > (1.0 + (double)r) * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d2 - 1;
      }

      d3 = (((double)s + (double)num_idx_1) - 1.0) * 9.0 + 1.0;
      if (d3 > ((double)s + (double)num_idx_1) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d3 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = d_x->data[unnamed_idx_2 + 9 * r];
        b_data[unnamed_idx_2] = d_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * r];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }

      d3 = ((double)s - 1.0) * 9.0 + 1.0;
      if (d3 > (double)s * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d3 - 1;
      }

      d4 = ((double)(((unsigned int)r + num_idx_1) + 1U) - 1.0) * 9.0 + 1.0;
      if (d4 > (double)(((unsigned int)r + num_idx_1) + 1U) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d4 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = d_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        b_data[unnamed_idx_2] = d_x->data[unnamed_idx_2 + 9 * r];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * r];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }

      loop_ub = X->size[1];
      term1_data_tmp = Ap->size[0] * Ap->size[1];
      Ap->size[0] = 9;
      Ap->size[1] = loop_ub;
      emxEnsureCapacity_real_T(Ap, term1_data_tmp);
      for (term1_data_tmp = 0; term1_data_tmp < loop_ub; term1_data_tmp++) {
        for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
          unnamed_idx_2 = b_term1_data_tmp + 9 * term1_data_tmp;
          Ap->data[unnamed_idx_2] = X->data[unnamed_idx_2 + ((9 * X->size[1]) <<
            1)];
        }
      }

      if (d2 > (1.0 + (double)r) * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d2 - 1;
      }

      d2 = (((double)s + (double)num_idx_1 * 2.0) - 1.0) * 9.0 + 1.0;
      if (d2 > ((double)s + (double)num_idx_1 * 2.0) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d2 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = c_x->data[unnamed_idx_2 + 9 * r];
        b_data[unnamed_idx_2] = c_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * r];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }

      if (d3 > (double)s * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d3 - 1;
      }

      d3 = (((1.0 + (double)r) + (double)num_idx_1 * 2.0) - 1.0) * 9.0 + 1.0;
      if (d3 > ((1.0 + (double)r) + (double)num_idx_1 * 2.0) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d3 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = c_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        b_data[unnamed_idx_2] = c_x->data[unnamed_idx_2 + 9 * r];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * r];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }

      loop_ub = X->size[1];
      term1_data_tmp = An->size[0] * An->size[1];
      An->size[0] = 9;
      An->size[1] = loop_ub;
      emxEnsureCapacity_real_T(An, term1_data_tmp);
      for (term1_data_tmp = 0; term1_data_tmp < loop_ub; term1_data_tmp++) {
        for (b_term1_data_tmp = 0; b_term1_data_tmp < 9; b_term1_data_tmp++) {
          unnamed_idx_2 = b_term1_data_tmp + 9 * term1_data_tmp;
          An->data[unnamed_idx_2] = X->data[unnamed_idx_2 + 9 * X->size[1]];
        }
      }

      /* psi_rs is the inner product of rth,sth col of remaining matrix */
      if (d4 > (double)(((unsigned int)r + num_idx_1) + 1U) * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d4 - 1;
      }

      if (d2 > ((double)s + (double)num_idx_1 * 2.0) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d2 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = b_x->data[unnamed_idx_2 + 9 * r];
        b_data[unnamed_idx_2] = b_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * r];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }

      d2 = ((double)(s + num_idx_1) - 1.0) * 9.0 + 1.0;
      if (d2 > (double)(s + num_idx_1) * 9.0) {
        term1_data_tmp = 0;
      } else {
        term1_data_tmp = (int)d2 - 1;
      }

      if (d3 > ((1.0 + (double)r) + (double)num_idx_1 * 2.0) * 9.0) {
        b_term1_data_tmp = 0;
      } else {
        b_term1_data_tmp = (int)d3 - 1;
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        a_data[unnamed_idx_2] = b_x->data[unnamed_idx_2 + 9 * ((int)s - 1)];
        b_data[unnamed_idx_2] = b_x->data[unnamed_idx_2 + 9 * r];
      }

      b_a = cblas_ddot((MKL_INT)9, &a_data[0], (MKL_INT)1, &b_data[0], (MKL_INT)
                       1);
      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        b_data[unnamed_idx_2] = b_a * An->data[unnamed_idx_2 + 9 * r];
        a_data[unnamed_idx_2] = Ap->data[unnamed_idx_2 + 9 * ((int)s - 1)];
      }

      for (unnamed_idx_2 = 0; unnamed_idx_2 < 9; unnamed_idx_2++) {
        for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
          varargout_1->data[(term1_data_tmp + unnamed_idx_2) + varargout_1->
            size[0] * (b_term1_data_tmp + b_loop_ub)] = b_data[unnamed_idx_2] *
            a_data[b_loop_ub];
        }
      }
    }
  }

  emxFree_real_T(&d_x);
  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  emxFree_real_T(&Ap);
  emxFree_real_T(&An);
  emxFree_real_T(&X);
  i14 = r3->size[0] * r3->size[1];
  r3->size[0] = varargout_1->size[0];
  r3->size[1] = varargout_1->size[1];
  emxEnsureCapacity_real_T(r3, i14);
  loop_ub = varargout_1->size[0] * varargout_1->size[1];
  for (i14 = 0; i14 < loop_ub; i14++) {
    r3->data[i14] = varargout_1->data[i14];
  }

  triu(r3);
  i14 = r4->size[0] * r4->size[1];
  r4->size[0] = varargout_1->size[0];
  r4->size[1] = varargout_1->size[1];
  emxEnsureCapacity_real_T(r4, i14);
  loop_ub = varargout_1->size[0] * varargout_1->size[1];
  for (i14 = 0; i14 < loop_ub; i14++) {
    r4->data[i14] = varargout_1->data[i14];
  }

  b_triu(r4);
  i14 = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = r3->size[0];
  varargout_1->size[1] = r3->size[1];
  emxEnsureCapacity_real_T(varargout_1, i14);
  loop_ub = r3->size[1];
  for (i14 = 0; i14 < loop_ub; i14++) {
    b_loop_ub = r3->size[0];
    for (i15 = 0; i15 < b_loop_ub; i15++) {
      varargout_1->data[i15 + varargout_1->size[0] * i14] = r3->data[i15 +
        r3->size[0] * i14] + r4->data[i14 + r4->size[0] * i15];
    }
  }

  emxFree_real_T(&r4);
  emxFree_real_T(&r3);

  /*  toc */
  /*  end */
}

/*
 * USAGE: cubicRegScript(i,num,rank,t,R,k,errThd,maxIts,outputDir)
 * Arguments    : double i
 *                double num
 *                double rank
 *                double k
 *                double errThd
 *                double maxIts
 *                const char outputDir[10]
 * Return Type  : void
 */
void cubicRegScript(double i, double num, double rank, double k, double errThd,
                    double maxIts, const char outputDir[10])
{
  double a;
  double U_tunableEnvironment[1];
  double V_tunableEnvironment[1];
  double W_tunableEnvironment[1];
  d_coder_internal_anonymous_func errFcn_tunableEnvironment[1];
  int i0;
  emxArray_real_T *x0;
  emxArray_real_T *errorHistory;
  emxArray_real_T *x;
  emxArray_boolean_T *idx;
  emxArray_char_T *charStr;
  int j;
  double b_j;
  unsigned int seed;
  int k0;
  int i1;
  char validatedHoleFilling_tmp[11];
  double d0;
  char b_validatedHoleFilling_tmp[11];
  signed char fileid;
  int nxin;
  int b_k;
  int nxout;
  a = (i - 1.0) * num + 1.0;

  /* matricize u, v, w */
  U_tunableEnvironment[0] = rank;
  V_tunableEnvironment[0] = rank;
  W_tunableEnvironment[0] = rank;

  /*  f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1); */
  /*  grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2); */
  /*  H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3); */
  errFcn_tunableEnvironment[0].tunableEnvironment.f1.tunableEnvironment[0] =
    rank;
  errFcn_tunableEnvironment[0].tunableEnvironment.f2.tunableEnvironment[0] =
    rank;
  errFcn_tunableEnvironment[0].tunableEnvironment.f3.tunableEnvironment[0] =
    rank;
  i0 = (int)(i * num + (1.0 - a));
  emxInit_real_T(&x0, 1);
  emxInit_real_T(&errorHistory, 1);
  emxInit_real_T(&x, 1);
  emxInit_boolean_T(&idx, 1);
  emxInit_char_T(&charStr, 2);
  for (j = 0; j < i0; j++) {
    b_j = a + (double)j;
    if (b_j + 3.3E+6 < 4.294967296E+9) {
      if (b_j + 3.3E+6 >= 0.0) {
        seed = (unsigned int)(b_j + 3.3E+6);
      } else {
        seed = 0U;
      }
    } else if (b_j + 3.3E+6 >= 4.294967296E+9) {
      seed = MAX_uint32_T;
    } else {
      seed = 0U;
    }

    if (seed == 0U) {
      seed = 5489U;
    }

    state[0] = seed;
    for (k0 = 0; k0 < 623; k0++) {
      seed = ((seed ^ seed >> 30U) * 1812433253U + k0) + 1U;
      state[k0 + 1] = seed;
    }

    state[624] = 624U;

    /* each subjob has a unique ID j and is used as seed */
    randn(27.0 * rank, x0);
    i1 = x0->size[0];
    emxEnsureCapacity_real_T(x0, i1);
    k0 = x0->size[0];
    for (i1 = 0; i1 < k0; i1++) {
      x0->data[i1] *= k;
    }

    printf("The first entry of x0 is %g.\n", x0->data[0]);
    fflush(stdout);
    for (i1 = 0; i1 < 10; i1++) {
      validatedHoleFilling_tmp[i1] = outputDir[i1];
    }

    validatedHoleFilling_tmp[10] = '\x00';
    for (i1 = 0; i1 < 11; i1++) {
      b_validatedHoleFilling_tmp[i1] = validatedHoleFilling_tmp[i1];
    }

    d0 = rt_roundd_snf(rank);
    if (d0 < 128.0) {
      if (d0 >= -128.0) {
        fileid = (signed char)d0;
      } else {
        fileid = MIN_int8_T;
      }
    } else if (d0 >= 128.0) {
      fileid = MAX_int8_T;
    } else {
      fileid = 0;
    }

    printf("%s/rank%d_k%g_errTol%g_maxIts%g.bin\n", b_validatedHoleFilling_tmp,
           fileid, k, errThd, maxIts);
    fflush(stdout);
    i1 = x->size[0];
    x->size[0] = x0->size[0];
    emxEnsureCapacity_real_T(x, i1);
    k0 = x0->size[0];
    for (i1 = 0; i1 < k0; i1++) {
      x->data[i1] = x0->data[i1];
    }

    cubicReg4Coder(U_tunableEnvironment, V_tunableEnvironment,
                   W_tunableEnvironment, U_tunableEnvironment,
                   V_tunableEnvironment, W_tunableEnvironment,
                   U_tunableEnvironment, V_tunableEnvironment,
                   W_tunableEnvironment, x, errFcn_tunableEnvironment, errThd,
                   maxIts, errorHistory);
    i1 = idx->size[0];
    idx->size[0] = errorHistory->size[0];
    emxEnsureCapacity_boolean_T(idx, i1);
    k0 = errorHistory->size[0];
    for (i1 = 0; i1 < k0; i1++) {
      idx->data[i1] = (errorHistory->data[i1] == 0.0);
    }

    nxin = errorHistory->size[0];
    k0 = 0;
    i1 = idx->size[0];
    for (b_k = 0; b_k < i1; b_k++) {
      k0 += idx->data[b_k];
    }

    nxout = errorHistory->size[0] - k0;
    k0 = -1;
    for (b_k = 0; b_k < nxin; b_k++) {
      if ((b_k + 1 > idx->size[0]) || (!idx->data[b_k])) {
        k0++;
        errorHistory->data[k0] = errorHistory->data[b_k];
      }
    }

    if (1 > nxout) {
      errorHistory->size[0] = 0;
    } else {
      i1 = errorHistory->size[0];
      errorHistory->size[0] = nxout;
      emxEnsureCapacity_real_T(errorHistory, i1);
    }

    if (errorHistory->data[errorHistory->size[0] - 1] <= 1.0E-8) {
      if (d0 < 128.0) {
        if (d0 >= -128.0) {
          fileid = (signed char)d0;
        } else {
          fileid = MIN_int8_T;
        }
      } else if (d0 >= 128.0) {
        fileid = MAX_int8_T;
      } else {
        fileid = 0;
      }

      d0 = rt_roundd_snf(b_j);
      if (d0 < 2.147483648E+9) {
        if (d0 >= -2.147483648E+9) {
          k0 = (int)d0;
        } else {
          k0 = MIN_int32_T;
        }
      } else if (d0 >= 2.147483648E+9) {
        k0 = MAX_int32_T;
      } else {
        k0 = 0;
      }

      for (i1 = 0; i1 < 11; i1++) {
        b_validatedHoleFilling_tmp[i1] = validatedHoleFilling_tmp[i1];
      }

      nxout = (int)snprintf(NULL, 0, "%s/rank%d_k%g_errTol%g_maxIts%g_%d.bin",
                            b_validatedHoleFilling_tmp, fileid, k, errThd,
                            maxIts, k0);
      i1 = charStr->size[0] * charStr->size[1];
      charStr->size[0] = 1;
      charStr->size[1] = nxout + 1;
      emxEnsureCapacity_char_T(charStr, i1);
      snprintf(&charStr->data[0], (size_t)(nxout + 1),
               "%s/rank%d_k%g_errTol%g_maxIts%g_%d.bin",
               validatedHoleFilling_tmp, fileid, k, errThd, maxIts, k0);
      if (1 > nxout) {
        charStr->size[1] = 0;
      } else {
        i1 = charStr->size[0] * charStr->size[1];
        charStr->size[1] = nxout;
        emxEnsureCapacity_char_T(charStr, i1);
      }

      /* save data as .mat using parsave */
      /* save(file,'x0','x','errorHistory'); */
      fileid = cfopen(charStr, "wb");
      b_fwrite(fileid, x0);
      b_fwrite(fileid, x);
      b_fwrite(fileid, errorHistory);
      b_fclose(fileid);
      printf("The last entry of errorHistory is %g.\n", errorHistory->
             data[errorHistory->size[0] - 1]);
      fflush(stdout);

      /*          figureDir = string(outputDir) + '/figures'; */
      /*          mkdir(figureDir); */
      /*          figurename = sprintf("%s/rank%d_k%g_errTol%g_maxIts%g_%d.png",figureDir,rank,k,errThd,maxIts,j); */
      /*          h=figure; */
      /*          set(h,'visible','off') */
      /*          semilogy(errorHistory); */
      /*          xlabel('iterations'); */
      /*          ylabel('f(x)'); */
      /*          saveas(h,figurename,'png'); */
    }
  }

  emxFree_char_T(&charStr);
  emxFree_boolean_T(&idx);
  emxFree_real_T(&x);
  emxFree_real_T(&errorHistory);
  emxFree_real_T(&x0);
}

/*
 * File trailer for cubicRegScript.c
 *
 * [EOF]
 */
