// example of using controls

pub fn print_ifs() {
    let var_u16: u16 = 9;

    if var_u16 % 2 == 0 {
        println!("Var is Even");
    } else if var_u16 % 2 == 1 {
        println!("Var is Odd");
    } else {
        println!("Var is undefined");
    }

    let var_size: &str = if var_u16 < 10 { "low" } else { "big" };
    println!("Var also {}", var_size);
}

pub fn print_loops() {
    println!("Loop: ");
    for i in 0..5 {
        print!("{} ", i);
    }
    println!();

    let mut j: u8 = 0;
    while j < 5 {
        print!("{} ", j);
        j = j + 1;
    }
    println!();
}
