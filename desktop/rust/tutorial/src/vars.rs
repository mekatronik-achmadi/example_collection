// example of declaring and print variables

pub fn print_vars() {
    // ignored variable started with '_'
    // everything with '_' is ignored
    let _var_ign = 0;
    let _cpu_hz = 16_000_000; // same as 16000000

    // immutable variables
    let var_int = -5;
    let var_float = 4.5;
    let var_ptr = &var_int;
    let var_chr = 'A';
    let var_str = "Hello World";

    // immutable variables with types
    let var_u16: u16 = 45;

    // changeable/mutable variables
    let mut mut_u16: u16 = 15;

    // constant
    const VAL_U16: u16 = 35;

    // printing
    println!("Var Int: {}", var_int);
    println!("Var Uint16: {}", var_u16);
    println!("Var Float: {}", var_float);
    println!("Var Pointer: {:p}", var_ptr);
    println!("Var Char: {}", var_chr);
    println!("Var String: {}", var_str);

    mut_u16 = mut_u16 + 10;
    println!("Mut Uint16: {}", mut_u16);

    println!("Const Uint16: {}", VAL_U16);
}
