/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fileManager.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 13:59:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cubicRegScript4Coder.h"
#include "fileManager.h"
#include "cubicRegScript4Coder_emxutil.h"
#include "cubicRegScript4Coder_data.h"

/* Function Declarations */
static signed char filedata(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char filedata(void)
{
  signed char f;
  int k;
  boolean_T exitg1;
  f = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 20)) {
    if (eml_openfiles[k] == NULL) {
      f = (signed char)(k + 1);
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/*
 * Arguments    : const emxArray_char_T *cfilename
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char cfopen(const emxArray_char_T *cfilename, const char * cpermission)
{
  signed char fileid;
  signed char j;
  emxArray_char_T *ccfilename;
  int i21;
  int loop_ub;
  FILE * filestar;
  fileid = -1;
  j = filedata();
  if (j >= 1) {
    emxInit_char_T(&ccfilename, 2);
    i21 = ccfilename->size[0] * ccfilename->size[1];
    ccfilename->size[0] = 1;
    ccfilename->size[1] = cfilename->size[1] + 1;
    emxEnsureCapacity_char_T(ccfilename, i21);
    loop_ub = cfilename->size[1];
    for (i21 = 0; i21 < loop_ub; i21++) {
      ccfilename->data[i21] = cfilename->data[i21];
    }

    ccfilename->data[cfilename->size[1]] = '\x00';
    filestar = fopen(&ccfilename->data[0], cpermission);
    emxFree_char_T(&ccfilename);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i21 = j + 2;
      if (i21 > 127) {
        i21 = 127;
      }

      fileid = (signed char)i21;
    }
  }

  return fileid;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void filedata_init(void)
{
  FILE * a;
  int i;
  a = NULL;
  for (i = 0; i < 20; i++) {
    eml_autoflush[i] = false;
    eml_openfiles[i] = a;
  }
}

/*
 * File trailer for fileManager.c
 *
 * [EOF]
 */
