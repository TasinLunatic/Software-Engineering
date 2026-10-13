#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include "leaderboard.h"

namespace leaderboard {
constexpr std::size_t TOP_COUNT = 5;
const std::string DEFAULT_FILE = "data/test1.txt";

std::string rankLabel(std::size_t i) {
    static const char* labels[] = {"第一名", "第二名", "第三名", "第四名", "第五名"};
    return labels[i];
}

bool loadScoresFromFile(std::vector<int>& scores, const std::string& path) {
    scores.assign(TOP_COUNT, 0);
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "[Warning] Cannot open " << path
                  << "; using default scores of 0.\n";
        return false;
    }

    for (std::size_t i = 0; i < TOP_COUNT; ++i) {
        std::string line;
        if (!std::getline(in, line)) break;
        const auto dot = line.find('.');
        if (dot == std::string::npos) {
            std::cerr << "[Warning] Invalid score format on line " << (i + 1)
                      << ": " << line << '\n';
            continue;
        }
        try {
            scores[i] = std::stoi(line.substr(dot + 1));
        } catch (const std::exception&) {
            std::cerr << "[Warning] Invalid score on line " << (i + 1) << '\n';
        }
    }
    return true;
}

bool saveScoresToFile(const std::vector<int>& scores, const std::string& path) {
    if (scores.size() < TOP_COUNT) {
        std::cerr << "[Error] Need five scores to save.\n";
        return false;
    }
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "[Error] Cannot write " << path << '\n';
        return false;
    }
    for (std::size_t i = 0; i < TOP_COUNT; ++i) {
        out << rankLabel(i) << '.' << scores[i] << '\n';
    }
    return static_cast<bool>(out);
}

std::vector<int> updateTopFive(const std::vector<int>& oldScores, int score) {
    std::vector<int> scores = oldScores;
    scores.resize(TOP_COUNT, 0);
    for (std::size_t i = 0; i < TOP_COUNT; ++i) {
        if (score > scores[i]) {
            for (std::size_t j = TOP_COUNT - 1; j > i; --j) {
                scores[j] = scores[j - 1];
            }
            scores[i] = score;
            break;
        }
    }
    return scores;
}

void gameOver(int score, const std::string& path) {
    std::cout << "======== GAME OVER!! ========\n";
    std::cout << "Your score: " << score << "\n\n";

    std::vector<int> scores;
    loadScoresFromFile(scores, path);
    scores = updateTopFive(scores, score);

    if (!saveScoresToFile(scores, path)) {
        std::cerr << "[Error] Leaderboard was not saved.\n";
    }

    std::cout << "Current top five scores:\n";
    for (std::size_t i = 0; i < TOP_COUNT; ++i) {
        std::cout << rankLabel(i) << ": " << scores[i] << '\n';
    }
}
} // namespace leaderboard

#ifndef UNIT_TEST
int main() {
    std::cout << "Enter this game's score (integer): ";
    int score{};
    while (!(std::cin >> score)) {
        std::cout << "[Error] Please enter an integer score: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    leaderboard::gameOver(score);
    return 0;
}
#endif
