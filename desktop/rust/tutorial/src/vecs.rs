// example of vectors

pub fn modify_vec(v: &mut Vec<u8>) {
    v.push(0);
    v.push(5);
}

pub fn print_vec(v: Vec<u8>) {
    println!("Vector: {:?}",v);
}

