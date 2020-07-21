/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kron.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "kron.h"
#include "cubicRegScript_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const double B_data[]
 *                emxArray_real_T *K
 * Return Type  : void
 */
void kron(const emxArray_real_T *A, const double B_data[], emxArray_real_T *K)
{
  int ma;
  int na;
  int kidx;
  int unnamed_idx_1;
  int j2;
  int i1;
  int i2;
  ma = A->size[0];
  na = A->size[1];
  kidx = A->size[0] * 9;
  unnamed_idx_1 = A->size[1] * 9;
  j2 = K->size[0] * K->size[1];
  K->size[0] = kidx;
  K->size[1] = unnamed_idx_1;
  emxEnsureCapacity_real_T(K, j2);
  kidx = -1;
  for (unnamed_idx_1 = 0; unnamed_idx_1 < na; unnamed_idx_1++) {
    for (j2 = 0; j2 < 9; j2++) {
      for (i1 = 0; i1 < ma; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          kidx++;
          K->data[kidx] = A->data[i1 + A->size[0] * unnamed_idx_1] * B_data[i2 +
            9 * j2];
        }
      }
    }
  }
}

/*
 * File trailer for kron.c
 *
 * [EOF]
 */
