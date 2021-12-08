function fct=polynomialInterpolation(x, y)
  %First methods using monomes
  sizeX = size(x);
  sizeY = size(y);
  %normalizing our vector to be verticals
  if(sizeX(1) == 1)
    x=x';
  endif
  if(sizeY(1) == 1)
    y=y';
  endif
  sizeY = length(y);
  for c=1:sizeY
    V(:,c) = x.^(c-1);
  endfor
  a=V\y;
  %allows us to use result on any x
  fct = @(x) (use(x, a));
endfunction

function r=use(x, a)
  r = 0;
  for d= 1: length(a)
    r+=a(d) * x.^(d-1);
  endfor
endfunction