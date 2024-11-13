
# Conway's Game of Life

Welcome to the **Conway's Game of Life** repository! This project implements the classic cellular automaton devised by mathematician John Conway. The Game of Life is a zero-player game where cells on a grid live, die, or evolve based on a set of rules.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Cleaning Up](#cleaning-up)
- [Rules of the Game](#rules-of-the-game)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Description

This implementation of Conway's Game of Life is written in C. It simulates an evolving grid of cells where each cell's next state depends on its neighboring cells. The project is designed to help users learn about cellular automata, C programming, and simple game simulations.

## Features
- Simulates Conway's Game of Life with an interactive console-based grid.
- Provides a Makefile for easy compilation and cleanup.
  
## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/hikmethankolay/conways-game-of-life.git
   ```
2. Navigate to the project directory:
   ```bash
   cd conways-game-of-life
   ```

## Prerequisites
- **C Compiler**: Make sure you have `gcc` or another C compiler installed.
- **Make**: Required to use the Makefile for compiling.
- 
### Building the Project

To build the project, simply use the following command in the terminal:
```bash
make
```
## Usage

Run the program with the following command:
```bash
./conways_game_of_life
```

You can modify the initial conditions and grid size within the `main.c` file to experiment with different patterns.

## Cleaning Up
To remove all compiled files and the executable, use:
```bash
make clean
```

## Rules of the Game

1. **Birth**: A dead cell with exactly 3 live neighbors becomes a live cell.
2. **Survival**: A live cell with 2 or 3 live neighbors stays alive.
3. **Death**: A live cell with fewer than 2 or more than 3 live neighbors dies.

These simple rules create complex and beautiful patterns over time, illustrating concepts of emergence and self-organization.

## Examples

- **Still Lifes**: Patterns that do not change from one generation to the next.
- **Oscillators**: Patterns that repeat after a fixed number of generations.
- **Spaceships**: Patterns that translate across the grid over time.

Modify the initial pattern in the code to explore these configurations.

## Contributing

Contributions are welcome! Please submit a pull request or open an issue if you have suggestions for improvements.

## License

This project is licensed under the MIT License.
