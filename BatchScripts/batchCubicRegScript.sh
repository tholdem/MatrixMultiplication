#!/bin/bash
#SBATCH --nodes=1
#SBATCH --qos=preemptable
#SBATCH --time=24:00:00
#SBATCH --ntasks=1
#SBATCH --job-name=batchCubicRegScript
#SBATCH --export=NONE
#SBATCH --constraint="avx2"
#SBATCH --output=/projects/zhwa9431/matrixMulti/cubicReg/output/stdout/%a.out
##SBATCH --account=blanca-appm
##SBATCH --qos=blanca-appm
##SBATCH --partition=blanca-appm


i=${SLURM_ARRAY_TASK_ID}

module purge

module load matlab

matlab -nodesktop -nodisplay -r "clear;addpath(genpath('/home/zhwa9431')); cubicRegScript(${i},$1,$2,$3,$4,$5,'$6');exit;"

