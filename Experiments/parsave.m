function parsave(fname, x0,x,errorHistory,Out) %#codegen
  save(fname, 'x0','x','errorHistory','Out');
end