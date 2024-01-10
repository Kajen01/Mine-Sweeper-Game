/**************************
21/ENG/089  N. KAJENTHIRAN
21/ENG/048  J. R. REMILTAN
21/ENG/006  A. ABINASH
***************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int gridSize;
    int numMines;
    vector<vector<char>> field;
    vector<vector<bool>> mines;
    int flagsRemaining;

public:
    Minesweeper(int size, int minesCount);
    void displayField();
    void placeMines();
    void revealLocation(int row, int col);
    void placeFlag(int row, int col);
    bool checkWin();
    void playGame();
    int countAdjacentMines(int row, int col);
    static int convertLetterToIndex(char letter);
};

Minesweeper::Minesweeper(int size, int minesCount)
    : gridSize(size), numMines(minesCount), flagsRemaining(minesCount) {
    field.assign(gridSize, vector<char>(gridSize, 'c'));
    mines.assign(gridSize, vector<bool>(gridSize, false));
    // Initialize the random seed
    srand(static_cast<unsigned>(time(nullptr)));
}

void Minesweeper::displayField() {
    // Display the current state of the field
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < gridSize; ++i) {
        cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < gridSize; ++j) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Flags Remaining: " << flagsRemaining << endl;
}

////



////

int Minesweeper::countAdjacentMines(int row, int col) {
    // Implement logic to count the number of adjacent mines
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (i != 0 || j != 0) {  // Exclude the center cell
                if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize) {
                    if (mines[newRow][newCol]) {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

int Minesweeper::convertLetterToIndex(char letter) {
    return toupper(letter) - 'A';
}

void Minesweeper::playGame() {
    placeMines();

    while (true) {
        displayField();

        cout << "Enter move (e.g., ABF for flag, ABR for reveal): ";
        string move;
        cin >> move;

        if (move.size() != 3) {
            cout << "Invalid move. Please enter a valid move." << endl;
            continue;
        }

        int row = convertLetterToIndex(move[0]);
        int col = convertLetterToIndex(move[1]);

        if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
            cout << "Invalid move. Please enter a valid move." << endl;
            continue;
        }

        char action = move[2];

        if (action == 'F') {
            placeFlag(row, col);
        } else if (action == 'R') {
            revealLocation(row, col);
        } else {
            cout << "Invalid move. Please enter a valid move." << endl;
            continue;
        }

        if (checkWin()) {
            cout << "Congratulations! You won!" << endl;
            break;
        }
    }
}

