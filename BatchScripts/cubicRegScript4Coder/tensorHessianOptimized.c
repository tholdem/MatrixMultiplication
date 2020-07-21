/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: tensorHessianOptimized.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "tensorHessianOptimized.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "mkl_cblas.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *varargout_1
 * Return Type  : void
 */
void d___anon_fcn(const emxArray_real_T *A, const emxArray_real_T *B,
                  emxArray_real_T *varargout_1)
{
  emxArray_real_T *a;
  int i16;
  emxArray_real_T *b;
  int loop_ub;
  int i17;
  emxArray_real_T *r4;
  emxInit_real_T(&a, 2);
  i16 = a->size[0] * a->size[1];
  a->size[0] = A->size[1];
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i16);
  for (i16 = 0; i16 < 9; i16++) {
    loop_ub = A->size[1];
    for (i17 = 0; i17 < loop_ub; i17++) {
      a->data[i17 + a->size[0] * i16] = A->data[i16 + 9 * i17];
    }
  }

  emxInit_real_T(&b, 2);
  i16 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = A->size[1];
  emxEnsureCapacity_real_T(b, i16);
  loop_ub = A->size[0] * A->size[1];
  for (i16 = 0; i16 < loop_ub; i16++) {
    b->data[i16] = A->data[i16];
  }

  if ((a->size[0] == 0) || (A->size[1] == 0)) {
    i16 = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = a->size[0];
    varargout_1->size[1] = A->size[1];
    emxEnsureCapacity_real_T(varargout_1, i16);
    loop_ub = a->size[0] * A->size[1];
    for (i16 = 0; i16 < loop_ub; i16++) {
      varargout_1->data[i16] = 0.0;
    }
  } else {
    i16 = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = a->size[0];
    varargout_1->size[1] = A->size[1];
    emxEnsureCapacity_real_T(varargout_1, i16);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                (MKL_INT)A->size[1], (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)
                a->size[0], &b->data[0], (MKL_INT)9, 0.0, &varargout_1->data[0],
                (MKL_INT)a->size[0]);
  }

  i16 = a->size[0] * a->size[1];
  a->size[0] = B->size[1];
  a->size[1] = 9;
  emxEnsureCapacity_real_T(a, i16);
  for (i16 = 0; i16 < 9; i16++) {
    loop_ub = B->size[1];
    for (i17 = 0; i17 < loop_ub; i17++) {
      a->data[i17 + a->size[0] * i16] = B->data[i16 + 9 * i17];
    }
  }

  i16 = b->size[0] * b->size[1];
  b->size[0] = 9;
  b->size[1] = B->size[1];
  emxEnsureCapacity_real_T(b, i16);
  loop_ub = B->size[0] * B->size[1];
  for (i16 = 0; i16 < loop_ub; i16++) {
    b->data[i16] = B->data[i16];
  }

  emxInit_real_T(&r4, 2);
  if ((a->size[0] == 0) || (B->size[1] == 0)) {
    i16 = r4->size[0] * r4->size[1];
    r4->size[0] = a->size[0];
    r4->size[1] = B->size[1];
    emxEnsureCapacity_real_T(r4, i16);
    loop_ub = a->size[0] * B->size[1];
    for (i16 = 0; i16 < loop_ub; i16++) {
      r4->data[i16] = 0.0;
    }
  } else {
    i16 = r4->size[0] * r4->size[1];
    r4->size[0] = a->size[0];
    r4->size[1] = B->size[1];
    emxEnsureCapacity_real_T(r4, i16);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)a->size[0],
                (MKL_INT)B->size[1], (MKL_INT)9, 1.0, &a->data[0], (MKL_INT)
                a->size[0], &b->data[0], (MKL_INT)9, 0.0, &r4->data[0], (MKL_INT)
                a->size[0]);
  }

  emxFree_real_T(&b);
  emxFree_real_T(&a);
  i16 = varargout_1->size[0] * varargout_1->size[1];
  i17 = varargout_1->size[0] * varargout_1->size[1];
  emxEnsureCapacity_real_T(varargout_1, i17);
  loop_ub = i16 - 1;
  for (i16 = 0; i16 <= loop_ub; i16++) {
    varargout_1->data[i16] *= r4->data[i16];
  }

  emxFree_real_T(&r4);
}

/*
 * File trailer for tensorHessianOptimized.c
 *
 * [EOF]
 */
