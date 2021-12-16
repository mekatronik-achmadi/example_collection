function yout = bpfilter(yin,f_sample,lw,hw)
	nyq = f_sample/2;
	cutL = lw/nyq;
	cutH = hw/nyq;
	[b,a] = butter(5,[cutL,cutH]);
	yout = filter(b,a,yin);
endfunction
