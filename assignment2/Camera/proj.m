function [Projection_Matrix] = proj(f)
%�������ͶӰ(projection)��ͼ������
%�������
%   f                   ������ࣨ����cm��
%�������
%   Projection_Matrix   ͶӰ���񣨾���
Projection_Matrix = [f 0 0 0; 0 f 0 0; 0 0 1 0];
return
