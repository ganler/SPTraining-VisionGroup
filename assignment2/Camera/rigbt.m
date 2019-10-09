function [RT] = rigbt(Phi, Psi, Theta, x0, y0, z0)
%����任����:rigid body transformation
%���������
%   ��=Phi       ��x��ת���ĽǶ�
%   ��=Psi       ��y��ת���ĽǶ�
%   ��=Theta     ��z��ת���ĽǶ�
%���������
%    RT ����������и���仯����ת+ƽ�ƣ����µ�������
%
%% ����
R1 = [1 0 0; 0 cos(Phi) sin(Phi); 0 -sin(Phi) cos(Phi)];%��X����ת
R2 = [cos(Psi) 0 -sin(Psi); 0 1 0; sin(Psi) 0 cos(Psi)];%��Y����ת
R3 = [cos(Theta) sin(Theta) 0;-sin(Theta) cos(Theta) 0; 0 0 1 ];%��Z����ת
R = R3 * R1 * R2;%��ת���󣨸���任һ���֣�
T = [x0; y0; z0];%ƽ�ƾ���
RT=[R T;0 0 0 1];%����任����
return
