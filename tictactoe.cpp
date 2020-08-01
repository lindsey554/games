#include <iostream> 
using namespace std;

//declare and initialize an array of characters to represent the board
char board[10] = {'1','2','3','4','5','6','7','8','9'};

//declare and initialize the move number 
int move = 1; 

//declare some functions
void makemove();
int gamestate(); 
void displayboard(); 

int main()
{
	int i = 0;

	//while i=0, i.e. the game isn't done
	//display the board, make a move, and then udate the gamestate
	do
	{
		displayboard();
		makemove();
		i=gamestate();
		move++;
	}while(i==0);

	//once i=/=0, i.e. the game is done, 
	//display the board again and print a message
	displayboard();

	if(i==1)
	{
		if(move % 2 == 1)
			cout << "Game over! Player 2 wins.\n";
		else
			cout << "Game over! Player 1 wins.\n";
	}else
		cout << "Game over! It's a draw.\n";
	
	return 0;
}

//this function asks for moves and then 
//changes the boards values to Xs and Os
void makemove()
{
	int choice; 
	if(move % 2 == 1)
		cout << "Player 1: Enter a number: ";
	else
		cout << "Player 2: Enter a number: ";
	cin >> choice;
	if(choice == (int)board[choice - 1] - 48)
	{
		if(move % 2 == 0)
			board[choice - 1] = 'O';
		else
			board[choice - 1] = 'X';
	}
	else
	{
		cout << "invalid\n";
		move--;
	}
}

//this function determines whether the game is 
//finished with a winner (1), finished with a draw (-1), or not done (0)
int gamestate()
{
	if(board[0] == board[1] && board[1] == board[2])
		return 1; 
	if(board[3] == board[4] && board[4] == board[5])
		return 1;
	if(board[6] == board[7] && board[7] == board[8])
		return 1;
	if(board[0] == board[3] && board[3] == board[6])
		return 1;
	if(board[1] == board[4] && board[4] == board[7])
		return 1;
	if(board[2] == board[5] && board[5] == board[8])
		return 1;
	if(board[0] == board[4] && board[4] == board[8])
		return 1;
	if(board[6] == board[4] && board[4] == board[2])
		return 1; 
	else if(board[0] != '1' && board[1] != '2' && board[2] != '3' && board[3] != '4' && board[4] != '5' && board[5] != '6' && board[6] != '7' && board[7] != '8' && board[8] != '9')
		return -1; 
	else 
		return 0;
}

//this function displays the current board
void displayboard()
{
	cout << "     |     |     \n";
	cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  \n";
	cout << "_____|_____|_____\n";
	cout << "     |     |     \n";
	cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  \n";
	cout << "_____|_____|_____\n";
	cout << "     |     |     \n";
	cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  \n";
	cout << "     |     |     \n\n";
}
