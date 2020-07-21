rng('default');
i=1;
num=2;
rank=22;
t=5;
R=100;
k=0.1;
errThd=1e-06;
maxIts=1e03;
f=@() cubicRegScriptCOPY(i,num,rank,t,R,k,errThd,maxIts);
time1=timeit(f);
tic
cubicRegScriptCOPY(i,num,rank,t,R,k,errThd,maxIts);
toc
g=@() system('cubicRegScriptCOPY 1 2 22 5 100 0.1 1e-06 1e3');
time2=timeit(g);
tic
system('cubicRegScriptCOPY 1 2 22 5 100 0.1 1e-06 1e3');
toc


