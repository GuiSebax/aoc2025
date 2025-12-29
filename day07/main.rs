use std::collections::{HashMap, HashSet};
use std::fs;

fn parse(conteudo: &str) -> Vec<Vec<char>> {
    conteudo
        .trim()
        .lines()
        .map(|l| l.chars().collect())
        .collect()
}

fn part1(conteudo: &str) -> i64 {
    let grid = parse(conteudo);
    let rows = grid.len();
    let cols = grid[0].len();

    // acha o S (sempre na primeira linha)
    let mut start_col = 0;
    for c in 0..cols {
        if grid[0][c] == 'S' {
            start_col = c;
            break;
        }
    }

    // feixes ativos: (linha, coluna)
    let mut beams: HashSet<(usize, usize)> = HashSet::new();
    beams.insert((0, start_col));

    let mut splits = 0i64;

    while !beams.is_empty() {
        let mut next_beams: HashSet<(usize, usize)> = HashSet::new();

        for (r, c) in beams {
            let nr = r + 1;

            // saiu da matriz
            if nr >= rows {
                continue;
            }

            let cell = grid[nr][c];

            if cell == '.' {
                next_beams.insert((nr, c));
            } else if cell == '^' {
                splits += 1;

                if c > 0 {
                    next_beams.insert((nr, c - 1));
                }
                if c + 1 < cols {
                    next_beams.insert((nr, c + 1));
                }
            }
        }

        beams = next_beams;
    }

    splits
}

fn part2(conteudo: &str) -> u128 {
    let grid = parse(conteudo);
    let rows = grid.len();
    let cols = grid[0].len();

    let mut start_col = 0;
    for c in 0..cols {
        if grid[0][c] == 'S' {
            start_col = c;
            break;
        }
    }

    let mut memo: HashMap<(usize, usize), u128> = HashMap::new();

    fn dfs(
        r: usize,
        c: usize,
        grid: &Vec<Vec<char>>,
        rows: usize,
        cols: usize,
        memo: &mut HashMap<(usize, usize), u128>,
    ) -> u128 {
        if r >= rows {
            return 1;
        }

        if let Some(v) = memo.get(&(r, c)) {
            return *v;
        }

        let cell = grid[r][c];
        let result: u128;

        if cell == '^' {
            let mut left = 0;
            let mut right = 0;

            if c > 0 {
                left = dfs(r + 1, c - 1, grid, rows, cols, memo);
            }
            if c + 1 < cols {
                right = dfs(r + 1, c + 1, grid, rows, cols, memo);
            }

            result = left + right;
        } else {
            // '.' ou 'S'
            result = dfs(r + 1, c, grid, rows, cols, memo);
        }

        memo.insert((r, c), result);
        result
    }

    dfs(1, start_col, &grid, rows, cols, &mut memo)
}

fn main() {
    let conteudo = fs::read_to_string("input.txt")
        .expect("Erro ao ler input.txt");

    println!("{}", part1(&conteudo));
    println!("{}", part2(&conteudo));
}
