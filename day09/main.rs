use std::{collections::HashSet, str::FromStr};

enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl FromStr for Direction {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "U" => Ok(Direction::Up),
            "D" => Ok(Direction::Down),
            "L" => Ok(Direction::Left),
            "R" => Ok(Direction::Right),
            _ => Err(()),
        }
    }
}

#[derive(Clone, Debug)]
struct Knot {
    x: i32,
    y: i32,
}

impl Knot {
    fn new() -> Knot {
        Knot { x: 0, y: 0 }
    }

    fn move_knot(&mut self, dir: &Direction) {
        match dir {
            Direction::Up => self.y += 1,
            Direction::Down => self.y -= 1,
            Direction::Left => self.x -= 1,
            Direction::Right => self.x += 1,
        }
    }

    fn are_adjacent(&self, tail: &Knot) -> bool {
        if (self.x - tail.x).abs() > 1 || (self.y - tail.y).abs() > 1 {
            return false;
        }
        return true;
    }
}

fn move_to_head(knots: &mut [Knot], i: usize) {
    let (dir_x, dir_y) = (knots[i - 1].x - knots[i].x, knots[i - 1].y - knots[i].y);
    if dir_x != 0 {
        knots[i].x += dir_x.signum();
    }
    if dir_y != 0 {
        knots[i].y += dir_y.signum();
    }
}

fn solve(input: &str, num_knots: usize) -> usize {
    let mut knots = vec![Knot::new(); num_knots];
    let mut tail_visited: HashSet<(i32, i32)> = HashSet::from([(0, 0)]);

    for line in input.lines().filter(|l| !l.is_empty()) {
        let (dir, steps) = line.split_once(' ').unwrap();
        let dir = dir.parse::<Direction>().expect("Couldn't parse direction!");
        let steps = steps.parse::<i32>().expect("Couldn't parse step value!");

        for _ in 0..steps {
            knots[0].move_knot(&dir);
            for i in 1..num_knots {
                if knots[i - 1].are_adjacent(&knots[i]) {
                    continue;
                } else {
                    move_to_head(&mut knots, i);
                }
                if i == num_knots - 1 {
                    tail_visited.insert((knots[i].x, knots[i].y));
                }
            }
        }
    }

    return tail_visited.len();
}

fn main() {
    let input = include_str!("input.txt");
    println!("Part 1 Answer: {}", solve(input, 2));
    println!("Part 2 Answer: {}", solve(input, 10));
}
