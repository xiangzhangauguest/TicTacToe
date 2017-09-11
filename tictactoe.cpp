#include <iostream>
#include <vector>

using namespace std;

const char player1_sign = 'X';
const char player2_sign = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
const int ROW = 3;
const int COL = 3;
vector<int> check(ROW + COL + 2);

void initGame(const vector<vector<char> >& board);
void player1Move(vector<vector<char> >& board);
void player2Move(vector<vector<char> >& board);
bool checkMoveValid(const vector<vector<char> >& board, int row, int col);
void updateBoard(vector<vector<char> >& board, int row, int col, char player_sign, bool is_add = true);
void displayBoard(const vector<vector<char> >& board);
char checkWinner(const vector<vector<char> >& board);
char firstHand();
char opponent(char turn);
void computerMove(vector<vector<char> >& board, char computer_sign);

int main()
{
    vector<vector<char> > board(ROW, vector<char>(COL, EMPTY));

    initGame(board);

    char turn = firstHand();
    while (checkWinner(board) == NO_ONE) {
        if (turn == player1_sign) {
            player1Move(board);
        }
        else {
            player2Move(board);
        }
        displayBoard(board);
        turn = opponent(turn);
    }

    if (checkWinner(board) == player1_sign) cout << "Player1 win!\n";
    else if (checkWinner(board) == player2_sign) cout << "Player2 win!\n";
    if (checkWinner(board) == TIE) cout << "Tie the game!\n";

    return 0;
}

void initGame(const vector<vector<char> >& board)
{
    cout << "Welcome to tic tac toe game!." << endl;
    displayBoard(board);
}

void displayBoard(const vector<vector<char> >& board)
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << "  " << board[i][j];
            if (j != COL - 1) cout << "|";
        }
        if (i != ROW - 1) cout << "\n-----------" << endl;
    }
    cout << endl;
}

void player1Move(vector<vector<char> >& board)
{
    int row, col;
    cout << "Player 1, your turn to go.\nInput the row and column you want to go. (1 - 3 and 1 - 3)" << endl;
    cin >> row >> col;
    while (!checkMoveValid(board, row - 1, col - 1)) {
        cout << "This sell is taken.\n";
        cout << "Input the row and column again.\n";
        cin >> row >> col;
    }
    updateBoard(board, row - 1, col - 1, player1_sign);
}

void player2Move(vector<vector<char> >& board)
{
//    int row, col;
//    cout << "Player 2, your turn to go.\nInput the row and column you want to go. (1 - 3 and 1 - 3)" << endl;
//    cin >> row >> col;
//    while (!checkMoveValid(board, row - 1, col - 1)) {
//        cout << "Input the row and column again." << endl;
//        cin >> row >> col;
//    }
//    updateBoard(board, row - 1, col - 1, player2_sign);

    computerMove(board, player2_sign);
}

void computerMove(vector<vector<char> >& board, char computer_sign)
{
    int row = 0, col = 0;
    bool found = false;

    while (!found && row < ROW && col < COL) {
        if (checkMoveValid(board, row, col)) {
            updateBoard(board, row, col, computer_sign);
            found = checkWinner(board) == computer_sign;
            updateBoard(board, row, col, computer_sign, false);
        }
        if (!found) {
            if (col + 1 < COL) col++;
            else {
                row++;
                col = 0;
            }
        }
    }

    if (!found) {
        char another_player_sign = opponent(computer_sign);
        row = 0, col = 0;
        while (!found && row < ROW && col < COL) {
            if (checkMoveValid(board, row, col)) {
                updateBoard(board, row, col, another_player_sign);
                found = checkWinner(board) == another_player_sign;
                updateBoard(board, row, col, another_player_sign, false);
            }
            if (!found) {
                if (col + 1 < COL) col++;
                else {
                    row++;
                    col = 0;
                }
            }
        }
    }

    if (!found) {
        const vector<pair<int, int> > BEST_MOVES = {{1, 1}, {0, 0}, {0, 2}, {2, 0}, {2, 2}, {0, 1}, {1, 0}, {1, 2}, {2, 1}};
        for (const auto& move_pair : BEST_MOVES) {
            if (checkMoveValid(board, move_pair.first, move_pair.second)) {
                row = move_pair.first;
                col = move_pair.second;
                break;
            }
        }
    }

    updateBoard(board, row, col, computer_sign);
    cout << "Computer go " << row + 1 << "," << col + 1 << endl;
}

bool checkMoveValid(const vector<vector<char> >& board, int row, int col)
{
    if (row > ROW || col > COL || row < 0 || col < 0 || board[row][col] != EMPTY) return false;
    else return true;
}

void updateBoard(vector<vector<char> >& board, int row, int col, char player_sign, bool is_add)
{
    if (is_add) {
        board[row][col] = player_sign;
        // update check to determine who win.
        int add_count = 1;
        if (player_sign == player2_sign) add_count = -1;
        check[row] += add_count;
        check[ROW + col] += add_count;
        if (row == col) check[ROW + COL] += add_count;
        if (row + col == ROW - 1) check[ROW + COL + 1] += add_count;
    }
    else {
        board[row][col] = EMPTY;
        // update check to determine who win.
        int add_count = -1;
        if (player_sign == player2_sign) add_count = 1;
        check[row] += add_count;
        check[ROW + col] += add_count;
        if (row == col) check[ROW + COL] += add_count;
        if (row + col == ROW - 1) check[ROW + COL + 1] += add_count;
    }
}

char checkWinner(const vector<vector<char> >& board)
{
    bool is_full = true;
    for (auto& row : board)
        for (auto& e : row)
            if (e == EMPTY)
                is_full = false;

    for (auto& c : check) {
        if (c == ROW) return player1_sign;
        else if (c == 0 - ROW) return player2_sign;
    }
    if (is_full) return TIE;
    else return NO_ONE;

}

char firstHand()
{
    cout << "You can choose which player you want to be.\nPlayer 1 go first.(1 or 2)";
    int tmp;
    char first_hand;
    while (cin >> tmp) {
        if (tmp == 1) {
            cout << "You choose go first.";
            return player1_sign;
        }
        else if (tmp == 2) {
            cout << "You choose not go first.";
            return player2_sign;
        }
        else cout << "You should input 1 or 2.";
    }
    return player1_sign;
}

char opponent(char turn)
{
    if (turn == player1_sign) turn = player2_sign;
    else turn = player1_sign;
    return turn;
}
