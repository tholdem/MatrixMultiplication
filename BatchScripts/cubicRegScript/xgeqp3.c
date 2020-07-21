/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "xgeqp3.h"
#include "cubicRegScript_emxutil.h"
#include "mkl_lapacke.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *A
 *                emxArray_real_T *tau
 *                emxArray_int32_T *jpvt
 * Return Type  : void
 */
void xgeqp3(emxArray_real_T *A, emxArray_real_T *tau, emxArray_int32_T *jpvt)
{
  int n;
  int yk;
  int u1;
  emxArray_lapack_int *jpvt_t;
  int i26;
  lapack_int m_t;
  lapack_int info_t;
  int i27;
  n = A->size[1];
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    tau->size[0] = 0;
    if (A->size[1] < 1) {
      n = 0;
    } else {
      n = A->size[1];
    }

    i26 = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = n;
    emxEnsureCapacity_int32_T(jpvt, i26);
    if (n > 0) {
      jpvt->data[0] = 1;
      yk = 1;
      for (u1 = 2; u1 <= n; u1++) {
        yk++;
        jpvt->data[u1 - 1] = yk;
      }
    }
  } else {
    yk = A->size[0];
    u1 = A->size[1];
    if (yk < u1) {
      u1 = yk;
    }

    emxInit_lapack_int(&jpvt_t, 1);
    i26 = tau->size[0];
    tau->size[0] = u1;
    emxEnsureCapacity_real_T(tau, i26);
    i26 = jpvt_t->size[0];
    jpvt_t->size[0] = A->size[1];
    emxEnsureCapacity_lapack_int(jpvt_t, i26);
    yk = A->size[1];
    for (i26 = 0; i26 < yk; i26++) {
      jpvt_t->data[i26] = (lapack_int)0;
    }

    m_t = (lapack_int)A->size[0];
    info_t = LAPACKE_dgeqp3(LAPACK_COL_MAJOR, m_t, (lapack_int)A->size[1],
      &A->data[0], m_t, &jpvt_t->data[0], &tau->data[0]);
    if ((int)info_t != 0) {
      i26 = A->size[0] * A->size[1];
      emxEnsureCapacity_real_T(A, i26);
      yk = A->size[1];
      for (i26 = 0; i26 < yk; i26++) {
        u1 = A->size[0];
        for (i27 = 0; i27 < u1; i27++) {
          A->data[i27 + A->size[0] * i26] = rtNaN;
        }
      }

      yk = tau->size[0];
      i26 = tau->size[0];
      tau->size[0] = yk;
      emxEnsureCapacity_real_T(tau, i26);
      for (i26 = 0; i26 < yk; i26++) {
        tau->data[i26] = rtNaN;
      }

      if (n < 1) {
        n = 0;
      }

      i26 = jpvt->size[0] * jpvt->size[1];
      jpvt->size[0] = 1;
      jpvt->size[1] = n;
      emxEnsureCapacity_int32_T(jpvt, i26);
      if (n > 0) {
        jpvt->data[0] = 1;
        yk = 1;
        for (u1 = 2; u1 <= n; u1++) {
          yk++;
          jpvt->data[u1 - 1] = yk;
        }
      }
    } else {
      i26 = jpvt->size[0] * jpvt->size[1];
      jpvt->size[0] = 1;
      jpvt->size[1] = jpvt_t->size[0];
      emxEnsureCapacity_int32_T(jpvt, i26);
      yk = jpvt_t->size[0];
      for (i26 = 0; i26 < yk; i26++) {
        jpvt->data[i26] = (int)jpvt_t->data[i26];
      }
    }

    emxFree_lapack_int(&jpvt_t);
  }
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */
