function fct=polynomialInterpolationFromFunction(f, n, a, b)
  interval = b-a;
  x =a:interval/(n-1):b;
  y = f(x);
  fct=polynomialInterpolation(x,y);
endfunction