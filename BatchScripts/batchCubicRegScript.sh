#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=2:00:00
#SBATCH --ntasks=2
#SBATCH --job-name=batchCubicRegScript
#SBATCH --output=batchCubicRegScript.out

module purge

module load matlab

matlab -nodesktop -nodisplay -r "clear;addpath(genpath('/home/zhwa9431')); cubicRegScript($1,$2,$3,$4,$5,$6,$7,'$8');exit;"