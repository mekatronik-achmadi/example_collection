function y = FormEffectiveMeasurement(y0, TM, keepsamples)

y0 = TM*y0;
y = y0(keepsamples);

end

