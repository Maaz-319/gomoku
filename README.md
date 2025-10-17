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

Notes & limitations
-------------------
- Input is not robust: non-integer input may cause undefined behavior.
- No AI — the game is for two local players sharing the console.
- The program uses `conio.h` and `getch()`; on some compilers/platforms (non-MSVC/MinGW) you may need to modify or remove that dependency.