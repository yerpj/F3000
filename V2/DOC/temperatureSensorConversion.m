%% F3000 Temperature sensor conversion into voltage
clc; clear all; close all;
%%
Rnom=[104,44,20,16];
Tnom=[60,85,110,120];

T2=linspace(1,120,120)

p=polyfit(Tnom,Rnom,2);
R2=p(1).*T2.*T2+p(2).*T2+p(3);

figure();
plot(Rnom,Tnom);
hold on;
plot(R2,T2,'r');
grid on;