function [Pixel_Matrix] = pixel(dx,dy,u0,v0)
%ͼ��������ɢ����ת��Ϊ��������
%���������
%   dx      x�᷽���Ϸֱ��ʣ����ش�С
%   dy      y�᷽���Ϸֱ��ʣ����ش�С
%   (u0,v0) �ο����꣬ͼ��ƽ������
if nargin==2
    u0 = 0;
    v0 = 0;
end
Pixel_Matrix = [1/dx 0 u0; 0 1/dy v0; 0 0 1];
return 
