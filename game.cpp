#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int BoardSize = 4;

// Represents a card on the board
struct Card {
    char symbol;
    bool faceUp;
};

// Function to initialize the game board
void initializeBoard(vector<vector<Card>>& board) {
    vector<char> symbols = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D' };
    random_shuffle(symbols.begin(), symbols.end());

    int index = 0;
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            board[i][j].symbol = symbols[index];
            board[i][j].faceUp = false;
            index++;
        }
    }
}

// Function to display the game board
void displayBoard(const vector<vector<Card>>& board) {
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if (board[i][j].faceUp) {
                cout << board[i][j].symbol << " ";
            } else {
                cout << "* ";
            }
        }
        cout << endl;
    }
}

// Function to check if the game is won
bool isGameWon(const vector<vector<Card>>& board) {
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if (!board[i][j].faceUp) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<Card>> board(BoardSize, vector<Card>(BoardSize));
    initializeBoard(board);

    int attempts = 0;

    cout << "Memory Game (Match pairs of letters A, B, C, D)" << endl;

    while (true) {
        displayBoard(board);

        int firstCardX, firstCardY, secondCardX, secondCardY;
        cout << "Enter the positions of two cards (e.g., 0 1 2 3): ";
        cin >> firstCardX >> firstCardY >> secondCardX >> secondCardY;

        if (firstCardX < 0 || firstCardX >= BoardSize || firstCardY < 0 || firstCardY >= BoardSize ||
            secondCardX < 0 || secondCardX >= BoardSize || secondCardY < 0 || secondCardY >= BoardSize ||
            (firstCardX == secondCardX && firstCardY == secondCardY) ||
            board[firstCardX][firstCardY].faceUp || board[secondCardX][secondCardY].faceUp) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        board[firstCardX][firstCardY].faceUp = true;
        board[secondCardX][secondCardY].faceUp = true;
        attempts++;

        if (board[firstCardX][firstCardY].symbol != board[secondCardX][secondCardY].symbol) {
            // If the cards don't match, flip them back after a short delay (simulate delay)
            displayBoard(board);
            cout << "No match. Try again." << endl;
            board[firstCardX][firstCardY].faceUp = false;
            board[secondCardX][secondCardY].faceUp = false;
        }

        if (isGameWon(board)) {
            displayBoard(board);
            cout << "Congratulations! You won in " << attempts << " attempts." << endl;
            break;
        }
    }

    cout << "Game over! Thank you for playing." << endl;

    return 0;
}