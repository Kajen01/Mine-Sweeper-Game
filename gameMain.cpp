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

void Minesweeper::placeMines() {
    // Place mines randomly on the field
    int minesPlaced = 0;
    while (minesPlaced < numMines) {
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        if (!mines[row][col]) {
            mines[row][col] = true;
            ++minesPlaced;
        }
    }
}

void Minesweeper::revealLocation(int row, int col) {
    // Implement logic to reveal the location and update the field
    if (mines[row][col]) {
        cout << "Game Over! You hit a mine." << endl;
        displayField();
        exit(0);
    }

    if (field[row][col] == 'c') {
        // Reveal the current location
        int adjacentMines = countAdjacentMines(row, col);
        if (adjacentMines == 0) {
            // No mines nearby, reveal neighboring locations recursively
            field[row][col] = '.';
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize) {
                        revealLocation(newRow, newCol);
                    }
                }
            }
        } else {
            // Display the number of adjacent mines
            field[row][col] = '0' + adjacentMines;
        }
    }
}

void Minesweeper::placeFlag(int row, int col) {
    // Implement logic to place a flag and update the field
    if (field[row][col] == 'c') {
        field[row][col] = 'F';
        --flagsRemaining;
    } else {
        cout << "Invalid move. You can only place a flag on a covered location." << endl;
    }
}

bool Minesweeper::checkWin() {
    // Implement logic to check if the player has won
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (mines[i][j] && field[i][j] != 'F') {
                return false;
            }
        }
    }
    return true;
}


