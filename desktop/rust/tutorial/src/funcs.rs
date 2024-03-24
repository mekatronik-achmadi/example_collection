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
