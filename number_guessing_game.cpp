#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

int main() {
	// Initialize random seed
	srand(static_cast<unsigned int>(time(0)));

	// Generate random number between 1 and 100
	int randomNumber = rand() % 100 + 1;
	int guess;
	bool guessedCorrectly = false;

	cout << "I have generated a random number between 1 and 100." << endl;
	cout << "Can you guess what it is?" << endl;

	while (!guessedCorrectly) {
		cout << "Enter your guess: ";
		cin >> guess;

		if (guess > randomNumber) {
			cout << "Too high! Try again." << endl;
		} else if (guess < randomNumber) {
			cout << "Too low! Try again." << endl;
		} else {
			cout << "Congratulations! You guessed the correct number: " << randomNumber << endl;
			guessedCorrectly = true;
		}
	}

	return 0;
}
