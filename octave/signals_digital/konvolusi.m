function [to yo] = konvolusi(f,g,t)

ink = t(2)-t(1);
yo=conv(f,g)*ink;
to=linspace(2*min(t),2*max(t),length(yo));