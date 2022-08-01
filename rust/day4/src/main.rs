use std::fs;

fn main() {
    let content = fs::read_to_string("./input.txt").unwrap();
    let mut content: Vec<&str> = content.trim().split("\n\n").collect();

    let rolls_str = content.swap_remove(0);
    let mut rolls: Vec<i32> = rolls_str
        .trim()
        .split(',')
        .map(|x| x.parse::<i32>().unwrap())
        .collect();
    rolls.reverse();

    let boards_str: Vec<&str> = content;

    // for i in &boards_str {
    //     println!("{}", i);
    // }
    let mut flat_boards: Vec<Vec<i32>> = Vec::new();
    for str in boards_str {
        flat_boards.push(
            str.trim()
                .split_whitespace()
                .map(|x| x.parse::<i32>().unwrap())
                .collect(),
        );
    }

    let mut boards: Vec<Vec<Vec<i32>>> = vec![vec![vec![0; 5]; 5]; flat_boards.len()];

    for (i, board) in flat_boards.iter().enumerate() {
        for (j, &num) in board.iter().enumerate() {
            boards[i][j / 5][j % 5] = num;
        }
    }

    let winner_board;
    let last_roll;
    'game: loop {
        let roll = match rolls.len() > 0 {
            true => rolls.pop().unwrap(),
            false => {
                println!("no board met the win condition!");
                return;
            }
        };

        // loop over all elements of all boards and mark places holding the roll number
        for board in &mut boards {
            for i in 0..board.len() {
                for j in 0..board[0].len() {
                    if board[i][j] == roll {
                        board[i][j] = -1;
                    }
                }
            }
        }

        // loop over all rows and columns of all boards and calculate the some of each row and column, sum = -5 (five marked items) determines a win condition
        let mut sum = 0;
        let mut index = 0;
        'check: while index < boards.len() {
            let board = boards[index].clone();
            //check each row
            for i in 0..board.len() {
                for j in 0..board[0].len() {
                    sum += board[i][j];
                }
                if sum == -5 {
                    if boards.len() == 1 {
                        winner_board = boards[index].clone();
                        last_roll = roll;
                        break 'game;
                    }
                    boards.swap_remove(index);
                    continue 'check;
                    // winner_board = board.clone();
                    // last_roll = roll;
                    // break 'game;
                }
                sum = 0;
            }
            //check each column
            for j in 0..board[0].len() {
                for i in 0..board.len() {
                    sum += board[i][j];
                }
                if sum == -5 {
                    if boards.len() == 1 {
                        winner_board = boards[index].clone();
                        last_roll = roll;
                        break 'game;
                    }
                    boards.swap_remove(index);
                    continue 'check;
                    // winner_board = board.clone();
                    // last_roll = roll;
                    // break 'game;
                }
                sum = 0;
            }
            index += 1;
        }
    }
    println!("winner board:");
    for i in &winner_board {
        println!("{:?}", i)
    }
    println!("last roll: {}", last_roll);

    println!("len: {}", boards.len());
    let answere = winner_board.into_iter().flatten().collect::<Vec<i32>>();
    let answere = answere
        .into_iter()
        .filter(|x| x.is_positive())
        .collect::<Vec<i32>>();
    let answere = answere.into_iter().sum::<i32>();
    let answere = answere * last_roll;

    println!("answere: {:?}", answere);
}
