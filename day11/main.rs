use std::{collections::LinkedList, str::FromStr};

#[derive(Debug, Clone)]
enum Operation {
    Add,
    Multiply,
    Square,
}

#[derive(Debug, Clone)]
struct Monkey {
    items: LinkedList<usize>,
    div_test: usize,
    true_monkey: usize,
    false_monkey: usize,
    op: Operation,
    op_num: Option<usize>,
    inspected: usize,
}

impl Monkey {
    fn inspect(&mut self, item: usize, supermodulo: usize, is_part1: bool) -> (usize, usize) {
        self.inspected += 1;
        let inspect_worry = match self.op {
            Operation::Square => item * item,
            Operation::Add => item + self.op_num.unwrap(),
            Operation::Multiply => item * self.op_num.unwrap(),
        };
        let bored_worry = if is_part1 {
            (inspect_worry as f64 / 3f64).trunc() as usize
        } else {
            inspect_worry % supermodulo
        };
        match bored_worry % self.div_test {
            0 => return (bored_worry, self.true_monkey),
            _ => return (bored_worry, self.false_monkey),
        }
    }
}

impl FromStr for Monkey {
    type Err = ();

    fn from_str(str: &str) -> Result<Self, Self::Err> {
        let lines: Vec<&str> = str.lines().filter(|l| !l.is_empty()).collect();
        // Items
        let items: LinkedList<usize> = lines[1]
            .split_once(':')
            .unwrap()
            .1
            .split(',')
            .filter_map(|s| s.trim().parse::<usize>().ok())
            .collect();
        // Operation
        let (op, op_num) = match lines[2]
            .split_once("old")
            .unwrap()
            .1
            .trim()
            .split_once(' ')
            .unwrap()
        {
            ("*", "old") => (Operation::Square, None),
            ("+", x) => (Operation::Add, x.parse::<usize>().ok()),
            ("*", x) => (Operation::Multiply, x.parse::<usize>().ok()),
            _ => panic!("Couldn't parse operation!"),
        };
        // Test
        let div_test = lines[3]
            .rsplit_once(' ')
            .unwrap()
            .1
            .parse::<usize>()
            .expect("Couldn't parse test condition!");
        let true_monkey = lines[4]
            .rsplit_once(' ')
            .unwrap()
            .1
            .parse::<usize>()
            .expect("Couldn't parse action if true!");
        let false_monkey = lines[5]
            .rsplit_once(' ')
            .unwrap()
            .1
            .parse::<usize>()
            .expect("Couldn't parse action if false!");

        return Ok(Monkey {
            items,
            div_test,
            true_monkey,
            false_monkey,
            op,
            op_num,
            inspected: 0,
        });
    }
}

fn solve(monkeys: &mut [Monkey], rounds: usize, is_part1: bool) -> usize {
    let supermodulo: usize = monkeys.iter().map(|m| m.div_test).product();
    for _ in 0..rounds {
        for i in 0..monkeys.len() {
            while !monkeys[i].items.is_empty() {
                let item = monkeys[i].items.pop_front().unwrap();
                let (item, target_monkey_index) = monkeys[i].inspect(item, supermodulo, is_part1);
                monkeys[target_monkey_index].items.push_back(item);
            }
        }
    }

    let mut inspections = monkeys.iter().map(|m| m.inspected).collect::<Vec<usize>>();
    inspections.sort_by(|a, b| b.cmp(a));

    return inspections[..2].iter().product();
}

fn main() {
    let input = include_str!("input.txt");
    let mut monkeys: Vec<Monkey> = input
        .split("\n\n")
        .filter_map(|l| l.parse::<Monkey>().ok())
        .collect();
    let mut monkeys2 = monkeys.clone();

    println!("Part 1 Answer: {}", solve(&mut monkeys, 20, true));
    println!("Part 2 Answer: {}", solve(&mut monkeys2, 10_000, false));
}
