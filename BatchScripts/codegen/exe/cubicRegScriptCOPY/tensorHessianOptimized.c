/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tensorHessianOptimized.c
 *
 * Code generation for function 'tensorHessianOptimized'
 *
 */

/* Include files */
#include "tensorHessianOptimized.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void f___anon_fcn(const emxArray_real_T *A, const emxArray_real_T *B,
                  emxArray_real_T *varargout_1)
{
  int mc;
  int nc;
  int i;
  int j;
  emxArray_real_T *r;
  int coffset;
  int boffset;
  int b_i;
  int k;
  double bkj;
  mc = A->size[1];
  nc = A->size[1];
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = A->size[1];
  varargout_1->size[1] = A->size[1];
  emxEnsureCapacity_real_T(varargout_1, i);
  for (j = 0; j < nc; j++) {
    coffset = j * mc;
    boffset = j * 9;
    for (b_i = 0; b_i < mc; b_i++) {
      varargout_1->data[coffset + b_i] = 0.0;
    }

    for (k = 0; k < 9; k++) {
      bkj = A->data[boffset + k];
      for (b_i = 0; b_i < mc; b_i++) {
        i = coffset + b_i;
        varargout_1->data[i] += A->data[b_i * 9 + k] * bkj;
      }
    }
  }

  emxInit_real_T(&r, 2);
  mc = B->size[1];
  nc = B->size[1];
  i = r->size[0] * r->size[1];
  r->size[0] = B->size[1];
  r->size[1] = B->size[1];
  emxEnsureCapacity_real_T(r, i);
  for (j = 0; j < nc; j++) {
    coffset = j * mc;
    boffset = j * 9;
    for (b_i = 0; b_i < mc; b_i++) {
      r->data[coffset + b_i] = 0.0;
    }

    for (k = 0; k < 9; k++) {
      bkj = B->data[boffset + k];
      for (b_i = 0; b_i < mc; b_i++) {
        i = coffset + b_i;
        r->data[i] += B->data[b_i * 9 + k] * bkj;
      }
    }
  }

  mc = varargout_1->size[0] * varargout_1->size[1];
  for (i = 0; i < mc; i++) {
    varargout_1->data[i] *= r->data[i];
  }

  emxFree_real_T(&r);
}

/* End of code generation (tensorHessianOptimized.c) */
