# Rock Scissors paper game

## The problem description

Write a parallel program to simulate a three-person rock/scissors/paper game. Each player randomly chooses one of rock, scissors, or paper. Then the players compare their choices to see who \won". Rock smashes scissors, scissors cut paper, and paper covers rock. Award a player 2 points if it beats both the others; award two players 1 point each if they both beat the third; otherwise award no points. Then the players play another game.

Use one thread/process for each player. The players must interact directly with each other. Do not use an additional coordinator thread. Print a trace of the results of each game as the program executes. At the end print the total points won by each player (the output should be just three numbers separated by a space, corresponding to the points won by each player). Read the number of games as a command line argument.

## Prerequisites

A C++ compiler with **OpenMP** support (e.g., GCC)

An environment that supports **OpenMP** (Linux, macOS, Windows)

## Compilation

To compile the program, use the following command in the terminal:

```bash
g++ -fopenmp -o rps_game rps_game.cpp
```

This command will create an executable named rps_game.

## Running the Program

Run the program by executing the generated binary:

```bash
./rps_game
```

Upon running, the program will automatically perform simulations for predefined problem sizes and output the execution time for each. The results will be printed to the console and also written to a file named benchmark_results.txt.

## Program Structure

### Main Components

- *enum Move*: Defines the possible moves (Rock, Paper, Scissors).
- *moveToString(Move)*: Converts a move to its string representation.
- *randomMove()*: Generates a random move for a player.
- *gameResult(Move, Move, Move)*: Calculates the score of a game based on players' moves.
- *main()*: The entry point of the program, handling the simulation loop and benchmarking.

### Parallel Execution

The program utilizes OpenMP to parallelize the game simulations.
The #pragma omp parallel for directive is used to distribute the execution of games across multiple threads.

## Benchmarking

The program measures the execution time for simulating a varying number of games to assess the performance of the parallel implementation.
Results are printed to the console and written to benchmark_results.txt.

- Problem Size: 1, Execution Time: 1.2069 milliseconds
- Problem Size: 10, Execution Time: 2.7545 milliseconds
- Problem Size: 100, Execution Time: 22.498 milliseconds
- Problem Size: 1000, Execution Time: 226.647 milliseconds
- Problem Size: 5000, Execution Time: 1151.58 milliseconds
- Problem Size: 10000, Execution Time: 2337.94 milliseconds
- Problem Size: 50000, Execution Time: 11542.7 milliseconds
- Problem Size: 100000, Execution Time: 23165.9 milliseconds

## Output

The program outputs the results of each game, including players' moves and the game score.
It also prints the total execution time for each problem size.
