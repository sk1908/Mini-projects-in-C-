#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

struct CardSet {
    int card1, card2, sum, extraCard;
};

void displayCard(int card1, int card2, int extraCard, int sum);
void displaySimpleCard(int card1, int card2, int sum);
bool continueGame(char choice, int funds);
int determineWinner(int bankerScore, int playerScore);
int calculatePayout(int result, int choice, int bet);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::string playerName;
    int betAmount, playerChoice, gameResult, prizeMoney;
    char replay;
    bool gameRunning = true;
    int funds = 10000;

    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    std::cout << "\nWelcome to the Baccarat Table, " << playerName << "!\n";

    while (gameRunning) {
        std::cout << "Balance: PHP " << funds << std::endl;
        std::cout << "Place your bet on:\n1 - Banker\n2 - Player\n";
        while (!(std::cin >> playerChoice) || playerChoice < 1 || playerChoice > 2) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid choice. Please choose 1 (Banker) or 2 (Player): ";
        }

        do {
            std::cout << "Enter bet amount (PHP): ";
            std::cin >> betAmount;
        } while (betAmount > funds);

        std::cout << "\nBanker's Turn:\n";
        CardSet banker = {rand() % 10 + 1, rand() % 10 + 1};
        banker.sum = (banker.card1 + banker.card2) % 10;

        if (banker.sum != 8 && banker.sum != 9) {
            banker.extraCard = rand() % 10 + 1;
            banker.sum = (banker.sum + banker.extraCard) % 10;
            displayCard(banker.card1, banker.card2, banker.extraCard, banker.sum);
        } else {
            displaySimpleCard(banker.card1, banker.card2, banker.sum);
        }

        std::cout << "\nPlayer's Turn:\n";
        CardSet player = {rand() % 10 + 1, rand() % 10 + 1};
        player.sum = (player.card1 + player.card2) % 10;

        if (player.sum != 8 && player.sum != 9) {
            player.extraCard = rand() % 10 + 1;
            player.sum = (player.sum + player.extraCard) % 10;
            displayCard(player.card1, player.card2, player.extraCard, player.sum);
        } else {
            displaySimpleCard(player.card1, player.card2, player.sum);
        }

        gameResult = determineWinner(banker.sum, player.sum);
        prizeMoney = calculatePayout(gameResult, playerChoice, betAmount);
        funds += prizeMoney;
        std::cout << "Current Balance: PHP " << funds << "\n";

        std::cout << "Play again? (Y/N): ";
        std::cin >> replay;
        gameRunning = continueGame(replay, funds);
    }

    return 0;
}

void displayCard(int card1, int card2, int extraCard, int sum) {
    std::cout << "===== Final Score: " << sum << " =====\n";
    std::cout << "Card 1: " << card1 << " | Card 2: " << card2 << " | Extra Card: " << extraCard << std::endl;
}

void displaySimpleCard(int card1, int card2, int sum) {
    std::cout << "===== Natural Score: " << sum << " =====\n";
    std::cout << "Card 1: " << card1 << " | Card 2: " << card2 << std::endl;
}

bool continueGame(char choice, int funds) {
    if (funds <= 0) {
        std::cout << "Insufficient funds. Game over.\n";
        return false;
    }

    return (choice == 'Y' || choice == 'y');
}

int determineWinner(int bankerScore, int playerScore) {
    std::cout << "\n======= Result =======\n";
    if (bankerScore > playerScore) {
        std::cout << "Banker Wins!\n";
        return 1;
    } else if (bankerScore < playerScore) {
        std::cout << "Player Wins!\n";
        return 2;
    } else {
        std::cout << "It's a Tie!\n";
        return 3;
    }
}

int calculatePayout(int result, int choice, int bet) {
    if (result == choice) {
        std::cout << "You Win! Prize: PHP " << bet << std::endl;
        return bet;
    } else if (result == 3) {
        std::cout << "It's a draw. No one wins or loses.\n";
        return 0;
    } else {
        std::cout << "You Lose! Loss: PHP " << bet << std::endl;
        return -bet;
    }
}
