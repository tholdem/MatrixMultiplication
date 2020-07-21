/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cubicRegScriptCOPY_api.c
 *
 * Code generation for function '_coder_cubicRegScriptCOPY_api'
 *
 */

/* Include files */
#include "_coder_cubicRegScriptCOPY_api.h"
#include "_coder_cubicRegScriptCOPY_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "cubicRegScriptCOPY",                /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *i, const
  char_T *identifier);

/* Function Definitions */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *i, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(i), &thisId);
  emlrtDestroyArray(&i);
  return y;
}

void cubicRegScriptCOPY_api(const mxArray * const prhs[8], int32_T nlhs)
{
  real_T i;
  real_T num;
  real_T rank;
  real_T t;
  real_T R;
  real_T k;
  real_T errThd;
  real_T maxIts;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  i = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "i");
  num = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "num");
  rank = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "rank");
  t = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "t");
  R = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "R");
  k = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "k");
  errThd = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "errThd");
  maxIts = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "maxIts");

  /* Invoke the target function */
  cubicRegScriptCOPY(i, num, rank, t, R, k, errThd, maxIts);
}

void cubicRegScriptCOPY_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  cubicRegScriptCOPY_xil_terminate();
  cubicRegScriptCOPY_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void cubicRegScriptCOPY_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void cubicRegScriptCOPY_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_cubicRegScriptCOPY_api.c) */
