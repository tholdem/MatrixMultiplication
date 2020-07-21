/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eye.c
 *
 * Code generation for function 'eye'
 *
 */

/* Include files */
#include "eye.h"
#include "cubicRegScriptCOPY.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void eye(double I_data[], int I_size[2])
{
  int k;
  I_size[0] = 9;
  I_size[1] = 9;
  memset(&I_data[0], 0, 81U * sizeof(double));
  for (k = 0; k < 9; k++) {
    I_data[k + 9 * k] = 1.0;
  }
}

/* End of code generation (eye.c) */
