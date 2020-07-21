/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cubicRegScriptCOPY_emxutil.h
 *
 * Code generation for function 'cubicRegScriptCOPY_emxutil'
 *
 */

#ifndef CUBICREGSCRIPTCOPY_EMXUTIL_H
#define CUBICREGSCRIPTCOPY_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cubicRegScriptCOPY_types.h"

/* Type Definitions */
#include "lapacke.h"

/* Function Declarations */
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_lapack_int(emxArray_lapack_int *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_lapack_int(emxArray_lapack_int **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_lapack_int(emxArray_lapack_int **pEmxArray, int
  numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (cubicRegScriptCOPY_emxutil.h) */
