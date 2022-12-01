#include <fstream>
#include <iostream>

int main() {

    int curCals{};
    int b1{}, b2{}, b3{};

    std::ifstream finput("input.txt");
    while (finput) {
        std::string line;
        getline(finput, line);
        if (line.length() == 0) {
            b3 = (curCals > b3) ? curCals : b3;
            if (b3 > b2) {
                std::swap(b2, b3);
            }
            if (b2 > b1) {
                std::swap(b1, b2);
            }
            curCals = 0;
        } else {
            curCals += stoi(line);
        }
    }

    std::cout << "Part 1 Answer: " << b1 << '\n';
    std::cout << "Part 2 Answer: " << b1 + b2 + b3 << '\n';

    return 0;
}