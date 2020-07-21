/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eye.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "eye.h"

/* Function Definitions */

/*
 * Arguments    : double I_data[]
 *                int I_size[2]
 * Return Type  : void
 */
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

/*
 * File trailer for eye.c
 *
 * [EOF]
 */
