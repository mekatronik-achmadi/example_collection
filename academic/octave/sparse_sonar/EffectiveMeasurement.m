%%Written by Taylor Williams
%
%quick function to take an original measurement y0 (Nx1) and create
%an effective measurement y (Nx1) by putting y0 through the provided
%linear transformation TM and keeping only the samples in keepsamples
%TM must be NxN where N is the length of y0
%
%keepsamples must contain only integer values in [1,N]

function y = FormEffectiveMeasurement2(y0, keepsamples)
    TM = randn(keepsamples,keepsamples);
    y0 = y0(1,1:keepsamples);
    y0 = TM*y0';
    y = y0;
end