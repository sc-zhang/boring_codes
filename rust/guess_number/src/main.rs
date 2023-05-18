use rand::Rng;

fn main() {
    const N:i32 = 10;
    let mut i:i32 = 0;
    let ans:i32 = rand::thread_rng().gen_range(0..1001);
    while i < N  {
        let mut input = String::new();
        println!("[{}/{}] Input a number not lager than 1000", i+1, N);
        std::io::stdin().read_line(&mut input)
        .ok()
        .expect("Failed to read line");
        let input_number: i32 = input.trim().parse::<i32>().unwrap();
        if input_number > 1000{
            println!("Invalid number, retry");
            continue;
        }
        if input_number > ans{
            println!("Too large");
        }else if input_number < ans {
            println!("Too lower")
        }else{
            println!("You win!");
            return;
        }
        i += 1;
    }
    println!("You lose! Answer={}", ans);
}
