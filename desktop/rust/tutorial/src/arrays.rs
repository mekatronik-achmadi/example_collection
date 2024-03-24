// example of arrays

pub fn print_arrays() {
    let var_arr: [u8; 5] = [0,1,2,3,4];
    let mut mut_arr: [u8; 5] = [0,2,4,6,8];

    for i in var_arr.iter(){
        print!("{} ",i);
    }
    println!();

    mut_arr[1] = 1;
    mut_arr[4] = 10;
    for i in mut_arr.iter(){
        print!("{} ",i);
    }
    println!();
}
