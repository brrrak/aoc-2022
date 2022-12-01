#include <fstream>
#include <iostream>
#include <queue>

void getCalories(std::priority_queue<int>& calories, std::string input_name) {
    int curCals{0};
    std::ifstream finput(input_name);
    while (finput) {
        std::string line;
        getline(finput, line);
        if (line.length() == 0) {
            if (curCals != 0) {
                calories.push(curCals);
            }
            curCals = 0;
        } else {
            curCals += stoi(line);
        }
    }
    if (curCals != 0) {
        calories.push(curCals);
        curCals = 0;
    }
}

int main() {

    std::priority_queue<int> calories;
    getCalories(calories, "input.txt");

    int sum{calories.top()};
    calories.pop();
    std::cout << "Part 1 Answer: " << sum << '\n';

    for (int i{0}; i < 2; ++i) {
        sum += calories.top();
        calories.pop();
    }
    std::cout << "Part 2 Answer: " << sum << '\n';

    return 0;
}