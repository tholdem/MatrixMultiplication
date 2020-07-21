/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kron.c
 *
 * Code generation for function 'kron'
 *
 */

/* Include files */
#include "kron.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void kron(const emxArray_real_T *A, const double B_data[], emxArray_real_T *K)
{
  int ma;
  int na;
  int kidx;
  int b_j1;
  int j2;
  int i1;
  int i2;
  ma = A->size[0];
  na = A->size[1];
  kidx = K->size[0] * K->size[1];
  K->size[0] = A->size[0] * 9;
  K->size[1] = A->size[1] * 9;
  emxEnsureCapacity_real_T(K, kidx);
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (j2 = 0; j2 < 9; j2++) {
      for (i1 = 0; i1 < ma; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          kidx++;
          K->data[kidx] = A->data[i1 + A->size[0] * b_j1] * B_data[i2 + 9 * j2];
        }
      }
    }
  }
}

/* End of code generation (kron.c) */
