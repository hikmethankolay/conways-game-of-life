#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms) ///< Macro to define sleep function in milliseconds for Windows.
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000) ///< Macro to define sleep function in milliseconds for Unix-based systems.
#endif

#define WIDTH 32    ///< Width of the grid.
#define HEIGHT 32   ///< Height of the grid.
#define MAX_CELLS WIDTH*HEIGHT
int grid[HEIGHT][WIDTH]; ///< 2D array representing the grid where each cell is either alive or dead.

/**
 * @brief Initializes the grid with specified alive cells.
 *
 * This function sets all cells in the grid to dead (0), and then sets specific cells to alive (1)
 * based on the coordinates provided in the `alive_cells` array.
 *
 * @param alive_cells Array of coordinates where each cell contains [x, y] positions of alive cells.
 * @param num_cells Number of alive cells in the initial configuration.
 */
void initialize_grid(int alive_cells[][2], int num_cells) {
    memset(grid, 0, sizeof(grid)); // Set all cells to dead (0)

    for (int i = 0; i < num_cells; i++) {
        int x = alive_cells[i][0];
        int y = alive_cells[i][1];
        
        if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
            grid[x][y] = 1; // Set specific cells to alive (1)
        }
    }
}

/**
 * @brief Displays the current state of the grid in the terminal.
 *
 * This function clears the terminal screen and prints the current state of the grid.
 * Alive cells are represented by "#" and dead cells by "--".
 */
void display_grid() {
    printf("\e[1;1H\e[2J"); // Clear the terminal screen

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf(grid[i][j] ? "#  " : "-- ");
        }
        printf("\n");
    }
}

/**
 * @brief Counts the number of alive neighbors around a given cell.
 *
 * This function checks the eight surrounding cells and counts how many of them are alive.
 *
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return The count of alive neighbors.
 */
int count_neighbors(int x, int y) {
    int count = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;

            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                if (grid[nx][ny] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 * @brief Computes the next generation of the grid.
 *
 * This function calculates the next generation based on the current state of each cell and its neighbors.
 * The new state is stored temporarily, then copied back to the main grid.
 */
void next_generation() {
    int temp_grid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
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

/**
 * @brief Takes user input to specify initial positions of alive cells.
 *
 * This function prompts the user to enter coordinates of cells they want to initialize as alive.
 * The user can stop entering coordinates by inputting a negative number for x or y.
 *
 * @param alive_cells Array to store the coordinates of alive cells entered by the user.
 * @param num_cells Pointer to an integer where the count of alive cells will be stored.
 */
void take_user_input_for_live_cells(int alive_cells[][2], int* num_cells){
    *num_cells = 0;
    int x, y;

    printf("Enter the coordinates for alive cells (x y). Enter -1 -1 to finish:\n");
    while (*num_cells < MAX_CELLS) {
        printf("Cell %d: ",*num_cells +1);
        scanf("%d %d", &x, &y);

        if (x == -1 || y == -1) break;

        if(x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH){
            alive_cells[*num_cells][0] = x;
            alive_cells[*num_cells][1] = y;
            (*num_cells)++;
        }else {
            printf("Invalid coordinates. Please enter values between 0 and %d for x and 0 and %d for y.\n", HEIGHT - 1, WIDTH - 1);
        }
    }
}

/**
 * @brief Main function that initializes the grid and starts the simulation loop.
 *
 * This function defines the initial positions of alive cells, initializes the grid, 
 * and enters an infinite loop to continuously update and display the grid at each generation.
 *
 * @return int Always returns 0.
 */
int main() {

    int alive_cells[MAX_CELLS][2];
    int num_cells;
    
    take_user_input_for_live_cells(alive_cells, &num_cells);

    initialize_grid(alive_cells, num_cells);
    while (1) {
        display_grid();
        next_generation();
        sleep_ms(150);
    }
    return 0;
}
