/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fwrite.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "fwrite.h"
#include "fclose.h"
#include "cubicRegScript4Coder_rtwutil.h"
#include "cubicRegScript4Coder_data.h"

/* Type Definitions */
#include <stddef.h>

/* Function Definitions */

/*
 * Arguments    : double fileID
 *                const emxArray_real_T *x
 * Return Type  : void
 */
void b_fwrite(double fileID, const emxArray_real_T *x)
{
  signed char fileid;
  FILE * filestar;
  boolean_T autoflush;
  size_t bytesOutSizet;
  fileid = (signed char)rt_roundd_snf(fileID);
  if ((fileid < 0) || (fileID != fileid)) {
    fileid = -1;
  }

  if (fileid >= 3) {
    filestar = eml_openfiles[fileid - 3];
    autoflush = eml_autoflush[fileid - 3];
  } else if (fileid == 0) {
    filestar = stdin;
    autoflush = true;
  } else if (fileid == 1) {
    filestar = stdout;
    autoflush = true;
  } else if (fileid == 2) {
    filestar = stderr;
    autoflush = true;
  } else {
    filestar = NULL;
    autoflush = true;
  }

  if (!(fileID != 0.0)) {
    filestar = NULL;
  }

  if ((filestar == NULL) || (x->size[0] == 0)) {
  } else {
    bytesOutSizet = fwrite(&x->data[0], (size_t)sizeof(double), (size_t)x->size
      [0], filestar);
    if (((double)bytesOutSizet > 0.0) && autoflush) {
      fflush(filestar);
    }
  }
}

/*
 * File trailer for fwrite.c
 *
 * [EOF]
 */
