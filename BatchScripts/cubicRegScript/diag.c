/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: diag.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "diag.h"
#include "cubicRegScript_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *v
 *                emxArray_real_T *d
 * Return Type  : void
 */
void b_diag(const emxArray_real_T *v, emxArray_real_T *d)
{
  int u0;
  int u1;
  if ((v->size[0] == 1) && (v->size[1] == 1)) {
    u1 = d->size[0];
    d->size[0] = 1;
    emxEnsureCapacity_real_T(d, u1);
    d->data[0] = v->data[0];
  } else {
    u0 = v->size[0];
    u1 = v->size[1];
    if (u0 < u1) {
      u1 = u0;
    }

    if (0 < v->size[1]) {
      u0 = u1;
    } else {
      u0 = 0;
    }

    u1 = d->size[0];
    d->size[0] = u0;
    emxEnsureCapacity_real_T(d, u1);
    u1 = u0 - 1;
    for (u0 = 0; u0 <= u1; u0++) {
      d->data[u0] = v->data[u0 + v->size[0] * u0];
    }
  }
}

/*
 * Arguments    : const emxArray_creal_T *v
 *                emxArray_creal_T *d
 * Return Type  : void
 */
void diag(const emxArray_creal_T *v, emxArray_creal_T *d)
{
  int u0;
  int u1;
  if ((v->size[0] == 1) && (v->size[1] == 1)) {
    u1 = d->size[0];
    d->size[0] = 1;
    emxEnsureCapacity_creal_T(d, u1);
    d->data[0] = v->data[0];
  } else {
    u0 = v->size[0];
    u1 = v->size[1];
    if (u0 < u1) {
      u1 = u0;
    }

    if (0 < v->size[1]) {
      u0 = u1;
    } else {
      u0 = 0;
    }

    u1 = d->size[0];
    d->size[0] = u0;
    emxEnsureCapacity_creal_T(d, u1);
    u1 = u0 - 1;
    for (u0 = 0; u0 <= u1; u0++) {
      d->data[u0] = v->data[u0 + v->size[0] * u0];
    }
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
