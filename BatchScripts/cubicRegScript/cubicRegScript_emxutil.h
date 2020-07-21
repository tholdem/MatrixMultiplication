/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript_emxutil.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

#ifndef CUBICREGSCRIPT_EMXUTIL_H
#define CUBICREGSCRIPT_EMXUTIL_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScript_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_lapack_int(emxArray_lapack_int *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_char_T(emxArray_char_T **pEmxArray);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_lapack_int(emxArray_lapack_int **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_char_T(emxArray_char_T **pEmxArray, int numDimensions);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_lapack_int(emxArray_lapack_int **pEmxArray, int
  numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for cubicRegScript_emxutil.h
 *
 * [EOF]
 */
