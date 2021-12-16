function y = clasifi(net,thers)
 if (net > thers)
     y = 1;
 elseif (net < -thers)
     y = -1;
 else
     y = 0;
 end
 return 
 