use std::fs;

// TODO: it's fucking messy!

fn main() {
    let content = fs::read_to_string("./input.txt").unwrap();
    let content = content.trim();

    let nums_str: Vec<&str> = content.split_whitespace().collect();

    let o2 = filter(nums_str.clone(), true);
    let co2 = filter(nums_str.clone(), false);
    println!("o2: {:?} co2: {:?}", o2, co2);

    let o2 = i32::from_str_radix(o2.as_str(), 2).unwrap();
    let co2 = i32::from_str_radix(co2.as_str(), 2).unwrap();
    println!("o2: {:?} co2: {:?}", o2, co2);
    println!("{:?}", o2 * co2);
}

fn filter(mut nums_str: Vec<&str>, more_common: bool) -> String {
    let mut ones: usize = 0;
    for i in 0..nums_str[0].len() {
        for num in &nums_str {
            let num = num.as_bytes();
            ones += (num[i] - 48) as usize;
        }

        let zero_one;
        if ones >= (nums_str.len() - (nums_str.len() / 2usize)) {
            zero_one = !more_common as usize;
        } else {
            zero_one = more_common as usize;
        }
        ones = 0;

        let mut j = 0;
        while j < nums_str.len() {
            let num = nums_str[j].as_bytes();
            if nums_str.len() == 1 {
                // println!("{:?}, {}", nums_str, zero_one);
                break;
            }
            if (num[i] - 48) as usize == zero_one {
                nums_str.swap_remove(j);
            } else {
                j += 1;
            }
            // println!("len: {}, j: {}, z: {}, num: {:?}", nums_str.len(), j, zero_one, num);
        }
    }
    nums_str[0].to_string()
}
