clc
clear
close all
%all the data are derived from C++ code.

x= [-4,3,8];
y= [3,5,4];


p1 = [3 3.19413 3.37672 3.54807 3.70848 3.85824 3.99764 4.127 4.2466 4.35674 4.45773 4.54985 4.6334 4.70869 4.776 4.83564 4.88791 4.93309 4.9715 5.00342 5.02915 5.049 5.06325 5.07221 5.07617 5.07544 5.0703 5.06105 5.048 5.03144 5.01166 4.98897 4.96366 4.93603 4.90638 4.875 4.84219 4.80825 4.77348 4.73817 4.70262 4.66713 4.632 4.59752 4.56399 4.53171 4.50097 4.47207 4.44532 4.421 4.39942 4.38087 4.36564 4.35405 4.34638 4.34293 4.344 4.34989 4.36089 4.3773 4.39942 4.42754 4.46197 4.503 4.55093 4.60605 4.66866 4.73907 4.81756 4.90444 5 5.10074 5.20269 5.30547 5.4087 5.512 5.61498 5.71725 5.81843 5.91814 6.016 6.11162 6.20461 6.29459 6.38118 6.464 6.54266 6.61677 6.68595 6.74982 6.808 6.8601 6.90573 6.94451 6.97606 7 7.01594 7.02349 7.02227 7.0119 6.992 6.96218 6.92205 6.87123 6.80934 6.736 6.65082 6.55341 6.44339 6.32038 6.184 6.03386 5.86957 5.69075 5.49702 5.288 5.0633 4.82253 4.56531 4.29126 4 4];

t = [-4 -3.9 -3.8 -3.7 -3.6 -3.5 -3.4 -3.3 -3.2 -3.1 -3 -2.9 -2.8 -2.7 -2.6 -2.5 -2.4 -2.3 -2.2 -2.1 -2 -1.9 -1.8 -1.7 -1.6 -1.5 -1.4 -1.3 -1.2 -1.1 -1 -0.9 -0.8 -0.7 -0.6 -0.5 -0.4 -0.3 -0.2 -0.1 2.41474e-15 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3 3.1 3.2 3.3 3.4 3.5 3.6 3.7 3.8 3.9 4 4.1 4.2 4.3 4.4 4.5 4.6 4.7 4.8 4.9 5 5.1 5.2 5.3 5.4 5.5 5.6 5.7 5.8 5.9 6 6.1 6.2 6.3 6.4 6.5 6.6 6.7 6.8 6.9 7 7.1 7.2 7.3 7.4 7.5 7.6 7.7 7.8 7.9 8 8];

p2 = [ 3 3.19759 3.39034 3.57818 3.76109 3.939 4.11187 4.27966 4.4423 4.59977 4.752 4.89895 5.04058 5.17682 5.30765 5.433 5.55283 5.6671 5.77574 5.87873 5.976 6.06751 6.15322 6.23306 6.30701 6.375 6.43699 6.49294 6.54278 6.58649 6.624 6.65527 6.68026 6.6989 6.71117 6.717 6.71635 6.70918 6.69542 6.67505 6.648 6.61423 6.5737 6.52634 6.47213 6.411 6.34291 6.26782 6.18566 6.09641 6 5.89775 5.792 5.68425 5.576 5.46875 5.364 5.26325 5.168 5.07975 5 4.93025 4.872 4.82675 4.796 4.78125 4.784 4.80575 4.848 4.91225 5 5.10074 5.20269 5.30547 5.4087 5.512 5.61498 5.71725 5.81843 5.91814 6.016 6.11162 6.20461 6.29459 6.38118 6.464 6.54266 6.61677 6.68595 6.74982 6.808 6.8601 6.90573 6.94451 6.97606 7 7.01594 7.02349 7.02227 7.0119 6.992 6.96218 6.92205 6.87123 6.80934 6.736 6.65082 6.55341 6.44339 6.32038 6.184 6.03386 5.86957 5.69075 5.49702 5.288 5.0633 4.82253 4.56531 4.29126 4 4];





plot(t,p1)

hold on 
plot(t,p2)
plot(x,y,'r*')
plot(1,6,'b*')