#include <iostream>
#include <omp.h>
#include <random>

enum Move
{
    ROCK,
    PAPER,
    SCISSORS
};

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

Move randomMove()
{
    static thread_local std::mt19937 generator(omp_get_thread_num());
    std::uniform_int_distribution<int> distribution(0, 2);
    return static_cast<Move>(distribution(generator));
}

int gameResult(Move a, Move b, Move c)
{
    int score[3] = {0, 0, 0};

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
    int numGames;
    std::cout << "Enter the number of games: ";
    std::cin >> numGames;

    int totalScore = 0;

#pragma omp parallel for reduction(+ : totalScore)
    for (int i = 0; i < numGames; ++i)
    {
        Move player1 = randomMove();
        Move player2 = randomMove();
        Move player3 = randomMove();

        int gameScore = gameResult(player1, player2, player3);
        totalScore += gameScore;

#pragma omp critical
        {
            std::cout << "Game " << i + 1 << ": "
                      << moveToString(player1) << ", "
                      << moveToString(player2) << ", "
                      << moveToString(player3)
                      << " | Game Score: " << gameScore << std::endl;
        }
    }

    std::cout << "Total Score: " << totalScore << std::endl;
    return 0;
}
