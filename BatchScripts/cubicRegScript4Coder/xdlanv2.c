/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdlanv2.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "xdlanv2.h"
#include "schur.h"
#include "cubicRegScript4Coder_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double *a
 *                double *b
 *                double *c
 *                double *d
 *                double *rt1r
 *                double *rt1i
 *                double *rt2r
 *                double *rt2i
 *                double *cs
 *                double *sn
 * Return Type  : void
 */
void xdlanv2(double *a, double *b, double *c, double *d, double *rt1r, double
             *rt1i, double *rt2r, double *rt2i, double *cs, double *sn)
{
  double tau;
  double p;
  double bcmax;
  double bcmis;
  double scale;
  int b_b;
  int b_c;
  double z;
  double b_p;
  int b_bcmis;
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    bcmax = *d;
    *d = *a;
    *a = bcmax;
    *b = -*c;
    *c = 0.0;
  } else {
    tau = *a - *d;
    if ((tau == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      p = 0.5 * tau;
      bcmis = fabs(*b);
      scale = fabs(*c);
      bcmax = fmax(bcmis, scale);
      if (!(*b < 0.0)) {
        b_b = 1;
      } else {
        b_b = -1;
      }

      if (!(*c < 0.0)) {
        b_c = 1;
      } else {
        b_c = -1;
      }

      bcmis = fmin(bcmis, scale) * (double)b_b * (double)b_c;
      scale = fmax(fabs(p), bcmax);
      z = p / scale * p + bcmax / scale * bcmis;
      if (z >= 8.8817841970012523E-16) {
        *a = sqrt(scale) * sqrt(z);
        if (!(p < 0.0)) {
          b_p = *a;
        } else {
          b_p = -*a;
        }

        z = p + b_p;
        *a = *d + z;
        *d -= bcmax / z * bcmis;
        tau = rt_hypotd_snf(*c, z);
        *cs = z / tau;
        *sn = *c / tau;
        *b -= *c;
        *c = 0.0;
      } else {
        bcmis = *b + *c;
        tau = rt_hypotd_snf(bcmis, tau);
        *cs = sqrt(0.5 * (1.0 + fabs(bcmis) / tau));
        if (!(bcmis < 0.0)) {
          b_bcmis = 1;
        } else {
          b_bcmis = -1;
        }

        *sn = -(p / (tau * *cs)) * (double)b_bcmis;
        bcmax = *a * *cs + *b * *sn;
        scale = -*a * *sn + *b * *cs;
        z = *c * *cs + *d * *sn;
        bcmis = -*c * *sn + *d * *cs;
        *b = scale * *cs + bcmis * *sn;
        *c = -bcmax * *sn + z * *cs;
        bcmax = 0.5 * ((bcmax * *cs + z * *sn) + (-scale * *sn + bcmis * *cs));
        *a = bcmax;
        *d = bcmax;
        if (*c != 0.0) {
          if (*b != 0.0) {
            if ((*b < 0.0) == (*c < 0.0)) {
              bcmis = sqrt(fabs(*b));
              z = sqrt(fabs(*c));
              *a = bcmis * z;
              if (!(*c < 0.0)) {
                p = *a;
              } else {
                p = -*a;
              }

              tau = 1.0 / sqrt(fabs(*b + *c));
              *a = bcmax + p;
              *d = bcmax - p;
              *b -= *c;
              *c = 0.0;
              scale = bcmis * tau;
              bcmis = z * tau;
              bcmax = *cs * scale - *sn * bcmis;
              *sn = *cs * bcmis + *sn * scale;
              *cs = bcmax;
            }
          } else {
            *b = -*c;
            *c = 0.0;
            bcmax = *cs;
            *cs = -*sn;
            *sn = bcmax;
          }
        }
      }
    }
  }

  *rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
    *rt2i = -*rt1i;
  }
}

/*
 * File trailer for xdlanv2.c
 *
 * [EOF]
 */