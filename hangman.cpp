#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Man {
    private:
        bool alive = true;
        int limbCount = 0;
        char currentMan[6] = {' ',' ',' ',' ',' ',' '};
        char completeMan[6] = {'O','|','-','-','/','\\'};

        void updateStatus() {
            // update the status of the man based on the limb count
            if (limbCount > 5) {
                alive = false;
            }
        }

    public:
        void hang() {
            // updates the array that displays the man, and increments limb count
            currentMan[limbCount] = completeMan[limbCount];
            limbCount++;
        }

        void draw() {
            // draw the man and the hanging post
            cout << "     ___\n";
            cout << "    |   |\n";
            cout << "    " << currentMan[0] << "   |\n";
            cout << "   " << currentMan[2] << currentMan[1] << currentMan[3] << "  |\n";
            cout << "   " << currentMan[4] << " " << currentMan[5] << "  |\n";
            cout << "        |\n";
            cout << "   _____|_____\n";
        }

        bool isAlive() {
            // return the status of the man
            updateStatus();
            return alive;
        }
};

class SecretWord {
    private:
        string secretWord;
        string displayWord;
        bool wordIsGuessed = false;
        string wordList[15] = {"elephant","chocolate","guitar","dinosaur","astronaut",
                                "pyramid","bicycle","dragonfly","whisper","volcano",
                                "mermaid","rainbow","treasure","blizzard","unicorn"};

        bool checkIfWordIsGuessed() {
            // returns true if the secret word has been fully guessed
            for(int i = 0; i < secretWord.length(); i++) {
                if (displayWord[i] == '_') {
                    return false;
                }
            }
            return true;
        }

    public:
        SecretWord() {
            // set secretWord to a random word in wordList
            srand(time(0));
            int randomIndex = rand() % 15;
            secretWord = wordList[randomIndex];

            // initiate the display word with underscores
            displayWord = secretWord;
            for(int i = 0; i < secretWord.length(); i++) {
                displayWord[i] = '_';
            }
        }

        void displayHint() {
            cout << displayWord << "\n";
        }

        bool inputNewGuess(string guess) {
            // returns true if the guess was in the secret word and updates the display word
            bool rValue = false;
            // check if they entered one letter or a word as their guess
            if (guess.length() == 1) { // they entered one letter
                // check if secret word contains the guess
                for(int i = 0; i < secretWord.length(); i++) {
                    if (secretWord[i] == guess[0]) {
                        rValue = true;
                        // update the display word
                        displayWord[i] = secretWord[i];
                    }
                }
            }
            else { // they entered a word
                // check if they guessed correctly
                if (secretWord == guess) {
                    rValue = true;
                    // update the display word
                    displayWord = secretWord;
                }
            }
            return rValue;
        }

        bool wordGuessed() {
            wordIsGuessed = checkIfWordIsGuessed();
            return wordIsGuessed;
        }

        string getSecretWord() {
            return secretWord;
        }
};

class Guesses {
    private:
        int numberOfGuesses = 0;
    public:
        string incorrectGuesses[6];

        void addIncorrectGuess(string guess) {
            // add a guess to the guesses list
            // make sure the index is in range
            if (numberOfGuesses < 6) {
                incorrectGuesses[numberOfGuesses] = guess;
                numberOfGuesses++;
            }
        }

        void displayGuesses() {
            for(string guess : incorrectGuesses) {
                cout << guess << "\n";
            }
        }
};

int main() {
    string input;
    // this while loop allows for multiple games to be played in a row
    while (true) {
        // this while loop is the main game loop
        bool run = true;
        SecretWord secretWord;
        Man man;
        Guesses guesses;
        while (run) {
            //display the hang man image, previous guesses, and the secret word hint
            man.draw();
            cout << "Previous guesses: \n";
            guesses.displayGuesses();
            secretWord.displayHint();

            // prompt the user to guess a letter or word
            cout << "What is your guess: ";
            cin >> input;

            // input the user guess into secret word and hang the man if the guess is wrong
            if(!secretWord.inputNewGuess(input)) {
                //incorrect guess
                man.hang();
                guesses.addIncorrectGuess(input);
            }

            // Congradulate the user if they guess the word
            if(secretWord.wordGuessed()) {
                man.draw();
                cout << "Previous guesses: \n";
                guesses.displayGuesses();
                secretWord.displayHint();
                cout << "Nice job! You guessed it!! \n";
                run = false;
            }

            // Shame the user if they failed to guess the word in time
            if(!man.isAlive()) {
                man.draw();
                cout << "Previous guesses: \n";
                guesses.displayGuesses();
                secretWord.displayHint();                
                cout << "Game over \n";
                cout << "The word was " + secretWord.getSecretWord() + " \n";
                run = false;
            }
        }

        // check if the user would like to play again
        cout << "Would you like to play again? (y/n): ";
        cin >> input;
        if (input == "n") {
            cout << "Thanks for playing!\n";
            break;
        }
    }
}