// example of variable structure

pub struct Stm32{
    pub pin_num: u16,
    pub cpu_arch: String,
}

pub fn print_struct(stm: &Stm32) {
    println!("Chip has {} pin with arch {}",stm.pin_num,stm.cpu_arch);
}

pub fn modify_struct(stm: &mut Stm32){
    println!("Modify Structs");
    stm.pin_num = 48;
    stm.cpu_arch = String::from("Cortex-M1");
}
