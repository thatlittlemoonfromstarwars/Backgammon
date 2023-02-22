/*
 13 14 15 16 17 18      19 20 21 22 23 24
 _________________________________________
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
     |     |     |   |      |     |     | 
                     |
  |     |     |      |   |     |     |   
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 12 11 10  9  8  7       6  5  4  3  2  1

 13 14 15 16 17 18      19 20 21 22 23 24
——————————————————————————————————————————
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
  |  |  |  |  |  |   |   |  |  |  |  |  | 
     |     |     |   |      |     |     | 
                     |
  |     |     |      |   |     |     |   
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
  |  |  |  |  |  |   |   |  |  |  |  |  |
——————————————————————————————————————————
 12 11 10  9  8  7       6  5  4  3  2  1
*/

#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

const short int SPACES = 24;

void printBoard(short int board[SPACES]);
void setupBoard(short int board[SPACES]);

int main()
{
	short int board[SPACES] = {0}; // makes up board
	// negative integers correspond to red pieces
	// positive integers correspond to white pieces
	setupBoard(board);
	printBoard(board);

	return EXIT_SUCCESS;
}

void printBoard(short int board[SPACES])
{
	cout << endl;
	cout << " 13 14 15 16 17 18      19 20 21 22 23 24" << endl;
	cout << " ————————————————————————————————————————" << endl;

	for(int row = 1; row <= 5; row++)
	{
		for(int col = SPACES/2 + 1; col <= SPACES; col++)
		{
			
			if(board[col-1] >= row)
				cout << "  0";
			
			else if(board[col-1] <= -row)
				cout << "  O";
			
			else if(row == 5 && col%2 == 1)
				cout << "   ";
			
			else
				cout << "  |";
				
			if(col == SPACES*3/4)
				cout << "   | ";

		}
		cout << endl;
	}

	cout << "                     |" << endl;
	
	for(int row = 5; row >= 1; row--)
	{
		for(int col = SPACES/2; col > 0; col--)
		{
			if(board[col-1] >= row)
				cout << "  0";
			
			else if(board[col-1] <= -row)
				cout << "  O";
			
			else if(row == 5 && col%2 == 1)
				cout << "   ";

			else
				cout << "  |";
				
			if(col == SPACES/4+1)
			{
				cout << "   | ";
			}
		}
		cout << endl;
	}

	cout << " ————————————————————————————————————————" << endl;
	cout <<  " 12 11 10  9  8  7       6  5  4  3  2  1";
	
} // end printBoard()

void setupBoard(short int board[SPACES])
{
	board[24 -1] = -2;
	board[1 -1] = 2;
	
	board[8 -1] = -3;
	board[17 -1] = 3;
	
	board[13 -1] = -5;
	board[12 -1] = 5;
	
	board[6 -1] = -5;
	board[19 -1] = 5;
	
} // end setupBoard()