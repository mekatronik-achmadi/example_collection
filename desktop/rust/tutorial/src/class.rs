// example of using struct/impl like Class
// also example using Generic Types

pub struct Kotak{
    pub wid: u16,
    pub hig: u16,
}

impl Kotak {
    pub fn area(&self) -> u16 {
        return self.wid * self.hig;
    }
}

pub struct GenVal<T>{
    pub val: T,
}

impl<T> GenVal<T> {
    pub fn value(&self) -> &T {
        return &self.val;
    }
}

