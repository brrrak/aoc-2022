fn main() {
    // Solution from ThePrimeagen's stream
    let input = include_str!("input.txt");

    let mut stack = vec![("/", 0)];
    let mut final_countdown = vec![];

    let report_amount = 100_000;
    let total_space = 70_000_000;
    let unused_space_req = 30_000_000;
    let mut total = 0;

    for line in input.lines().filter(|l| !l.is_empty()) {
        if line == "$ cd /" || line == "ls" {
            continue;
        }

        if line.starts_with("$ cd ") {
            let dir = line.strip_prefix("$ cd ").unwrap();
            if dir == ".." {
                let (name, amount) = stack.pop().unwrap();
                if amount <= report_amount {
                    total += amount;
                }
                stack.last_mut().unwrap().1 += amount;
                final_countdown.push((name, amount));
            } else {
                stack.push((dir, 0));
            }
            continue;
        }

        let (amount, _) = line.split_once(' ').unwrap();

        if let Ok(amount) = amount.parse::<usize>() {
            stack.last_mut().unwrap().1 += amount;
        }
    }

    println!("Part 1 Answer: {}", total);

    while !stack.is_empty() {
        let (name, amount) = stack.pop().unwrap();
        final_countdown.push((name, amount));

        if !stack.is_empty() {
            stack.last_mut().unwrap().1 += amount;
        }
    }

    let free_space = total_space - final_countdown.last().unwrap().1;
    let space_to_empty = unused_space_req - free_space;

    let space_emptied = final_countdown
        .into_iter()
        .filter(|(_, amount)| *amount >= space_to_empty)
        .map(|(_, amount)| amount)
        .min()
        .unwrap();

    println!("Part 2 Answer: {}", space_emptied);
}
