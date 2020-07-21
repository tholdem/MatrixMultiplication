#!/bin/bash

ml purge
ml matlab
ml gcc/6.1.0

export LD_LIBRARY_PATH=/curc/sw/intel/17.4/mkl/lib/intel64:/curc/sw/intel/17.4/lib/intel64:/curc/sw/intel/17.4/mkl/include:$LD_LIBRARY_PATH
./cubicRegScriptCOPY 1 2 22 5 100 0.1 1e-6 1e3 
