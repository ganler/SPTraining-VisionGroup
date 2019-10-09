function [RT] = rigbt(Phi, Psi, Theta, x0, y0, z0)
%刚体变换函数:rigid body transformation
%输入参数：
%   φ=Phi       绕x轴转动的角度
%   ψ=Psi       绕y轴转动的角度
%   θ=Theta     绕z轴转动的角度
%输出参数：
%    RT 将坐标轴进行刚体变化（旋转+平移）成新的坐标轴
%
%% 程序
R1 = [1 0 0; 0 cos(Phi) sin(Phi); 0 -sin(Phi) cos(Phi)];%绕X轴旋转
R2 = [cos(Psi) 0 -sin(Psi); 0 1 0; sin(Psi) 0 cos(Psi)];%绕Y轴旋转
R3 = [cos(Theta) sin(Theta) 0;-sin(Theta) cos(Theta) 0; 0 0 1 ];%绕Z轴旋转
R = R3 * R1 * R2;%旋转矩阵（刚体变换一部分）
T = [x0; y0; z0];%平移矩阵
RT=[R T;0 0 0 1];%刚体变换矩阵
return
