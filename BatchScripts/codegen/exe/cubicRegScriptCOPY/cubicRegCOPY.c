/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cubicRegCOPY.c
 *
 * Code generation for function 'cubicRegCOPY'
 *
 */

/* Include files */
#include "cubicRegCOPY.h"
#include "ARCSubproblem.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "cubicRegScriptCOPY_rtwutil.h"
#include "eig.h"
#include "evalPenaltyFcn_CP.h"
#include "lapacke.h"
#include "minOrMax.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
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
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
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

void cubicRegCOPY(const double c_f_tunableEnvironment_f1_tunab[1], const double
                  d_f_tunableEnvironment_f1_tunab[1], double
                  f_tunableEnvironment_f2, double f_tunableEnvironment_f3, const
                  double c_f_tunableEnvironment_f4_tunab[1], const double
                  c_f_tunableEnvironment_f5_tunab[1], const double
                  c_f_tunableEnvironment_f6_tunab[1], double
                  grad_tunableEnvironment_f1, double grad_tunableEnvironment_f2,
                  const double c_grad_tunableEnvironment_f3_tu[1], const double
                  c_grad_tunableEnvironment_f4_tu[1], const double
                  c_grad_tunableEnvironment_f5_tu[1], const cell_6
                  H_tunableEnvironment, emxArray_real_T *x, double errThd,
                  double maxIts, const d_coder_internal_anonymous_func
                  errFcn_tunableEnvironment[1], emxArray_real_T *errHistory)
{
  double sigma;
  int loop_ub;
  int i;
  emxArray_creal_T *gx;
  emxArray_real_T *r;
  double varargout_1;
  double fx;
  emxArray_real_T *Hx;
  emxArray_real_T *r1;
  emxArray_creal_T *v1;
  emxArray_creal_T *V;
  emxArray_creal_T *D;
  creal_T lambda1;
  unsigned int b_i;
  emxArray_creal_T *p;
  emxArray_creal_T *varargin_1;
  emxArray_creal_T *b_varargout_1;
  emxArray_creal_T *maxval;
  emxArray_creal_T *b_maxval;
  emxArray_creal_T *y;
  emxArray_creal_T *b_y;
  emxArray_creal_T *c_y;
  double s_re;
  int j;
  int inner;
  int coffset;
  int c_i;
  double s_im;
  int nx;
  int k;
  creal_T y_data[81];
  lapack_int info_t;
  double s_data[9];
  double superb_data[8];
  double re;
  double im;
  double y_re;
  double y_im;
  double c_re;
  double c_im;
  double b_c_re;
  double b_c_im;

  /* Usage: [x,errFcn] = cubicReg(f,grad,varargin) */
  /* most code is adapted from this python implementation */
  /* https://github.com/cjones6/cubic_reg/blob/2d1ed4c156bdfc34159b374a264012f3fe79adfe/src/cubic_reg.py#L258 */
  /* citations include: */
  /* C. Cartis, N. I. M. Gould, and P. L. Toint, “Adaptive cubic regularisation methods for unconstrained optimization. Part I: Motivation, convergence and numerical results,” Math. Program., vol. 127, no. 2, pp. 245–295, 2011. */
  /* Conn, A. R., Gould, N. I., & Toint, P. L. (2000). Trust region methods (Vol. 1). Siam. */
  sigma = 1.0;
  loop_ub = (int)maxIts;
  i = errHistory->size[0];
  errHistory->size[0] = loop_ub;
  emxEnsureCapacity_real_T(errHistory, i);
  for (i = 0; i < loop_ub; i++) {
    errHistory->data[i] = 0.0;
  }

  emxInit_creal_T(&gx, 1);
  emxInit_real_T(&r, 1);

  /*  if p.Results.projection == "on" */
  /*      Proj = p.Results.projFcn; */
  /*  else */
  /*      Proj = @(x) x; */
  /*  end */
  /*  if p.Results.penalty == "on" */
  /*  else */
  /*  end */
  /* m = @(p,fx,gx,Hx,sigma) fx+ dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3; */
  /* we can remove fx since we are using the difference between fx and m(p) */
  varargout_1 = __anon_fcn(c_f_tunableEnvironment_f1_tunab,
    d_f_tunableEnvironment_f1_tunab, x);
  fx = varargout_1 + evalPenaltyFcn_CP(x, f_tunableEnvironment_f2,
    f_tunableEnvironment_f3, c_f_tunableEnvironment_f4_tunab,
    c_f_tunableEnvironment_f5_tunab, c_f_tunableEnvironment_f6_tunab);
  d___anon_fcn(x, gx);
  b_evalPenaltyFcn_CP(x, grad_tunableEnvironment_f1, grad_tunableEnvironment_f2,
                      c_grad_tunableEnvironment_f3_tu,
                      c_grad_tunableEnvironment_f4_tu,
                      c_grad_tunableEnvironment_f5_tu, r);
  loop_ub = gx->size[0];
  for (i = 0; i < loop_ub; i++) {
    gx->data[i].re += r->data[i];
  }

  emxInit_real_T(&Hx, 2);
  emxInit_real_T(&r1, 2);
  e___anon_fcn(H_tunableEnvironment.f1.tunableEnvironment.f1.tunableEnvironment,
               H_tunableEnvironment.f1.tunableEnvironment.f2.tunableEnvironment,
               H_tunableEnvironment.f1.tunableEnvironment.f3.tunableEnvironment,
               x, Hx);
  c_evalPenaltyFcn_CP(x, H_tunableEnvironment.f2, H_tunableEnvironment.f3,
                      H_tunableEnvironment.f4.tunableEnvironment,
                      H_tunableEnvironment.f5.tunableEnvironment,
                      H_tunableEnvironment.f6.tunableEnvironment, r1);
  loop_ub = Hx->size[0] * Hx->size[1];
  for (i = 0; i < loop_ub; i++) {
    Hx->data[i] += r1->data[i];
  }

  emxInit_creal_T(&v1, 1);
  emxInit_creal_T(&V, 2);
  emxInit_creal_T(&D, 2);
  eig(Hx, V, D);
  loop_ub = V->size[0];
  i = v1->size[0];
  v1->size[0] = V->size[0];
  emxEnsureCapacity_creal_T(v1, i);
  for (i = 0; i < loop_ub; i++) {
    v1->data[i] = V->data[i];
  }

  lambda1 = D->data[0];

  /* Hess = Hess(x,p);%in case explicit Hessian is not available */
  b_i = 0U;

  /* Cartis et al 2011 Algorithm 2.1  */
  emxInit_creal_T(&p, 1);
  emxInit_creal_T(&varargin_1, 1);
  emxInit_creal_T(&b_varargout_1, 2);
  emxInit_creal_T(&maxval, 2);
  emxInit_creal_T(&b_maxval, 2);
  emxInit_creal_T(&y, 2);
  emxInit_creal_T(&b_y, 2);
  emxInit_creal_T(&c_y, 2);
  while ((b_norm(gx) > errThd) && (b_i < maxIts)) {
    b_i++;
    ARCSubproblem(gx, Hx, v1, lambda1, sigma, maxIts / 10.0, p);
    i = varargin_1->size[0];
    varargin_1->size[0] = x->size[0];
    emxEnsureCapacity_creal_T(varargin_1, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      varargin_1->data[i].re = x->data[i] + p->data[i].re;
      varargin_1->data[i].im = p->data[i].im;
    }

    s_re = 9.0 * d_f_tunableEnvironment_f1_tunab[0] + 1.0;
    if (s_re > d_f_tunableEnvironment_f1_tunab[0] * 18.0) {
      i = 1;
    } else {
      i = (int)s_re;
    }

    j = y->size[0] * y->size[1];
    y->size[0] = 9;
    inner = (int)d_f_tunableEnvironment_f1_tunab[0];
    y->size[1] = inner;
    emxEnsureCapacity_creal_T(y, j);
    loop_ub = 9 * inner;
    for (j = 0; j < loop_ub; j++) {
      y->data[j] = varargin_1->data[(i + j) - 1];
    }

    i = b_varargout_1->size[0] * b_varargout_1->size[1];
    b_varargout_1->size[0] = 9;
    inner = (int)c_f_tunableEnvironment_f1_tunab[0];
    b_varargout_1->size[1] = inner;
    emxEnsureCapacity_creal_T(b_varargout_1, i);
    loop_ub = 9 * inner;
    for (i = 0; i < loop_ub; i++) {
      b_varargout_1->data[i] = varargin_1->data[i];
    }

    for (j = 0; j < 9; j++) {
      coffset = j * 9;
      for (c_i = 0; c_i < 9; c_i++) {
        s_re = 0.0;
        s_im = 0.0;
        for (k = 0; k < inner; k++) {
          nx = k * 9 + c_i;
          loop_ub = k * 9 + j;
          s_re += b_varargout_1->data[nx].re * y->data[loop_ub].re -
            b_varargout_1->data[nx].im * y->data[loop_ub].im;
          s_im += b_varargout_1->data[nx].re * y->data[loop_ub].im +
            b_varargout_1->data[nx].im * y->data[loop_ub].re;
        }

        i = coffset + c_i;
        y_data[i].re = s_re;
        y_data[i].im = s_im;
      }
    }

    varargout_1 = 0.0;
    for (j = 0; j < 9; j++) {
      for (c_i = 0; c_i < 9; c_i++) {
        nx = c_i + 9 * j;
        s_re = rt_hypotd_snf(y_data[nx].re, y_data[nx].im);
        if (rtIsNaN(s_re) || (s_re > varargout_1)) {
          varargout_1 = s_re;
        }
      }
    }

    if ((!rtIsInf(varargout_1)) && (!rtIsNaN(varargout_1))) {
      info_t = LAPACKE_zgesvd(LAPACK_COL_MAJOR, 'N', 'N', (lapack_int)9,
        (lapack_int)9, (lapack_complex_double *)&y_data[0], (lapack_int)9,
        &s_data[0], NULL, (lapack_int)1, NULL, (lapack_int)1, &superb_data[0]);
      if ((int)info_t < 0) {
        for (i = 0; i < 9; i++) {
          s_data[i] = rtNaN;
        }
      }

      varargout_1 = s_data[0];
    }

    /* Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,W,i) */
    /* as t decreases, the penalty gets larger */
    /* R is the radius of the spheres we constrain the columns in  */
    /* U,V,W are matricization functions */
    /* i is the index of output function. 1=f,2=grad,3=H. */
    s_re = 9.0 * c_f_tunableEnvironment_f5_tunab[0] + 1.0;
    if (s_re > c_f_tunableEnvironment_f5_tunab[0] * 18.0) {
      i = 1;
    } else {
      i = (int)s_re;
    }

    s_re = c_f_tunableEnvironment_f6_tunab[0] * 18.0 + 1.0;
    if (s_re > varargin_1->size[0]) {
      j = 1;
    } else {
      j = (int)s_re;
    }

    /* phi, if norm(column)>=R, this sum increases */
    s_re = f_tunableEnvironment_f3 * f_tunableEnvironment_f3;
    inner = b_varargout_1->size[0] * b_varargout_1->size[1];
    b_varargout_1->size[0] = 9;
    nx = (int)c_f_tunableEnvironment_f4_tunab[0];
    b_varargout_1->size[1] = nx;
    emxEnsureCapacity_creal_T(b_varargout_1, inner);
    loop_ub = 9 * nx;
    for (inner = 0; inner < loop_ub; inner++) {
      b_varargout_1->data[inner] = varargin_1->data[inner];
    }

    inner = y->size[0] * y->size[1];
    y->size[0] = 9;
    y->size[1] = b_varargout_1->size[1];
    emxEnsureCapacity_creal_T(y, inner);
    nx = 9 * b_varargout_1->size[1];
    for (k = 0; k < nx; k++) {
      y->data[k].re = b_varargout_1->data[k].re * b_varargout_1->data[k].re -
        b_varargout_1->data[k].im * b_varargout_1->data[k].im;
      y->data[k].im = b_varargout_1->data[k].re * b_varargout_1->data[k].im +
        b_varargout_1->data[k].im * b_varargout_1->data[k].re;
    }

    if (y->size[1] == 0) {
      b_y->size[0] = 1;
      b_y->size[1] = 0;
    } else {
      coffset = y->size[1];
      inner = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = y->size[1];
      emxEnsureCapacity_creal_T(b_y, inner);
      for (c_i = 0; c_i < coffset; c_i++) {
        nx = c_i * 9;
        re = y->data[nx].re;
        im = y->data[nx].im;
        for (k = 0; k < 8; k++) {
          loop_ub = (nx + k) + 1;
          re += y->data[loop_ub].re;
          im += y->data[loop_ub].im;
        }

        b_y->data[c_i].re = re;
        b_y->data[c_i].im = im;
      }
    }

    inner = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_creal_T(c_y, inner);
    loop_ub = b_y->size[0] * b_y->size[1];
    for (inner = 0; inner < loop_ub; inner++) {
      c_y->data[inner].re = b_y->data[inner].re - s_re;
      c_y->data[inner].im = b_y->data[inner].im;
    }

    maximum2(c_y, maxval);
    inner = b_varargout_1->size[0] * b_varargout_1->size[1];
    b_varargout_1->size[0] = 9;
    nx = (int)c_f_tunableEnvironment_f5_tunab[0];
    b_varargout_1->size[1] = nx;
    emxEnsureCapacity_creal_T(b_varargout_1, inner);
    loop_ub = 9 * nx;
    for (inner = 0; inner < loop_ub; inner++) {
      b_varargout_1->data[inner] = varargin_1->data[(i + inner) - 1];
    }

    i = y->size[0] * y->size[1];
    y->size[0] = 9;
    y->size[1] = b_varargout_1->size[1];
    emxEnsureCapacity_creal_T(y, i);
    nx = 9 * b_varargout_1->size[1];
    for (k = 0; k < nx; k++) {
      y->data[k].re = b_varargout_1->data[k].re * b_varargout_1->data[k].re -
        b_varargout_1->data[k].im * b_varargout_1->data[k].im;
      y->data[k].im = b_varargout_1->data[k].re * b_varargout_1->data[k].im +
        b_varargout_1->data[k].im * b_varargout_1->data[k].re;
    }

    if (y->size[1] == 0) {
      b_y->size[0] = 1;
      b_y->size[1] = 0;
    } else {
      coffset = y->size[1];
      i = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = y->size[1];
      emxEnsureCapacity_creal_T(b_y, i);
      for (c_i = 0; c_i < coffset; c_i++) {
        nx = c_i * 9;
        re = y->data[nx].re;
        im = y->data[nx].im;
        for (k = 0; k < 8; k++) {
          loop_ub = (nx + k) + 1;
          re += y->data[loop_ub].re;
          im += y->data[loop_ub].im;
        }

        b_y->data[c_i].re = re;
        b_y->data[c_i].im = im;
      }
    }

    i = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_creal_T(c_y, i);
    loop_ub = b_y->size[0] * b_y->size[1];
    for (i = 0; i < loop_ub; i++) {
      c_y->data[i].re = b_y->data[i].re - s_re;
      c_y->data[i].im = b_y->data[i].im;
    }

    maximum2(c_y, b_maxval);
    i = b_varargout_1->size[0] * b_varargout_1->size[1];
    b_varargout_1->size[0] = 9;
    inner = (int)c_f_tunableEnvironment_f6_tunab[0];
    b_varargout_1->size[1] = inner;
    emxEnsureCapacity_creal_T(b_varargout_1, i);
    loop_ub = 9 * inner;
    for (i = 0; i < loop_ub; i++) {
      b_varargout_1->data[i] = varargin_1->data[(j + i) - 1];
    }

    i = y->size[0] * y->size[1];
    y->size[0] = 9;
    y->size[1] = b_varargout_1->size[1];
    emxEnsureCapacity_creal_T(y, i);
    nx = 9 * b_varargout_1->size[1];
    for (k = 0; k < nx; k++) {
      y->data[k].re = b_varargout_1->data[k].re * b_varargout_1->data[k].re -
        b_varargout_1->data[k].im * b_varargout_1->data[k].im;
      y->data[k].im = b_varargout_1->data[k].re * b_varargout_1->data[k].im +
        b_varargout_1->data[k].im * b_varargout_1->data[k].re;
    }

    if (y->size[1] == 0) {
      b_y->size[0] = 1;
      b_y->size[1] = 0;
    } else {
      coffset = y->size[1];
      i = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = y->size[1];
      emxEnsureCapacity_creal_T(b_y, i);
      for (c_i = 0; c_i < coffset; c_i++) {
        nx = c_i * 9;
        re = y->data[nx].re;
        im = y->data[nx].im;
        for (k = 0; k < 8; k++) {
          loop_ub = (nx + k) + 1;
          re += y->data[loop_ub].re;
          im += y->data[loop_ub].im;
        }

        b_y->data[c_i].re = re;
        b_y->data[c_i].im = im;
      }
    }

    i = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_creal_T(c_y, i);
    loop_ub = b_y->size[0] * b_y->size[1];
    for (i = 0; i < loop_ub; i++) {
      c_y->data[i].re = b_y->data[i].re - s_re;
      c_y->data[i].im = b_y->data[i].im;
    }

    maximum2(c_y, b_y);
    nx = maxval->size[1];
    if (maxval->size[1] == 0) {
      s_re = 0.0;
      s_im = 0.0;
    } else {
      s_re = maxval->data[0].re;
      s_im = maxval->data[0].im;
      for (k = 2; k <= nx; k++) {
        s_re += maxval->data[k - 1].re;
        s_im += maxval->data[k - 1].im;
      }
    }

    nx = b_maxval->size[1];
    if (b_maxval->size[1] == 0) {
      re = 0.0;
      im = 0.0;
    } else {
      re = b_maxval->data[0].re;
      im = b_maxval->data[0].im;
      for (k = 2; k <= nx; k++) {
        re += b_maxval->data[k - 1].re;
        im += b_maxval->data[k - 1].im;
      }
    }

    nx = b_y->size[1];
    if (b_y->size[1] == 0) {
      y_re = 0.0;
      y_im = 0.0;
    } else {
      y_re = b_y->data[0].re;
      y_im = b_y->data[0].im;
      for (k = 2; k <= nx; k++) {
        y_re += b_y->data[k - 1].re;
        y_im += b_y->data[k - 1].im;
      }
    }

    /*  %log-barrier function and derivatives */
    /*  c = m+n; %number of functions in the sum, which is the total number of columns in U and V */
    /*  phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1)))); */
    /*  phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))]; */
    c_re = 0.0;
    c_im = 0.0;
    if (p->size[0] >= 1) {
      nx = p->size[0];
      for (k = 0; k < nx; k++) {
        c_re += p->data[k].re * gx->data[k].re + p->data[k].im * gx->data[k].im;
        c_im += p->data[k].re * gx->data[k].im - p->data[k].im * gx->data[k].re;
      }
    }

    i = V->size[0] * V->size[1];
    V->size[0] = Hx->size[0];
    V->size[1] = Hx->size[1];
    emxEnsureCapacity_creal_T(V, i);
    loop_ub = Hx->size[0] * Hx->size[1];
    for (i = 0; i < loop_ub; i++) {
      V->data[i].re = Hx->data[i];
      V->data[i].im = 0.0;
    }

    i = varargin_1->size[0];
    varargin_1->size[0] = V->size[0];
    emxEnsureCapacity_creal_T(varargin_1, i);
    loop_ub = V->size[0];
    for (i = 0; i < loop_ub; i++) {
      varargin_1->data[i].re = 0.0;
      varargin_1->data[i].im = 0.0;
      nx = V->size[1];
      for (j = 0; j < nx; j++) {
        varargin_1->data[i].re += V->data[i + V->size[0] * j].re * p->data[j].re
          - V->data[i + V->size[0] * j].im * p->data[j].im;
        varargin_1->data[i].im += V->data[i + V->size[0] * j].re * p->data[j].im
          + V->data[i + V->size[0] * j].im * p->data[j].re;
      }
    }

    b_c_re = 0.0;
    b_c_im = 0.0;
    if (varargin_1->size[0] >= 1) {
      nx = varargin_1->size[0];
      for (k = 0; k < nx; k++) {
        b_c_re += varargin_1->data[k].re * p->data[k].re + varargin_1->data[k].
          im * p->data[k].im;
        b_c_im += varargin_1->data[k].re * p->data[k].im - varargin_1->data[k].
          im * p->data[k].re;
      }
    }

    s_re = (s_re + re) + y_re;
    s_im = (s_im + im) + y_im;
    varargout_1 = fx - (varargout_1 + 1.0 / f_tunableEnvironment_f2 * s_re);
    y_im = 0.0 - 1.0 / f_tunableEnvironment_f2 * s_im;
    y_re = -((c_re + 0.5 * b_c_re) + 0.33333333333333331 * sigma * rt_powd_snf
             (b_norm(p), 3.0));
    im = -(c_im + 0.5 * b_c_im);
    if (im == 0.0) {
      if (y_im == 0.0) {
        s_re = varargout_1 / y_re;
      } else if (varargout_1 == 0.0) {
        s_re = 0.0;
      } else {
        s_re = varargout_1 / y_re;
      }
    } else if (y_re == 0.0) {
      if (varargout_1 == 0.0) {
        s_re = y_im / im;
      } else if (y_im == 0.0) {
        s_re = 0.0;
      } else {
        s_re = y_im / im;
      }
    } else {
      s_re = fabs(y_re);
      re = fabs(im);
      if (s_re > re) {
        s_re = im / y_re;
        s_re = (varargout_1 + s_re * y_im) / (y_re + s_re * im);
      } else if (re == s_re) {
        if (y_re > 0.0) {
          y_re = 0.5;
        } else {
          y_re = -0.5;
        }

        if (im > 0.0) {
          im = 0.5;
        } else {
          im = -0.5;
        }

        s_re = (varargout_1 * y_re + y_im * im) / s_re;
      } else {
        s_re = y_re / im;
        s_re = (s_re * varargout_1 + y_im) / (im + s_re * y_re);
      }
    }

    /* successful, move in that direction */
    if (s_re >= 0.1) {
      /* x = Proj(x + p); */
      loop_ub = x->size[0];
      for (i = 0; i < loop_ub; i++) {
        x->data[i] += p->data[i].re;
      }

      /* fprintf('norm(x)=%f\n',norm(x)) */
      varargout_1 = __anon_fcn(c_f_tunableEnvironment_f1_tunab,
        d_f_tunableEnvironment_f1_tunab, x);
      fx = varargout_1 + evalPenaltyFcn_CP(x, f_tunableEnvironment_f2,
        f_tunableEnvironment_f3, c_f_tunableEnvironment_f4_tunab,
        c_f_tunableEnvironment_f5_tunab, c_f_tunableEnvironment_f6_tunab);
      d___anon_fcn(x, gx);
      b_evalPenaltyFcn_CP(x, grad_tunableEnvironment_f1,
                          grad_tunableEnvironment_f2,
                          c_grad_tunableEnvironment_f3_tu,
                          c_grad_tunableEnvironment_f4_tu,
                          c_grad_tunableEnvironment_f5_tu, r);
      loop_ub = gx->size[0];
      for (i = 0; i < loop_ub; i++) {
        gx->data[i].re += r->data[i];
      }

      e___anon_fcn
        (H_tunableEnvironment.f1.tunableEnvironment.f1.tunableEnvironment,
         H_tunableEnvironment.f1.tunableEnvironment.f2.tunableEnvironment,
         H_tunableEnvironment.f1.tunableEnvironment.f3.tunableEnvironment, x, Hx);
      c_evalPenaltyFcn_CP(x, H_tunableEnvironment.f2, H_tunableEnvironment.f3,
                          H_tunableEnvironment.f4.tunableEnvironment,
                          H_tunableEnvironment.f5.tunableEnvironment,
                          H_tunableEnvironment.f6.tunableEnvironment, r1);
      loop_ub = Hx->size[0] * Hx->size[1];
      for (i = 0; i < loop_ub; i++) {
        Hx->data[i] += r1->data[i];
      }

      eig(Hx, V, D);
      loop_ub = V->size[0];
      i = v1->size[0];
      v1->size[0] = V->size[0];
      emxEnsureCapacity_creal_T(v1, i);
      for (i = 0; i < loop_ub; i++) {
        v1->data[i] = V->data[i];
      }

      lambda1 = D->data[0];

      /* Hess = Hess(x,p); */
      /* very successful,expand TR radius */
      if (s_re > 0.9) {
        sigma *= 0.5;
      }

      /* unsuccessful, shrink TR radius */
    } else {
      sigma *= 2.0;
    }

    errHistory->data[(int)b_i - 1] = __anon_fcn(errFcn_tunableEnvironment[0].
      tunableEnvironment.f1.tunableEnvironment, errFcn_tunableEnvironment[0].
      tunableEnvironment.f2.tunableEnvironment, x);

    /*          if ~mod( i, iterInterval ) */
    /*              fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) ); */
    /*          end */
  }

  emxFree_creal_T(&c_y);
  emxFree_creal_T(&b_y);
  emxFree_creal_T(&y);
  emxFree_creal_T(&b_maxval);
  emxFree_creal_T(&maxval);
  emxFree_creal_T(&b_varargout_1);
  emxFree_real_T(&r1);
  emxFree_real_T(&r);
  emxFree_creal_T(&varargin_1);
  emxFree_creal_T(&D);
  emxFree_creal_T(&V);
  emxFree_creal_T(&p);
  emxFree_creal_T(&v1);
  emxFree_real_T(&Hx);
  emxFree_creal_T(&gx);

  /* fprintf("sigma=%f\n",sigma); */
}

/* End of code generation (cubicRegCOPY.c) */
