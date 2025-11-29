#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Board dimensions and start position, read from input
int N, M;
int START_R, START_C;

// All 8 possible moves for a knight
const int move_x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int move_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// A structure to hold a potential move and its "degree" for Warnsdorff's rule
typedef struct {
    int r;
    int c;
    int degree;
} Move;

// A comparator function for qsort to sort moves by their degree
int compareMoves(const void* a, const void* b) {
    return ((Move*)a)->degree - ((Move*)b)->degree;
}

// Checks if a square (r, c) is on the board and has not been visited yet
bool isValid(int r, int c, int board[8][8]) {
    return (r >= 0 && r < N && c >= 0 && c < M && board[r][c] == 0);
}

// Calculates the "degree" of a square: the number of valid onward moves
// This is the core of Warnsdorff's heuristic
int getDegree(int r, int c, int board[8][8]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int next_r = r + move_x[i];
        int next_c = c + move_y[i];
        if (isValid(next_r, next_c, board)) {
            count++;
        }
    }
    return count;
}

// The main recursive backtracking function to find the tour
bool solveTourUtil(int r, int c, int move_count, int board[8][8]) {
    // Base Case: If all squares have been visited
    if (move_count == N * M) {
        // Check if the tour is closed (can we jump back to the start?)
        for (int i = 0; i < 8; i++) {
            if (r + move_x[i] == START_R && c + move_y[i] == START_C) {
                return true; // Solution found!
            }
        }
        return false; // Tour is complete but not closed
    }

    // --- Warnsdorff's Rule Implementation ---
    Move next_moves[8];
    int num_moves = 0;
    // Find all valid next moves and calculate their degrees
    for (int i = 0; i < 8; i++) {
        int next_r = r + move_x[i];
        int next_c = c + move_y[i];
        if (isValid(next_r, next_c, board)) {
            next_moves[num_moves].r = next_r;
            next_moves[num_moves].c = next_c;
            // Temporarily mark the board to accurately calculate the degree from the next square
            board[next_r][next_c] = 1; 
            next_moves[num_moves].degree = getDegree(next_r, next_c, board);
            board[next_r][next_c] = 0; // Unmark it
            num_moves++;
        }
    }

    // Sort the possible moves by their degree in ascending order
    qsort(next_moves, num_moves, sizeof(Move), compareMoves);
    // --- End of Warnsdorff's Rule ---

    // Recursively try all valid moves, starting with the one with the lowest degree
    for (int i = 0; i < num_moves; i++) {
        int next_r = next_moves[i].r;
        int next_c = next_moves[i].c;

        board[next_r][next_c] = move_count + 1; // Make the move

        // Recur for the next move
        if (solveTourUtil(next_r, next_c, move_count + 1, board)) {
            return true;
        } else {
            // If the move didn't lead to a solution, backtrack
            board[next_r][next_c] = 0;
        }
    }

    return false; // No valid moves led to a solution
}

// Initializes the board and calls the recursive utility
void findClosedTour() {
    int board[8][8];
    memset(board, 0, sizeof(board));

    // Place the knight on the starting square
    board[START_R][START_C] = 1;

    // Start the backtracking process
    if (!solveTourUtil(START_R, START_C, 1, board)) {
        printf("-1\n");
    } else {
        // Print the solution board
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
    }
}

int main() {
    int r, c;
    if (scanf("%d %d %d %d", &N, &M, &r, &c) != 4) {
        return 1; // Input error
    }

    START_R = r;
    START_C = c;

    findClosedTour();

    return 0;
}