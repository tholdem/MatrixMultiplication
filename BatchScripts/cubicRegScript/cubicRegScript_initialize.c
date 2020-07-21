/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicRegScript_initialize.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "cubicRegScript_initialize.h"
#include "fileManager.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void cubicRegScript_initialize(void)
{
  rt_InitInfAndNaN(8U);
  c_eml_rand_mt19937ar_stateful_i();
  filedata_init();
}

/*
 * File trailer for cubicRegScript_initialize.c
 *
 * [EOF]
 */
