// example of vectors

pub fn modify_vec(v: &mut Vec<u8>) {
    v.push(5);
    v.push(3);
}

pub fn print_vec(v: Vec<u8>) {
    for i in 0..v.len() {
        print!("{} ", v[i]);
    }
    println!();
}
