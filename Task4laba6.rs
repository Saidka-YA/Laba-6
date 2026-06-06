use std::collections::{HashMap, VecDeque};
use std::io;

static mut N: usize = 0;
static mut M: usize = 0;

fn encode(board: &Vec<Vec<i32>>) -> i32 {
    let mut mask = 0;
    let mut pos = 0;

    unsafe {
        for i in 0..N {
            for j in 0..M {
                if board[i][j] == 1 {
                    mask |= 1 << pos;
                }
                pos += 1;
            }
        }
    }

    mask
}

fn decode(mask: i32) -> Vec<Vec<i32>> {
    let mut board;

    unsafe {
        board = vec![vec![0; M]; N];

        let mut pos = 0;

        for i in 0..N {
            for j in 0..M {
                board[i][j] = (mask >> pos) & 1;
                pos += 1;
            }
        }
    }

    board
}

fn build_target(edge_val: i32) -> i32 {
    let mut target;

    unsafe {
        target = vec![vec![0; M]; N];

        for i in 0..N {
            for j in 0..M {
                if i == 0 || i == N - 1 || j == 0 || j == M - 1 {
                    target[i][j] = edge_val;
                } else {
                    target[i][j] = 1 - edge_val;
                }
            }
        }
    }

    encode(&target)
}

fn bfs(start_mask: i32, target_mask: i32) -> i32 {
    if start_mask == target_mask {
        return 0;
    }

    let mut visited: HashMap<i32, i32> = HashMap::new();
    let mut q: VecDeque<i32> = VecDeque::new();

    visited.insert(start_mask, 0);
    q.push_back(start_mask);

    let dx = [0, 0, 1, -1];
    let dy = [1, -1, 0, 0];

    while !q.is_empty() {
        let cur = q.pop_front().unwrap();
        let cur_dist = *visited.get(&cur).unwrap();

        unsafe {
            for i in 0..N {
                for j in 0..M {
                    for d in 0..4 {
                        let ni = i as i32 + dx[d];
                        let nj = j as i32 + dy[d];

                        if ni < 0 || ni >= N as i32 || nj < 0 || nj >= M as i32 {
                            continue;
                        }

                        let pos1 = (i * M + j) as i32;
                        let pos2 = (ni as usize * M + nj as usize) as i32;

                        let new_mask = cur ^ (1 << pos1) ^ (1 << pos2);

                        if new_mask == target_mask {
                            return cur_dist + 1;
                        }

                        if !visited.contains_key(&new_mask) {
                            visited.insert(new_mask, cur_dist + 1);
                            q.push_back(new_mask);
                        }
                    }
                }
            }
        }
    }

    -1
}

fn read_number() -> i32 {
    loop {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();

        if let Ok(x) = s.trim().parse::<i32>() {
            return x;
        }

        println!("Ошибка ввода.");
    }
}

fn main() {
    unsafe {
        println!("Введите N (от 2 до 4): ");

        loop {
            let x = read_number();

            if x >= 2 && x <= 4 {
                N = x as usize;
                break;
            }

            println!("Ошибка: введите от 2 до 4");
        }

        println!("Введите M (от 2 до 4): ");

        loop {
            let x = read_number();

            if x >= 2 && x <= 4 {
                M = x as usize;
                break;
            }

            println!("Ошибка: введите от 2 до 4");
        }

        let mut board = vec![vec![0; M]; N];

        println!("Введите доску (0 и 1):");

        for i in 0..N {
            for j in 0..M {
                loop {
                    let x = read_number();

                    if x == 0 || x == 1 {
                        board[i][j] = x;
                        break;
                    }

                    println!("Ошибка: введите 0 или 1");
                }
            }
        }

        println!("\nВведённая доска:");

        for i in 0..N {
            for j in 0..M {
                print!("{:3}", board[i][j]);
            }
            println!();
        }

        let start_mask = encode(&board);
        let mut best_answer = 1000000;

        for edge_val in 0..2 {
            let target_mask = build_target(edge_val);
            let target_board = decode(target_mask);

            println!(
                "\nЦелевая рамка (края={}, внутри={}):",
                edge_val,
                1 - edge_val
            );

            for i in 0..N {
                for j in 0..M {
                    print!("{:3}", target_board[i][j]);
                }
                println!();
            }

            let result = bfs(start_mask, target_mask);

            if result == -1 {
                println!("Невозможно достичь.");
            } else {
                println!("Ходов: {}", result);

                if result < best_answer {
                    best_answer = result;
                }
            }
        }

        println!("\nМинимальное число ходов: {}", best_answer);
    }
}