function ShowImage(result,bounds,spacing,f_hand,title_string,cscale)

if bounds(5) == bounds(6)
    Show2DImage(result,bounds,f_hand,title_string,cscale,'X (m)','Y (m)');
    
elseif bounds(1) == bounds(2) 
    bounds = bounds(1,3:end);
    Show2DImage(squeeze(result).',bounds,f_hand,title_string,cscale,'Y (m)','Z (m)');

elseif bounds(3) == bounds(4)
    bounds = [bounds(1,1:2) bounds(1,5:6)];
    Show2DImage(squeeze(result).',bounds,f_hand,title_string,cscale,'X (m)','Z (m)');

else
    figure(f_hand)
    clf
    
    x = bounds(1):spacing:bounds(2);
    y = bounds(3):spacing:bounds(4);
    z = bounds(5):spacing:bounds(6);
    

    isosurface(x,y,z,20*log10(abs(result)/max(abs(result(:)))),cscale(1));
    axis(bounds);
    title(title_string);
    
end

end

