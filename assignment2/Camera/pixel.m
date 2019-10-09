function [Pixel_Matrix] = pixel(dx,dy,u0,v0)
%图像坐标离散化，转化为像素坐标
%输入参数：
%   dx      x轴方向上分辨率，像素大小
%   dy      y轴方向上分辨率，像素大小
%   (u0,v0) 参考坐标，图像平面中心
if nargin==2
    u0 = 0;
    v0 = 0;
end
Pixel_Matrix = [1/dx 0 u0; 0 1/dy v0; 0 0 1];
return 
