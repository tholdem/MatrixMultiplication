/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a ss of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "cubicRegScript4Coder.h"
#include "cubicRegScript4Coder_terminate.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static double argInit_real_T(void);
static void main_cubicRegScript4Coder(double i,double num,double rank,float k,double errTol,double maxIts, char *outputDir);

/* Function Definitions */
static double argInit_real_T(void)
{
  return 0.0;
}

static void main_cubicRegScript4Coder(double i,double num,double rank,float k,double errTol,double maxIts, char *outputDir)
{
  /* Initialize function 'cubicRegScript4Coder' input arguments. */

  /* Call the entry-point 'cubicRegScript4Coder'. */
  cubicRegScript4Coder(i, num, rank, k, errTol, maxIts, outputDir);
}

int main(int argc, const char * const argv[])
{
  double i = atof(argv[1]);
  double num = atof(argv[2]);
  double rank = atof(argv[3]);
  float k = atof(argv[4]);
  double errTol = atof(argv[5]);
  double maxIts = atof(argv[6]);
  char *outputDir = argv[7];
  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_cubicRegScript4Coder(i, num, rank, k, errTol, maxIts, outputDir);

  /* Terminate the application.
     You do not need to do this more than one time. */
  cubicRegScript4Coder_terminate();
  return 0;
}

/* End of code generation (main.c) */
