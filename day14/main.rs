use std::{collections::HashSet, cmp::max};

fn parse_grid(input: &str) -> (HashSet<(isize, isize)>, isize) {
    let mut grid: HashSet<(isize, isize)> = HashSet::new();
    let mut max_y = 0;
    let lines = input.lines().filter(|l| !l.is_empty());
    for line in lines {
        let rocks = line.split(" -> ");
        let mut rocks = rocks.map(|s| s.split_once(',').unwrap()).map(|(x, y)| {
            (
                x.parse::<isize>().ok().unwrap(),
                y.parse::<isize>().ok().unwrap(),
            )
        });
        let (mut start_x, mut start_y) = rocks.next().unwrap();
        grid.insert((start_x, start_y));
        max_y = max(start_y, max_y);

        for (x, y) in rocks {
            while start_x != x {
                start_x += (x - start_x).signum();
                grid.insert((start_x, start_y));
            }
            while start_y != y {
                start_y += (y - start_y).signum();
                grid.insert((start_x, start_y));
                max_y = max(start_y, max_y);
            }
            (start_x, start_y) = (x, y);
            grid.insert((start_x, start_y));
            max_y = max(start_y, max_y);
        }
    }

    return (grid, max_y);
}

fn solve_part1(mut grid: HashSet<(isize, isize)>, max_y: isize) -> isize {
    let sand_origin: (isize, isize) = (500, 0);
    let mut sands_at_rest = 0;
    let mut sand = sand_origin;
    loop {
        let (x, y) = sand;
        if !grid.contains(&(x, y + 1)) {
            sand = (x, y + 1);
        } else if !grid.contains(&(x - 1, y + 1)) {
            sand = (x - 1, y + 1);
        } else if !grid.contains(&(x + 1, y + 1)) {
            sand = (x + 1, y + 1);
        } else {
            grid.insert(sand);
            sands_at_rest += 1;
            sand = sand_origin;
        }
        // Terminating Condition
        if sand.1 >= max_y {
            return sands_at_rest;
        }
    }
}

fn solve_part2(mut grid: HashSet<(isize, isize)>, max_y: isize) -> isize {
    let sand_origin: (isize, isize) = (500, 0);
    let mut sands_at_rest = 0;
    let mut sand = sand_origin;
    loop {
        let (x, y) = sand;
        if !grid.contains(&(x, y + 1)) && y + 1 < max_y + 2 {
            sand = (x, y + 1);
        } else if !grid.contains(&(x - 1, y + 1)) && y + 1 < max_y + 2 {
            sand = (x - 1, y + 1);
        } else if !grid.contains(&(x + 1, y + 1)) && y + 1 < max_y + 2 {
            sand = (x + 1, y + 1);
        } else {
            grid.insert(sand);
            sands_at_rest += 1;
            sand = sand_origin;
        }
        // Terminating Condition
        if grid.contains(&(sand_origin)) {
            return sands_at_rest;
        }
    }
}

fn main() {
    let input = include_str!("input.txt");
    let (grid, max_y) = parse_grid(input);
    println!("Part 1 Answer: {}", solve_part1(grid.clone(), max_y));
    println!("Part 2 Answer: {}", solve_part2(grid, max_y));
}
