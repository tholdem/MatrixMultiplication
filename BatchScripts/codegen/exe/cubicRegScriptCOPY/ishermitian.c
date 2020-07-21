/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ishermitian.c
 *
 * Code generation for function 'ishermitian'
 *
 */

/* Include files */
#include "ishermitian.h"
#include "cubicRegScriptCOPY.h"
#include "rt_nonfinite.h"

/* Function Definitions */
boolean_T ishermitian(const emxArray_real_T *A)
{
  boolean_T p;
  int j;
  boolean_T exitg2;
  int i;
  int exitg1;
  p = (A->size[0] == A->size[1]);
  if (p) {
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j <= A->size[1] - 1)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= j) {
          if (!(A->data[i + A->size[0] * j] == A->data[j + A->size[0] * i])) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  }

  return p;
}

/* End of code generation (ishermitian.c) */
