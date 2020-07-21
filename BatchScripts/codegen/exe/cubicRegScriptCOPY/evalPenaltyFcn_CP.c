/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * evalPenaltyFcn_CP.c
 *
 * Code generation for function 'evalPenaltyFcn_CP'
 *
 */

/* Include files */
#include "evalPenaltyFcn_CP.h"
#include "cubicRegScriptCOPY.h"
#include "cubicRegScriptCOPY_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R, const
  double U_tunableEnvironment[1], const double V_tunableEnvironment[1], const
  double W_tunableEnvironment[1], emxArray_real_T *outputFcn)
{
  double y;
  int loop_ub;
  int i;
  double scale;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  emxArray_real_T *phi_gradU;
  int i6;
  int j;
  int b_loop_ub;
  emxArray_real_T *phi_gradV;
  emxArray_real_T *phi_gradW;
  emxArray_real_T *b_x;
  double absxk;
  double b_t;

  /* Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,W,i) */
  /* as t decreases, the penalty gets larger */
  /* R is the radius of the spheres we constrain the columns in  */
  /* U,V,W are matricization functions */
  /* i is the index of output function. 1=f,2=grad,3=H. */
  y = 9.0 * U_tunableEnvironment[0];
  if (1.0 > y) {
    loop_ub = 0;
  } else {
    loop_ub = (int)y;
  }

  i = (int)U_tunableEnvironment[0];
  y = 9.0 * V_tunableEnvironment[0] + 1.0;
  scale = V_tunableEnvironment[0] * 18.0;
  if (y > scale) {
    i1 = 0;
    i2 = 0;
  } else {
    i1 = (int)y - 1;
    i2 = (int)scale;
  }

  i3 = (int)V_tunableEnvironment[0];
  y = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (y > x->size[0]) {
    i4 = 0;
    i5 = 0;
  } else {
    i4 = (int)y - 1;
    i5 = x->size[0];
  }

  emxInit_real_T(&phi_gradU, 2);
  i6 = (int)W_tunableEnvironment[0];
  j = phi_gradU->size[0] * phi_gradU->size[1];
  phi_gradU->size[0] = 9;
  phi_gradU->size[1] = i;
  emxEnsureCapacity_real_T(phi_gradU, j);
  b_loop_ub = 9 * i;
  for (j = 0; j < b_loop_ub; j++) {
    phi_gradU->data[j] = 0.0;
  }

  emxInit_real_T(&phi_gradV, 2);
  j = phi_gradV->size[0] * phi_gradV->size[1];
  phi_gradV->size[0] = 9;
  phi_gradV->size[1] = i3;
  emxEnsureCapacity_real_T(phi_gradV, j);
  b_loop_ub = 9 * i3;
  for (i3 = 0; i3 < b_loop_ub; i3++) {
    phi_gradV->data[i3] = 0.0;
  }

  emxInit_real_T(&phi_gradW, 2);
  i3 = phi_gradW->size[0] * phi_gradW->size[1];
  phi_gradW->size[0] = 9;
  phi_gradW->size[1] = i6;
  emxEnsureCapacity_real_T(phi_gradW, i3);
  b_loop_ub = 9 * i6;
  for (i3 = 0; i3 < b_loop_ub; i3++) {
    phi_gradW->data[i3] = 0.0;
  }

  /* going through each column since they are separable in differentiation */
  emxInit_real_T(&b_x, 1);
  for (j = 0; j < i; j++) {
    i3 = b_x->size[0];
    b_x->size[0] = loop_ub;
    emxEnsureCapacity_real_T(b_x, i3);
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_x->data[i3] = x->data[i3];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
      absxk = fabs(b_x->data[b_loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      /* fill the gradient of column at the right location in gradient of x */
      y = 2.0 / t;
      i3 = b_x->size[0];
      b_x->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x, i3);
      for (i3 = 0; i3 < loop_ub; i3++) {
        b_x->data[i3] = x->data[i3];
      }

      for (i3 = 0; i3 < 9; i3++) {
        i6 = i3 + 9 * j;
        phi_gradU->data[i6] = y * b_x->data[i6];
      }

      /*  easier bookkeeping */
    }
  }

  for (j = 0; j < i; j++) {
    loop_ub = i2 - i1;
    i3 = b_x->size[0];
    b_x->size[0] = loop_ub;
    emxEnsureCapacity_real_T(b_x, i3);
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_x->data[i3] = x->data[i1 + i3];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
      absxk = fabs(b_x->data[b_loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      y = 2.0 / t;
      i3 = b_x->size[0];
      b_x->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x, i3);
      for (i3 = 0; i3 < loop_ub; i3++) {
        b_x->data[i3] = x->data[i1 + i3];
      }

      for (i3 = 0; i3 < 9; i3++) {
        i6 = i3 + 9 * j;
        phi_gradV->data[i6] = y * b_x->data[i6];
      }
    }
  }

  for (j = 0; j < i; j++) {
    loop_ub = i5 - i4;
    i1 = b_x->size[0];
    b_x->size[0] = loop_ub;
    emxEnsureCapacity_real_T(b_x, i1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_x->data[i1] = x->data[i4 + i1];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (b_loop_ub = 0; b_loop_ub < 9; b_loop_ub++) {
      absxk = fabs(b_x->data[b_loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      y = 2.0 / t;
      i1 = b_x->size[0];
      b_x->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x->data[i1] = x->data[i4 + i1];
      }

      for (i1 = 0; i1 < 9; i1++) {
        i2 = i1 + 9 * j;
        phi_gradW->data[i2] = y * b_x->data[i2];
      }
    }
  }

  emxFree_real_T(&b_x);
  i = outputFcn->size[0];
  outputFcn->size[0] = (9 * phi_gradU->size[1] + 9 * phi_gradV->size[1]) + 9 *
    phi_gradW->size[1];
  emxEnsureCapacity_real_T(outputFcn, i);
  loop_ub = 9 * phi_gradU->size[1];
  for (i = 0; i < loop_ub; i++) {
    outputFcn->data[i] = phi_gradU->data[i];
  }

  loop_ub = 9 * phi_gradV->size[1];
  for (i = 0; i < loop_ub; i++) {
    outputFcn->data[i + 9 * phi_gradU->size[1]] = phi_gradV->data[i];
  }

  loop_ub = 9 * phi_gradW->size[1];
  for (i = 0; i < loop_ub; i++) {
    outputFcn->data[(i + 9 * phi_gradU->size[1]) + 9 * phi_gradV->size[1]] =
      phi_gradW->data[i];
  }

  emxFree_real_T(&phi_gradW);
  emxFree_real_T(&phi_gradV);
  emxFree_real_T(&phi_gradU);

  /*  easier bookkeping */
  /*  %log-barrier function and derivatives */
  /*  c = m+n; %number of functions in the sum, which is the total number of columns in U and V */
  /*  phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1)))); */
  /*  phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))]; */
}

void c_evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R, const
  double U_tunableEnvironment[1], const double V_tunableEnvironment[1], const
  double W_tunableEnvironment[1], emxArray_real_T *outputFcn)
{
  double y;
  int i;
  double scale;
  int nv;
  int i1;
  int i2;
  int i3;
  emxArray_real_T *phi_HU;
  int i4;
  int i5;
  int loop_ub;
  emxArray_real_T *phi_HV;
  emxArray_real_T *phi_HW;
  int b_loop_ub;
  emxArray_real_T *b_x;
  int j;
  int c_loop_ub;
  int d_loop_ub;
  double absxk;
  double b_t;

  /* Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,W,i) */
  /* as t decreases, the penalty gets larger */
  /* R is the radius of the spheres we constrain the columns in  */
  /* U,V,W are matricization functions */
  /* i is the index of output function. 1=f,2=grad,3=H. */
  y = 9.0 * U_tunableEnvironment[0];
  if (1.0 > y) {
    i = 0;
  } else {
    i = (int)y;
  }

  y = 9.0 * V_tunableEnvironment[0] + 1.0;
  scale = V_tunableEnvironment[0] * 18.0;
  if (y > scale) {
    nv = 0;
    i1 = 0;
  } else {
    nv = (int)y - 1;
    i1 = (int)scale;
  }

  y = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (y > x->size[0]) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = (int)y - 1;
    i3 = x->size[0];
  }

  emxInit_real_T(&phi_HU, 2);
  i4 = phi_HU->size[0] * phi_HU->size[1];
  phi_HU->size[0] = 9;
  i5 = (int)U_tunableEnvironment[0];
  phi_HU->size[1] = i5;
  emxEnsureCapacity_real_T(phi_HU, i4);
  loop_ub = 9 * i5;
  for (i4 = 0; i4 < loop_ub; i4++) {
    phi_HU->data[i4] = 0.0;
  }

  emxInit_real_T(&phi_HV, 2);
  i4 = phi_HV->size[0] * phi_HV->size[1];
  phi_HV->size[0] = 9;
  loop_ub = (int)V_tunableEnvironment[0];
  phi_HV->size[1] = loop_ub;
  emxEnsureCapacity_real_T(phi_HV, i4);
  loop_ub *= 9;
  for (i4 = 0; i4 < loop_ub; i4++) {
    phi_HV->data[i4] = 0.0;
  }

  emxInit_real_T(&phi_HW, 2);
  i4 = phi_HW->size[0] * phi_HW->size[1];
  phi_HW->size[0] = 9;
  loop_ub = (int)W_tunableEnvironment[0];
  phi_HW->size[1] = loop_ub;
  emxEnsureCapacity_real_T(phi_HW, i4);
  loop_ub *= 9;
  for (i4 = 0; i4 < loop_ub; i4++) {
    phi_HW->data[i4] = 0.0;
  }

  i4 = i5 - 1;
  if (0 <= i4) {
    b_loop_ub = i;
  }

  emxInit_real_T(&b_x, 1);
  for (j = 0; j < i5; j++) {
    loop_ub = b_x->size[0];
    b_x->size[0] = i;
    emxEnsureCapacity_real_T(b_x, loop_ub);
    for (loop_ub = 0; loop_ub < b_loop_ub; loop_ub++) {
      b_x->data[loop_ub] = x->data[loop_ub];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      absxk = fabs(b_x->data[loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      /* fill the Hessian of column for its corresponding diagonal spots in */
      /* Hessian of x */
      for (loop_ub = 0; loop_ub < 9; loop_ub++) {
        phi_HU->data[loop_ub + 9 * j] = 2.0 / t;
      }
    }
  }

  if (0 <= i4) {
    c_loop_ub = i1 - nv;
  }

  for (j = 0; j < i5; j++) {
    i = b_x->size[0];
    b_x->size[0] = i1 - nv;
    emxEnsureCapacity_real_T(b_x, i);
    for (i = 0; i < c_loop_ub; i++) {
      b_x->data[i] = x->data[nv + i];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      absxk = fabs(b_x->data[loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      for (i = 0; i < 9; i++) {
        phi_HV->data[i + 9 * j] = 2.0 / t;
      }
    }
  }

  if (0 <= i4) {
    d_loop_ub = i3 - i2;
  }

  for (j = 0; j < i5; j++) {
    i = b_x->size[0];
    b_x->size[0] = i3 - i2;
    emxEnsureCapacity_real_T(b_x, i);
    for (i = 0; i < d_loop_ub; i++) {
      b_x->data[i] = x->data[i2 + i];
    }

    y = 0.0;
    scale = 3.3121686421112381E-170;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      absxk = fabs(b_x->data[loop_ub + 9 * j]);
      if (absxk > scale) {
        b_t = scale / absxk;
        y = y * b_t * b_t + 1.0;
        scale = absxk;
      } else {
        b_t = absxk / scale;
        y += b_t * b_t;
      }
    }

    y = scale * sqrt(y);
    if (y >= R) {
      for (i = 0; i < 9; i++) {
        phi_HW->data[i + 9 * j] = 2.0 / t;
      }
    }
  }

  i = b_x->size[0];
  b_x->size[0] = (9 * phi_HU->size[1] + 9 * phi_HV->size[1]) + 9 * phi_HW->size
    [1];
  emxEnsureCapacity_real_T(b_x, i);
  loop_ub = 9 * phi_HU->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_x->data[i] = phi_HU->data[i];
  }

  loop_ub = 9 * phi_HV->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_x->data[i + 9 * phi_HU->size[1]] = phi_HV->data[i];
  }

  loop_ub = 9 * phi_HW->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_x->data[(i + 9 * phi_HU->size[1]) + 9 * phi_HV->size[1]] = phi_HW->data[i];
  }

  emxFree_real_T(&phi_HW);
  emxFree_real_T(&phi_HV);
  emxFree_real_T(&phi_HU);
  nv = b_x->size[0];
  i = outputFcn->size[0] * outputFcn->size[1];
  outputFcn->size[0] = b_x->size[0];
  outputFcn->size[1] = b_x->size[0];
  emxEnsureCapacity_real_T(outputFcn, i);
  loop_ub = b_x->size[0] * b_x->size[0];
  for (i = 0; i < loop_ub; i++) {
    outputFcn->data[i] = 0.0;
  }

  for (j = 0; j < nv; j++) {
    outputFcn->data[j + outputFcn->size[0] * j] = b_x->data[j];
  }

  emxFree_real_T(&b_x);

  /*  %log-barrier function and derivatives */
  /*  c = m+n; %number of functions in the sum, which is the total number of columns in U and V */
  /*  phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1)))); */
  /*  phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))]; */
}

