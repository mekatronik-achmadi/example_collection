mod vars;
mod strings;
mod ifloop;
mod arrays;
mod funcs;

fn main() {
    println!("Hello, world!");

    println!("App arguments:");
    for arg in std::env::args(){
        print!("{}",arg);
    }
    println!();

    println!("==== Variables ====");
    vars::print_vars();

    println!("====== String =====");
    strings::print_strings();

    println!("===== If/Loop =====");
    ifloop::print_ifs();
    ifloop::print_loops();

    println!("===== Arrays =====");
    arrays::print_arrays();

    println!("==== Functions ===");

    println!("Fn Power: {}",funcs::fn_power(4,3));

    let mut in_val: u16 = 45;
    funcs::fn_zero(&mut in_val);
    println!("Fn Zero: {}",in_val);
}
