#include <iostream>
#include <conio.h>
#include <iomanip>
#define rows 15
#define cols 15
#define TRAVERSE_BOARD for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++)

using namespace std;

enum TURNS { FIRST_PLAYER = 'W', SECOND_PLAYER = 'B' };
enum STATUS { FIRST_WIN, SECOND_WIN, DRAW, ONGOING };

class Board
{
    char board[rows][cols];
    STATUS game_status = ONGOING;
    TURNS curr_player = FIRST_PLAYER;
    int total_moves = 0;

public:
    Board() { TRAVERSE_BOARD board[i][j] = '.'; }

    STATUS get_game_status() { return this->game_status; }
    TURNS get_current_player() { return this->curr_player; }

    void set_current_player(TURNS pl) { this->curr_player = pl; }
    void set_game_status(STATUS st) { this->game_status = st; }

    void display_board()
    {
        cout << "\t";
        for (int i = 0; i < cols; i++) cout << left << setw(2) << i << " ";
        TRAVERSE_BOARD
        {
            if (!j) cout << "\n" << i << "\t";
            cout << board[i][j] << "  ";
        }
        cout << "\n";
    }

    void handle_player_move()
    {
        int r, c;
        while (this->game_status == ONGOING)
        {
            system("cls");
            display_board();
            cout << "\nPlayer " << (char)get_current_player() << ", enter move (row col): ";
            cin >> r >> c;

            if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != '.')
            {
                cerr << "INVALID MOVE. Try again.\n";
                getch();
                continue;
            }

            board[r][c] = this->curr_player;
            total_moves++;

            if (check_win_from(r, c))
            {
                this->game_status = (this->curr_player == FIRST_PLAYER) ? FIRST_WIN : SECOND_WIN;
                display_board();
                return;
            }

            if (total_moves == rows * cols)
            {
                this->game_status = DRAW;
                display_board();
                return;
            }

            this->curr_player = (this->curr_player == FIRST_PLAYER) ? SECOND_PLAYER : FIRST_PLAYER;
        }
    }

    void display_winner()
    {
        if (game_status == FIRST_WIN) cout << "\nPlayer W wins!\n";
        else if (game_status == SECOND_WIN) cout << "\nPlayer B wins!\n";
        else if (game_status == DRAW) cout << "\nIt's a draw!\n";
    }

    bool check_win_from(int r, int c)
    {
        char player = board[r][c];
        if (player == '.') return false;

        int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

        for (int d = 0; d < 4; ++d)
        {
            int dx = directions[d][0];
            int dy = directions[d][1];
            int count = 1;

            for (int k = 1; k < 5; ++k)
            {
                int nr = r + k * dx;
                int nc = c + k * dy;
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) break;
                if (board[nr][nc] == player) count++;
                else break;
            }

            for (int k = 1; k < 5; ++k)
            {
                int nr = r - k * dx;
                int nc = c - k * dy;
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) break;
                if (board[nr][nc] == player) count++;
                else break;
            }

            if (count >= 5) return true;
        }
        return false;
    }
};

int main()
{
    Board board;
    board.handle_player_move();
    board.display_winner();
    return 0;
}
