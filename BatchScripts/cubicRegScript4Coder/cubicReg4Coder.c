/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cubicReg4Coder.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "cubicReg4Coder.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "diag.h"
#include "eig.h"
#include "dot.h"
#include "norm.h"
#include "ARCSubproblem.h"
#include "mkl_cblas.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d5;
  double d6;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d5 = fabs(u0);
    d6 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d5 == 1.0) {
        y = 1.0;
      } else if (d5 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d6 == 0.0) {
      y = 1.0;
    } else if (d6 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Usage: [x,errFcn] = cubicReg(f,grad,varargin)
 * most code is adapted from this python implementation
 * https://github.com/cjones6/cubic_reg/blob/2d1ed4c156bdfc34159b374a264012f3fe79adfe/src/cubic_reg.py#L258
 * citations include:
 * C. Cartis, N. I. M. Gould, and P. L. Toint, “Adaptive cubic regularisation methods for unconstrained optimization. Part I: Motivation, convergence and numerical results,” Math. Program., vol. 127, no. 2, pp. 245–295, 2011.
 * Conn, A. R., Gould, N. I., & Toint, P. L. (2000). Trust region methods (Vol. 1). Siam.
 * Arguments    : const double c_f_tunableEnvironment_f1_tunab[1]
 *                const double c_f_tunableEnvironment_f2_tunab[1]
 *                const double c_f_tunableEnvironment_f3_tunab[1]
 *                const double c_grad_tunableEnvironment_f1_tu[1]
 *                const double c_grad_tunableEnvironment_f2_tu[1]
 *                const double c_grad_tunableEnvironment_f3_tu[1]
 *                const double c_H_tunableEnvironment_f1_tunab[1]
 *                const double c_H_tunableEnvironment_f2_tunab[1]
 *                const double c_H_tunableEnvironment_f3_tunab[1]
 *                emxArray_real_T *x
 *                const d_coder_internal_anonymous_func errFcn_tunableEnvironment[1]
 *                double errThd
 *                double maxIts
 *                emxArray_real_T *errHistory
 * Return Type  : void
 */
void cubicReg4Coder(const double c_f_tunableEnvironment_f1_tunab[1], const
                    double c_f_tunableEnvironment_f2_tunab[1], const double
                    c_f_tunableEnvironment_f3_tunab[1], const double
                    c_grad_tunableEnvironment_f1_tu[1], const double
                    c_grad_tunableEnvironment_f2_tu[1], const double
                    c_grad_tunableEnvironment_f3_tu[1], const double
                    c_H_tunableEnvironment_f1_tunab[1], const double
                    c_H_tunableEnvironment_f2_tunab[1], const double
                    c_H_tunableEnvironment_f3_tunab[1], emxArray_real_T *x,
                    const d_coder_internal_anonymous_func
                    errFcn_tunableEnvironment[1], double errThd, double maxIts,
                    emxArray_real_T *errHistory)
{
  double sigma;
  int i22;
  int idx;
  emxArray_real_T *gx;
  emxArray_real_T *Hx;
  emxArray_real_T *p;
  emxArray_creal_T *V;
  emxArray_creal_T *D;
  emxArray_creal_T *r7;
  double fx;
  int n;
  double lambda1;
  int k;
  boolean_T exitg1;
  emxArray_boolean_T *r8;
  emxArray_int32_T *r9;
  emxArray_real_T *v1;
  unsigned int i;
  emxArray_int32_T *r10;
  emxArray_real_T *b_x;
  double varargout_1;
  double rho;
  sigma = 1.0;
  i22 = errHistory->size[0];
  idx = (int)maxIts;
  errHistory->size[0] = idx;
  emxEnsureCapacity_real_T(errHistory, i22);
  for (i22 = 0; i22 < idx; i22++) {
    errHistory->data[i22] = 0.0;
  }

  emxInit_real_T(&gx, 1);
  emxInit_real_T(&Hx, 2);
  emxInit_real_T(&p, 1);
  emxInit_creal_T(&V, 2);
  emxInit_creal_T(&D, 2);
  emxInit_creal_T(&r7, 1);

  /* m = @(p,fx,gx,Hx,sigma) fx+ dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3; */
  /* we can remove fx since we are using the difference between fx and m(p) */
  fx = __anon_fcn(c_f_tunableEnvironment_f1_tunab,
                  c_f_tunableEnvironment_f2_tunab,
                  c_f_tunableEnvironment_f3_tunab, x);
  b___anon_fcn(c_grad_tunableEnvironment_f1_tu, c_grad_tunableEnvironment_f2_tu,
               c_grad_tunableEnvironment_f3_tu, x, gx);
  c___anon_fcn(c_H_tunableEnvironment_f1_tunab, c_H_tunableEnvironment_f2_tunab,
               c_H_tunableEnvironment_f3_tunab, x, Hx);
  eig(Hx, V, D);
  b_diag(D, r7);
  i22 = p->size[0];
  p->size[0] = r7->size[0];
  emxEnsureCapacity_real_T(p, i22);
  idx = r7->size[0];
  for (i22 = 0; i22 < idx; i22++) {
    p->data[i22] = r7->data[i22].re;
  }

  n = p->size[0];
  if (p->size[0] <= 2) {
    if (p->size[0] == 1) {
      lambda1 = p->data[0];
    } else if ((p->data[0] > p->data[1]) || (rtIsNaN(p->data[0]) && (!rtIsNaN
                 (p->data[1])))) {
      lambda1 = p->data[1];
    } else {
      lambda1 = p->data[0];
    }
  } else {
    if (!rtIsNaN(p->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= p->size[0])) {
        if (!rtIsNaN(p->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      lambda1 = p->data[0];
    } else {
      lambda1 = p->data[idx - 1];
      i22 = idx + 1;
      for (k = i22; k <= n; k++) {
        if (lambda1 > p->data[k - 1]) {
          lambda1 = p->data[k - 1];
        }
      }
    }
  }

  emxInit_boolean_T(&r8, 1);
  b_diag(D, r7);
  i22 = r8->size[0];
  r8->size[0] = r7->size[0];
  emxEnsureCapacity_boolean_T(r8, i22);
  idx = r7->size[0];
  for (i22 = 0; i22 < idx; i22++) {
    r8->data[i22] = ((r7->data[i22].re == lambda1) && (r7->data[i22].im == 0.0));
  }

  k = r8->size[0] - 1;
  idx = 0;
  for (n = 0; n <= k; n++) {
    if (r8->data[n]) {
      idx++;
    }
  }

  emxInit_int32_T(&r9, 1);
  i22 = r9->size[0];
  r9->size[0] = idx;
  emxEnsureCapacity_int32_T(r9, i22);
  idx = 0;
  for (n = 0; n <= k; n++) {
    if (r8->data[n]) {
      r9->data[idx] = n + 1;
      idx++;
    }
  }

  emxInit_real_T(&v1, 2);
  idx = V->size[0];
  i22 = v1->size[0] * v1->size[1];
  v1->size[0] = idx;
  v1->size[1] = r9->size[0];
  emxEnsureCapacity_real_T(v1, i22);
  n = r9->size[0];
  for (i22 = 0; i22 < n; i22++) {
    for (k = 0; k < idx; k++) {
      v1->data[k + v1->size[0] * i22] = V->data[k + V->size[0] * (r9->data[i22]
        - 1)].re;
    }
  }

  emxFree_int32_T(&r9);

  /*  Hx1 = Hx; */
  /*  [v1,lambda1] = eigs(Hx,1); */
  /*  if isnan(lambda1) */
  /*      [V,D]=eig(Hx); */
  /*      v1 = V(:,1); */
  /*      lambda1 = D(1,1); */
  /*  elseif lambda1>0 */
  /*      Hx1(1:1+size(Hx1,1):end) = diag(Hx)-lambda1; */
  /*      [v1,lambda2] = eigs(Hx1,1); */
  /*      if isnan(lambda2) */
  /*          [V,D]=eig(Hx); */
  /*          v1 = V(:,1); */
  /*          lambda1 = D(1,1); */
  /*      else */
  /*          lambda1=lambda1+lambda2; */
  /*      end */
  /*  end */
  /* Hess = Hess(x,p);%in case explicit Hessian is not available */
  i = 0U;

  /* Cartis et al 2011 Algorithm 2.1  */
  emxInit_int32_T(&r10, 1);
  emxInit_real_T(&b_x, 1);
  while ((c_norm(gx) > errThd) && (i < maxIts)) {
    i++;

    /* fprintf('gx(1)=%g,Hx(1,1)=%g,Hx(1,244)=%g,Hx(1,729)=%g,v1(1)=%g,lambda1=%g,maxIts=%d.\n',gx(1),Hx(1,1),Hx(1,244),Hx(1,729),v1(1),lambda1,int32(maxIts)); */
    ARCSubproblem(gx, Hx, v1, lambda1, sigma, maxIts / 10.0, p);
    i22 = b_x->size[0];
    b_x->size[0] = x->size[0];
    emxEnsureCapacity_real_T(b_x, i22);
    idx = x->size[0];
    for (i22 = 0; i22 < idx; i22++) {
      b_x->data[i22] = x->data[i22] + p->data[i22];
    }

    varargout_1 = __anon_fcn(c_f_tunableEnvironment_f1_tunab,
      c_f_tunableEnvironment_f2_tunab, c_f_tunableEnvironment_f3_tunab, b_x);
    if ((Hx->size[1] == 1) || (p->size[0] == 1)) {
      i22 = b_x->size[0];
      b_x->size[0] = Hx->size[0];
      emxEnsureCapacity_real_T(b_x, i22);
      idx = Hx->size[0];
      for (i22 = 0; i22 < idx; i22++) {
        b_x->data[i22] = 0.0;
        n = Hx->size[1];
        for (k = 0; k < n; k++) {
          b_x->data[i22] += Hx->data[i22 + Hx->size[0] * k] * p->data[k];
        }
      }
    } else if ((Hx->size[0] == 0) || (Hx->size[1] == 0) || (p->size[0] == 0)) {
      i22 = b_x->size[0];
      b_x->size[0] = Hx->size[0];
      emxEnsureCapacity_real_T(b_x, i22);
      idx = Hx->size[0];
      for (i22 = 0; i22 < idx; i22++) {
        b_x->data[i22] = 0.0;
      }
    } else {
      i22 = b_x->size[0];
      b_x->size[0] = Hx->size[0];
      emxEnsureCapacity_real_T(b_x, i22);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, (MKL_INT)Hx->size[0],
                  (MKL_INT)1, (MKL_INT)Hx->size[1], 1.0, &Hx->data[0], (MKL_INT)
                  Hx->size[0], &p->data[0], (MKL_INT)Hx->size[1], 0.0,
                  &b_x->data[0], (MKL_INT)Hx->size[0]);
    }

    rho = c_norm(p);
    rho = (dot(p, gx) + 0.5 * dot(b_x, p)) + 0.33333333333333331 * sigma *
      rt_powd_snf(rho, 3.0);
    rho = (fx - varargout_1) / -rho;

    /* successful, move in that direction */
    if (rho >= 0.1) {
      /* x = Proj(x + p); */
      i22 = x->size[0];
      emxEnsureCapacity_real_T(x, i22);
      idx = x->size[0];
      for (i22 = 0; i22 < idx; i22++) {
        x->data[i22] += p->data[i22];
      }

      /*          fprintf('norm(x)=%f\n',norm(x)); */
      fx = __anon_fcn(c_f_tunableEnvironment_f1_tunab,
                      c_f_tunableEnvironment_f2_tunab,
                      c_f_tunableEnvironment_f3_tunab, x);
      b___anon_fcn(c_grad_tunableEnvironment_f1_tu,
                   c_grad_tunableEnvironment_f2_tu,
                   c_grad_tunableEnvironment_f3_tu, x, gx);
      c___anon_fcn(c_H_tunableEnvironment_f1_tunab,
                   c_H_tunableEnvironment_f2_tunab,
                   c_H_tunableEnvironment_f3_tunab, x, Hx);
      eig(Hx, V, D);
      b_diag(D, r7);
      i22 = p->size[0];
      p->size[0] = r7->size[0];
      emxEnsureCapacity_real_T(p, i22);
      idx = r7->size[0];
      for (i22 = 0; i22 < idx; i22++) {
        p->data[i22] = r7->data[i22].re;
      }

      n = p->size[0];
      if (p->size[0] <= 2) {
        if (p->size[0] == 1) {
          lambda1 = p->data[0];
        } else if ((p->data[0] > p->data[1]) || (rtIsNaN(p->data[0]) &&
                    (!rtIsNaN(p->data[1])))) {
          lambda1 = p->data[1];
        } else {
          lambda1 = p->data[0];
        }
      } else {
        if (!rtIsNaN(p->data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= p->size[0])) {
            if (!rtIsNaN(p->data[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          lambda1 = p->data[0];
        } else {
          lambda1 = p->data[idx - 1];
          i22 = idx + 1;
          for (k = i22; k <= n; k++) {
            if (lambda1 > p->data[k - 1]) {
              lambda1 = p->data[k - 1];
            }
          }
        }
      }

      b_diag(D, r7);
      i22 = r8->size[0];
      r8->size[0] = r7->size[0];
      emxEnsureCapacity_boolean_T(r8, i22);
      idx = r7->size[0];
      for (i22 = 0; i22 < idx; i22++) {
        r8->data[i22] = ((r7->data[i22].re == lambda1) && (r7->data[i22].im ==
          0.0));
      }

      k = r8->size[0] - 1;
      idx = 0;
      for (n = 0; n <= k; n++) {
        if (r8->data[n]) {
          idx++;
        }
      }

      i22 = r10->size[0];
      r10->size[0] = idx;
      emxEnsureCapacity_int32_T(r10, i22);
      idx = 0;
      for (n = 0; n <= k; n++) {
        if (r8->data[n]) {
          r10->data[idx] = n + 1;
          idx++;
        }
      }

      idx = V->size[0];
      i22 = v1->size[0] * v1->size[1];
      v1->size[0] = idx;
      v1->size[1] = r10->size[0];
      emxEnsureCapacity_real_T(v1, i22);
      n = r10->size[0];
      for (i22 = 0; i22 < n; i22++) {
        for (k = 0; k < idx; k++) {
          v1->data[k + v1->size[0] * i22] = V->data[k + V->size[0] * (r10->
            data[i22] - 1)].re;
        }
      }

      /* eigs */
      /*          Hx1 = Hx; */
      /*          [v1,lambda1] = eigs(Hx,1); */
      /*          if isnan(lambda1) */
      /*              [V,D]=eig(Hx); */
      /*              v1 = V(:,1); */
      /*              lambda1 = D(1,1); */
      /*          elseif lambda1>0 */
      /*              Hx1(1:1+size(Hx1,1):end) = diag(Hx)-lambda1; */
      /*              [v1,lambda2] = eigs(Hx1,1); */
      /*              if isnan(lambda2) */
      /*                  [V,D]=eig(Hx); */
      /*                  v1 = V(:,1); */
      /*                  lambda1 = D(1,1); */
      /*              else */
      /*                  lambda1=lambda1+lambda2; */
      /*              end */
      /*          end */
      /* Hess = Hess(x,p); */
      /* very successful,expand TR radius */
      if (rho > 0.9) {
        sigma *= 0.5;
      }

      /* unsuccessful, shrink TR radius */
    } else {
      sigma *= 2.0;
    }

    errHistory->data[(int)i - 1] = __anon_fcn(errFcn_tunableEnvironment[0].
      tunableEnvironment.f1.tunableEnvironment, errFcn_tunableEnvironment[0].
      tunableEnvironment.f2.tunableEnvironment, errFcn_tunableEnvironment[0].
      tunableEnvironment.f3.tunableEnvironment, x);

    /*          if ~mod( i, iterInterval ) */
    /*              fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) ); */
    /*          end */
  }

  emxFree_real_T(&b_x);
  emxFree_creal_T(&r7);
  emxFree_int32_T(&r10);
  emxFree_boolean_T(&r8);
  emxFree_creal_T(&D);
  emxFree_creal_T(&V);
  emxFree_real_T(&p);
  emxFree_real_T(&v1);
  emxFree_real_T(&Hx);
  emxFree_real_T(&gx);

  /* fprintf("sigma=%g\n",sigma); */
}

/*
 * File trailer for cubicReg4Coder.c
 *
 * [EOF]
 */
