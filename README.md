# Software Engineering Experiment 1 — Tetris Leaderboard Unit Testing

A small C++ project for VS Code. It demonstrates basis-path-style testing of a Tetris leaderboard's `gameOver()` logic.

## Requirements
- Visual Studio Code
- A C++ compiler available on PATH:
  - Windows: MinGW-w64 g++ (MSYS2 recommended), or another compiler compatible with the commands below
  - Linux/macOS: g++
- VS Code C/C++ extension (Microsoft)

> This project uses a portable command-line test runner rather than Visual Studio's proprietary C++ Unit Test Framework, so it can be run from VS Code.

## Folder structure
```text
Software_Engineering_Experiment_1_VSCode/
├── .vscode/
│   ├── tasks.json
│   └── launch.json
├── data/
│   └── test1.txt
├── src/
│   ├── leaderboard.cpp
│   └── leaderboard.h
├── tests/
│   └── test_leaderboard.cpp
├── README.md
├── run_tests.bat
└── run_tests.sh
```

## Run on Windows (VS Code)
1. Extract the ZIP.
2. Open the extracted `Software_Engineering_Experiment_1_VSCode` folder in VS Code.
3. Install the Microsoft **C/C++** extension if it is not already installed.
4. Install a C++ compiler and ensure `g++ --version` works in the VS Code terminal.
5. Open **Terminal → New Terminal**.
6. Run tests:
   ```powershell
   .\run_tests.bat
   ```
7. Run the interactive leaderboard:
   ```powershell
   g++ -std=c++17 -Wall -Wextra -pedantic src/leaderboard.cpp -o leaderboard.exe
   .\leaderboard.exe
   ```
   Enter an integer score when prompted.

## Run on Linux/macOS
```bash
chmod +x run_tests.sh
./run_tests.sh
g++ -std=c++17 -Wall -Wextra -pedantic src/leaderboard.cpp -o leaderboard
./leaderboard
```

## Expected test output
The test runner runs seven checks: insertion into each of the five positions, a score below the top five, and an equal score (which is inserted after the existing first-place score under the current strict-comparison logic). You should see `[PASS]` for each case and `All 7 tests passed.`

## Basis path analysis
The original `gameOver()` chain has five decision conditions. Its cyclomatic complexity for that decision structure is:

`V(G) = D + 1 = 5 + 1 = 6`

The six main basis paths correspond to inserting at ranks 1–5 and leaving the leaderboard unchanged. One additional tie test checks the strict `>` comparison behavior.

## Notes
- The application uses `data/test1.txt` relative to the project root. Run commands from the project root.
- Tests use a separate temporary score file so they do not overwrite the starter leaderboard.
- The source file uses UTF-8 Chinese rank labels, as in the supplied source material.
