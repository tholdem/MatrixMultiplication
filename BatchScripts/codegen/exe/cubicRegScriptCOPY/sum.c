/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "sum.h"
#include "cubicRegScriptCOPY.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void sum(const emxArray_real_T *x, double y_data[], int y_size[2])
{
  int vlen;
  int k;
  int vstride;
  int j;
  int xoffset;
  vlen = x->size[2];
  if (x->size[2] == 0) {
    y_size[0] = 9;
    y_size[1] = 9;
    memset(&y_data[0], 0, 81U * sizeof(double));
  } else {
    k = 3;
    if (x->size[2] == 1) {
      k = 2;
    }

    if (3 > k) {
      vstride = 81 * x->size[2];
    } else {
      vstride = 81;
    }

    y_size[0] = 9;
    y_size[1] = 9;
    for (j = 0; j < vstride; j++) {
      y_data[j] = x->data[j];
    }

    for (k = 2; k <= vlen; k++) {
      xoffset = (k - 1) * vstride;
      for (j = 0; j < vstride; j++) {
        y_data[j] += x->data[xoffset + j];
      }
    }
  }
}

/* End of code generation (sum.c) */
