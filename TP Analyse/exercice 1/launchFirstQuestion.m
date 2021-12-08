x=[0;1;2;4;5;6;7;9;10;11];
y=[0;0;1;1;0;0;1;1;0;0];
polyFct = polynomialInterpolation(x,y);
splineFct = spline(x,y);
moindreCarreFct = moindreCarre(x,y);


xgenerated = -0.1:0.001:11.5;
ypoly=polyFct(xgenerated);
yspline=splineFct(xgenerated);
yMoindreCarre = moindreCarreFct(xgenerated);

plot(x,y, "o")
title("Question 1")

hold on

plot(xgenerated, ypoly,"r");

plot(xgenerated, yspline, "g");

plot(xgenerated, yMoindreCarre, "b");

legend("point", "Polynomial Interpolation", "Spline", "Moindre carré");
hold off