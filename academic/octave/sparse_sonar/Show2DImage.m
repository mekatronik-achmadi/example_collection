function Show2DImage(data,bounds,f_hand,title_string,cscale,x_string,y_string)

if nargin < 6
    x_string = 'X (m)';
    y_string = 'Y (m)';
end

figure(f_hand)
clf

imagesc(bounds(1,1:2),bounds(1,3:4),20*log10(abs(data/max(abs(data(:))))),cscale);
set(gca,'YDir','normal','fontsize',11,'fontweight','bold');
grid off

axis square
xlabel(x_string,'fontsize',12,'fontweight','bold');
ylabel(y_string,'fontsize',12,'fontweight','bold');
title(title_string,'fontsize',12,'fontweight','bold');
colormap('jet');
colorbar

end

