// example of Fibonacci

pub fn fibs(n: u16) -> u16 {
    if n <= 2 {
        return 1;
    } else {
        return fibs(n - 1) + fibs(n - 2);
    }
}
