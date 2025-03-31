// Chapter 6 Exercise 24 - Rock. Paper , Scissors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Programmer: Brenna Meyer 
// Date: March 30, 2025 
// Requirements: When the program begins, a random number in the range of 1 through 3 is generated. 
// If the number is 1, then the computer has chosen rock. If the number is 2, then the computer has chosen paper.
// If the number is 3, then the computer has chosen scissors. (Don’t display the computer’s choice yet.)
//The user enters his or her choice of “rock”, “paper”, or “scissors” at the keyboard. (You can use a menu if you prefer.)
//The computer’s choice is displayed.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//Varables 
const int rock = 1,
paper = 2,
scissors = 3;
const string SCORES_FILE = "rps_scores.txt";

//Compter Choice
int ComputerChoice()
{
    return (rand() % 3) + 1;
}

//Choice
int getValidChoice()
{
    int choice;
    while (true) {
        cout << "Choose (1) Rock, (2) Paper, or (3) Scissors: ";

        if (cin >> choice && choice >= 1 && choice <= 3) {
            cin.ignore(100, '\n');
            return choice;
        }

        cout << "Invalid input. Please enter 1, 2, or 3.\n";
        cin.clear(); // Clear error flags
        cin.ignore(100, '\n');
    }
}

//Choice and winner 
void displayChoice(int choice)
{
    switch (choice) {
    case rock:  cout << "Rock"; break;
    case paper:  cout << "Paper"; break;
    case  scissors: cout << "Scissors"; break;
    }
}

//Winner 
void determineWinner(int computer, int user, bool& playAgain, int& wins)
{
    if (computer == user) {
        cout << " Tie. Play again to determine the winner.\n";
        playAgain = true;
        return;
    }

    bool userWins =
        (user == rock && computer == scissors) ||
        (user == paper && computer == rock) ||
        (user == scissors && computer == paper);

    cout << "\n" << (userWins ? "You win" : "Computer wins") << ": ";

    if (user == rock && computer == scissors)
        cout << "Rock smashes scissors!";
    else if (user == paper && computer == rock)
        cout << "Paper covers rock!";
    else if (user == scissors && computer == paper)
        cout << "Scissors cut paper!";
    else if (computer == rock && user == scissors)
        cout << "Rock smashes scissors!";
    else if (computer == paper && user == rock)
        cout << "Paper covers rock!";
    else if (computer == scissors && user == paper)
        cout << "Scissors cut paper!";

    if (userWins) wins++;
    cout << "\n";
   playAgain = false;
}

void saveScore(string name, int score) {
    ofstream file(SCORES_FILE, ios::app);
    if (file) file << name << " " << score << endl;
}
void showScores() {
    ifstream file(SCORES_FILE);
    if (!file) {
        cout << "No scores yet.\n";
        return;
    }
    cout << "Previous Scores:\n";
    string name; int score;
    while (file >> name >> score)
        cout << name << ": " << score << " wins\n";
}

void deleteScores() {
    remove(SCORES_FILE.c_str());
    cout << "Scores cleared.\n";
}


//Main
int main() {
    srand(time(0));

    while (true) {
        cout << "\n1. View scores\n2. New game\n3. Clear scores\n4. Exit\nChoose: ";
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');

        if (choice == 1) showScores();
        else if (choice == 2) {
            // Your original game code with one addition
            string playerName;
            int wins = 0;
            bool playAgain;

            cout << "Enter your name:";
            cin >> playerName;
            cin.ignore();

            do {
                int computer = ComputerChoice();
                int user = getValidChoice();
                cout << "Computer chose: ";
                displayChoice(computer);
                determineWinner(computer, user, playAgain, wins);
            } while (playAgain);

            cout << "Game over. " << playerName << " won " << wins << " times.\n";
            saveScore(playerName, wins); // Added this line
        }
        else if (choice == 3) deleteScores();
        else if (choice == 4) break;
        else cout << "Invalid choice.\n";
    }

    return 0;
}