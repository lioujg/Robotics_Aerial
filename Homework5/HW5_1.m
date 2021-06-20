data = xlsread('HW5-1.xls');
A = ones(50,3);
for i = 1:50
    A(i,1) = data(i,1);
    A(i,2) = data(i,2);
end
Y = data(:,3);
x = (((A.') * A) \ (A.')) * Y;
%.' transpose
%\ inverse. And it's better than inv()
disp(x);