#include <stdio.h>
#include <stdbool.h>

#define GRID_SIZE 9

// The Sudoku grid
int grid[GRID_SIZE][GRID_SIZE];

// Prints the Sudoku grid.
void printGrid() {
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            printf("%d", grid[r][c]);
            if (c < GRID_SIZE - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Checks if placing 'num' at grid[r][c] is valid.
bool isSafe(int r, int c, int num) {
    // Check row
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[r][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[x][c] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int startRow = r - r % 3;
    int startCol = c - c % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Solves the Sudoku puzzle using backtracking.
bool solve() {
    int r = -1, c = -1;
    bool emptyFound = false;

    // Find an empty cell (0)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                r = i;
                c = j;
                emptyFound = true;
                break;
            }
        }
        if (emptyFound) {
            break;
        }
    }

    // Base case: no empty cells means puzzle is solved
    if (!emptyFound) {
        return true;
    }

    // Try numbers 1-9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(r, c, num)) {
            // Tentative assignment
            grid[r][c] = num;

            // Recurse
            if (solve()) {
                return true;
            }

            // Backtrack
            grid[r][c] = 0;
        }
    }

    return false; // Triggers backtracking
}

int main() {
    // Read the 9x9 grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Solve and print
    if (solve()) {
        printGrid();
    }

    return 0;
}
