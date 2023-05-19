use rand::seq::SliceRandom;
use rand::thread_rng;
use std::collections::HashSet;

fn main() {
    const N: i32 = 10;
    let mut arr = vec!['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
    let mut rng = thread_rng();

    let mut input = String::new();
    arr.shuffle(&mut rng);

    // println!("{:?}", arr);
    let mut i: i32 = 1;
    let mut input_set: HashSet<char> = HashSet::new();
    while i < N + 1 {
        println!("[{}/{}] Input 4 different digit", i, N);
        std::io::stdin()
            .read_line(&mut input)
            .ok()
            .expect("Faile to read line");

        for _c in input.trim().chars() {
            input_set.insert(_c);
        }

        if input_set.len() != 4 || input.trim().len() != 4 {
            println!("Invalid input, retry");
            input.clear();
            input_set.clear();
            continue;
        }

        let mut correct_cnt = 0;
        let mut semi_correct_cnt = 0;
        for _j in 0..4 {
            if arr[_j] == input.chars().nth(_j).unwrap() {
                correct_cnt += 1;
            } else if input_set.contains(&arr[_j]) {
                semi_correct_cnt += 1;
            }
        }
        if correct_cnt == 4 {
            println!("You win!");
            return;
        }
        println!("{}A{}B", correct_cnt, semi_correct_cnt);
        input.clear();
        input_set.clear();
        i += 1;
    }
    println!("You lose! Answer: {}{}{}{}", arr[0], arr[1], arr[2], arr[3]);
}
