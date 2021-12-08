function fct=moindreCarre(x,y,m=4)
  Q = zeros(m, m);
  V = zeros(m, 1);
  for c=0:m-1
    for r=0:m-1
      [Q(r+1, c+1), V(r+1, 1)] = generateLine(x, y, c, r);
    endfor
  endfor
  a = Q\V;
  Q
  V
  a
  fct = @(z) applyMoindreCarre(z, a);
endfunction

function r=applyMoindreCarre(x,a)
  r=0;
  for k=1:length(a)
    r+= a(k) * x.^(k-1);
  endfor
  
endfunction

function [q,v]=generateLine(x, y, c, r)
  q = 0;
  v = 0;
  for i= 1:length(x)
    q += x(i).^c * x(i).^r;
    v += x(i).^r * y(i);
  endfor
endfunction