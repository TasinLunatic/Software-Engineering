#pragma once
#include <string>
#include <vector>

namespace leaderboard {
bool loadScoresFromFile(std::vector<int>& scores, const std::string& path = "data/test1.txt");
bool saveScoresToFile(const std::vector<int>& scores, const std::string& path = "data/test1.txt");
std::vector<int> updateTopFive(const std::vector<int>& oldScores, int score);
void gameOver(int score, const std::string& path = "data/test1.txt");
}
