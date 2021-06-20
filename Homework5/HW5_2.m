clc;
q = [1 0 0 0];
acc = xlsread('HW5-2.xls');
deltaT = 0.001;
iter = 1000;
qua_predict = zeros(100,4);

for j = 1:100
    for i = 1:iter
        norm = sqrt(sum(acc(j,:).^2));
        a_x = acc(j,1) / norm;
        a_y = acc(j,2) / norm;
        a_z = acc(j,3) / norm;
        
        f_1 = -2 * (q(2) * q(4) - q(1) * q(3)) - a_x;
        f_2 = -2 * (q(1) * q(2) + q(3) * q(4)) - a_y;
        f_3 = -2 * (0.5 - q(2) * q(2) - q(3) * q(3)) - a_z;
        f = [f_1;f_2;f_3];
        J = [ 2*q(3) -2*q(4)  2*q(1) -2*q(2);
             -2*q(2) -2*q(1) -2*q(4) -2*q(3);
                  0   4*q(2)  4*q(3)      0 ];
        G = J'*f;
        
        norm = sqrt(sum(G(:,1).^2));
        G = G / norm;
        q = q - deltaT * G';
        norm = sqrt(sum(q.^2));
        q = q / norm;
    end
    for k = 1:4
        qua_predict(j,k) = q(k);
    end
    
    quat1 = quaternion(q(1),q(2),q(3),q(4));
    [a,b,c,d] = parts(quat1);
    quat1inv = quatinv([a,b,c,d]);
    quat1inv = quaternion(quat1inv);
    quat2 = quaternion(0,0,0,-9.8);
    
    quat2 = quat1inv * quat2 * quat1;
    [A(j,:),B(j,:),C(j,:),D(j,:)] = parts(quat2);
end

M = [B,C,D];
csvwrite("acc.csv",M);