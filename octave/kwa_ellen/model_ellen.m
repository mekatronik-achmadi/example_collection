function rf=model_ellen(x)

    %Design of heat exchanger to minimize fouling, minimize area/size, maximize
    %U By :  Totok R. Biyanto, Ph.D
     
     %% parameter crude
     dens = x(1);
     sp_heat = x(2);
     visco = x(3);
     t_cond = x(4);
     
     %t_cond = 0.1015;

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
    
    reys = dens * us * do * visco;
    prs = sp_heat * visco / t_cond;
    
    rf = ((c_depo * (reys*0.8) * (prs^-0.33333)) ^ (-e_activ/rtw)) - ((c_supp*c_depo)^0.8);
end





















