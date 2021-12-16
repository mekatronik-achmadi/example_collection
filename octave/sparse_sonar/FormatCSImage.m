function image = FormatCSImage(x,N)
indices = ((0:N)*N)+1;
for col = 1:N
    image(1:N,col) = flipud(x(indices(col):(indices(col+1)-1)));
end


end

