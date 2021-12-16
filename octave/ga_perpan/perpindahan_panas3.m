% Penurunan persamaan fungsi objektif dari Heat Exchanger

function U = perpindahan_panas3(do,sudut)
% Heat Exchanger yang dioptimasi mempunyai baffle bentuk helical
% Data - data yang dimasukkan berupa data properties dan data geometri

%% Data Properties Heat Exchanger
Thin = 148.88;
% Temperatur tube input, celcius
Thout = 93.33;
% Temperatur tube output, celcius
Tcin = 54.72;
% Temperatur shell input, celcius
Tcout = 82.2;
% Temperatur shell output, celcius
mt = 5516.8746;
% Laju aliran massa steam, kg/h
mt_t = mt./3600;
% Laju aliran massa steam, kg/s
ms = 154031.25; 81828.1;
% Laju aliran massa crude, kg/hr
ms_t = ms./3600;
% Laju aliran massa production fluid, kg/s
kt = 0.59;
% Thermal Conductivity tube, W/m.C
ks = 0.66;
% Thermal Conductivity shell, W/m.C
Rho_s = 929.16;
% Density Shell
Rho_t = 970.37;
% Density Tube
cp_t = 3840;
% Heat specific tube, j/kg.C
cp_s = 4190;
% Heat specific shell, j/kg.C
miu_t = 0.00013;
% viscosity dynamic tube, kg/m.s
miu_s = 0.003;
% viscosity shell, kg/m.s
Q_t = (mt_t.*cp_t.*(Thin - Thout));
% Energy
Q_t_Mega= Q_t./10.^6;
S = (Tcout-Tcin)./(Thin-Tcin);
R = (Thin-Thout)./(Tcout-Tcin);
F = (((((sqrt(R.^2 +1))./2./(R-1)).*log((1-S)./(1-S.*R)))./log((2./S-1-R+(2./S).*sqrt((1-S).*(1-S.*R))+sqrt(R.^2+1))./(2./S-1-R+(2./S).*sqrt((1-S).*(1-S.*R))-sqrt(R.^2+1)))))-0.1; %factor correction
LMTD = (((Thin-Tcin)-(Thout-Tcout))/(log((Thin-Tcin)./(Thout-Tcout)))); %Log mean Temperature, celcius
MTD = LMTD.*F; %Log mean Temperatur correction, celcius

%% Data Geometri Heat Exchanger
Lt = 6.225;
% Panjang tube,sesuai dengan desain awal karena pertimbangan luasan area lapangan m
dct = 1.5.*do;
P = 1825;
% Design Pressure, kPa
S = 95248;
% Tensile Strength, nilai stress dari material(kPa)
% dari Tabel A-1 pada ASME B31.3-2002
E = 1;
% faktor kualitas
% dari Tabel A-1A atau A-1B pada ASME B31.3-2002
Y = 0.4;
% koefisien untuk D/6 (Tabel 2.3)
% dari tabel 304.1.1 ASME B31.3-2002
tw_min= (P.*do)./(2.*((S.*E) + (P.*Y)));
% ketebalan tube minimum, meter
c = 1.75.*(10.^-3);
% Corrosion Allowence, 1.75 mm
tw = tw_min + c ;
di = do - (2.*tw);
% diameter input shell
Ds = 1.016;
% Diamaeter Shell, m
Lpt = 1.25*do;
% Pitch Tube, m
B = Ds.*tand(sudut);
% Baffle Spacing, m
Np = 2;
% Jumlah tube passes
Lbb = (12 + (0.005.*(Ds./1000)))./1000;
% Bundle to shell clearence, m
Dotl = Ds -(2.*Lbb);
Dctl = Dotl-do;
Nt = (round(0.78.*(Dctl.^2)./(Lpt.^2)))./Np; %Jumlah Tube
de = (4.*((Lpt.^2)-(pi.*((do.^2)/4))))./(pi.*do); % diameter ekuivalen untuk layout tube 90 derajat
At = (Nt.*pi.*di.^2)./4;
% Luas Aliran sebelah Tube, m2
As = 0.5.*(1 - (dct./Ds)).*B.*Ds.*(1 -(do./Lpt)); % Luas Permukaan Shell, m2
vt = mt_t./(At.*Rho_t);
vs = ms_t./(As.*Rho_s);
Gt = mt_t./At;
% Kecepatan fluida dalam tube
Gs = ms_t./As;
% Kecepatan fluida dalam shell
Aht = pi.*do.*Lt.*Np.*Nt;
% Luas Permukaan HE

%% Analisis Aliran Heat Exchanger
Ret = (di.*vt.*Rho_t)./(miu_t);
% Reynold Number tube
Res = (de.*vs.*Rho_s)./miu_s;
% Reynold Number Shell
Prt = (miu_t.*cp_t)./kt;
% Prandtl Number tube
Prs = (miu_s.*cp_s)./ks;
% Prandtl Number Shell
Nus = 0.0451.*(Res.^0.699).*(Prs.^0.33);
% Nusselt Number Shell
Nut = 0.023.*(Ret.^0.8).*(Prt.^0.4);
% Nusselt Number Tube

%% Analisis Pressure Drop
ft = ((1.58.*log(Ret)) - 3.28).^-2 ;

% Koefisien gesekan sisi tube, dari tabel Faktor gesekan
% dengan nilai Re tube sekitar 42000, maka nilai ft = 0.00018 ft2/in2 = 0.02592 in2/in2
fs = exp(0.576-0.19.*log(Res));
% Faktor friksi aliran dalam shell
dP = (0.5.*Rho_s.*(vs^2).*fs.*Lt)./(do.*1000);
% Pressure Drop from B.Peng Journal

%% Analisis Performansi dari Heat Exchanger
ht = ((kt.*Nut)./di);
% Heat transfer coefficient tube side, T. Kuppan
hs = ((0.0451.*(Res.^0.699).*(Prs.^0.33).*ks)./do);
% Heat transfer coefficient shell side,B. Peng equation
Kcs = 60;
Rfs = 0.0005;
% faktor pengotor dari hydrocarbon heavy Uf = 2000 W/m2C
Rft = 0.0004;
% faktor pengotor steam condensate, Uf = 2500 W/m2C
U = (((do./(di.*ht)) + ((do.*Rft)./di) + (do.*log(do./di))./(2.*Kcs) + Rfs + (1./hs)).^-1);% Overall Heat Transfer didasarkan pada luas tube
Ud = (Q_t./(Aht.*MTD));

% Perhitungan Koef. Perpindahan Panas Keselurhan Untuk Perencanaan
end