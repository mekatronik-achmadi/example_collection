// example of concurrency

use std::thread;
use std::time::Duration;

pub fn thds_test() {
    // new threads
    print!("thread 0: ");
    thread::spawn(||{
        for i in 0..10 {
            print!("{} ",i);
            thread::sleep(Duration::from_millis(10));
        }
    });

    // new threads
    print!("thread 1: ");
    thread::spawn(||{
        for i in 0..10 {
            print!("{} ",i);
            thread::sleep(Duration::from_millis(10));
        }
    });

    // concurrency in main thread
    // must be the last thread
    print!("thread Main:");
    for i in 0..10  {
        print!("{} ",i);
        thread::sleep(Duration::from_millis(10));
    }
}

