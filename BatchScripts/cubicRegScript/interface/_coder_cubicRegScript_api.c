/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_cubicRegScript_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 15:07:30
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_cubicRegScript_api.h"
#include "_coder_cubicRegScript_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "cubicRegScript",                    /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *outputDir,
  const char_T *identifier, char_T y[10]);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[10]);
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *i, const
  char_T *identifier);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[10]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *outputDir
 *                const char_T *identifier
 *                char_T y[10]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *outputDir,
  const char_T *identifier, char_T y[10])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(outputDir), &thisId, y);
  emlrtDestroyArray(&outputDir);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y[10]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[10])
{
  f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *i
 *                const char_T *identifier
 * Return Type  : real_T
 */
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret[10]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[10])
{
  static const int32_T dims[2] = { 1, 10 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims);
  emlrtImportCharArrayR2015b(sp, src, &ret[0], 10);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[7]
 *                int32_T nlhs
 * Return Type  : void
 */
void cubicRegScript_api(const mxArray * const prhs[7], int32_T nlhs)
{
  real_T i;
  real_T num;
  real_T rank;
  real_T k;
  real_T errThd;
  real_T maxIts;
  char_T outputDir[10];
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
  k = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "k");
  errThd = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "errThd");
  maxIts = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "maxIts");
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "outputDir", outputDir);

  /* Invoke the target function */
  cubicRegScript(i, num, rank, k, errThd, maxIts, outputDir);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void cubicRegScript_atexit(void)
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
  cubicRegScript_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void cubicRegScript_initialize(void)
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

/*
 * Arguments    : void
 * Return Type  : void
 */
void cubicRegScript_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_cubicRegScript_api.c
 *
 * [EOF]
 */
