#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
mkdir -p data
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_leaderboard.cpp -o tests/test_leaderboard
./tests/test_leaderboard
rm -f tests/test_leaderboard
