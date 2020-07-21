/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cat.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "cat.h"
#include "cubicRegScript_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_real_T *varargin_2
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *y
 * Return Type  : void
 */
void cat(const emxArray_real_T *varargin_1, const emxArray_real_T *varargin_2,
         const emxArray_real_T *varargin_3, emxArray_real_T *y)
{
  unsigned int ysize_idx_0;
  unsigned int ysize_idx_1;
  int i13;
  int iy;
  int j;
  ysize_idx_0 = (unsigned int)varargin_1->size[0];
  ysize_idx_1 = (unsigned int)varargin_1->size[1];
  i13 = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = (int)ysize_idx_0;
  y->size[1] = (int)ysize_idx_1;
  y->size[2] = 3;
  emxEnsureCapacity_real_T(y, i13);
  iy = -1;
  i13 = varargin_1->size[0] * varargin_1->size[1];
  for (j = 0; j < i13; j++) {
    iy++;
    y->data[iy] = varargin_1->data[j];
  }

  i13 = varargin_2->size[0] * varargin_2->size[1];
  for (j = 0; j < i13; j++) {
    iy++;
    y->data[iy] = varargin_2->data[j];
  }

  i13 = varargin_3->size[0] * varargin_3->size[1];
  for (j = 0; j < i13; j++) {
    iy++;
    y->data[iy] = varargin_3->data[j];
  }
}

/*
 * File trailer for cat.c
 *
 * [EOF]
 */
