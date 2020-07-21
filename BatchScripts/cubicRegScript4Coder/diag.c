/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: diag.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "diag.h"
#include "cubicRegScript4Coder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *v
 *                emxArray_creal_T *d
 * Return Type  : void
 */
void b_diag(const emxArray_creal_T *v, emxArray_creal_T *d)
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
 * Arguments    : const emxArray_real_T *v
 *                emxArray_real_T *d
 * Return Type  : void
 */
void c_diag(const emxArray_real_T *v, emxArray_real_T *d)
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
 * Arguments    : const emxArray_real_T *v
 *                emxArray_real_T *d
 * Return Type  : void
 */
void diag(const emxArray_real_T *v, emxArray_real_T *d)
{
  int nv;
  int unnamed_idx_0;
  int unnamed_idx_1;
  int i18;
  nv = v->size[0];
  unnamed_idx_0 = v->size[0];
  unnamed_idx_1 = v->size[0];
  i18 = d->size[0] * d->size[1];
  d->size[0] = unnamed_idx_0;
  d->size[1] = unnamed_idx_1;
  emxEnsureCapacity_real_T(d, i18);
  unnamed_idx_0 *= unnamed_idx_1;
  for (i18 = 0; i18 < unnamed_idx_0; i18++) {
    d->data[i18] = 0.0;
  }

  for (unnamed_idx_0 = 0; unnamed_idx_0 < nv; unnamed_idx_0++) {
    d->data[unnamed_idx_0 + d->size[0] * unnamed_idx_0] = v->data[unnamed_idx_0];
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
