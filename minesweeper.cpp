#include <iostream> 
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>  
using namespace std;

struct square{
	bool isselected; 
	bool isamine;
	bool isdefused; 
	int adjacentmines; 
};

const int Rows = 8; 
const int Cols = 10; 
const int Mines = 10; 

//declare an array of squares to represent the board
square board[Rows+1][Cols+1];

//declare some functions
void SetUpBoard();
void PlaceMine();
void GetMove(int *x, int *y, char *z);
void MakeMove();
int GameState(); 
void DisplayBoard(); 
void ClearArea(int &x, int &y);
bool IsValid(int x, int y);

int main()
{
	int i = 0; 
	SetUpBoard();

	//while i=0, i.e. the game isn't done
	//display the board, make a move, and then udate the gamestate
	do{ 
		DisplayBoard();
		MakeMove();
		i=GameState();
	}while(i==0);
	
	//once i=/=0, i.e. the game is done, 
	//display the board again and print a message
	DisplayBoard();
	if(i==1)
		cout << "You lose!\n";
	else
		cout << "You win!\n";
	
	return 0;
}

//places mines
bool IsValid(int x, int y)
{
	if(x > -1 && x < Rows && y > -1 && y < Cols){
		return true;
	}else{
		return false; 	
	}
}

//places a single mine on a random square 
//which doesnt yet have a mine
void PlaceMine()
{
	int row = rand() % Rows;
	int col = rand() % Cols;
	if(board[row][col].isamine == true){
		PlaceMine();
	}else{
		cout << "mine at " << row << " " << col << "\n"; 
		board[row][col].isamine = true;
	}
}

//initializes the board, places mines, and computes adjacencies
void SetUpBoard()
{
	//initializes board values
	for(int i = 0; i < Rows; ++i){
    	for(int j = 0; j < Cols; ++j){    
			board[i][j].isselected = false; 
			board[i][j].isamine = false;
			board[i][j].isdefused = false;
			board[i][j].adjacentmines = 0;
		}
	}
	
	// places Mine number of mines randomly
	srand (time(NULL));	
	for(int i = 0; i < Mines; ++i){
		PlaceMine();
	}
	
	// computes how many mines adjacent to each square
	for(int row = 0; row < Rows; ++row)
    	for(int col = 0; col < Cols; ++col){    
			if(board[row][col].isamine == true){
				for(int i = row - 1; i < row + 2; ++i){
					for(int j = col - 1; j < col + 2; ++j){
						if(IsValid(i,j)){
							board[i][j].adjacentmines++; 
						}
					}
				}
			}
		}
}

// clears the squares around a square with no adjacent mines
// continues recursively
void ClearArea(int &x, int &y)
{
	if(board[x][y].adjacentmines == 0){
		for(int i = x - 1; i < x + 2; ++i){
			for(int j = y - 1; j < y + 2; ++j){
				if(IsValid(i,j) && board[i][j].isselected == false){
					board[i][j].isselected = true;
					ClearArea(i,j);
				}
			}
		}
	}
}

// gets a move from the user and checks that it's valid
void GetMove(int *x, int *y, char *z) 
{ 
	string valid_options1("0123456789");
   string valid_options2("YyNn");
	string rowchoice, columnchoice; 
	string mines;

	cout << "Enter a row number: ";
	cin >> rowchoice;
	while (rowchoice.size() != 1 || valid_options1.find(rowchoice) == string::npos){
		 cout << "Input invalid. Enter a row number: ";
		 cin >> rowchoice;
	}
	*x = (int)rowchoice[0] - 48;
	
	cout << "Enter a column number: ";
	cin >> columnchoice;
	while (columnchoice.size() != 1 || valid_options1.find(columnchoice) == string::npos){
		 cout << "Input invalid. Enter a row number: ";
		 cin >> columnchoice;
	}	
	*y = (int)columnchoice[0] - 48;
	
	cout << "Is this a mine?: ";
	cin >> mines;
	while (mines.size() != 1 || valid_options2.find(mines) == string::npos){
		 cout << "Input invalid. Enter a row number: ";
		 cin >> mines;
	}
	*z = mines[0];

}

// asks for moves and then clears space accordingly
void MakeMove()
{
	int rowchoice, columnchoice; 
	char mine; 
	GetMove(&rowchoice,&columnchoice,&mine);
	
	board[rowchoice][columnchoice].isselected = true; 
	if(mine == 'Y' || mine == 'y'){
		board[rowchoice][columnchoice].isdefused = true; 
	}else{
		board[rowchoice][columnchoice].isdefused = false; 
		ClearArea(rowchoice, columnchoice); 
	}

}

//determines whether the game is lost (1), won (-1), or unfinished (0)
int GameState()
{
	for(int row = 0; row < Rows; ++row)
    {
		for(int col = 0; col < Cols; ++col)
		{    
			//if any mine is selected but not defused, game over
			//if a non-mine
			if(board[row][col].isselected == true && board[row][col].isamine == true && board[row][col].isdefused == false){
				return 1;
			}else if(board[row][col].isamine == false){
				if(board[row][col].isselected == false || board[row][col].isdefused == true){
					return 0; 
				}
			}
		}
	}
	
	//otherwise, the game has been won
	return -1; 
}

// displays the current board
void DisplayBoard()
{	
	cout << "\n     ";
	for(int col = 0; col < Cols - 1; ++col){
		cout << "   " << col << "  ";
	}
	cout << "   " << Cols - 1 << "  \n      ";
	for(int col = 0; col < Cols - 1; ++col){
		cout << "______";
	}
	cout << "_____ \n";
	
	for(int row = 0; row < Rows; ++row){
		for(int col = 0; col < Cols; ++col){
			cout << "     |";
		}
		cout << "     |\n" << "  " << row << "  "; 
		
    	for(int col = 0; col < Cols; ++col){    
			if(board[row][col].isselected == true){
				if(board[row][col].isamine == true && board[row][col].isdefused == false)
				{
					cout << "|  X  "; 
				}else if(board[row][col].isamine == true && board[row][col].isdefused == true)
				{
					cout << "|  M  "; 
				}else if(board[row][col].isamine == false && board[row][col].isdefused == true)
				{
					cout << "|  M  "; 
				}else
					cout << "|  " << board[row][col].adjacentmines << "  "; 
			}else
			{
				cout << "|  *  ";
			}
		}
		cout << "|\n" << "     |";

		for(int col = 0; col < Cols - 1; ++col)
		{
			cout << "_____|";
		}
		cout << "_____|\n";
	}
	cout << "\n";
}
