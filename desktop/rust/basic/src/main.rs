use std::thread;
use std::time::Duration;

fn main() {
// Tutorial sources
// https://www.tutorialspoint.com/rust/
// https://stevedonovan.github.io/rust-gentle-intro/

///////////////// Declaration ///////////////////////
    // variables
    let var_int = -5;
    let var_u16: u16 = 45;
    let var_float = 4.5;
    let var_ptr = &var_int;
    let var_chr = 'A';
    let var_str = "Hello World";

    // changeable/mutable variables
    let mut mut_u16: u16 = 15;

    // constant
    const VAL_U16: u16 = 35;

    // string object
    let mut str_obj = String::new();

///////////////// Action ///////////////////////////
    // print command line arguments
    for arg in std::env::args() {
        print!("{} ",arg);
    }
    println!();

    // some compilation checking
    assert_eq!(var_u16, 45);

    // printing
    println!("Var Int: {}",var_int);
    println!("Var Uint16: {}",var_u16);
    println!("Var Float: {}",var_float);
    println!("Var Pointer: {:p}",var_ptr);
    println!("Var Char: {}",var_chr);
    println!("Var String: {}",var_str);

    mut_u16 = mut_u16 + 10;
    println!("Mut Uint16: {}",mut_u16);

    println!("Const Uint16: {}",VAL_U16);

    str_obj.push_str("Rust Programming");
    println!("Str Obj: {} (length {})",str_obj,str_obj.len());

    let lang = &str_obj[0..5];
    println!("Str Lang: {}",lang);

///////////////// Control ///////////////////////////

    if mut_u16 % 2 == 0 {
        println!("Var Uint16 is Even");
    }
    else {
        println!("Var Uint16 is Odd");
    }

    let var_oddeven = mut_u16 % 2;
    let var_str_oddeven = match var_oddeven{
        0 => "Even",
        1 => "Odd",
        _ => "Undefined"
    };
    println!("Var Uint16: {}",var_str_oddeven);

///////////////// Looping ///////////////////////////

    for i in 0..5{
        print!("{} ",i);
    }
    println!();

    let mut j = 0;
    while j<5 {
        print!("{} ",j);
        j = j +1;
    }
    println!();

///////////////// Array ///////////////////////////

    let var_arr: [u16;5] = [0,1,3,5,7];

    print!("Array: ");
    for i in var_arr.iter() {
        print!("{} ",i);
    }
    println!();

    print!("Array Elements: ");
    let mut j = 0;
    while j<var_arr.len() {
        print!("{} ",var_arr[j]);
        j = j + 1;
    }
    println!();

///////////////// Function ///////////////////////////

    println!("Power Fn: {}",power(3, 4));

    let mut tozero: u16 = 100;
    zeroing(&mut tozero);
    println!("Zeroing {}",tozero);

    println!("{}",str_ret());
    println!("{}",strobj_ret());

///////////////// Struct/Enum ///////////////////////////

    enum PowerLevel {
        Low, High
    }

    struct Stm32{
        pin_num: u16,
        cpu_arch: String,
        _pwr_lvl: PowerLevel,
    }

    let f103c8 = Stm32{
        pin_num:48,
        cpu_arch:String::from("Cortex-M1"),
        _pwr_lvl:PowerLevel::Low,
    };

    let f407vg = Stm32{
        pin_num:144,
        cpu_arch:String::from("Cortex-M4+"),
        _pwr_lvl:PowerLevel::High,
    };

    println!("Chip has {} pin with arch {}",
        f103c8.pin_num,
        f103c8.cpu_arch,
    );

    println!("Chip has {} pin with arch {}",
        f407vg.pin_num,
        f407vg.cpu_arch,
    );

///////////////// Vector ///////////////////////////

    let mut var_vec = vec![3,5,7];
    var_vec.push(9);

    let mut var_vect: Vec<u16> = Vec::new();
    var_vect.push(10);
    var_vect.push(25);
    var_vect.push(45);

    println!("Vectors: {:?} \nAnd {:?}",var_vec,var_vect);

////////////////// Threading ///////////////////////

    // new thread
    print!("thread ");
    thread::spawn(||{
        for i in 1..10 {
            print!("{} ",i);
            thread::sleep(Duration::from_millis(10));
        }
    });

    // new thread
    print!("thread ");
    thread::spawn(||{
        for i in 1..10 {
            print!("{} ",i);
            thread::sleep(Duration::from_millis(10));
        }
    });

    // concurrent in main thread
    // should be the last thread
    print!("main ");
    for i in 1..10 {
        print!("{} ",i);
        thread::sleep(Duration::from_millis(10));
    }

//////////////////////////////////////////////////////

    println!();

}

// pass by value
fn power(v_root:u16,mut v_pwr:u16) -> u16 {
    let mut ret: u16 = 1;
    let mut idx: u16 = 0;

    if v_pwr > 3 {v_pwr = 3}

    while idx < v_pwr {
        ret = ret * v_root;
        idx = idx + 1;
    }

    return ret;
}

// pass by reference
fn zeroing(val: &mut u16) {
    *val = 0;
}

// string return
fn str_ret() -> &'static str{
    let str_msg = "Rust string function";

    return str_msg;
}

// string object return
fn strobj_ret() -> String {
    let mut str_msg = String::new();
    str_msg.push_str("Rust string object function");

    return str_msg;
}

////////////////// Untested ///////////////////////
// Class/Impl
// Macro
// Tuple
// Ownership
// Borrowing
// Mutable Slice
// Generic Types
// Panic/Error
// I/O
// Box Pointer
// Move
// Module
// Package Manager
