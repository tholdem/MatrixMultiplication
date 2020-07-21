/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: khatriraoOptimized.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "khatriraoOptimized.h"
#include "cubicRegScript4Coder_emxutil.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *C
 * Return Type  : void
 */
void khatriraoOptimized(const emxArray_real_T *A, const emxArray_real_T *B,
  emxArray_real_T *C)
{
  int i9;
  int kidx;
  int j;
  int i1;
  int i2;
  double K_data[81];
  i9 = C->size[0] * C->size[1];
  C->size[0] = 81;
  C->size[1] = B->size[1];
  emxEnsureCapacity_real_T(C, i9);
  kidx = 81 * B->size[1];
  for (i9 = 0; i9 < kidx; i9++) {
    C->data[i9] = 0.0;
  }

  if (A->size[1] != B->size[1]) {
    printf("Error: column dimensions of input matrices don\'t match.\n");
    fflush(stdout);
  } else {
    i9 = B->size[1];
    for (j = 0; j < i9; j++) {
      kidx = -1;
      for (i1 = 0; i1 < 9; i1++) {
        for (i2 = 0; i2 < 9; i2++) {
          kidx++;
          K_data[kidx] = A->data[i1 + 9 * j] * B->data[i2 + 9 * j];
        }
      }

      for (kidx = 0; kidx < 81; kidx++) {
        C->data[kidx + 81 * j] = K_data[kidx];
      }
    }
  }
}

/*
 * File trailer for khatriraoOptimized.c
 *
 * [EOF]
 */
