#include "../include/Game.h"

Game::Game() = default;

void Game::initGame() {
    gameBoard.reset();
    score = 0;
    moveCount = 0;
    historyGameBoards = std::stack<GameBoard>();
    historyScores = std::stack<int>();
    startTime = std::chrono::system_clock::now();
    historyGameBoards.push(gameBoard);  // Save initial state
    historyScores.push(score); //Save initial score
}

void Game::updateGame(Direction direction) {
    // Save current state to history
    // TODO 1


    // Get move score and update score
    // TODO 2

    int currentScore = gameBoard.move(direction);
    historyScores.push(currentScore);
    score += currentScore;

    // update move count
    // TODO 3

    historyGameBoards.push(gameBoard);
    moveCount++;

}

void Game::undoLastMove() {
    if (historyGameBoards.size() > 1) {
        // Remove current state
        // TODO 1

        historyGameBoards.pop();
        score -= historyScores.top();
        historyScores.pop();
        moveCount++;

        // Restore previous state
        // TODO 2

        gameBoard = historyGameBoards.top();

    } else {
        gameBoard.reset();
    }
}

bool Game::hasWon() const {
    return gameBoard.hasWinningTile();
}

bool Game::hasLost() const {
    return gameBoard.isGameOver();
}

double Game::getElapsedTime() const {
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

int Game::getScore() const {
    return score;
}

int Game::getMoveCount() const {
    return moveCount;
}

const GameBoard& Game::getGameBoard() const {
    return gameBoard;
}