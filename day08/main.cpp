#include <fstream>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

void parseMatrix(Matrix& matrix, std::string_view filename) {
    std::string line;
    std::ifstream fin(static_cast<std::string>(filename));
    while (getline(fin, line, '\n')) {
        std::vector<int> row;
        for (auto ch : line) {
            row.push_back(static_cast<int>(ch - '0'));
        }
        matrix.push_back(row);
    }
    fin.close();
}

void solvePart1(const Matrix& matrix) {
    const int rows{static_cast<int>(matrix.size())}, cols{static_cast<int>(matrix[0].size())};
    int visibleCount{};

    Matrix visible(
        rows,
        std::vector<int>(cols, 0));

    for (int i{}; i < rows; ++i) {  // West wind
        int visHeight{-1};
        for (int j{}; j < cols; ++j) {
            if (matrix[i][j] > visHeight && visible[i][j] < 1) {
                ++visible[i][j];
                ++visibleCount;
            }
            visHeight = std::max(visHeight, matrix[i][j]);
        }
    }

    for (int i{rows - 1}; i >= 0; --i) {  // East wind
        int visHeight{-1};
        for (int j{cols - 1}; j >= 0; --j) {
            if (matrix[i][j] > visHeight && visible[i][j] < 1) {
                ++visible[i][j];
                ++visibleCount;
            }
            visHeight = std::max(visHeight, matrix[i][j]);
        }
    }

    for (int j{}; j < cols; ++j) {  // North wind
        int visHeight{-1};
        for (int i{}; i < rows; ++i) {
            if (matrix[i][j] > visHeight && visible[i][j] < 1) {
                ++visible[i][j];
                ++visibleCount;
            }
            visHeight = std::max(visHeight, matrix[i][j]);
        }
    }

    for (int j{cols - 1}; j >= 0; --j) {  // South wind
        int visHeight{-1};
        for (int i{rows - 1}; i >= 0; --i) {
            if (matrix[i][j] > visHeight && visible[i][j] < 1) {
                ++visible[i][j];
                ++visibleCount;
            }
            visHeight = std::max(visHeight, matrix[i][j]);
        }
    }

    std::cout << "Part 1 Answer: " << visibleCount << '\n';
}

void solvePart2(const Matrix& matrix) {
    const int rows{static_cast<int>(matrix.size())}, cols{static_cast<int>(matrix[0].size())};
    int scenic_score{};

    for (int i{1}; i < rows-1; ++i) {
        for (int j{1}; j < cols-1; ++j) {
            int westScore{0};
            for (int k{j - 1}; k >= 0; --k) {
                ++westScore;
                if (matrix[i][k] >= matrix[i][j])
                    break;
            }

            int eastScore{0};
            for (int k{j + 1}; k < cols; ++k) {
                ++eastScore;
                if (matrix[i][k] >= matrix[i][j])
                    break;
            }

            int northScore{0};
            for (int k{i - 1}; k >= 0; --k) {
                ++northScore;
                if (matrix[k][j] >= matrix[i][j])
                    break;
            }

            int southScore{0};
            for (int k{i + 1}; k < rows; ++k) {
                ++southScore;
                if (matrix[k][j] >= matrix[i][j])
                    break;
            }

            int score {westScore * eastScore * northScore * southScore};
            scenic_score = std::max(
                scenic_score,
                score);
        }
    }

    std::cout << "Part 2 Answer: " << scenic_score << '\n';
}

int main() {
    Matrix matrix;
    std::string_view inputfile{"input.txt"};

    parseMatrix(matrix, inputfile);

    solvePart1(matrix);
    solvePart2(matrix);

    return 0;
}