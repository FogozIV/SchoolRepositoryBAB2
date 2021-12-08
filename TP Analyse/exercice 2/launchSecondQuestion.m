
xGenerated = -5:0.001:5;

function y=fct(x)
  y = (1 + x.^2).^-1;
endfunction

polynomial5 = polynomialInterpolationFromFunction(@(x) fct(x), 6, -5, 5);
polynomial11 = polynomialInterpolationFromFunction(@(x) fct(x), 11, -5, 5);

yGenerated = fct(xGenerated);
yPol5 = polynomial5(xGenerated);
yPol11 = polynomial11(xGenerated);


plot(xGenerated, yGenerated)
title("Question 2")
hold on

plot(xGenerated, yPol5, "r");
plot(xGenerated, yPol11, "g");


legend("1/(1+x^2)", "Polynomial Interpolation 5", "Polynomial Interpolation 11");

hold off