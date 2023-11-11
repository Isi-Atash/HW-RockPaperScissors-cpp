#include <iostream>
#include <omp.h>
#include <random>
#include <chrono>
#include <fstream>

// Enumeration for the possible moves in the game
enum Move
{
    ROCK,
    PAPER,
    SCISSORS
};

// Function to convert enum Move to its string representation
const char *moveToString(Move move)
{
    switch (move)
    {
    case ROCK:
        return "Rock";
    case PAPER:
        return "Paper";
    case SCISSORS:
        return "Scissors";
    default:
        return "Unknown";
    }
}

// Function to generate a random move for a player
Move randomMove()
{
    // Thread-local random number generator to avoid conflicts in parallel execution
    static thread_local std::mt19937 generator(omp_get_thread_num());
    std::uniform_int_distribution<int> distribution(0, 2);
    return static_cast<Move>(distribution(generator));
}

// Function to determine the result of a game based on the moves of the players
int gameResult(Move a, Move b, Move c)
{
    int score[3] = {0, 0, 0};

    // Scoring logic based on the rules of Rock-Paper-Scissors
    // Determine the score for each player
    if (a == ROCK && b == SCISSORS)
        score[0]++;
    if (a == ROCK && c == SCISSORS)
        score[0]++;
    if (b == ROCK && a == SCISSORS)
        score[1]++;
    if (b == ROCK && c == SCISSORS)
        score[1]++;
    if (c == ROCK && a == SCISSORS)
        score[2]++;
    if (c == ROCK && b == SCISSORS)
        score[2]++;

    if (a == SCISSORS && b == PAPER)
        score[0]++;
    if (a == SCISSORS && c == PAPER)
        score[0]++;
    if (b == SCISSORS && a == PAPER)
        score[1]++;
    if (b == SCISSORS && c == PAPER)
        score[1]++;
    if (c == SCISSORS && a == PAPER)
        score[2]++;
    if (c == SCISSORS && b == PAPER)
        score[2]++;

    if (a == PAPER && b == ROCK)
        score[0]++;
    if (a == PAPER && c == ROCK)
        score[0]++;
    if (b == PAPER && a == ROCK)
        score[1]++;
    if (b == PAPER && c == ROCK)
        score[1]++;
    if (c == PAPER && a == ROCK)
        score[2]++;
    if (c == PAPER && b == ROCK)
        score[2]++;

    // Return the total score for this game
    return score[0] + score[1] + score[2];
}

int main()
{
    // Open a file to write the benchmark results
    std::ofstream file("benchmark_results.txt");

    // Define different problem sizes for the benchmark
    const int problemSizes[] = {1, 10, 100, 1000, 5000, 10000, 50000, 100000};
    const int numSizes = sizeof(problemSizes) / sizeof(problemSizes[0]);

    for (int s = 0; s < numSizes; ++s)
    {
        int numGames = problemSizes[s];
        int totalScore = 0;

        // Start measuring time for benchmark
        auto start = std::chrono::high_resolution_clock::now();

        // Parallel for loop to simulate multiple games
#pragma omp parallel for reduction(+ : totalScore)
        for (int i = 0; i < numGames; ++i)
        {
            // Simulate moves for three players
            Move player1 = randomMove();
            Move player2 = randomMove();
            Move player3 = randomMove();

            // Calculate and accumulate game score
            int gameScore = gameResult(player1, player2, player3);
            totalScore += gameScore;

            // Critical section to ensure proper console output
#pragma omp critical
            {
                std::cout << "Game " << i + 1 << ": "
                          << moveToString(player1) << ", "
                          << moveToString(player2) << ", "
                          << moveToString(player3)
                          << " | Game Score: " << gameScore << std::endl;
            }
        }

        // Stop measuring time after simulations
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // Output and write the benchmark results
        std::cout << "Problem Size: " << numGames << ", Execution Time: " << duration.count() << " milliseconds" << std::endl;
        file << "Problem Size: " << numGames << ", Execution Time: " << duration.count() << " milliseconds\n";
    }

    // Close the file after writing all benchmark results
    file.close();
    return 0;
}
