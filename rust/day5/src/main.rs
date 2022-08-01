use std::fs;

fn main() {
    let content = fs::read_to_string("./test.txt").unwrap();
    let points: Vec<(i32, i32)> = content
        .trim()
        .split(&['-', '>', ' ', '\n'])
        .filter(|x| !x.is_empty())
        .map(|x| {
            let (i, j) = x.split_once(',').unwrap();
            let i = i.parse::<i32>().unwrap();
            let j = j.parse::<i32>().unwrap();
            (i, j)
        })
        .collect();

    let mut board = [[0; 10]; 10];
    let mut i = 0;
    while i < points.len() {
        let mut x = points[i].0;
        let mut y = points[i].1;
        let x_dif = points[i + 1].0 - points[i].0;
        let y_dif = points[i + 1].1 - points[i].1;
        let len = match x_dif != 0 {
            true => x_dif.abs(),
            false => y_dif.abs(),
        };

        if x_dif != 0 || y_dif != 0 {
            board[y as usize][x as usize] += 1;
            for j in 0..len {
                x += x_dif / len;
                y += y_dif / len;
                board[y as usize][x as usize] += 1;
            }
        }

        i += 2;
    }

    println!("{:?}", points);

    for row in board {
        println!("{:?}", row);
    }
}
