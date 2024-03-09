fn main() {
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
}
