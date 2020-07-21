/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cubicRegScriptCOPY_initialize.c
 *
 * Code generation for function 'cubicRegScriptCOPY_initialize'
 *
 */

/* Include files */
#include "cubicRegScriptCOPY_initialize.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_data.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void cubicRegScriptCOPY_initialize(void)
{
  rt_InitInfAndNaN();
  c_eml_rand_mt19937ar_stateful_i();
  isInitialized_cubicRegScriptCOPY = true;
}

/* End of code generation (cubicRegScriptCOPY_initialize.c) */
