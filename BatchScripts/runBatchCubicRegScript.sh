#!/bin/bash
N=
n=
rank=22
#t=5
#R=1000
k=0.2
errTol=1e-06
maxIts=1e03
scriptdir=/home/zhwa9431/matrixMulti/batchScripts
outdir=/projects/zhwa9431/matrixMulti/cubicReg/output

print_usage() {
  printf "Usage: runBatchCubicRegScript.sh -N <number of jobs> -n <optional: number of subjobs per job (default: 1e02)> -r <optional: rank (Default:22)> -t <optional: penalty inverse scaling parameter(default: 5)> -R <optional: radius of penalty (default: 100)> -k <optional: scaling factor of initial point (default: 1)> -e <optional: error tolerance (default: 1e-06)> -m <optional: maximum iterations: default: 1e06> -i <optional: script directory(default: '/home/zhwa9431/matrixMulti/batchScripts')> -o <optional: output parent directory (default: '/projects/zhwa9431/matrixMulti/cubicReg/output')>\n"
}

while getopts 'N:n:r:t:R:k:e:m:' flag; do
  case "${flag}" in
    N) N=${OPTARG} ;;
	n) n=${OPTARG} ;;
    r) rank=${OPTARG} ;;
    #t) t=${OPTARG} ;;
    #R) R=${OPTARG} ;;
    k) k=${OPTARG} ;;
    e) errTol=${OPTARG} ;;
    m) maxIts=${OPTARG} ;;
	s) scriptdir="${OPTARG}" ;;
    o) outdir="${OPTARG}" ;;	
    *) print_usage
       exit 1 ;;
  esac
done

if [ -z "${N}" ]; then
    print_usage
	exit 1
fi

if [ -z "${n}" ]; then
    print_usage
	exit 1
fi

output_path=${outdir}/rank${rank}_k${k}_error${errTol}_maxIts${maxIts}

if [ ! -d ${output_path} ]; then
  mkdir -p ${output_path};
fi

sbatch --array=1-${N} ${scriptdir}/batchCubicRegScript.sh ${n} ${rank} ${k} ${errTol} ${maxIts} ${output_path}