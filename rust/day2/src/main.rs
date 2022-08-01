use std::fs;

fn main() {
    let content = fs::read_to_string("./input.txt").unwrap();
    let content = content.trim();

    let lines: Vec<&str> = content.split('\n').collect();

    let mut ver_depth = 0;
    let mut hor_depth = 0;
    let mut aim = 0;
    for cmd in lines {
        let cmd: Vec<&str> = cmd.trim().split_whitespace().collect();
        match cmd[0] {
            "forward" => {
                let forward = cmd[1].parse::<i32>().unwrap();
                hor_depth += forward;
                ver_depth += forward * aim;
            },
            "down" => aim += cmd[1].parse::<i32>().unwrap(),
            "up" => aim -= cmd[1].parse::<i32>().unwrap(),
            _ => continue
        }
    }
    println!("ver: {}, hor: {}, answer: {}", ver_depth, hor_depth, ver_depth * hor_depth);
}
