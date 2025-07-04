#include <iostream>
#include <cmath>
using namespace std;

int N; 
int grid[9][9];
int boxSize;


void printLine() {
    cout << "+";
    for (int i = 0; i < N; i++) {
        cout << "--";
        if ((i + 1) % boxSize == 0) cout << "+";
    }
    cout << "\n";
}


void printGrid() {
    printLine();
    for (int i = 0; i < N; i++) {
        cout << "| ";
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) cout << ". ";
            else cout << grid[i][j] << " ";
            if ((j + 1) % boxSize == 0) cout << "| ";
        }
        cout << "\n";
        if ((i + 1) % boxSize == 0) printLine();
    }
}


bool isValid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    int startRow = row - row % boxSize;
    int startCol = col - col % boxSize;

    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}


bool solveSudoku() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= N; num++) {
                    if (isValid(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku())
                            return true;
                        grid[row][col] = 0; 
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    cout << "🔢 Enter Sudoku size (3, 4, or 9): ";
    cin >> N;

    if (N != 3 && N != 4 && N != 9) {
        cout << "❌ Invalid size. Only 3, 4, or 9 supported.\n";
        return 1;
    }

    boxSize = sqrt(N);

    cout << "\nEnter your " << N << "x" << N << " Sudoku grid (row by row, use 0 for blanks):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[i][j];

    cout << "\n🧾 Input Grid:\n";
    printGrid();

    if (solveSudoku()) {
        cout << "\n✅ Solved Sudoku:\n";
        printGrid();
    } else {
        cout << "\n❌ No solution exists.\n";
    }

    return 0;
}
