#!/bin/bash

if [ $# -lt 2 ]
then
	echo "USAGE : batchCubicRegScript.sh <number of repetition> <rank> <penalty inverse scaling parameter t(default: 5)> <radius of penalty (default: 100)> <scaling factor k of initial point (default: 0.1)> <error tolerance (default: 1e-6)> <maximum iterations: default: 1e5>"
	exit
fi
N=$1
rank=$2
if [ -z "$3" ]
then
	t=5
else
	t=$3
fi
if [ -z "$4" ]
then
	R=100
else
	R=$4
fi
if [ -z "$5" ]
then
    k=0.1
else
	k=$5
fi
if [ -z "$6" ]
then
    errTol=1e-06
else
	errTol=$6
fi
if [ -z "$7" ]
then
    maxIts=1e05
else
	maxIts=$7
fi
script_path=/home/zhwa9431/matrixMulti/batchScripts
output_path=/projects/zhwa9431/matrixMulti/cubicReg/output/rank${rank}_t${t}_R${R}_k${k}_error${errTol}_maxIts${maxIts}

if [ ! -d $output_path ]; then
  mkdir -p $output_path;
fi

for (( i=1; i<=$N; i++ )); do
	sbatch ${script_path}/batchCubicRegScript.sh $i $rank $t $R $k $errTol $maxIts $output_path
done 