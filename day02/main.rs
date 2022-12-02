fn main() {
    let input = include_str!("input.txt");
    let lines = input.split('\n');
    let lines_clone = lines.clone();
    let mut score = 0;
    for line in lines {
        let (opp, me) = match line.split_once(' ') {
            Some(k) => k,
            None => continue,
        };
        match me {
            "X" => score += 1,
            "Y" => score += 2,
            "Z" => score += 3,
            _ => (),
        }
        match (opp, me) {
            ("A", "Y") | ("B", "Z") | ("C", "X") => score += 6,
            ("A", "X") | ("B", "Y") | ("C", "Z") => score += 3,
            _ => (),
        }
    }
    println!("Part 1 Answer: {}", score);

    let mut score = 0;
    let lines = lines_clone;
    for line in lines {
        let (opp, win) = match line.split_once(' ') {
            Some(k) => k,
            None => continue,
        };

        if win == "X" {
            match opp {
                "A" => score += 3,
                "B" => score += 1,
                "C" => score += 2,
                _ => (),
            }
        } else if win == "Y" {
            score += 3;
            match opp {
                "A" => score += 1,
                "B" => score += 2,
                "C" => score += 3,
                _ => (),
            }
        } else {
            score += 6;
            match opp {
                "A" => score += 2,
                "B" => score += 3,
                "C" => score += 1,
                _ => (),
            }
        }
    }
    println!("Part 2 Answer: {}", score);
}
