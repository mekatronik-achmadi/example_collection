function keepsamples = CompressedSensing( tx,rx,data,n_keep )

li = 1;
for ix = 1:length(tx)
    for iy = 1:length(rx)
        keepsamples{li} = EffectiveMeasurement(data{ix,iy},n_keep);
        li = li + 1;
    end
end


end