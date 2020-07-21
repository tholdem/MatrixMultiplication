/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ARCSubproblem.c
 *
 * Code generation for function 'ARCSubproblem'
 *
 */

/* Include files */
#include "ARCSubproblem.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "cubicRegScriptCOPY_rtwutil.h"
#include "lapacke.h"
#include "minOrMax.h"
#include "mldivide.h"
#include "norm.h"
#include "relop.h"
#include "roots.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

/* Function Definitions */
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

void ARCSubproblem(const emxArray_creal_T *gx, const emxArray_real_T *B, const
                   emxArray_creal_T *v1, const creal_T lambda1, double sigma,
                   double maxIts, emxArray_creal_T *p)
{
  double lambda_re;
  double lambda_im;
  double mb;
  boolean_T SCALEB;
  double lambda_const_re;
  double absbi;
  double lambda_const_im;
  double Delta_re;
  double Mb;
  double Delta_im;
  creal_T tau;
  int i;
  int loop_ub;
  emxArray_real_T *B1;
  double b_i;
  emxArray_creal_T *q;
  emxArray_real_T *R;
  emxArray_real_T *A_tmp;
  emxArray_real_T *d;
  emxArray_real_T *b_R;
  boolean_T exitg1;
  int i1;
  int n;
  int jmax;
  int info;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  lapack_int info_t;
  double b_lambda_re;
  double b_lambda_im;
  double br;
  creal_T dcv[3];
  creal_T varargin_1_data[2];
  int varargin_1_size[1];

  /*  Usage: p = ARCSubproblem(gx,B,V,D,sigma,kappa_easy,maxIts) */
  /* adapted from Algorithm 7.3.6, Conn et al 2000, Algorithm 4.3, Nocedal */
  /* and Wright, 2006, and Cartis et al 2011 */
  lambda_re = -lambda1.re;
  lambda_im = -lambda1.im;
  if (rtIsNaN(-lambda1.re) || rtIsNaN(-lambda1.im)) {
    SCALEB = false;
  } else {
    mb = fabs(-lambda1.re);
    if ((mb > 8.9884656743115785E+307) || (fabs(-lambda1.im) >
         8.9884656743115785E+307)) {
      SCALEB = true;
    } else {
      SCALEB = false;
    }

    if (SCALEB) {
      absbi = rt_hypotd_snf(-lambda1.re / 2.0, -lambda1.im / 2.0);
    } else {
      absbi = rt_hypotd_snf(-lambda1.re, -lambda1.im);
    }

    if (iseq(0.0, absbi)) {
      absbi = fabs(-lambda1.im);
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
        absbi = rt_atan2d_snf(-lambda1.im, -lambda1.re);
        if (iseq(0.0, absbi)) {
          absbi = -lambda1.im;
          if (iseq(0.0, -lambda1.im)) {
            absbi = 0.0;
          }
        }
      }
    }

    SCALEB = (0.0 < absbi);
  }

  if (!SCALEB) {
    lambda_re = 0.0;
    lambda_im = 0.0;
  }

  lambda_const_re = 1.4901161193847656E-8 * (lambda_re + 1.0);
  lambda_const_im = 1.4901161193847656E-8 * lambda_im;
  if ((lambda_re != 0.0) || (lambda_im != 0.0)) {
    /* strictly greater than */
    lambda_re += lambda_const_re;
    lambda_im += lambda_const_im;
  }

  if (lambda_im == 0.0) {
    Delta_re = lambda_re / sigma;
    Delta_im = 0.0;
  } else if (lambda_re == 0.0) {
    Delta_re = 0.0;
    Delta_im = lambda_im / sigma;
  } else {
    Delta_re = lambda_re / sigma;
    Delta_im = lambda_im / sigma;
  }

  /* garbage value just to pass the condition of while loop */
  tau.re = Delta_re + 1.001;
  tau.im = Delta_im;
  i = p->size[0];
  p->size[0] = gx->size[0];
  emxEnsureCapacity_creal_T(p, i);
  loop_ub = gx->size[0];
  for (i = 0; i < loop_ub; i++) {
    p->data[i] = tau;
  }

  emxInit_real_T(&B1, 2);
  i = B1->size[0] * B1->size[1];
  B1->size[0] = B->size[0];
  B1->size[1] = B->size[1];
  emxEnsureCapacity_real_T(B1, i);
  loop_ub = B->size[0] * B->size[1];
  for (i = 0; i < loop_ub; i++) {
    B1->data[i] = B->data[i];
  }

  b_i = 0.0;

  /* we are trying to find the global minimizer of m(p). It should satisfy  */
  /* 1. (B+lambda*I)p = -g */
  /* 2. lambda^2 = sigma^2*norm(p) */
  /* see Eqn (6.1) in Cartis et al 2011 */
  emxInit_creal_T(&q, 1);
  emxInit_real_T(&R, 2);
  emxInit_real_T(&A_tmp, 2);
  emxInit_real_T(&d, 1);
  emxInit_real_T(&b_R, 2);
  exitg1 = false;
  while ((!exitg1) && ((rt_hypotd_snf(b_norm(p) - Delta_re, 0.0 - Delta_im) >
                        0.001) && (b_i < maxIts))) {
    b_i++;
    i = B1->size[0] * B1->size[1];
    if (1 > i) {
      i1 = 1;
      i = 0;
    } else {
      i1 = B1->size[0] + 1;
    }

    if ((B->size[0] == 1) && (B->size[1] == 1)) {
      jmax = d->size[0];
      d->size[0] = 1;
      emxEnsureCapacity_real_T(d, jmax);
      d->data[0] = B->data[0];
    } else {
      n = B->size[0];
      jmax = B->size[1];
      if (n < jmax) {
        jmax = n;
      }

      if (0 < B->size[1]) {
        n = jmax;
      } else {
        n = 0;
      }

      jmax = d->size[0];
      d->size[0] = n;
      emxEnsureCapacity_real_T(d, jmax);
      jmax = n - 1;
      for (n = 0; n <= jmax; n++) {
        d->data[n] = B->data[n + B->size[0] * n];
      }
    }

    loop_ub = div_s32_floor(i - 1, i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      B1->data[i1 * i] = d->data[i] + lambda_re;
    }

    i = R->size[0] * R->size[1];
    R->size[0] = B1->size[0];
    R->size[1] = B1->size[1];
    emxEnsureCapacity_real_T(R, i);
    loop_ub = B1->size[0] * B1->size[1];
    for (i = 0; i < loop_ub; i++) {
      R->data[i] = B1->data[i];
    }

    n = R->size[1];
    info = 0;
    if (R->size[1] != 0) {
      info_t = LAPACKE_dpotrf_work(LAPACK_COL_MAJOR, 'U', (lapack_int)R->size[1],
        &R->data[0], (lapack_int)R->size[1]);
      info = (int)info_t;
      if (info < 0) {
        loop_ub = R->size[1];
        for (i = 0; i < loop_ub; i++) {
          jmax = R->size[0];
          for (i1 = 0; i1 < jmax; i1++) {
            R->data[i1 + R->size[0] * i] = rtNaN;
          }
        }
      }

      if (info == 0) {
        jmax = n;
      } else {
        jmax = info - 1;
      }

      for (n = 0; n < jmax; n++) {
        i = n + 2;
        for (loop_ub = i; loop_ub <= jmax; loop_ub++) {
          R->data[(loop_ub + R->size[0] * n) - 1] = 0.0;
        }
      }

      if (1 > jmax) {
        loop_ub = 0;
        jmax = 0;
      } else {
        loop_ub = jmax;
      }

      i = b_R->size[0] * b_R->size[1];
      b_R->size[0] = loop_ub;
      b_R->size[1] = jmax;
      emxEnsureCapacity_real_T(b_R, i);
      for (i = 0; i < jmax; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_R->data[i1 + b_R->size[0] * i] = R->data[i1 + R->size[0] * i];
        }
      }

      i = R->size[0] * R->size[1];
      R->size[0] = b_R->size[0];
      R->size[1] = b_R->size[1];
      emxEnsureCapacity_real_T(R, i);
      loop_ub = b_R->size[0] * b_R->size[1];
      for (i = 0; i < loop_ub; i++) {
        R->data[i] = b_R->data[i];
      }
    }

    /*      [R,flag] = chol(B+lambda*eye(size(B))); */
    guard1 = false;
    guard2 = false;
    if (info != 0) {
      /* if this error occurs it means there is numerical instability with */
      /* factorization, attempts resolving by incrementing a bit */
      /* fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist.\n'); */
      /*          lambda = lambda + 2*lambda_const; */
      /*          [R,flag] = chol(B+lambda*eye(size(B))); */
      i = B1->size[0] * B1->size[1];
      if (1 > i) {
        i1 = 1;
        i = 0;
      } else {
        i1 = B1->size[0] + 1;
      }

      tau.re = 2.0 * lambda_const_re;
      if ((B1->size[0] == 1) && (B1->size[1] == 1)) {
        jmax = d->size[0];
        d->size[0] = 1;
        emxEnsureCapacity_real_T(d, jmax);
        d->data[0] = B1->data[0];
      } else {
        n = B1->size[0];
        jmax = B1->size[1];
        if (n < jmax) {
          jmax = n;
        }

        if (0 < B1->size[1]) {
          n = jmax;
        } else {
          n = 0;
        }

        jmax = d->size[0];
        d->size[0] = n;
        emxEnsureCapacity_real_T(d, jmax);
        jmax = n - 1;
        for (n = 0; n <= jmax; n++) {
          d->data[n] = B1->data[n + B1->size[0] * n];
        }
      }

      loop_ub = div_s32_floor(i - 1, i1) + 1;
      for (i = 0; i < loop_ub; i++) {
        B1->data[i1 * i] = d->data[i] + tau.re;
      }

      i = R->size[0] * R->size[1];
      R->size[0] = B->size[0];
      R->size[1] = B->size[1];
      emxEnsureCapacity_real_T(R, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        R->data[i] = B->data[i];
      }

      n = R->size[1];
      info = 0;
      if (R->size[1] != 0) {
        info_t = LAPACKE_dpotrf_work(LAPACK_COL_MAJOR, 'U', (lapack_int)R->size
          [1], &R->data[0], (lapack_int)R->size[1]);
        info = (int)info_t;
        if (info < 0) {
          loop_ub = R->size[1];
          for (i = 0; i < loop_ub; i++) {
            jmax = R->size[0];
            for (i1 = 0; i1 < jmax; i1++) {
              R->data[i1 + R->size[0] * i] = rtNaN;
            }
          }
        }

        if (info == 0) {
          jmax = n;
        } else {
          jmax = info - 1;
        }

        for (n = 0; n < jmax; n++) {
          i = n + 2;
          for (loop_ub = i; loop_ub <= jmax; loop_ub++) {
            R->data[(loop_ub + R->size[0] * n) - 1] = 0.0;
          }
        }

        if (1 > jmax) {
          loop_ub = 0;
          jmax = 0;
        } else {
          loop_ub = jmax;
        }

        i = b_R->size[0] * b_R->size[1];
        b_R->size[0] = loop_ub;
        b_R->size[1] = jmax;
        emxEnsureCapacity_real_T(b_R, i);
        for (i = 0; i < jmax; i++) {
          for (i1 = 0; i1 < loop_ub; i1++) {
            b_R->data[i1 + b_R->size[0] * i] = R->data[i1 + R->size[0] * i];
          }
        }

        i = R->size[0] * R->size[1];
        R->size[0] = b_R->size[0];
        R->size[1] = b_R->size[1];
        emxEnsureCapacity_real_T(R, i);
        loop_ub = b_R->size[0] * b_R->size[1];
        for (i = 0; i < loop_ub; i++) {
          R->data[i] = b_R->data[i];
        }
      }

      if (info != 0) {
        /* fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist. Exiting...\n'); */
        i = p->size[0];
        p->size[0] = gx->size[0];
        emxEnsureCapacity_creal_T(p, i);
        loop_ub = gx->size[0];
        for (i = 0; i < loop_ub; i++) {
          p->data[i].re = 0.0;
          p->data[i].im = 0.0;
        }

        /* no step taken */
        exitg1 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      i = A_tmp->size[0] * A_tmp->size[1];
      A_tmp->size[0] = R->size[1];
      A_tmp->size[1] = R->size[0];
      emxEnsureCapacity_real_T(A_tmp, i);
      loop_ub = R->size[0];
      for (i = 0; i < loop_ub; i++) {
        jmax = R->size[1];
        for (i1 = 0; i1 < jmax; i1++) {
          A_tmp->data[i1 + A_tmp->size[0] * i] = R->data[i + R->size[0] * i1];
        }
      }

      i = p->size[0];
      p->size[0] = gx->size[0];
      emxEnsureCapacity_creal_T(p, i);
      loop_ub = gx->size[0];
      for (i = 0; i < loop_ub; i++) {
        p->data[i] = gx->data[i];
      }

      mldiv(A_tmp, p);
      i = b_R->size[0] * b_R->size[1];
      b_R->size[0] = R->size[0];
      b_R->size[1] = R->size[1];
      emxEnsureCapacity_real_T(b_R, i);
      loop_ub = R->size[0] * R->size[1];
      for (i = 0; i < loop_ub; i++) {
        b_R->data[i] = -R->data[i];
      }

      mldiv(b_R, p);

      /*      H_inv = V/(D+lambda*eye(size(D)))*V.'; %alternative to Cholesky,slower */
      /*      p = -H_inv*gx; */
      mb = b_norm(p);
      if (mb <= Delta_re) {
        if (((lambda_re == 0.0) && (lambda_im == 0.0)) || ((mb == Delta_re) &&
             (0.0 == Delta_im))) {
          exitg1 = true;
        } else {
          /* "hard case", Nocedal and Wright, 2006 P88 Equation 4.45 */
          /* also see Algorithm 7.3.6, P199 of Conn 2000 */
          /* fprintf('A wild "hard case" appeared!\n'); */
          /* 1*tau^2+0*tau+(norm^2-Delta^2)=0 */
          /* hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2]; */
          dcv[0].re = 1.0;
          dcv[0].im = 0.0;
          dcv[1].re = 0.0;
          dcv[1].im = 0.0;
          absbi = Delta_re * Delta_im;
          dcv[2].re = mb * mb - (Delta_re * Delta_re - Delta_im * Delta_im);
          dcv[2].im = 0.0 - (absbi + absbi);
          roots(dcv, varargin_1_data, varargin_1_size);
          tau = maximum(varargin_1_data, varargin_1_size);
          i = p->size[0];
          p->size[0] = v1->size[0];
          emxEnsureCapacity_creal_T(p, i);
          loop_ub = v1->size[0];
          for (i = 0; i < loop_ub; i++) {
            p->data[i].re += tau.re * v1->data[i].re - tau.im * v1->data[i].im;
            p->data[i].im += tau.re * v1->data[i].im + tau.im * v1->data[i].re;
          }

          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }

    if (guard1) {
      i = q->size[0];
      q->size[0] = p->size[0];
      emxEnsureCapacity_creal_T(q, i);
      loop_ub = p->size[0];
      for (i = 0; i < loop_ub; i++) {
        q->data[i] = p->data[i];
      }

      mldiv(A_tmp, q);
      if (lambda_re < 2.2204460492503131E-16) {
        lambda_re += lambda_const_re;
        lambda_im += lambda_const_im;
      } else {
        /* Newton method to update lambda, simplified version of phi(lambda)/phi'(lambda) eqn (6.7) and (6.10) */
        Mb = b_norm(q) / mb;
        absbi = mb - Delta_re;
        b_lambda_re = lambda_re * absbi - lambda_im * (0.0 - Delta_im);
        b_lambda_im = lambda_re * (0.0 - Delta_im) + lambda_im * absbi;
        absbi = Mb * Mb;
        br = mb + (Delta_re * lambda_re - Delta_im * lambda_im) * absbi;
        mb = (Delta_re * lambda_im + Delta_im * lambda_re) * absbi;
        if (mb == 0.0) {
          if (b_lambda_im == 0.0) {
            Delta_im = b_lambda_re / br;
            b_lambda_im = 0.0;
          } else if (b_lambda_re == 0.0) {
            Delta_im = 0.0;
            b_lambda_im /= br;
          } else {
            Delta_im = b_lambda_re / br;
            b_lambda_im /= br;
          }
        } else if (br == 0.0) {
          if (b_lambda_re == 0.0) {
            Delta_im = b_lambda_im / mb;
            b_lambda_im = 0.0;
          } else if (b_lambda_im == 0.0) {
            Delta_im = 0.0;
            b_lambda_im = -(b_lambda_re / mb);
          } else {
            Delta_im = b_lambda_im / mb;
            b_lambda_im = -(b_lambda_re / mb);
          }
        } else {
          Delta_re = fabs(br);
          absbi = fabs(mb);
          if (Delta_re > absbi) {
            Mb = mb / br;
            absbi = br + Mb * mb;
            Delta_im = (b_lambda_re + Mb * b_lambda_im) / absbi;
            b_lambda_im = (b_lambda_im - Mb * b_lambda_re) / absbi;
          } else if (absbi == Delta_re) {
            if (br > 0.0) {
              Mb = 0.5;
            } else {
              Mb = -0.5;
            }

            if (mb > 0.0) {
              absbi = 0.5;
            } else {
              absbi = -0.5;
            }

            Delta_im = (b_lambda_re * Mb + b_lambda_im * absbi) / Delta_re;
            b_lambda_im = (b_lambda_im * Mb - b_lambda_re * absbi) / Delta_re;
          } else {
            Mb = br / mb;
            absbi = mb + Mb * br;
            Delta_im = (Mb * b_lambda_re + b_lambda_im) / absbi;
            b_lambda_im = (Mb * b_lambda_im - b_lambda_re) / absbi;
          }
        }

        lambda_re += Delta_im;
        lambda_im += b_lambda_im;

        /*          lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(dot(p,H_inv*p)/normp^2)); */
      }

      if (lambda_im == 0.0) {
        Delta_re = lambda_re / sigma;
        Delta_im = 0.0;
      } else if (lambda_re == 0.0) {
        Delta_re = 0.0;
        Delta_im = lambda_im / sigma;
      } else {
        Delta_re = lambda_re / sigma;
        Delta_im = lambda_im / sigma;
      }
    }
  }

  emxFree_real_T(&b_R);
  emxFree_real_T(&d);
  emxFree_real_T(&A_tmp);
  emxFree_real_T(&R);
  emxFree_creal_T(&q);
  emxFree_real_T(&B1);
}

/* End of code generation (ARCSubproblem.c) */
