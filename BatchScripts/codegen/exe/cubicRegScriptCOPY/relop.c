/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * relop.c
 *
 * Code generation for function 'relop'
 *
 */

/* Include files */
#include "relop.h"
#include "cubicRegScriptCOPY.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
boolean_T iseq(double x, double y)
{
  boolean_T p;
  double absx;
  int exponent;
  absx = fabs(y / 2.0);
  if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
    if (absx <= 2.2250738585072014E-308) {
      absx = 4.94065645841247E-324;
    } else {
      frexp(absx, &exponent);
      absx = ldexp(1.0, exponent - 53);
    }
  } else {
    absx = rtNaN;
  }

  if ((fabs(y - x) < absx) || (rtIsInf(x) && rtIsInf(y) && ((x > 0.0) == (y >
         0.0)))) {
    p = true;
  } else {
    p = false;
  }

  return p;
}

/* End of code generation (relop.c) */
