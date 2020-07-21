/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.c
 *
 * Code generation for function 'minOrMax'
 *
 */

/* Include files */
#include "minOrMax.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "cubicRegScriptCOPY_rtwutil.h"
#include "norm.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
creal_T maximum(const creal_T x_data[], const int x_size[1])
{
  creal_T ex;
  int istop;
  int k;
  boolean_T SCALEA;
  double ma;
  double mb;
  boolean_T SCALEB;
  double absai;
  double absbi;
  double Ma;
  double Mb;
  istop = x_size[0];
  ex = x_data[0];
  for (k = 2; k <= istop; k++) {
    if (rtIsNaN(x_data[1].re) || rtIsNaN(x_data[1].im)) {
      SCALEA = false;
    } else if (rtIsNaN(ex.re) || rtIsNaN(ex.im)) {
      SCALEA = true;
    } else {
      ma = fabs(ex.re);
      if ((ma > 8.9884656743115785E+307) || (fabs(ex.im) >
           8.9884656743115785E+307)) {
        SCALEA = true;
      } else {
        SCALEA = false;
      }

      mb = fabs(x_data[1].re);
      if ((mb > 8.9884656743115785E+307) || (fabs(x_data[1].im) >
           8.9884656743115785E+307)) {
        SCALEB = true;
      } else {
        SCALEB = false;
      }

      if (SCALEA || SCALEB) {
        absai = rt_hypotd_snf(ex.re / 2.0, ex.im / 2.0);
        absbi = rt_hypotd_snf(x_data[1].re / 2.0, x_data[1].im / 2.0);
      } else {
        absai = rt_hypotd_snf(ex.re, ex.im);
        absbi = rt_hypotd_snf(x_data[1].re, x_data[1].im);
      }

      if (iseq(absai, absbi)) {
        absai = fabs(ex.im);
        absbi = fabs(x_data[1].im);
        if (ma > absai) {
          Ma = ma;
          ma = absai;
        } else {
          Ma = absai;
        }

        if (mb > absbi) {
          Mb = mb;
          mb = absbi;
        } else {
          Mb = absbi;
        }

        if (Ma > Mb) {
          if (ma < mb) {
            absai = Ma - Mb;
            absbi = (ma / 2.0 + mb / 2.0) / (Ma / 2.0 + Mb / 2.0) * (mb - ma);
          } else {
            absai = Ma;
            absbi = Mb;
          }
        } else if (Ma < Mb) {
          if (ma > mb) {
            absbi = Mb - Ma;
            absai = (ma / 2.0 + mb / 2.0) / (Ma / 2.0 + Mb / 2.0) * (ma - mb);
          } else {
            absai = Ma;
            absbi = Mb;
          }
        } else {
          absai = ma;
          absbi = mb;
        }

        if (iseq(absai, absbi)) {
          absai = rt_atan2d_snf(ex.im, ex.re);
          absbi = rt_atan2d_snf(x_data[1].im, x_data[1].re);
          if (iseq(absai, absbi)) {
            if (absai > 0.78539816339744828) {
              if (absai > 2.3561944901923448) {
                absai = -ex.im;
                absbi = -x_data[1].im;
              } else {
                absai = -ex.re;
                absbi = -x_data[1].re;
              }
            } else if (absai > -0.78539816339744828) {
              absai = ex.im;
              absbi = x_data[1].im;
            } else if (absai > -2.3561944901923448) {
              absai = ex.re;
              absbi = x_data[1].re;
            } else {
              absai = -ex.im;
              absbi = -x_data[1].im;
            }

            if (iseq(absai, absbi)) {
              absai = 0.0;
              absbi = 0.0;
            }
          }
        }
      }

      SCALEA = (absai < absbi);
    }

    if (SCALEA) {
      ex = x_data[1];
    }
  }

  return ex;
}

void maximum2(const emxArray_creal_T *y, emxArray_creal_T *ex)
{
  int nx;
  int k;
  double mb;
  boolean_T p;
  double absbi;
  double Mb;
  nx = ex->size[0] * ex->size[1];
  ex->size[0] = 1;
  ex->size[1] = y->size[1];
  emxEnsureCapacity_creal_T(ex, nx);
  nx = y->size[1];
  for (k = 0; k < nx; k++) {
    ex->data[k] = y->data[k];
    if (rtIsNaN(y->data[k].re) || rtIsNaN(y->data[k].im)) {
      p = false;
    } else {
      mb = fabs(y->data[k].re);
      if ((mb > 8.9884656743115785E+307) || (fabs(y->data[k].im) >
           8.9884656743115785E+307)) {
        absbi = rt_hypotd_snf(y->data[k].re / 2.0, y->data[k].im / 2.0);
      } else {
        absbi = rt_hypotd_snf(y->data[k].re, y->data[k].im);
      }

      if (iseq(0.0, absbi)) {
        absbi = fabs(y->data[k].im);
        if (mb > absbi) {
          Mb = mb;
          mb = absbi;
        } else {
          Mb = absbi;
        }

        if (0.0 < Mb) {
          absbi = Mb;
        } else {
          absbi = mb;
        }

        if (iseq(0.0, absbi)) {
          absbi = rt_atan2d_snf(y->data[k].im, y->data[k].re);
          if (iseq(0.0, absbi)) {
            absbi = y->data[k].im;
            if (iseq(0.0, y->data[k].im)) {
              absbi = 0.0;
            }
          }
        }
      }

      p = (0.0 < absbi);
    }

    if (!p) {
      ex->data[k].re = 0.0;
      ex->data[k].im = 0.0;
    }
  }
}

/* End of code generation (minOrMax.c) */
