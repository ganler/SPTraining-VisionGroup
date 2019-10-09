function [Camera_Parameters] = camera_parameters()
% ����������ת��Ϊ��������Ĳ���(�����������)
% ����,����ʡ��ʡȥ�Ļ�������������Ӧ�����
Phi = pi/4;%��x����ת�Ƕ�
Psi = pi/4;%��y����ת�Ƕ�
Theta = pi/4;%��z����ת�Ƕ�
x0 = 0;%xƽ����
y0 = 0;%yƽ����
z0 = 0;%zƽ����
f = 35e-3;%35mm���
dx = 0.026;%һ�����صĳ�
dy = 0.026;%һ�����صĿ�
u0 = 0;
v0 =0;
 
%% step1:����������ת��Ϊ������꣬�ȱ�����С�������תƽ��(����任)
RT = (Phi, Psi, Theta, x0, y0, z0);%����任����
 
%% step2:���������ת��Ϊͼ������(ͶӰ)
Projection_Matrix = proj(f);%ͶӰ����
 
%% step3:��ͼ��������ɢ����
Pixel_Matrix = pixel(dx,dy,u0,v0);%1���أ�0.635���ס�24��0.026458����
%% ��������
Camera_Internal_Parameters = Pixel_Matrix * Projection_Matrix;%����ڲ���
Camera_External_Parameters = RT;%��������
%�������
Camera_Parameters = Camera_Internal_Parameters*Camera_External_Parameters; 
