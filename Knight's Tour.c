#include <stdio.h>

int n, m, r, c;
int board[8][8];

int kx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int ky[8] = {1, -1, 1, -1, 2, -2, 2, -2};

int is_valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == -1);
}

int countt(int x, int y) {
    int count = 0;
    for (int i = 0; i<8; i++) {
        int nx = x + kx[i], ny = y + ky[i];
        if (is_valid(nx, ny)) count++;
    }
    return count;
}

int solve(int x, int y, int movei) {
    if (movei > n*m) {
        for (int i = 0; i<8; i++) {
            int nx = x + kx[i];
            int ny = y + ky[i];
            if (nx == r && ny == c) return 1;
        }
        return 0;
    }

    int min_deg = 9;
    int cand_x[8], cand_y[8], cand_cnt = 0;

    for (int i = 0; i < 8; i++) {
        int nx = x + kx[i], ny = y + ky[i];
        
        if (is_valid(nx, ny)) {
            int deg = countt(nx, ny);
            
            if (deg<min_deg) {
                min_deg = deg;
                cand_cnt = 0;
                cand_x[cand_cnt] = nx;
                cand_y[cand_cnt] = ny;
                cand_cnt++;
            } else if (deg == min_deg) {
                cand_x[cand_cnt] = nx;
                cand_y[cand_cnt] = ny;
                cand_cnt++;
            }
        }
    }

    for (int i = 0; i<cand_cnt; i++) {
        int nx = cand_x[i], ny = cand_y[i];
        board[nx][ny] = movei;
        if (solve(nx, ny, movei + 1)) return 1;
        board[nx][ny] = -1;
    }
    return 0;
}

int main(void) {
    scanf("%d %d %d %d", &n, &m, &r, &c);

    for (int i = 0; i<n; i++)
        for (int j = 0; j < m; j++)
            board[i][j] = -1;

    int x = r, y = c;
    board[x][y] = 1;

    if (solve(r, c, 2)) {
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                printf("%2d ", board[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("-1");
    }

}