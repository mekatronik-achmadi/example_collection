// example of using Functions

// pass by value example
pub fn fn_power(v_root: u16, v_pwr: u16) -> u16 {
    let mut r: u16 = 1;

    for _i in 0..v_pwr  {
        r = r * v_root;
    }

    return r;
}

// pass by reference example
pub fn fn_zero(val_in: &mut u16) {
   *val_in = 0;
}

// immutable string return
pub fn fn_strlet() -> &'static str {
    let str_msg = "Immutable Rust String";

    return str_msg;
}

// mutable string return
pub fn fn_strmut() -> String {
    let mut str_msg = String::new();
    str_msg.push_str("Mutable Rust String Object");

    return str_msg;
}

