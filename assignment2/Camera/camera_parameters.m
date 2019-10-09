function [Camera_Parameters] = camera_parameters()
% 将世界坐标转化为像素坐标的参数(相机参数矩阵)
% 参数,可以省，省去的话，必须设置相应的入参
Phi = pi/4;%绕x轴旋转角度
Psi = pi/4;%绕y轴旋转角度
Theta = pi/4;%绕z轴旋转角度
x0 = 0;%x平移量
y0 = 0;%y平移量
z0 = 0;%z平移量
f = 35e-3;%35mm相机
dx = 0.026;%一个像素的长
dy = 0.026;%一个像素的宽
u0 = 0;
v0 =0;
 
%% step1:将世界坐标转化为相机坐标，等比例缩小，外加旋转平移(刚体变换)
RT = (Phi, Psi, Theta, x0, y0, z0);%刚体变换矩阵
 
%% step2:将相机坐标转化为图像坐标(投影)
Projection_Matrix = proj(f);%投影矩阵
 
%% step3:将图像坐标离散抽样
Pixel_Matrix = pixel(dx,dy,u0,v0);%1像素＝0.635厘米÷24≈0.026458厘米
%% 数据整合
Camera_Internal_Parameters = Pixel_Matrix * Projection_Matrix;%相机内参数
Camera_External_Parameters = RT;%相机外参数
%相机参数
Camera_Parameters = Camera_Internal_Parameters*Camera_External_Parameters; 
