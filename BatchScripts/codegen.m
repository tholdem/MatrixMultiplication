ml slurm/blanca
sinteractive --partition=blanca-appm -N 1 -n 1 

ml purge
ml matlab/R2018b
ml intel/17.4
ml mkl/17.3
cd matrixMulti/batchScripts 
matlab

cfg = coder.config('exe');
cfg.CustomSource = 'main.c';
cfg.CustomInclude = '/home/zhwa9431/matrixMulti/batchScripts';
cfg.CustomLAPACKCallback = 'myLAPACK';
cfg.CustomBLASCallback = 'myBLAS';
codegen cubicRegScript4Coder -args {0,0,0,coder.typeof(0.1),coder.typeof(1e-06),coder.typeof(1e08),coder.typeof('~/zhwa9431')} -config cfg -report

exit
/usr/bin/time ./cubicRegScript4Coder 1 5 27 0.1 1e-6 1e3 "/projects/zhwa9431/matrixMulti/cubicReg/output"

cubicRegScript(1,5,27,0.1,1e-6,1e3,'/projects/zhwa9431/matrixMulti/cubicReg/output')

tic
cubicRegScript(1,1,22,0.5,1e-6,5e2,"C:\Users\bryan\Documents\GitHub\MatrixMultiplication\BatchScripts")
toc
