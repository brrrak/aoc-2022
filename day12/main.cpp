#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using Grid = std::vector<std::vector<int>>;

struct Point {
    int row{}, col{}, steps{};
    // Hash function
    size_t operator()(const Point& c) const { return std::hash<int>()(c.col) ^ std::hash<int>()(c.row); }
    // Equal Function
    bool operator==(const Point& other) const { return (col == other.col && row == other.row); }
};

int parse_grid(Grid& grid, std::string_view filename, Point& start, Point& end) {
    std::ifstream infile{static_cast<std::string>(filename)};
    if (!infile) {
        std::cerr << "Cannot open file or it doesn't exist!\n";
        return 1;
    }

    int i{};
    while (infile) {
        std::vector<int> row;
        std::string line;
        std::getline(infile, line);
        if (line.length() < 1) {
            continue;
        }
        for (size_t j{}; j < line.length(); ++j) {
            switch (line[j]) {
                case 'S':
                    start.col = static_cast<int>(j);
                    start.row = i;
                    line[j] = 'a';
                    break;
                case 'E':
                    end.col = static_cast<int>(j);
                    end.row = i;
                    line[j] = 'z';
                    break;
                default:
                    break;
            }
            row.push_back(static_cast<int>(line[j] - 'a'));
        }
        ++i;
        grid.push_back(row);
    }
    infile.close();

    return 0;
}

int get_manhattan(const Point& pos, const Point& end) {
    return abs(end.row - pos.row) + abs(end.col - pos.col) + pos.steps;
}

std::vector<Point> get_successors(const Point& pos, const Grid& grid, bool is_part2) {
    std::vector<Point> successors;
    int rows{static_cast<int>(grid.size())}, cols{static_cast<int>(grid[0].size())};
    int cur_height = grid[pos.row][pos.col];

    // This part looks terrible
    if (!is_part2) {
        if (pos.row + 1 < rows && grid[pos.row + 1][pos.col] - cur_height < 2) {
            successors.push_back(Point{pos.row + 1, pos.col, pos.steps + 1});
        }
        if (pos.row - 1 >= 0 && grid[pos.row - 1][pos.col] - cur_height < 2) {
            successors.push_back(Point{pos.row - 1, pos.col, pos.steps + 1});
        }
        if (pos.col + 1 < cols && grid[pos.row][pos.col + 1] - cur_height < 2) {
            successors.push_back(Point{pos.row, pos.col + 1, pos.steps + 1});
        }
        if (pos.col - 1 >= 0 && grid[pos.row][pos.col - 1] - cur_height < 2) {
            successors.push_back(Point{pos.row, pos.col - 1, pos.steps + 1});
        }
    } else {
        if (pos.row + 1 < rows && cur_height - grid[pos.row + 1][pos.col] < 2) {
            successors.push_back(Point{pos.row + 1, pos.col, pos.steps + 1});
        }
        if (pos.row - 1 >= 0 && cur_height - grid[pos.row - 1][pos.col] < 2) {
            successors.push_back(Point{pos.row - 1, pos.col, pos.steps + 1});
        }
        if (pos.col + 1 < cols && cur_height - grid[pos.row][pos.col + 1] < 2) {
            successors.push_back(Point{pos.row, pos.col + 1, pos.steps + 1});
        }
        if (pos.col - 1 >= 0 && cur_height - grid[pos.row][pos.col - 1] < 2) {
            successors.push_back(Point{pos.row, pos.col - 1, pos.steps + 1});
        }
    }

    return successors;
}

int solve1(const Grid& grid, const Point start, const Point end) {
    // A*
    auto cmp = [&end](Point& left, Point& right) {
        return get_manhattan(left, end) > get_manhattan(right, end);
    };
    std::priority_queue<Point, std::vector<Point>, decltype(cmp)> fringe(cmp);
    fringe.push(start);
    std::unordered_set<Point, Point> explored;

    while (fringe.size() > 0) {
        Point node = fringe.top();
        fringe.pop();

        if (node == end) {
            return node.steps;
        }

        if (explored.count(node) == 0) {
            explored.insert(node);
            for (auto child : get_successors(node, grid, false)) {
                fringe.push(child);
            }
        }
    }

    std::cerr << "Failure! Couldn't find a valid path!\n";
    return -1;
}

int solve2(const Grid& grid, const Point start) {
    // BFS
    std::queue<Point> fringe;
    fringe.push(start);
    std::unordered_set<Point, Point> explored;

    while (fringe.size() > 0) {
        Point node = fringe.front();
        fringe.pop();

        if (grid[node.row][node.col] == 0) {
            return node.steps;
        }

        if (explored.count(node) == 0) {
            explored.insert(node);
            for (auto child : get_successors(node, grid, true)) {
                fringe.push(child);
            }
        }
    }

    std::cerr << "Failure! Couldn't find a valid path!\n";
    return -1;
}

int main() {
    Grid grid;
    Point start, end;
    std::string_view input_file{"input.txt"};
    parse_grid(grid, input_file, start, end);

    std::cout << "Part 1 Answer: " << solve1(grid, start, end) << '\n';
    std::cout << "Part 2 Answer: " << solve2(grid, end) << '\n';

    return 0;
}