int fungsiSaya(int num){
    if (num==0)
        return 0;
    else
        return ((num&(num-1))==0 ? 1 : 0);
}
