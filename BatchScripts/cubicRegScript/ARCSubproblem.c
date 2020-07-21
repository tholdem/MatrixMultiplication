/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ARCSubproblem.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "cubicRegScript.h"
#include "ARCSubproblem.h"
#include "cubicRegScript_emxutil.h"
#include "norm.h"
#include "mldivide.h"
#include "eig.h"
#include "diag.h"
#include "mkl_lapacke.h"

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * Usage: p = ARCSubproblem(gx,B,V,D,sigma,kappa_easy,maxIts)
 * adapted from Algorithm 7.3.6, Conn et al 2000, Algorithm 4.3, Nocedal
 * and Wright, 2006, and Cartis et al 2011
 * Arguments    : const emxArray_real_T *gx
 *                const emxArray_real_T *B
 *                const emxArray_real_T *v1
 *                double lambda1
 *                double sigma
 *                double maxIts
 *                emxArray_real_T *p
 * Return Type  : void
 */
void ARCSubproblem(const emxArray_real_T *gx, const emxArray_real_T *B, const
                   emxArray_real_T *v1, double lambda1, double sigma, double
                   maxIts, emxArray_real_T *p)
{
  double lambda;
  double lambda_const;
  double Delta;
  unsigned int unnamed_idx_0;
  int j;
  int companDim;
  emxArray_real_T *B1;
  int i;
  emxArray_real_T *q;
  emxArray_real_T *R;
  emxArray_int32_T *r7;
  emxArray_real_T *r8;
  emxArray_real_T *b_R;
  int exitg1;
  double normp;
  int nTrailingZeros;
  int k1;
  int n;
  int info;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  lapack_int info_t;
  double a;
  double hp[3];
  creal_T r_data[2];
  boolean_T exitg2;
  int a_size[2];
  boolean_T exitg3;
  double varargin_1_data[2];
  creal_T a_data[4];
  double ctmp[3];
  creal_T eiga_data[2];
  int eiga_size[1];
  maxIts = fmax(50.0, fmin(500.0, maxIts));
  lambda = fmax(0.0, -lambda1);
  lambda_const = (1.0 + lambda) * 1.4901161193847656E-8;
  if (lambda != 0.0) {
    /* strictly greater than */
    lambda += lambda_const;
  }

  Delta = lambda / sigma;

  /* garbage value just to pass the condition of while loop */
  unnamed_idx_0 = (unsigned int)gx->size[0];
  j = p->size[0];
  p->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity_real_T(p, j);
  companDim = (int)unnamed_idx_0;
  for (j = 0; j < companDim; j++) {
    p->data[j] = 1.001 + Delta;
  }

  emxInit_real_T(&B1, 2);
  j = B1->size[0] * B1->size[1];
  B1->size[0] = B->size[0];
  B1->size[1] = B->size[1];
  emxEnsureCapacity_real_T(B1, j);
  companDim = B->size[0] * B->size[1];
  for (j = 0; j < companDim; j++) {
    B1->data[j] = B->data[j];
  }

  i = 0;

  /* we are trying to find the global minimizer of m(p). It should satisfy  */
  /* 1. (B+lambda*I)p = -g */
  /* 2. lambda^2 = sigma^2*norm(p) */
  /* see Eqn (6.1) in Cartis et al 2011 */
  emxInit_real_T(&q, 1);
  emxInit_real_T(&R, 2);
  emxInit_int32_T(&r7, 2);
  emxInit_real_T(&r8, 2);
  emxInit_real_T(&b_R, 2);
  do {
    exitg1 = 0;
    normp = c_norm(p) - Delta;
    if ((fabs(normp) > 0.001) && (i < maxIts)) {
      i++;
      j = B1->size[0] * B1->size[1];
      if (1 > j) {
        nTrailingZeros = 1;
        j = -1;
      } else {
        nTrailingZeros = B1->size[0] + 1;
        j--;
      }

      k1 = r7->size[0] * r7->size[1];
      r7->size[0] = 1;
      companDim = div_s32_floor(j, nTrailingZeros);
      r7->size[1] = companDim + 1;
      emxEnsureCapacity_int32_T(r7, k1);
      for (j = 0; j <= companDim; j++) {
        r7->data[j] = nTrailingZeros * j;
      }

      b_diag(B, q);
      companDim = r7->size[0] * r7->size[1] - 1;
      for (j = 0; j <= companDim; j++) {
        B1->data[r7->data[j]] = q->data[j] + lambda;
      }

      j = R->size[0] * R->size[1];
      R->size[0] = B1->size[0];
      R->size[1] = B1->size[1];
      emxEnsureCapacity_real_T(R, j);
      companDim = B1->size[0] * B1->size[1];
      for (j = 0; j < companDim; j++) {
        R->data[j] = B1->data[j];
      }

      n = R->size[1];
      info = 0;
      if (R->size[1] != 0) {
        info_t = LAPACKE_dpotrf_work(LAPACK_COL_MAJOR, 'U', (lapack_int)R->size
          [1], &R->data[0], (lapack_int)R->size[1]);
        info = (int)info_t;
        if (info < 0) {
          j = R->size[0] * R->size[1];
          emxEnsureCapacity_real_T(R, j);
          companDim = R->size[1];
          for (j = 0; j < companDim; j++) {
            k1 = R->size[0];
            for (nTrailingZeros = 0; nTrailingZeros < k1; nTrailingZeros++) {
              R->data[nTrailingZeros + R->size[0] * j] = rtNaN;
            }
          }
        }

        if (info == 0) {
        } else {
          n = info - 1;
        }

        for (j = 0; j < n; j++) {
          for (k1 = j + 2; k1 <= n; k1++) {
            R->data[(k1 + R->size[0] * j) - 1] = 0.0;
          }
        }

        if (1 > n) {
          companDim = 0;
          k1 = 0;
        } else {
          companDim = n;
          k1 = n;
        }

        j = b_R->size[0] * b_R->size[1];
        b_R->size[0] = companDim;
        b_R->size[1] = k1;
        emxEnsureCapacity_real_T(b_R, j);
        for (j = 0; j < k1; j++) {
          for (nTrailingZeros = 0; nTrailingZeros < companDim; nTrailingZeros++)
          {
            b_R->data[nTrailingZeros + b_R->size[0] * j] = R->
              data[nTrailingZeros + R->size[0] * j];
          }
        }

        j = R->size[0] * R->size[1];
        R->size[0] = b_R->size[0];
        R->size[1] = b_R->size[1];
        emxEnsureCapacity_real_T(R, j);
        companDim = b_R->size[0] * b_R->size[1];
        for (j = 0; j < companDim; j++) {
          R->data[j] = b_R->data[j];
        }
      }

      /*      [R,flag] = chol(B+lambda*eye(size(B))); */
      guard1 = false;
      guard2 = false;
      if (info != 0) {
        /* if this error occurs it means there is numerical instability with */
        /* factorization, attempts resolving by incrementing a bit */
        /*          fprintf('ERROR: lambda=%g < - smallest eigenvalue; the Cholesky factorization does not exist.\n',lambda); */
        /*          lambda = lambda + 2*lambda_const; */
        /*          [R,flag] = chol(B+lambda*eye(size(B))); */
        j = B1->size[0] * B1->size[1];
        if (1 > j) {
          nTrailingZeros = 1;
          j = -1;
        } else {
          nTrailingZeros = B1->size[0] + 1;
          j--;
        }

        k1 = r7->size[0] * r7->size[1];
        r7->size[0] = 1;
        companDim = div_s32_floor(j, nTrailingZeros);
        r7->size[1] = companDim + 1;
        emxEnsureCapacity_int32_T(r7, k1);
        for (j = 0; j <= companDim; j++) {
          r7->data[j] = nTrailingZeros * j;
        }

        b_diag(B1, q);
        companDim = r7->size[0] * r7->size[1] - 1;
        normp = 2.0 * lambda_const;
        for (j = 0; j <= companDim; j++) {
          B1->data[r7->data[j]] = q->data[j] + normp;
        }

        j = R->size[0] * R->size[1];
        R->size[0] = B->size[0];
        R->size[1] = B->size[1];
        emxEnsureCapacity_real_T(R, j);
        companDim = B->size[0] * B->size[1];
        for (j = 0; j < companDim; j++) {
          R->data[j] = B->data[j];
        }

        n = R->size[1];
        info = 0;
        if (R->size[1] != 0) {
          info_t = LAPACKE_dpotrf_work(LAPACK_COL_MAJOR, 'U', (lapack_int)
            R->size[1], &R->data[0], (lapack_int)R->size[1]);
          info = (int)info_t;
          if (info < 0) {
            j = R->size[0] * R->size[1];
            emxEnsureCapacity_real_T(R, j);
            companDim = R->size[1];
            for (j = 0; j < companDim; j++) {
              k1 = R->size[0];
              for (nTrailingZeros = 0; nTrailingZeros < k1; nTrailingZeros++) {
                R->data[nTrailingZeros + R->size[0] * j] = rtNaN;
              }
            }
          }

          if (info == 0) {
          } else {
            n = info - 1;
          }

          for (j = 0; j < n; j++) {
            for (k1 = j + 2; k1 <= n; k1++) {
              R->data[(k1 + R->size[0] * j) - 1] = 0.0;
            }
          }

          if (1 > n) {
            companDim = 0;
            k1 = 0;
          } else {
            companDim = n;
            k1 = n;
          }

          j = b_R->size[0] * b_R->size[1];
          b_R->size[0] = companDim;
          b_R->size[1] = k1;
          emxEnsureCapacity_real_T(b_R, j);
          for (j = 0; j < k1; j++) {
            for (nTrailingZeros = 0; nTrailingZeros < companDim; nTrailingZeros
                 ++) {
              b_R->data[nTrailingZeros + b_R->size[0] * j] = R->
                data[nTrailingZeros + R->size[0] * j];
            }
          }

          j = R->size[0] * R->size[1];
          R->size[0] = b_R->size[0];
          R->size[1] = b_R->size[1];
          emxEnsureCapacity_real_T(R, j);
          companDim = b_R->size[0] * b_R->size[1];
          for (j = 0; j < companDim; j++) {
            R->data[j] = b_R->data[j];
          }
        }

        if (info != 0) {
          /*              fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist. Return zeros...\n'); */
          unnamed_idx_0 = (unsigned int)gx->size[0];
          j = p->size[0];
          p->size[0] = (int)unnamed_idx_0;
          emxEnsureCapacity_real_T(p, j);
          companDim = (int)unnamed_idx_0;
          for (j = 0; j < companDim; j++) {
            p->data[j] = 0.0;
          }

          /* no step taken */
          exitg1 = 1;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }

      if (guard2) {
        j = p->size[0];
        p->size[0] = gx->size[0];
        emxEnsureCapacity_real_T(p, j);
        companDim = gx->size[0];
        for (j = 0; j < companDim; j++) {
          p->data[j] = gx->data[j];
        }

        j = b_R->size[0] * b_R->size[1];
        b_R->size[0] = R->size[1];
        b_R->size[1] = R->size[0];
        emxEnsureCapacity_real_T(b_R, j);
        companDim = R->size[0];
        for (j = 0; j < companDim; j++) {
          k1 = R->size[1];
          for (nTrailingZeros = 0; nTrailingZeros < k1; nTrailingZeros++) {
            b_R->data[nTrailingZeros + b_R->size[0] * j] = R->data[j + R->size[0]
              * nTrailingZeros];
          }
        }

        mldivide(b_R, p);
        j = b_R->size[0] * b_R->size[1];
        b_R->size[0] = R->size[0];
        b_R->size[1] = R->size[1];
        emxEnsureCapacity_real_T(b_R, j);
        companDim = R->size[0] * R->size[1];
        for (j = 0; j < companDim; j++) {
          b_R->data[j] = -R->data[j];
        }

        mldivide(b_R, p);

        /*      H_inv = V/(D+lambda*eye(size(D)))*V.'; %alternative to Cholesky,slower */
        /*      p = -H_inv*gx; */
        normp = c_norm(p);
        if (normp <= Delta) {
          if ((lambda == 0.0) || (normp == Delta)) {
            exitg1 = 1;
          } else {
            /* "hard case", Nocedal and Wright, 2006 P88 Equation 4.45 */
            /* also see Algorithm 7.3.6, P199 of Conn 2000 */
            /* fprintf('A wild "hard case" appeared!\n'); */
            /* 1*tau^2+0*tau+(norm^2-Delta^2)=0 */
            /* hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2]; */
            a = c_norm(p);
            hp[0] = 1.0;
            hp[1] = 0.0;
            hp[2] = a * a - Delta * Delta;
            r_data[0].re = 0.0;
            r_data[0].im = 0.0;
            r_data[1].re = 0.0;
            r_data[1].im = 0.0;
            k1 = 1;
            while ((k1 <= 3) && (!(hp[k1 - 1] != 0.0))) {
              k1++;
            }

            n = 3;
            while ((n >= k1) && (!(hp[n - 1] != 0.0))) {
              n--;
            }

            nTrailingZeros = 2 - n;
            if (k1 < n) {
              companDim = n - k1;
              exitg2 = false;
              while ((!exitg2) && (companDim > 0)) {
                j = 0;
                exitg3 = false;
                while ((!exitg3) && (j + 1 <= companDim)) {
                  ctmp[j] = hp[k1 + j] / hp[k1 - 1];
                  if (rtIsInf(fabs(ctmp[j]))) {
                    exitg3 = true;
                  } else {
                    j++;
                  }
                }

                if (j + 1 > companDim) {
                  exitg2 = true;
                } else {
                  k1++;
                  companDim--;
                }
              }

              if (companDim < 1) {
                if (1 > 3 - n) {
                  k1 = 0;
                } else {
                  k1 = 3 - n;
                }
              } else {
                a_size[0] = companDim;
                a_size[1] = companDim;
                memset(&a_data[0], 0, (unsigned int)(companDim * companDim *
                        (int)sizeof(creal_T)));
                if (0 <= companDim - 2) {
                  a_data[0].re = -ctmp[0];
                  a_data[0].im = 0.0;
                  a_data[1].re = 1.0;
                  a_data[1].im = 0.0;
                }

                j = companDim * (companDim - 1);
                a_data[j].re = -ctmp[companDim - 1];
                a_data[j].im = 0.0;
                for (k1 = 0; k1 <= nTrailingZeros; k1++) {
                  r_data[k1].re = 0.0;
                  r_data[k1].im = 0.0;
                }

                b_eig(a_data, a_size, eiga_data, eiga_size);
                for (k1 = 0; k1 < companDim; k1++) {
                  r_data[(k1 - n) + 3] = eiga_data[k1];
                }

                k1 = (companDim - n) + 3;
              }
            } else if (1 > 3 - n) {
              k1 = 0;
            } else {
              k1 = 3 - n;
            }

            for (j = 0; j < k1; j++) {
              varargin_1_data[j] = r_data[j].re;
            }

            if (k1 == 1) {
              a = varargin_1_data[0];
            } else if ((varargin_1_data[0] < varargin_1_data[1]) || (rtIsNaN
                        (varargin_1_data[0]) && (!rtIsNaN(varargin_1_data[1]))))
            {
              a = varargin_1_data[1];
            } else {
              a = varargin_1_data[0];
            }

            j = r8->size[0] * r8->size[1];
            r8->size[0] = v1->size[0];
            r8->size[1] = v1->size[1];
            emxEnsureCapacity_real_T(r8, j);
            companDim = v1->size[0] * v1->size[1];
            for (j = 0; j < companDim; j++) {
              r8->data[j] = a * v1->data[j];
            }

            companDim = r8->size[0];
            j = p->size[0];
            p->size[0] = companDim;
            emxEnsureCapacity_real_T(p, j);
            for (j = 0; j < companDim; j++) {
              p->data[j] += r8->data[j];
            }

            guard1 = true;
          }
        } else {
          guard1 = true;
        }
      }

      if (guard1) {
        j = q->size[0];
        q->size[0] = p->size[0];
        emxEnsureCapacity_real_T(q, j);
        companDim = p->size[0];
        for (j = 0; j < companDim; j++) {
          q->data[j] = p->data[j];
        }

        j = b_R->size[0] * b_R->size[1];
        b_R->size[0] = R->size[1];
        b_R->size[1] = R->size[0];
        emxEnsureCapacity_real_T(b_R, j);
        companDim = R->size[0];
        for (j = 0; j < companDim; j++) {
          k1 = R->size[1];
          for (nTrailingZeros = 0; nTrailingZeros < k1; nTrailingZeros++) {
            b_R->data[nTrailingZeros + b_R->size[0] * j] = R->data[j + R->size[0]
              * nTrailingZeros];
          }
        }

        mldivide(b_R, q);
        if (lambda < 2.2204460492503131E-16) {
          lambda += lambda_const;
        } else {
          /* Newton method to update lambda, simplified version of phi(lambda)/phi'(lambda) eqn (6.7) and (6.10) */
          a = c_norm(q) / normp;
          lambda += lambda * (normp - Delta) / (normp + Delta * lambda * (a * a));

          /*          lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(dot(p,H_inv*p)/normp^2)); */
        }

        Delta = lambda / sigma;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&b_R);
  emxFree_real_T(&r8);
  emxFree_int32_T(&r7);
  emxFree_real_T(&R);
  emxFree_real_T(&q);
  emxFree_real_T(&B1);
}

/*
 * File trailer for ARCSubproblem.c
 *
 * [EOF]
 */
