#include <iostream>
#include <iomanip>
#include <limits>
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

    void clear_screen()
    {
        // Cross-platform clear screen alternative
        #ifdef _WIN32
            system("cls");
        #else
            cout << "\033[2J\033[1;1H"; // ANSI escape codes
        #endif
    }

    void pause_screen()
    {
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    bool get_player_input(int &r, int &c)
    {
        cout << "\nPlayer " << (char)get_current_player() << ", enter move (row col): ";
        
        // Clear any error flags
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Try to read input
        if (!(cin >> r))
        {
            // Handle non-integer input or EOF
            if (cin.eof())
            {
                cout << "\nInput closed. Exiting game.\n";
                return false;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "INVALID INPUT: Please enter integers only.\n";
            return false;
        }

        if (!(cin >> c))
        {
            // Handle non-integer input for column
            if (cin.eof())
            {
                cout << "\nInput closed. Exiting game.\n";
                return false;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "INVALID INPUT: Please enter integers only.\n";
            return false;
        }

        // Clear remaining input on the line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    bool is_valid_move(int r, int c)
    {
        // Check bounds
        if (r < 0 || r >= rows)
        {
            cerr << "INVALID MOVE: Row " << r << " is out of bounds (0-" << rows - 1 << ").\n";
            return false;
        }

        if (c < 0 || c >= cols)
        {
            cerr << "INVALID MOVE: Column " << c << " is out of bounds (0-" << cols - 1 << ").\n";
            return false;
        }

        // Check if cell is occupied
        if (board[r][c] != '.')
        {
            cerr << "INVALID MOVE: Cell (" << r << ", " << c << ") is already occupied.\n";
            return false;
        }

        return true;
    }

    void make_move(int r, int c)
    {
        board[r][c] = this->curr_player;
        total_moves++;
    }

    void switch_player()
    {
        this->curr_player = (this->curr_player == FIRST_PLAYER) ? SECOND_PLAYER : FIRST_PLAYER;
    }

    bool is_board_full()
    {
        return total_moves == rows * cols;
    }

    void update_game_status_after_move(int r, int c)
    {
        if (check_win_from(r, c))
        {
            this->game_status = (this->curr_player == FIRST_PLAYER) ? FIRST_WIN : SECOND_WIN;
        }
        else if (is_board_full())
        {
            this->game_status = DRAW;
        }
    }

    void handle_player_move()
    {
        int r, c;
        while (this->game_status == ONGOING)
        {
            clear_screen();
            display_board();

            // Get player input with validation
            if (!get_player_input(r, c))
            {
                // If input fails (EOF or error), ask again or exit
                if (cin.eof())
                {
                    this->game_status = DRAW;
                    return;
                }
                pause_screen();
                continue;
            }

            // Validate the move
            if (!is_valid_move(r, c))
            {
                pause_screen();
                continue;
            }

            // Make the move
            make_move(r, c);

            // Check game status
            update_game_status_after_move(r, c);

            // If game ended, display final board and return
            if (this->game_status != ONGOING)
            {
                clear_screen();
                display_board();
                return;
            }

            // Switch to next player
            switch_player();
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
