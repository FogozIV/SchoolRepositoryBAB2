clear all;
clc;
[abscisse, ordonnee] = bissection(@(x) sin(2*x), -5, 5, 1, 0.001);



x = -5:0.001:5;
y = sin(2*x);

plot(x, y, "b");
hold on
title("Question 3");
plot(abscisse, ordonnee, "o");
hold off