/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript4Coder_initialize.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "cubicRegScript4Coder_initialize.h"
#include "fileManager.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void cubicRegScript4Coder_initialize(void)
{
  rt_InitInfAndNaN(8U);
  c_eml_rand_mt19937ar_stateful_i();
  filedata_init();
}

/*
 * File trailer for cubicRegScript4Coder_initialize.c
 *
 * [EOF]
 */
