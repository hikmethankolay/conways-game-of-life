#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

#define WIDTH 32
#define HEIGHT 32
int grid[HEIGHT][WIDTH];

void initialize_grid(int alive_cells[][2], int num_cells) {
    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < num_cells; i++) {
        int x = alive_cells[i][0];
        int y = alive_cells[i][1];
        
        if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
            grid[x][y] = 1;
        }
    }
}

void display_grid() {
    printf("\e[1;1H\e[2J");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf(grid[i][j] ? "#  " : "-- ");
        }
        printf("\n");
    }
}

int count_neighbors(int x, int y) {
    int count = 0;
    for(int i = -1; i<=1; i++){
        for(int j = -1; j<=1; j++){
            if (i == 0 && j == 0) continue;

            int nx = x+i;
            int ny = y+j;

            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                if (grid[nx][ny] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

void next_generation() {
    int temp_grid[HEIGHT][WIDTH];

    for (int i = 0; i<HEIGHT; i++) {
        for (int j = 0; j<WIDTH; j++) {
            int neighbors = count_neighbors(i, j);

            if (grid[i][j] == 1) {
                temp_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            }
            else {
                temp_grid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = temp_grid[i][j];
        }
    }
}


int main() {
int alive_cells[][2] = {
    {10, 12}, {10, 13}, {10, 14}, {10, 18}, {10, 19}, {10, 20},
    {12, 10}, {13, 10}, {14, 10}, {18, 10}, {19, 10}, {20, 10},
    {12, 15}, {13, 15}, {14, 15}, {18, 15}, {19, 15}, {20, 15},
    {15, 12}, {15, 13}, {15, 14}, {15, 18}, {15, 19}, {15, 20},
    {12, 17}, {13, 17}, {14, 17}, {18, 17}, {19, 17}, {20, 17},
    {17, 12}, {17, 13}, {17, 14}, {17, 18}, {17, 19}, {17, 20}
};

    int num_cells = sizeof(alive_cells) / sizeof(alive_cells[0]);
    
    initialize_grid(alive_cells, num_cells);
    while (1) {
        display_grid();
        next_generation();
        sleep_ms(2000); 
    }
    return 0;
}