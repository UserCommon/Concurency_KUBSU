use std::thread;
use std::sync::mpsc;
use std::fs;

fn get_mx(filename: &str) -> i32 {
    let f = fs::read_to_string(filename).unwrap();
    let res: i32 = f.split_whitespace()
        .map(|x| x.parse::<i32>().unwrap())
        .fold(0, |a, b| a.max(b));

    res
}

fn main() {
    let (send, recv) = mpsc::channel();

    for i in 1..=3 {
        let s = send.clone();
        thread::spawn(move || {
            let fin = format!("f{}.txt", i);
            s.send(get_mx(&fin));
        });
    }

    for _ in 0..3 {
        let i = recv.recv().unwrap();
        println!("{}", i);
    }
}
