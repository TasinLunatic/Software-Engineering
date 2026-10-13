#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define UNIT_TEST
#include "../src/leaderboard.cpp"

namespace fs = std::filesystem;

static const std::string testFile = "data/test1_test_runtime.txt";

void writeInitialScores() {
    const std::vector<int> initial{50, 40, 30, 20, 10};
    assert(leaderboard::saveScoresToFile(initial, testFile));
}

std::vector<int> readScores() {
    std::vector<int> scores;
    assert(leaderboard::loadScoresFromFile(scores, testFile));
    return scores;
}

void checkCase(int newScore, const std::vector<int>& expected, const char* name) {
    writeInitialScores();
    leaderboard::gameOver(newScore, testFile);
    const auto actual = readScores();
    if (actual != expected) {
        std::cerr << "[FAIL] " << name << " expected: ";
        for (int x : expected) std::cerr << x << ' ';
        std::cerr << "\n       actual:   ";
        for (int x : actual) std::cerr << x << ' ';
        std::cerr << '\n';
        std::exit(1);
    }
    std::cout << "[PASS] " << name << '\n';
}

int main() {
    fs::create_directories("data");
    checkCase(99, {99, 50, 40, 30, 20}, "Insert first place");
    checkCase(45, {50, 45, 40, 30, 20}, "Insert second place");
    checkCase(35, {50, 40, 35, 30, 20}, "Insert third place");
    checkCase(25, {50, 40, 30, 25, 20}, "Insert fourth place");
    checkCase(15, {50, 40, 30, 20, 15}, "Insert fifth place");
    checkCase(5,  {50, 40, 30, 20, 10}, "Score outside top five");
    checkCase(50, {50, 50, 40, 30, 20}, "Equal score is inserted after the existing first-place score");
    std::remove(testFile.c_str());
    std::cout << "\nAll 7 tests passed.\n";
    return 0;
}
