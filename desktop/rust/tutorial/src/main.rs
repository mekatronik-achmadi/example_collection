mod vars;
mod strings;

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
}
