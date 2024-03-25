// example of main module

mod arrays;
mod concurs;
mod fibs;
mod funcs;
mod ifloop;
mod strcts;
mod strings;
mod vars;
mod vecs;

fn main() {
    println!("Hello, world!");

    println!("App arguments:");
    for arg in std::env::args() {
        print!("{}", arg);
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

    println!("Fn Power: {}", funcs::fn_power(4, 3));

    let mut in_val: u16 = 45;
    funcs::fn_zero(&mut in_val);
    println!("Fn Zero: {}", in_val);

    println!("Fn Str: {}", funcs::fn_strlet());
    println!("Fn StrMut: {}", funcs::fn_strmut());

    println!("===== Structs ====");
    let mut f103c = strcts::Stm32 {
        pin_num: 64,
        cpu_arch: String::from("Cortex-M4"),
    };
    strcts::print_struct(&f103c);
    strcts::modify_struct(&mut f103c);
    strcts::print_struct(&f103c);

    println!("===== Vector ====");
    let mut var_vec: Vec<u8> = Vec::new();
    var_vec.push(7);

    // can't move value before borrowed
    //vecs::print_vec(var_vec);

    vecs::modify_vec(&mut var_vec);
    vecs::print_vec(var_vec);

    println!("===== Fibonacci ====");
    println!("Fib: {}", fibs::fibs(10));

    // threading should be the last calls
    println!("===== Threading ====");
    concurs::thds_test();
    println!();
}

////////////////// Untested ///////////////////////
// Class/Impl
// Macro
// Tuple
// Ownership
// Borrowing
// Mutable Slice
// Generic Types
// Generic/Templates
// Panic/Error
// I/O
// Box Pointer
// Move
// Unwrap
// Workspace
// Package Manager
