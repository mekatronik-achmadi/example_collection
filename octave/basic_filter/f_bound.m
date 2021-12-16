function [low_freq,high_freq] = f_bound(centre_freq,bandwidth)
	low_freq = centre_freq - (bandwidth/2);
	high_freq = centre_freq + (bandwidth/2);
endfunction
