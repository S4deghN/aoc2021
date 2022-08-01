use std::fs;

fn main() {
    let contents = fs::read_to_string("src/input.txt").unwrap();
    let contents = contents.trim();
    let lines: Vec<&str> = contents.split('\n').collect();

    let numbers: Vec<i32> = lines
        .iter()
        // .map(|x| match x.trim().parse::<i32>() { Ok(num) => num, Err(_) => -1 })
        .map(|x| x.trim().parse::<i32>().unwrap())
        .collect();


    let mut per_num = 0;
    let mut counter = -1;
    println!("{} and {}", numbers.len(), 1);
    for index in 0..(numbers.len() + (3 - numbers.len() % 3) - 3) {

        let num = numbers[index] + numbers[index + 1] + numbers[index + 2];

        if num > per_num {
            counter += 1;
        }
        per_num = num;

        println!("{}: {}", index, numbers[index]);
    }
    println!("the answer is {}", counter);
}

