function [abscisse, ordonnee]=bissection(f, a, b, h, epsilon=0.1)
  x = a:h:b;
  abscisse = [];
  ordonnee = [];
  for k = 1:length(x) -1
    if(f(x(k))*f(x(k+1)) <= 0)
      [abscisse(end+1), ordonnee(end+1)] = uniqueBissection(f, x(k), x(k+1), epsilon);
    endif
  endfor
endfunction

function [abscisse, ordonnee]=uniqueBissection(f, a, b, epsilon)
  while( abs(b - a) > epsilon)
    newM = (a + b) / 2;
    if(f(a) * f(newM) <= 0)
      b = newM;
    else
      a = newM;
    endif
  endwhile
  abscisse = (a+b)/2;
  ordonnee = f(abscisse);
endfunction