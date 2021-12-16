clc;

sh_dens = 739.2068;
 sp_heat = 2692.4;
 sh_vis = 0.4252;
 %t_cond = x(4);

 t_cond = 0.1015;

do = 0.019;
%     nb = 10;
%     lbi = 0.68;
%     lbo = 0.76;
%     lbb = 0.012;
%     ltp = 0.023;
%     as = 0.034;
us = 2.327;
rtw = 1.174e-6;
c_depo = 277.8;
c_supp = 1.417e-13;
e_activ = 48;

reys = sh_dens * us * do * sh_vis;
prs = sp_heat * sh_vis / t_cond;

rf = ((c_depo * (reys^-0.8) * (prs^-0.3)) * 1.17416e-6 ) - (c_supp * (reys^0.8));
%rf = c_depo * 
