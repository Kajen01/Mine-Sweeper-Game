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
    srand(static_cast<unsigned>(time(nullptr)));
}

// Display the current state of the field
void Minesweeper::displayField() {
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

// Place mines randomly on the field
void Minesweeper::placeMines() {
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

// Implement logic to reveal the location and update the field
void Minesweeper::revealLocation(int row, int col) {
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
            field[row][col] = '0' + adjacentMines;
        }
    }
}

// Implement logic to place a flag and update the field
void Minesweeper::placeFlag(int row, int col) {
    if (field[row][col] == 'c') {
        field[row][col] = 'F';
        --flagsRemaining;
    } else {
        cout << "Invalid move. You can only place a flag on a covered location." << endl;
    }
}

// Implement logic to check if the player has won
bool Minesweeper::checkWin() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (mines[i][j] && field[i][j] != 'F') {
                return false;
            }
        }
    }
    return true;
}

// Implement logic to count the number of adjacent mines
int Minesweeper::countAdjacentMines(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (i != 0 || j != 0) {
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


int main()
{  
    cout << "1. 10-by-10 (12 Mines)" << endl;
    cout << "2. 15-by-15 (18 Mines)" << endl;
    cout << "3. 20-by-20 (24 Mines)" << endl;
    cout << "\nSelect Field Option: ";

    int option;
    cin >> option;
    
    cout << endl << endl;

    int gridSize, numMines;

    switch (option) {
    case 1:
        gridSize = 10;
        numMines = 12;
        break;
    case 2:
        gridSize = 15;
        numMines = 18;
        break;
    case 3:
        gridSize = 20;
        numMines = 24;
        break;
    default:
        cout << "Invalid option. Exiting." << endl;
        return 1;
    }

    Minesweeper game(gridSize, numMines);
    game.playGame();

	return 0;
}

