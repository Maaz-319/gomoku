Gomoku
======

A simple console-based Gomoku (Five-in-a-Row) game implemented in C++.

File
----
- `start.cpp` — main source containing a 15x15 board, two-player turns (W and B), and simple win detection (5 in a row horizontally, vertically, or diagonally).

How to play
-----------
- The board is 15x15. Empty cells are shown as `.`.
- Players alternate: `W` (first) and `B` (second).
- When prompted, enter a move as two integers: row and column (zero-based indices), separated by space or newline.
- Example input: `7 7` (places a stone at row 7, column 7).
- The game detects a win when a player has 5 or more stones consecutively in any of the four main directions.

Improvements
------------
- **Robust Input Validation**: The game now handles non-integer input, out-of-bounds coordinates, and occupied cells gracefully with clear error messages.
- **Cross-platform Compatibility**: Removed dependency on `conio.h` and `system("cls")` for better portability across different platforms.
- **Better Code Organization**: Functions are now properly separated by concerns for improved maintainability.

Notes & limitations
-------------------
- No AI — the game is for two local players sharing the console.
- Screen clearing uses ANSI escape codes on Unix-like systems and `system("cls")` on Windows.