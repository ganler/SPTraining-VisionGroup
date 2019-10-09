function [Projection_Matrix] = proj(f)
%相机坐标投影(projection)成图像坐标
%输入参数
%   f                   相机焦距（数，cm）
%输出参数
%   Projection_Matrix   投影成像（矩阵）
Projection_Matrix = [f 0 0 0; 0 f 0 0; 0 0 1 0];
return
