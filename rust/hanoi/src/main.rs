use std::env;

fn hanoi(num:i32, from:char, mid:char, to:char){
    if num==1 {
        println!("move {} -> {}", from, to);
    }
    else{
        hanoi(num-1, from, to, mid);
        hanoi(1, from, mid, to);
        hanoi(num-1, mid, from, to);
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len()!=2 {
        println!("usage hanoi <number>");
    }else{
        let num = args[1].parse::<i32>().unwrap();
        hanoi(num, 'A', 'B', 'C');
    }
}
