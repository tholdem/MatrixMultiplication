/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ktensorOptimized.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "ktensorOptimized.h"
#include "cubicRegScript_emxutil.h"
#include "khatriraoOptimized.h"
#include <stdio.h>
#include "mkl_cblas.h"

/* Function Definitions */

/*
 * sum of columnwise outer products
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                double D[729]
 * Return Type  : void
 */
void ktensorOptimized(const emxArray_real_T *A, const emxArray_real_T *B, const
                      emxArray_real_T *C, double D[729])
{
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *y;
  emxArray_real_T *r0;
  int i6;
  int loop_ub;
  int i7;
  int b_loop_ub;
  int i8;
  emxInit_real_T(&a, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&r0, 2);
  if ((A->size[1] != B->size[1]) || (A->size[1] != C->size[1])) {
    printf("Error: column dimensions of input matrices don\'t match.\n");
    fflush(stdout);
    memset(&D[0], 0, 729U * sizeof(double));
  } else {
    /* compute the matricized tensor using KhatriRao product (see Sandia */
    /* technical paper 2009), flatten over mode-3 */
    i6 = a->size[0] * a->size[1];
    a->size[0] = 9;
    a->size[1] = C->size[1];
    emxEnsureCapacity_real_T(a, i6);
    loop_ub = C->size[0] * C->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      a->data[i6] = C->data[i6];
    }

    khatriraoOptimized(B, A, r0);
    i6 = b->size[0] * b->size[1];
    b->size[0] = r0->size[1];
    b->size[1] = 81;
    emxEnsureCapacity_real_T(b, i6);
    for (i6 = 0; i6 < 81; i6++) {
      loop_ub = r0->size[1];
      for (i7 = 0; i7 < loop_ub; i7++) {
        b->data[i7 + b->size[0] * i6] = r0->data[i6 + 81 * i7];
      }
    }

    if ((C->size[1] == 1) || (b->size[0] == 1) || (C->size[1] == 0) || (b->size
         [0] == 0)) {
    } else {
      i6 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = 81;
      emxEnsureCapacity_real_T(y, i6);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)81, (MKL_INT)C->size[1], 1.0, &a->data[0], (MKL_INT)9,
                  &b->data[0], (MKL_INT)C->size[1], 0.0, &y->data[0], (MKL_INT)9);
    }

    i6 = a->size[0] * a->size[1];
    a->size[0] = 9;
    a->size[1] = C->size[1];
    emxEnsureCapacity_real_T(a, i6);
    loop_ub = C->size[0] * C->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      a->data[i6] = C->data[i6];
    }

    khatriraoOptimized(B, A, r0);
    i6 = b->size[0] * b->size[1];
    b->size[0] = r0->size[1];
    b->size[1] = 81;
    emxEnsureCapacity_real_T(b, i6);
    for (i6 = 0; i6 < 81; i6++) {
      loop_ub = r0->size[1];
      for (i7 = 0; i7 < loop_ub; i7++) {
        b->data[i7 + b->size[0] * i6] = r0->data[i6 + 81 * i7];
      }
    }

    if ((C->size[1] == 1) || (b->size[0] == 1) || (C->size[1] == 0) || (b->size
         [0] == 0)) {
    } else {
      i6 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = 81;
      emxEnsureCapacity_real_T(y, i6);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)81, (MKL_INT)C->size[1], 1.0, &a->data[0], (MKL_INT)9,
                  &b->data[0], (MKL_INT)C->size[1], 0.0, &y->data[0], (MKL_INT)9);
    }

    i6 = a->size[0] * a->size[1];
    a->size[0] = 9;
    a->size[1] = C->size[1];
    emxEnsureCapacity_real_T(a, i6);
    loop_ub = C->size[0] * C->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      a->data[i6] = C->data[i6];
    }

    khatriraoOptimized(B, A, r0);
    i6 = b->size[0] * b->size[1];
    b->size[0] = r0->size[1];
    b->size[1] = 81;
    emxEnsureCapacity_real_T(b, i6);
    for (i6 = 0; i6 < 81; i6++) {
      loop_ub = r0->size[1];
      for (i7 = 0; i7 < loop_ub; i7++) {
        b->data[i7 + b->size[0] * i6] = r0->data[i6 + 81 * i7];
      }
    }

    if ((C->size[1] == 1) || (b->size[0] == 1)) {
      i6 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = b->size[1];
      emxEnsureCapacity_real_T(y, i6);
      for (i6 = 0; i6 < 9; i6++) {
        loop_ub = b->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          y->data[i6 + y->size[0] * i7] = 0.0;
          b_loop_ub = C->size[1];
          for (i8 = 0; i8 < b_loop_ub; i8++) {
            y->data[i6 + y->size[0] * i7] += C->data[i6 + 9 * i8] * b->data[i8 +
              b->size[0] * i7];
          }
        }
      }
    } else if ((C->size[1] == 0) || (b->size[0] == 0)) {
      i6 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = 81;
      emxEnsureCapacity_real_T(y, i6);
      for (i6 = 0; i6 < 729; i6++) {
        y->data[i6] = 0.0;
      }
    } else {
      i6 = y->size[0] * y->size[1];
      y->size[0] = 9;
      y->size[1] = 81;
      emxEnsureCapacity_real_T(y, i6);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)9,
                  (MKL_INT)81, (MKL_INT)C->size[1], 1.0, &a->data[0], (MKL_INT)9,
                  &b->data[0], (MKL_INT)C->size[1], 0.0, &y->data[0], (MKL_INT)9);
    }

    i6 = a->size[0] * a->size[1];
    a->size[0] = y->size[1];
    a->size[1] = y->size[0];
    emxEnsureCapacity_real_T(a, i6);
    loop_ub = y->size[0];
    for (i6 = 0; i6 < loop_ub; i6++) {
      b_loop_ub = y->size[1];
      for (i7 = 0; i7 < b_loop_ub; i7++) {
        a->data[i7 + a->size[0] * i6] = y->data[i6 + y->size[0] * i7];
      }
    }

    for (i6 = 0; i6 < 729; i6++) {
      D[i6] = a->data[i6];
    }
  }

  emxFree_real_T(&r0);
  emxFree_real_T(&y);
  emxFree_real_T(&b);
  emxFree_real_T(&a);
}

/*
 * File trailer for ktensorOptimized.c
 *
 * [EOF]
 */
