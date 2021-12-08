function fct=spline(x,y)
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
  %start 
  n = length(y);
  for l=1:n-1
    h(l) = x(l+1) - x(l); % step
  endfor
  A = zeros(n,n);
  b = zeros(n,1);
  for k=1: n-2
    A(k,k) = h(k);
    A(k,k+1) = 2*(h(k) + h(k+1));
    A(k,k+2) = h(k+1);
    b(k) = 6*((y(k+2) - y(k+1))/h(k+1) - (y(k+1) - y(k))/h(k));
  endfor
  %defined value
  A(n-1, n) = 1;
  A(n, n) = 1;
  M = A\b;
  M(1) =0;
  M(n) = 0;
  %generating vectors of data
  for k=1: n-1
    a(k) = (M(k+1) - M(k))/(6*h(k));
    b(k) = M(k)/2;
    c(k) = (y(k+1) - y(k))/h(k) - h(k)/6 * (M(k+1) + 2 * M(k));
    d(k) = y(k);
  endfor
  %generating function that will allow us to draw it much more easily
  fct= @(v) (splineFct(v, x, y, a, b, c, d)); 
endfunction

function z=splineFct(v, x, y, a, b, c, d)
  z=zeros(length(v), 1);
  %for each element in v just in case it's a vector
  for h=1:length(v)
    %%check if outer or inner the space where our spline can be drawn
    if(v(h) < x(1) == 1)
      z(h) = 0;
    elseif(v(h) > x(length(x)) == 1)
      z(h) = 0;
    else
      %set value to 1 just in case but should not be necessary 
      value = 1;
      for k=2:length(x)
        if(v(h) <= x(k))
          value = k-1;
          break; %break out of the loop because we found the index we were looking for
        endif
      endfor
      %generate the result based on the position of the point relative to the x values
      z(h) = a(value) * (v(h)-x(value)).^3 + b(value) * (v(h)-x(value)).^2 + c(value) * (v(h)-x(value)) + d(value);
    endif
  endfor
endfunction