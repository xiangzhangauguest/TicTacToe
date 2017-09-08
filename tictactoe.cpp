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
bool updateBoard(vector<vector<char> >& board, int row, int col, char sign);
void displayBoard(const vector<vector<char> >& board);
char checkWinner(const vector<vector<char> >& board);
char firstHand();
char opponent(char turn);

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
    while (!updateBoard(board, row - 1, col - 1, player1_sign)) {
        cout << "Input the row and column again." << endl;
        cin >> row >> col;
    }
}

void player2Move(vector<vector<char> >& board)
{
    int row, col;
    cout << "Player 2, your turn to go.\nInput the row and column you want to go. (1 - 3 and 1 - 3)" << endl;
    cin >> row >> col;
    while (!updateBoard(board, row - 1, col - 1, player2_sign)) {
        cout << "Input the row and column again." << endl;
        cin >> row >> col;
    }
}

bool checkMoveValid(const vector<vector<char> >& board, int row, int col)
{
    if (row > ROW || col > COL || row < 0 || col < 0) {
        cout << "You move outside the board!" << endl;
        return false;
    }
    else if (board[row][col] != EMPTY) {
        cout << "This cell is full." << endl;
        return false;
    }
    else {
        cout << "OK." << endl;
        return true;
    }
}

bool updateBoard(vector<vector<char> >& board, int row, int col, char sign)
{
    if (checkMoveValid(board, row, col)) {
        board[row][col] = sign;
        // update check to determine who win.
        int add_count = 1;
        if (sign == player2_sign) add_count = -1;
        check[row] += add_count;
        check[ROW + col] += add_count;
        if (row == col) check[ROW + COL] += add_count;
        if (row + col == ROW) check[ROW + COL + 1] += add_count;
        return true;
    }
    else return false;
}

char checkWinner(const vector<vector<char> >& board)
{
    bool is_full = true;
    for (auto& row : board)
        for (auto& e : row)
            if (e == EMPTY)
                is_full = false;

    for (auto& c : check) {
        if (c == ROW) {
            cout << "Player 1 win!" << endl;
            return player1_sign;
        }
        else if (c == 0 - ROW) {
            cout << "Player 2 win!" << endl;
            return player2_sign;
        }
    }
    if (is_full) {
        cout << "Tie the game!";
        return TIE;
    }
    else {
        return NO_ONE;
    }
}

char firstHand()
{
    cout << "You can choose which player you want to be.\nPlayer 1 go first.(1 or 2)";
    int tmp;
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
}

char opponent(char turn)
{
    if (turn == player1_sign) turn = player2_sign;
    else turn = player1_sign;
    return turn;
}
