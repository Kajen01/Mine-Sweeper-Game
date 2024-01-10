import random

class MinesweeperGame:
    def __init__(self, size, mines):
        self.size = size
        self.mines = mines
        self.flags = mines
        self.board = [['c' for _ in range(size)] for _ in range(size)]
        self.mine_locations = [[False for _ in range(size)] for _ in range(size)]

    def initialize_board(self):
        mines_placed = 0
        while mines_placed < self.mines:
            row = random.randint(0, self.size - 1)
            col = random.randint(0, self.size - 1)
            if not self.mine_locations[row][col]:
                self.mine_locations[row][col] = True
                mines_placed += 1

    def display_board(self):
        print(" ", end=" ")
        for i in range(self.size):
            print(chr(ord('A') + i), end=" ")
        print()

        for i in range(self.size):
            print(chr(ord('A') + i), end=" ")
            for j in range(self.size):
                print(self.board[i][j], end=" ")
            print()

    def reveal_cell(self, row, col):
        if not (0 <= row < self.size and 0 <= col < self.size):
            print("Invalid move. Try again.")
            return

        if self.board[row][col] == 'F':
            print("Cannot reveal a flagged location. Try again.")
            return

        if self.mine_locations[row][col]:
            print("Game over! You revealed a mine.")
            self.display_board()
            exit()

        adjacent_mines = sum(self.mine_locations[i][j]
                             for i in range(row-1, row+2)
                             for j in range(col-1, col+2)
                             if 0 <= i < self.size and 0 <= j < self.size)
        
        if adjacent_mines > 0:
            self.board[row][col] = str(adjacent_mines)
        else:
            self.board[row][col] = '.'
            for i in range(row-1, row+2):
                for j in range(col-1, col+2):
                    if 0 <= i < self.size and 0 <= j < self.size and self.board[i][j] == 'c':
                        self.reveal_cell(i, j)

    def place_flag(self, row, col):
        if not (0 <= row < self.size and 0 <= col < self.size):
            print("Invalid move. Try again.")
            return

        if self.board[row][col] == 'c' and self.flags > 0:
            self.board[row][col] = 'F'
            self.flags -= 1
        else:
            print("Cannot place a flag here. Try again.")

    def is_game_over(self):
        return all(self.board[i][j] != 'c' or self.mine_locations[i][j]
                   for i in range(self.size) for j in range(self.size))

    def is_game_won(self):
        return all(self.board[i][j] != 'c' or not self.mine_locations[i][j]
                   for i in range(self.size) for j in range(self.size))

    def play(self):
        self.initialize_board()

        while not self.is_game_over() and not self.is_game_won():
            self.display_board()

            command = input("Enter command (R to reveal, F to place flag): ")
            row, col = input("Enter row and column (e.g., 'A B'): ").split()
            row_index, col_index = ord(row) - ord('A'), ord(col) - ord('A')

            if not (0 <= row_index < self.size and 0 <= col_index < self.size):
                print("Invalid move. Try again.")
                continue

            if command == 'R':
                self.reveal_cell(row_index, col_index)
            elif command == 'F':
                self.place_flag(row_index, col_index)
            else:
                print("Invalid command. Try again.")

        if self.is_game_won():
            print("Congratulations! You won the game!")
        else:
            print("Game over! You revealed a mine.")
            self.display_board()

if __name__ == "__main__":
    size_choice = int(input("Choose a field size (1: 10x10, 2: 15x15, 3: 20x20): "))
    if size_choice == 1:
        size, mines = 10, 12
    elif size_choice == 2:
        size, mines = 15, 18
    elif size_choice == 3:
        size, mines = 20, 24
    else:
        print("Invalid choice. Exiting...")
        exit(1)

    game = MinesweeperGame(size, mines)
    game.play()
