clear 
clc
close all
x = [-4 7 ]; %x???x
y = [3  5]; %y???
s = [2 -1]; %???

F = [x(1)^3     x(1)^2      x(1)        1;
     x(2)^3     x(2)^2      x(2)        1;
     3*x(1)^2   2*x(1)      1           0;
     3*x(2)^2   2*x(2)      1           0]
 
rank(F)
 
B =[y(1);
    y(2);
    s(1);
    s(2)]

A = F\B

c = -100:0.001:100;
v = A(1)*c.^3 +A(2)*c.^2 + A(3)*c +A(4);

plot(c,v)
hold on
plot(x,y,'*')