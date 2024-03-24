// example of declaring and print strings

pub fn print_strings(){
    // immuttable string
    let str_auto = "String Auto";
    let str_var: &str = "String Var";

    // mutable string
    let mut str_obj = String::new();

    // printing
    println!("String Auto: {}",str_auto);
    println!("String Var: {}",str_var);

    str_obj.push_str("Mutable String");
    println!("String Obj: {} in {}",str_obj,str_obj.len());
}
