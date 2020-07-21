/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * roots.c
 *
 * Code generation for function 'roots'
 *
 */

/* Include files */
#include "roots.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_rtwutil.h"
#include "lapacke.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void roots(const creal_T c[3], creal_T r_data[], int r_size[1])
{
  int k1;
  int k2;
  int nTrailingZeros;
  int companDim;
  boolean_T exitg1;
  int j;
  int a_size_idx_0;
  boolean_T exitg2;
  creal_T a_data[4];
  int ar_tmp;
  double br;
  creal_T ctmp[3];
  double bi;
  int i;
  double brm;
  double bim;
  double s;
  boolean_T p;
  creal_T eiga_data[2];
  int exitg3;
  creal_T A_data[4];
  lapack_int info_t;
  creal_T vl;
  creal_T vr;
  creal_T tau_data[1];
  r_data[0].re = 0.0;
  r_data[0].im = 0.0;
  r_data[1].re = 0.0;
  r_data[1].im = 0.0;
  k1 = 1;
  while ((k1 <= 3) && ((!(c[k1 - 1].re != 0.0)) && (!(c[k1 - 1].im != 0.0)))) {
    k1++;
  }

  k2 = 3;
  while ((k2 >= k1) && ((!(c[k2 - 1].re != 0.0)) && (!(c[k2 - 1].im != 0.0)))) {
    k2--;
  }

  nTrailingZeros = 2 - k2;
  if (k1 < k2) {
    companDim = k2 - k1;
    exitg1 = false;
    while ((!exitg1) && (companDim > 0)) {
      j = 0;
      exitg2 = false;
      while ((!exitg2) && (j + 1 <= companDim)) {
        ar_tmp = k1 + j;
        br = c[k1 - 1].re;
        bi = c[k1 - 1].im;
        if (bi == 0.0) {
          if (c[ar_tmp].im == 0.0) {
            ctmp[j].re = c[ar_tmp].re / br;
            ctmp[j].im = 0.0;
          } else if (c[ar_tmp].re == 0.0) {
            ctmp[j].re = 0.0;
            ctmp[j].im = c[ar_tmp].im / br;
          } else {
            ctmp[j].re = c[ar_tmp].re / br;
            ctmp[j].im = c[ar_tmp].im / br;
          }
        } else if (br == 0.0) {
          if (c[ar_tmp].re == 0.0) {
            ctmp[j].re = c[ar_tmp].im / bi;
            ctmp[j].im = 0.0;
          } else if (c[ar_tmp].im == 0.0) {
            ctmp[j].re = 0.0;
            ctmp[j].im = -(c[ar_tmp].re / bi);
          } else {
            ctmp[j].re = c[ar_tmp].im / bi;
            ctmp[j].im = -(c[ar_tmp].re / bi);
          }
        } else {
          brm = fabs(br);
          bim = fabs(bi);
          if (brm > bim) {
            s = bi / br;
            bim = br + s * bi;
            ctmp[j].re = (c[ar_tmp].re + s * c[ar_tmp].im) / bim;
            ctmp[j].im = (c[ar_tmp].im - s * c[ar_tmp].re) / bim;
          } else if (bim == brm) {
            if (br > 0.0) {
              s = 0.5;
            } else {
              s = -0.5;
            }

            if (bi > 0.0) {
              bim = 0.5;
            } else {
              bim = -0.5;
            }

            ctmp[j].re = (c[ar_tmp].re * s + c[ar_tmp].im * bim) / brm;
            ctmp[j].im = (c[ar_tmp].im * s - c[ar_tmp].re * bim) / brm;
          } else {
            s = br / bi;
            bim = bi + s * br;
            ctmp[j].re = (s * c[ar_tmp].re + c[ar_tmp].im) / bim;
            ctmp[j].im = (s * c[ar_tmp].im - c[ar_tmp].re) / bim;
          }
        }

        if (rtIsInf(rt_hypotd_snf(ctmp[j].re, ctmp[j].im))) {
          exitg2 = true;
        } else {
          j++;
        }
      }

      if (j + 1 > companDim) {
        exitg1 = true;
      } else {
        k1++;
        companDim--;
      }
    }

    if (companDim < 1) {
      if (1 > 3 - k2) {
        r_size[0] = 0;
      } else {
        r_size[0] = 3 - k2;
      }
    } else {
      a_size_idx_0 = companDim;
      k1 = companDim * companDim;
      if (0 <= k1 - 1) {
        memset(&a_data[0], 0, k1 * sizeof(creal_T));
      }

      if (0 <= companDim - 2) {
        a_data[0].re = -ctmp[0].re;
        a_data[0].im = -ctmp[0].im;
        a_data[1].re = 1.0;
        a_data[1].im = 0.0;
      }

      i = companDim * (companDim - 1);
      a_data[i].re = -ctmp[companDim - 1].re;
      a_data[i].im = -ctmp[companDim - 1].im;
      if (0 <= nTrailingZeros) {
        memset(&r_data[0], 0, (nTrailingZeros + 1) * sizeof(creal_T));
      }

      ar_tmp = companDim * companDim;
      p = true;
      for (k1 = 0; k1 < ar_tmp; k1++) {
        if ((!p) || (rtIsInf(a_data[k1].re) || rtIsInf(a_data[k1].im) ||
                     (rtIsNaN(a_data[k1].re) || rtIsNaN(a_data[k1].im)))) {
          p = false;
        }
      }

      if (!p) {
        if (companDim == 1) {
          eiga_data[0].re = rtNaN;
          eiga_data[0].im = 0.0;
        } else {
          for (i = 0; i < companDim; i++) {
            eiga_data[i].re = rtNaN;
            eiga_data[i].im = 0.0;
          }
        }
      } else if (companDim == 1) {
        eiga_data[0] = a_data[0];
      } else {
        p = true;
        j = 0;
        exitg1 = false;
        while ((!exitg1) && (j <= companDim - 1)) {
          k1 = 0;
          do {
            exitg3 = 0;
            if (k1 <= j) {
              i = k1 + companDim * j;
              nTrailingZeros = j + companDim * k1;
              if ((!(a_data[i].re == a_data[nTrailingZeros].re)) || (!(a_data[i]
                    .im == -a_data[nTrailingZeros].im))) {
                p = false;
                exitg3 = 1;
              } else {
                k1++;
              }
            } else {
              j++;
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          if (exitg3 == 1) {
            exitg1 = true;
          }
        }

        if (p) {
          p = true;
          for (k1 = 0; k1 < ar_tmp; k1++) {
            if ((!p) || (rtIsInf(a_data[k1].re) || rtIsInf(a_data[k1].im) ||
                         (rtIsNaN(a_data[k1].re) || rtIsNaN(a_data[k1].im)))) {
              p = false;
            }
          }

          if (!p) {
            a_size_idx_0 = (signed char)companDim;
            k1 = (signed char)companDim * (signed char)companDim;
            for (i = 0; i < k1; i++) {
              a_data[i].re = rtNaN;
              a_data[i].im = 0.0;
            }

            if (1 < (signed char)companDim) {
              a_data[1].re = 0.0;
              a_data[1].im = 0.0;
            }
          } else {
            if (companDim > 1) {
              info_t = LAPACKE_zgehrd(LAPACK_COL_MAJOR, (lapack_int)2,
                (lapack_int)1, (lapack_int)2, (lapack_complex_double *)&a_data[0],
                (lapack_int)2, (lapack_complex_double *)&tau_data[0]);
              if ((int)info_t != 0) {
                for (i = 0; i < companDim; i++) {
                  for (nTrailingZeros = 0; nTrailingZeros < 2; nTrailingZeros++)
                  {
                    k1 = nTrailingZeros + 2 * i;
                    a_data[k1].re = rtNaN;
                    a_data[k1].im = 0.0;
                  }
                }
              }
            }

            vl.re = 0.0;
            vl.im = 0.0;
            info_t = (lapack_int)companDim;
            info_t = LAPACKE_zhseqr(LAPACK_COL_MAJOR, 'S', 'N', info_t,
              (lapack_int)1, (lapack_int)companDim, (lapack_complex_double *)
              &a_data[0], info_t, (lapack_complex_double *)&eiga_data[0],
              (lapack_complex_double *)&vl, (lapack_int)companDim);
            if ((int)info_t < 0) {
              for (i = 0; i < companDim; i++) {
                for (nTrailingZeros = 0; nTrailingZeros < companDim;
                     nTrailingZeros++) {
                  k1 = nTrailingZeros + companDim * i;
                  a_data[k1].re = rtNaN;
                  a_data[k1].im = 0.0;
                }
              }
            }
          }

          for (k1 = 0; k1 < a_size_idx_0; k1++) {
            eiga_data[k1].re = a_data[k1 + a_size_idx_0 * k1].re;
            eiga_data[k1].im = 0.0;
          }
        } else {
          if (0 <= ar_tmp - 1) {
            memcpy(&A_data[0], &a_data[0], ar_tmp * sizeof(creal_T));
          }

          info_t = LAPACKE_zgeev(LAPACK_COL_MAJOR, 'N', 'N', (lapack_int)
            companDim, (lapack_complex_double *)&A_data[0], (lapack_int)
            companDim, (lapack_complex_double *)&eiga_data[0],
            (lapack_complex_double *)&vl, (lapack_int)1, (lapack_complex_double *)
            &vr, (lapack_int)1);
          if ((int)info_t < 0) {
            for (i = 0; i < companDim; i++) {
              eiga_data[i].re = rtNaN;
              eiga_data[i].im = 0.0;
            }
          }
        }
      }

      for (k1 = 0; k1 < companDim; k1++) {
        r_data[(k1 - k2) + 3] = eiga_data[k1];
      }

      r_size[0] = (companDim - k2) + 3;
    }
  } else if (1 > 3 - k2) {
    r_size[0] = 0;
  } else {
    r_size[0] = 3 - k2;
  }
}

/* End of code generation (roots.c) */