double evalPenaltyFcn_CP(const emxArray_real_T *x, double t, double R, const
  double U_tunableEnvironment[1], const double V_tunableEnvironment[1], const
  double W_tunableEnvironment[1])
{
  double outputFcn;
  double y;
  int i;
  int i1;
  emxArray_real_T *b_y;
  emxArray_real_T *a;
  double c_tmp;
  int b_i;
  int nx;
  int k;
  emxArray_real_T *c_y;
  int npages;
  emxArray_real_T *z1;
  emxArray_real_T *b_z1;
  emxArray_real_T *c_z1;
  double d_y;

  /* Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,W,i) */
  /* as t decreases, the penalty gets larger */
  /* R is the radius of the spheres we constrain the columns in  */
  /* U,V,W are matricization functions */
  /* i is the index of output function. 1=f,2=grad,3=H. */
  y = 9.0 * V_tunableEnvironment[0] + 1.0;
  if (y > V_tunableEnvironment[0] * 18.0) {
    i = 1;
  } else {
    i = (int)y;
  }

  y = W_tunableEnvironment[0] * 18.0 + 1.0;
  if (y > x->size[0]) {
    i1 = 1;
  } else {
    i1 = (int)y;
  }

  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);

  /* phi, if norm(column)>=R, this sum increases */
  c_tmp = R * R;
  b_i = a->size[0] * a->size[1];
  a->size[0] = 9;
  nx = (int)U_tunableEnvironment[0];
  a->size[1] = nx;
  emxEnsureCapacity_real_T(a, b_i);
  nx *= 9;
  for (b_i = 0; b_i < nx; b_i++) {
    a->data[b_i] = x->data[b_i];
  }

  b_i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 9;
  b_y->size[1] = a->size[1];
  emxEnsureCapacity_real_T(b_y, b_i);
  nx = 9 * a->size[1];
  for (k = 0; k < nx; k++) {
    b_y->data[k] = a->data[k] * a->data[k];
  }

  emxInit_real_T(&c_y, 2);
  if (b_y->size[1] == 0) {
    c_y->size[0] = 1;
    c_y->size[1] = 0;
  } else {
    npages = b_y->size[1];
    b_i = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_real_T(c_y, b_i);
    for (b_i = 0; b_i < npages; b_i++) {
      nx = b_i * 9;
      y = b_y->data[nx];
      for (k = 0; k < 8; k++) {
        y += b_y->data[(nx + k) + 1];
      }

      c_y->data[b_i] = y;
    }
  }

  b_i = c_y->size[0] * c_y->size[1];
  nx = c_y->size[0] * c_y->size[1];
  c_y->size[0] = 1;
  emxEnsureCapacity_real_T(c_y, nx);
  nx = b_i - 1;
  for (b_i = 0; b_i <= nx; b_i++) {
    c_y->data[b_i] -= c_tmp;
  }

  emxInit_real_T(&z1, 2);
  b_i = z1->size[0] * z1->size[1];
  z1->size[0] = 1;
  z1->size[1] = c_y->size[1];
  emxEnsureCapacity_real_T(z1, b_i);
  nx = c_y->size[1];
  for (k = 0; k < nx; k++) {
    y = c_y->data[k];
    if ((0.0 > y) || rtIsNaN(y)) {
      z1->data[k] = 0.0;
    } else {
      z1->data[k] = y;
    }
  }

  b_i = a->size[0] * a->size[1];
  a->size[0] = 9;
  nx = (int)V_tunableEnvironment[0];
  a->size[1] = nx;
  emxEnsureCapacity_real_T(a, b_i);
  nx *= 9;
  for (b_i = 0; b_i < nx; b_i++) {
    a->data[b_i] = x->data[(i + b_i) - 1];
  }

  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 9;
  b_y->size[1] = a->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  nx = 9 * a->size[1];
  for (k = 0; k < nx; k++) {
    b_y->data[k] = a->data[k] * a->data[k];
  }

  if (b_y->size[1] == 0) {
    c_y->size[0] = 1;
    c_y->size[1] = 0;
  } else {
    npages = b_y->size[1];
    i = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_real_T(c_y, i);
    for (b_i = 0; b_i < npages; b_i++) {
      nx = b_i * 9;
      y = b_y->data[nx];
      for (k = 0; k < 8; k++) {
        y += b_y->data[(nx + k) + 1];
      }

      c_y->data[b_i] = y;
    }
  }

  i = c_y->size[0] * c_y->size[1];
  b_i = c_y->size[0] * c_y->size[1];
  c_y->size[0] = 1;
  emxEnsureCapacity_real_T(c_y, b_i);
  nx = i - 1;
  for (i = 0; i <= nx; i++) {
    c_y->data[i] -= c_tmp;
  }

  emxInit_real_T(&b_z1, 2);
  i = b_z1->size[0] * b_z1->size[1];
  b_z1->size[0] = 1;
  b_z1->size[1] = c_y->size[1];
  emxEnsureCapacity_real_T(b_z1, i);
  nx = c_y->size[1];
  for (k = 0; k < nx; k++) {
    y = c_y->data[k];
    if ((0.0 > y) || rtIsNaN(y)) {
      b_z1->data[k] = 0.0;
    } else {
      b_z1->data[k] = y;
    }
  }

  i = a->size[0] * a->size[1];
  a->size[0] = 9;
  b_i = (int)W_tunableEnvironment[0];
  a->size[1] = b_i;
  emxEnsureCapacity_real_T(a, i);
  nx = 9 * b_i;
  for (i = 0; i < nx; i++) {
    a->data[i] = x->data[(i1 + i) - 1];
  }

  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 9;
  b_y->size[1] = a->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  nx = 9 * a->size[1];
  for (k = 0; k < nx; k++) {
    b_y->data[k] = a->data[k] * a->data[k];
  }

  emxFree_real_T(&a);
  if (b_y->size[1] == 0) {
    c_y->size[0] = 1;
    c_y->size[1] = 0;
  } else {
    npages = b_y->size[1];
    i = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_y->size[1];
    emxEnsureCapacity_real_T(c_y, i);
    for (b_i = 0; b_i < npages; b_i++) {
      nx = b_i * 9;
      y = b_y->data[nx];
      for (k = 0; k < 8; k++) {
        y += b_y->data[(nx + k) + 1];
      }

      c_y->data[b_i] = y;
    }
  }

  emxFree_real_T(&b_y);
  i = c_y->size[0] * c_y->size[1];
  i1 = c_y->size[0] * c_y->size[1];
  c_y->size[0] = 1;
  emxEnsureCapacity_real_T(c_y, i1);
  nx = i - 1;
  for (i = 0; i <= nx; i++) {
    c_y->data[i] -= c_tmp;
  }

  emxInit_real_T(&c_z1, 2);
  i = c_z1->size[0] * c_z1->size[1];
  c_z1->size[0] = 1;
  c_z1->size[1] = c_y->size[1];
  emxEnsureCapacity_real_T(c_z1, i);
  nx = c_y->size[1];
  for (k = 0; k < nx; k++) {
    y = c_y->data[k];
    if ((0.0 > y) || rtIsNaN(y)) {
      c_z1->data[k] = 0.0;
    } else {
      c_z1->data[k] = y;
    }
  }

  emxFree_real_T(&c_y);
  nx = z1->size[1];
  if (z1->size[1] == 0) {
    y = 0.0;
  } else {
    y = z1->data[0];
    for (k = 2; k <= nx; k++) {
      y += z1->data[k - 1];
    }
  }

  emxFree_real_T(&z1);
  nx = b_z1->size[1];
  if (b_z1->size[1] == 0) {
    c_tmp = 0.0;
  } else {
    c_tmp = b_z1->data[0];
    for (k = 2; k <= nx; k++) {
      c_tmp += b_z1->data[k - 1];
    }
  }

  emxFree_real_T(&b_z1);
  nx = c_z1->size[1];
  if (c_z1->size[1] == 0) {
    d_y = 0.0;
  } else {
    d_y = c_z1->data[0];
    for (k = 2; k <= nx; k++) {
      d_y += c_z1->data[k - 1];
    }
  }

  emxFree_real_T(&c_z1);
  outputFcn = 1.0 / t * ((y + c_tmp) + d_y);

  /*  %log-barrier function and derivatives */
  /*  c = m+n; %number of functions in the sum, which is the total number of columns in U and V */
  /*  phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1)))); */
  /*  phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))]; */
  return outputFcn;
}

/* End of code generation (evalPenaltyFcn_CP.c) */
