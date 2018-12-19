#include <iostream>
#include <ctime>
using namespace std;

void display(char[]);
void aiMain(char[], bool&);
bool connectThree(char[], char);

int main()
{
	int lossCount = 0,
		tieCount = 0;
	bool gameOver = false;
	srand((unsigned)time(0));
	char marks[11], // the Xs and Os
		choice;

	// initialize marks with spaces. marks[0] is not used so that the element number coincides with the input
	for (int i = 1; i < 10; i++)
		marks[i] = ' ';

	cout << "\n Tic-Tac-Toe!\n\n Use your number pad to choose a space. \n\n    |   |\n "
		" 7 | 8 | 9\n -----------\n    |   |\n  4 | 5 | 6\n    |   |\n -----------\n  1 | 2 | 3\n    |   |\n";
	display(marks);

	while (true) // each iteration of this loop is one round of the game
	{
		cout << "       Player's turn";

		do
		{
			cout << "\n> ";
			cin >> choice;
		} while (marks[choice - '0'] != ' ' || choice == '0');

		marks[choice - '0'] = 'X'; // the player is always X and always goes first
		display(marks);

		// check whether the game is over
		if (marks[1] + marks[2] + marks[3] + marks[4] + marks[5] + marks[6] + marks[7] + marks[8] + marks[9] == 5 * 'X' + 4 * 'O')
		{
			cout << "\n\n Tie game!";
			gameOver = true;
			tieCount++;
		}
		else
		{
			cout << "       Computer's turn ";
			aiMain(marks, gameOver);
			display(marks);

			if (gameOver)
			{
				cout << "\n\n The computer has won!";
				lossCount++;
			}
		}

		if (gameOver)
		{
			cout << "\n\n\n Your wins: 0 \n Your losses: " << lossCount << "\n Ties: " << tieCount << "\n\n\n Play again? (1/0) ";
			// winCount variable not needed as the player cannot win

			do
			{
				cout << "\n> ";
				cin >> choice;
				if (choice == '0')
					return 0;
			} while (choice != '1');

			// reset and start a new game
			for (int i = 1; i < 10; i++)
				marks[i] = ' ';
			gameOver = false;
			display(marks);
		}
	}
}

void display(char marks[])
{
	cout << "\n\n\n    |   |\n  " << marks[7] << " | " << marks[8] << " | " << marks[9]
		<< "\n -----------\n    |   |\n  " << marks[4] << " | " << marks[5] << " | " << marks[6]
		<< "\n    |   |\n -----------\n  " << marks[1] << " | " << marks[2] << " | " << marks[3] << "\n    |   |";
}

void aiMain(char marks[], bool& gameOver)
{
	int p;

	// the middle is the best space
	if (marks[5] == ' ')
		marks[5] = 'O';

	// look for a way to win on this turn
	else if (connectThree(marks, 'O'))
		gameOver = true;

	// block the player if there are 2 Xs in a row
	else if (connectThree(marks, 'X'));

	/* prevent a "triangle trap" on the AI's second turn
	O4 |	| X3	O4 |	|       O4 |	| X3
	------------	------------	------------	  <-- examples in which the trap was not prevented
	   | O2 |          | O2 | X3	   | O2 |			  (numbers show the order of turns taken)
	------------	------------	------------
	X1 |	| X5	   | X1 | X5	   | X1	| X5		*/

	else if (marks[2] + marks[8] != 2 * 'X' && marks[4] + marks[6] != 2 * 'X' &&
		marks[1] + marks[2] + marks[3] + marks[4] + marks[6] + marks[7] + marks[8] + marks[9] == 6 * ' ' + 2 * 'X')
	{
		if (marks[1] + marks[9] == 2 * 'X' || marks[3] + marks[7] == 2 * 'X')
			marks[2 * (1 + rand() % 4)] = 'O';
		else if (marks[2] + marks[4] == 2 * 'X' || marks[3] + marks[4] == 2 * 'X' || marks[2] + marks[7] == 2 * 'X')
			marks[1] = 'O';
		else if (marks[2] + marks[6] == 2 * 'X' || marks[2] + marks[9] == 2 * 'X' || marks[1] + marks[6] == 2 * 'X')
			marks[3] = 'O';
		else if (marks[4] + marks[8] == 2 * 'X' || marks[4] + marks[9] == 2 * 'X' || marks[1] + marks[8] == 2 * 'X')
			marks[7] = 'O';
		else
			marks[9] = 'O';
	}

	// choose a random corner if there's nothing else to do
	else if (marks[1] + marks[3] + marks[7] + marks[9] < 4 * 'O')
	{
		do
		{
			p = 1 + rand() % 4;

			if (p % 2 == 0)
				p += 5;
		} while (marks[p] != ' ');

		marks[p] = 'O';
	}

	// choose a random edge space if there's still nothing else to do
	else
	{
		do
		{
			p = 2 * (1 + rand() % 4);
		} while (marks[p] != ' ');

		marks[p] = 'O';
	}
}

bool connectThree(char marks[], char letter)
{
	// the sequence array holds every possible combination of 3 elements that form a line
	int sequence[] = { 1, 2, 3,  4, 5, 6,  7, 8, 9,  1, 4, 7,  2, 5, 8,  3, 6, 9,  1, 5, 9,  3, 5, 7,
                       2, 3, 1,  5, 6, 4,  8, 9, 7,  4, 7, 1,  5, 8, 2,  6, 9, 3,  5, 9, 1,  5, 7, 3,
                       3, 1, 2,  6, 4, 5,  9, 7, 8,  7, 1, 4,  8, 2, 5,  9, 3, 6,  9, 1, 5,  7, 3, 5 };

	for (int i = 0; i < 70; i += 3)
	{
		if (marks[sequence[i]] + marks[sequence[i + 1]] == 2 * letter && marks[sequence[i + 2]] == ' ')
		{
			marks[sequence[i + 2]] = 'O';
			return true;
		}
	}

	return false;
}
