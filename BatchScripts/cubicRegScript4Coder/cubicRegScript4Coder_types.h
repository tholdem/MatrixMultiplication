/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript4Coder_types.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

#ifndef CUBICREGSCRIPT4CODER_TYPES_H
#define CUBICREGSCRIPT4CODER_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#include <stdio.h>
#ifndef typedef_c_coder_internal_anonymous_func
#define typedef_c_coder_internal_anonymous_func

typedef struct {
  double tunableEnvironment[1];
} c_coder_internal_anonymous_func;

#endif                                 /*typedef_c_coder_internal_anonymous_func*/

#ifndef typedef_cell_1
#define typedef_cell_1

typedef struct {
  c_coder_internal_anonymous_func f1;
  c_coder_internal_anonymous_func f2;
  c_coder_internal_anonymous_func f3;
} cell_1;

#endif                                 /*typedef_cell_1*/

#ifndef typedef_d_coder_internal_anonymous_func
#define typedef_d_coder_internal_anonymous_func

typedef struct {
  cell_1 tunableEnvironment;
} d_coder_internal_anonymous_func;

#endif                                 /*typedef_d_coder_internal_anonymous_func*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T

struct emxArray_char_T
{
  char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_char_T*/

#ifndef typedef_emxArray_char_T
#define typedef_emxArray_char_T

typedef struct emxArray_char_T emxArray_char_T;

#endif                                 /*typedef_emxArray_char_T*/

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T

typedef struct {
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} emxArray_creal_T;

#endif                                 /*typedef_emxArray_creal_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#include "mkl_lapacke.h"
#ifndef struct_emxArray_lapack_int
#define struct_emxArray_lapack_int

struct emxArray_lapack_int
{
  lapack_int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_lapack_int*/

#ifndef typedef_emxArray_lapack_int
#define typedef_emxArray_lapack_int

typedef struct emxArray_lapack_int emxArray_lapack_int;

#endif                                 /*typedef_emxArray_lapack_int*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/
#endif

/*
 * File trailer for cubicRegScript4Coder_types.h
 *
 * [EOF]
 */
