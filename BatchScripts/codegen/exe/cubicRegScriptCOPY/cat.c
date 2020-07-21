/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cat.c
 *
 * Code generation for function 'cat'
 *
 */

/* Include files */
#include "cat.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void cat(const emxArray_real_T *varargin_1, const emxArray_real_T *varargin_2,
         const emxArray_real_T *varargin_3, emxArray_real_T *y)
{
  int i;
  int iy;
  int j;
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = varargin_1->size[0];
  y->size[1] = varargin_1->size[1];
  y->size[2] = 3;
  emxEnsureCapacity_real_T(y, i);
  iy = -1;
  i = varargin_1->size[0] * varargin_1->size[1];
  for (j = 0; j < i; j++) {
    iy++;
    y->data[iy] = varargin_1->data[j];
  }

  i = varargin_2->size[0] * varargin_2->size[1];
  for (j = 0; j < i; j++) {
    iy++;
    y->data[iy] = varargin_2->data[j];
  }

  i = varargin_3->size[0] * varargin_3->size[1];
  for (j = 0; j < i; j++) {
    iy++;
    y->data[iy] = varargin_3->data[j];
  }
}

/* End of code generation (cat.c) */
