const EPS: f64 = 1e-3;

fn lu(a: [[f64; 4]; 4], l: &mut [[f64; 4]; 4], u: &mut [[f64; 4]; 4]) {
    for i in 0..4 {
        for j in 0..4 {
            l[i][j] = 0.0;
            u[i][j] = 0.0;
        }
    }

    for i in 0..4 {
        for k in i..4 {
            let mut sum = 0.0;
            for j in 0..i {
                sum += l[i][j] * u[j][k];
            }
            u[i][k] = a[i][k] - sum;
        }

        for k in i..4 {
            if i == k {
                l[i][i] = 1.0;
            } else {
                let mut sum = 0.0;
                for j in 0..i {
                    sum += l[k][j] * u[j][i];
                }
                l[k][i] = (a[k][i] - sum) / u[i][i];
            }
        }
    }
}

fn solve_lu(l: [[f64; 4]; 4], u: [[f64; 4]; 4], b: [f64; 4]) {
    let mut y = [0.0; 4];
    let mut x = [0.0; 4];

    for i in 0..4 {
        let mut sum = 0.0;
        for j in 0..i {
            sum += l[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    for i in (0..4).rev() {
        let mut sum = 0.0;
        for j in (i + 1)..4 {
            sum += u[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / u[i][i];
    }

    println!("\nРешение методом LU:");
    for i in 0..4 {
        println!("x{} = {:10.6}", i + 1, x[i]);
    }
}

fn seidel(a: [[f64; 4]; 4], b: [f64; 4]) {
    let mut x = [0.0; 4];
    let mut old_x = [0.0; 4];

    let mut iteration = 0;

    println!("\nМетод Зейделя:");
    println!(
        "{:>5}{:>12}{:>12}{:>12}{:>12}{:>12}",
        "N", "x1", "x2", "x3", "x4", "eps"
    );

    loop {
        for i in 0..4 {
            old_x[i] = x[i];
        }

        for i in 0..4 {
            let mut sum = b[i];

            for j in 0..4 {
                if i != j {
                    sum -= a[i][j] * x[j];
                }
            }

            x[i] = sum / a[i][i];
        }

        let mut max_diff = 0.0;

        for i in 0..4 {
            let diff = (x[i] - old_x[i]).abs();
            if diff > max_diff {
                max_diff = diff;
            }
        }

        iteration += 1;

        println!(
            "{:>5}{:>12.6}{:>12.6}{:>12.6}{:>12.6}{:>12.6}",
            iteration,
            x[0],
            x[1],
            x[2],
            x[3],
            max_diff
        );

        if max_diff < EPS {
            break;
        }

        if iteration > 1000 {
            println!("Метод не сошелся.");
            break;
        }
    }
}

fn main() {
    let a = [
        [-1.13, -0.04, 0.21, -1.16],
        [0.25, -1.23, 0.14, -0.09],
        [-0.21, 0.14, 0.80, -0.13],
        [0.15, -1.31, 0.06, 0.87],
    ];

    let b = [-1.24, 0.87, 2.56, -1.13];

    let mut l = [[0.0; 4]; 4];
    let mut u = [[0.0; 4]; 4];

    lu(a, &mut l, &mut u);

    println!("Матрица L:");
    for i in 0..4 {
        for j in 0..4 {
            print!("{:12.6}", l[i][j]);
        }
        println!();
    }

    println!("\nМатрица U:");
    for i in 0..4 {
        for j in 0..4 {
            print!("{:12.6}", u[i][j]);
        }
        println!();
    }

    solve_lu(l, u, b);

    seidel(a, b);
}