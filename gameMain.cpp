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

