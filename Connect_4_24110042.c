#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char board[4][5];
#define MAX_ROWS 4
#define MAX_COLS 5

void init_board(){
    for(size_t i=0; i<4; i++){
        for (size_t j=0; j<5; j++){
            board[i][j] = '.';
        }
    }
}

int valid_move(int col){
    return ((col>=0) && (col<MAX_COLS) && (board[0][col]=='.'));
}

int make_move(int col, char player){
    if(!valid_move(col)) return -1;
    for(int i=4; i>=0; i--){
        if(board[i][col]=='.'){
            board[i][col]=player;
            return i;
        }
    }
}

void undo_move(int col) {
    for (int r = 0; r < 4; r++) {
        if (board[r][col] != '.') {
            board[r][col] = '.';
            return;
        }
    }
}

int check_win(char player){
    //horizontal check
    for(size_t i=0; i<4; i++){
        for(size_t j=0; j<2; j++){
            if((board[i][j]==player)&&
            (board[i][j+1]==player)&&
            (board[i][j+2]==player)&&
            (board[i][j+3]==player)){
                return 1;
            }
        }
    }
    //vertical check
    for(size_t i=0; i<1; i++){
        for(size_t j=0; j<5; j++){
            if((board[i][j]==player)&&
            (board[i+1][j]==player)&&
            (board[i+2][j]==player)&&
            (board[i+3][j]==player)){
                return 1;
            }
        }
    }
    //diagonal 1
    for(size_t i=0; i<1; i++){
        for(size_t j=0; j<2; j++){
            if((board[i][j]==player)&&
            (board[i+1][j+1]==player)&&
            (board[i+2][j+2]==player)&&
            (board[i+3][j+3]==player)){
                return 1;
            }
        }
    }
    //diagonal 2
    for(size_t i=0; i<1; i++){
        for(size_t j=4; j>2; j--){
            if((board[i][j]==player)&&
            (board[i+1][j-1]==player)&&
            (board[i+2][j-2]==player)&&
            (board[i+3][j-3]==player)){
                return 1;
            }
        }
    }

    return 0;
}

int board_full(){
    for(size_t i=0; i<5; i++){
        if(board[0][i]=='.') return 0;
    }
    return 1;
}

int evaluate_board(){
    if (check_win('Y')) return 1000;
    if (check_win('R')) return -1000;
    return 0;
}

int score_window(char window[4], char player) {
    char opponent = (player == 'Y' ? 'R' : 'Y');
    int countP = 0, countO = 0, countE = 0;
    for (int i = 0; i < 4; i++) {
        if (window[i] == player) countP++;
        else if (window[i] == opponent) countO++;
        else countE++;
    }
    if (countO > 0) return 0;
    if (countP == 4)    return 100;
    if (countP == 3)    return 10;
    if (countP == 2)    return 2;
    return 0;
}

int heuristic(char player) {
    int score = 0;
    // Center column bonus
    int center = 5 / 2;
    for (int r = 0; r < 4; r++) {
        if (board[r][center] == player) score += 3;
    }
    // Evaluate windows
    char window[4];
    // Horizontal
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c <= MAX_COLS - 4; c++) {
            for (int i = 0; i < 4; i++) window[i] = board[r][c+i];
            score += score_window(window, player);
        }
    }
    // Vertical
    for (int r = 0; r <= 4 - 4; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            for (int i = 0; i < 4; i++) window[i] = board[r+i][c];
            score += score_window(window, player);
        }
    }
    // Diagonals
    for (int r = 0; r <= MAX_ROWS - 4; r++) {
        for (int c = 0; c <= MAX_COLS - 4; c++) {
            for (int i = 0; i < 4; i++) window[i] = board[r+i][c+i];
            score += score_window(window, player);
        }
        for (int c = 3; c < MAX_COLS; c++) {
            for (int i = 0; i < 4; i++) window[i] = board[r+i][c-i];
            score += score_window(window, player);
        }
    }
    return score;
}

int evaluate(){
    int val = evaluate_board();
    if (val != 0) return val;
    if (board_full()) return 0;
    return heuristic('Y') - heuristic('R');
}

int minimax(int depth, int alpha, int beta, int maximizing){
    int boardVal = evaluate_board();
    if (boardVal == 1000) return boardVal - depth;
    if (boardVal == -1000) return boardVal + depth;
    if (board_full() || depth == 0) return evaluate();
    if (maximizing) {
        int maxEval = INT_MIN;
        for (int c = 0; c < MAX_COLS; c++) {
            if (valid_move(c)) {
                make_move(c, 'Y');
                int eval = minimax(depth-1, alpha, beta, 0);
                undo_move(c);
                if (eval > maxEval) maxEval = eval;
                if (eval > alpha) alpha = eval;
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int c = 0; c < MAX_COLS; c++) {
            if (valid_move(c)) {
                make_move(c, 'R');
                int eval = minimax(depth-1, alpha, beta, 1);
                undo_move(c);
                if (eval < minEval) minEval = eval;
                if (eval < beta) beta = eval;
                if (beta <= alpha) break;
            }
        }
        return minEval;
    }
}

int best_move(char player){
    int bestCol =0;
    if(player=='Y'){
        int best_score = INT_MIN;
        for (int c = 0; c < 5; c++) {
            if (valid_move(c)) {
                make_move(c, player);
                int score = minimax(8, INT_MIN, INT_MAX, 0);
                undo_move(c);
                if (score > best_score) {
                    best_score = score;
                    bestCol = c;
                }
            }
        }
    }
    else{
        int best_score = INT_MAX;
        for(int c=0; c<5; c++){
            if (valid_move(c)) {
                make_move(c, player);
                int score = minimax(8, INT_MIN, INT_MAX, 1);
                undo_move(c);
                if (score < best_score) {
                    best_score = score;
                    bestCol = c;
                }
            }
        }
    }
    return bestCol;
}

int main(void){
    init_board();
    char computer;
    scanf("%c", &computer);
    char human = (computer == 'Y'  ? 'R' : 'Y');
    char turn = 'Y';

    while(1){
        if(check_win('Y')){
            printf("Y won\n");
            break;
        }
        if(check_win('R')){
            printf("R won\n");
            break;
        }
        if(board_full()){
            printf("draw\n");
            break;
        }

        if(turn == computer){
            int col = best_move(computer);
            make_move(col, computer);
            printf("%c %d\n", computer, col+1);
        }
        else{
            char color;
            int col;
            scanf(" %c %d", &color, &col);
            make_move(col-1,color);
        }
        turn = (turn == 'Y' ? 'R':'Y');
    }
}