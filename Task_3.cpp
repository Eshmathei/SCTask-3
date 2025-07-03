#include <iostream>
using namespace std;

int grid[9][9];
int N;       // grid size
int boxSize; // box size (1 for 3x3, 2 for 4x4, 3 for 9x9)

bool isSafe(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % boxSize;
    int startCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++)
        for (int j = 0; j < boxSize; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool solve(int row, int col) {
    if (row == N) return true;
    if (col == N) return solve(row + 1, 0);
    if (grid[row][col] != 0) return solve(row, col + 1);

    for (int num = 1; num <= N; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solve(row, col + 1)) return true;
            grid[row][col] = 0;
        }
    }

    return false;
}

void printGrid() {
    cout << "\n✅ Solved Sudoku:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

int main() {
    cout << "🔢 Enter Sudoku size (3, 4, or 9): ";
    cin >> N;

    // ✅ Replace sqrt with direct mapping
    if (N == 3)
        boxSize = 1;
    else if (N == 4)
        boxSize = 2;
    else if (N == 9)
        boxSize = 3;
    else {
        cout << "❌ Invalid size. Only 3, 4, or 9 are allowed.\n";
        return 1;
    }

    cout << "\nEnter your " << N << "x" << N << " Sudoku grid (use 0 for blanks):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[i][j];

    if (solve(0, 0))
        printGrid();
    else
        cout << "\n❌ No solution exists.\n";

    return 0;
}