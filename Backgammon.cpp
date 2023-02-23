/*
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
 
 Checkers Safe: 0
 —————————————————————————————————————————
 Dice: 0 0
 Choose a piece to move:
*/

#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

const short int SPACES = 24;

void printBoard(bool const &turn, short int board[SPACES]);
void setupBoard(short int board[SPACES]);
void takeTurn(bool &turn, short int board[SPACES], short int safe_checkers[2], short int checks_on_bar[2]);
bool checkLegalMove(bool const &turn, int piece, int roll, short int board[SPACES]);
void copyBoard(short int board[SPACES], short int new_board[SPACES]);

int main()
{
	bool turn = true;
	short int board[SPACES] = {0}; // makes up board
	// negative integers correspond to red pieces. These will have the board inverted
	// positive integers correspond to white pieces
	short int safe_checkers[2] = {0};
	short int checks_on_bar [2] = {0};
	srand((int) time(0));
	
	// for testing
	setupBoard(board);
	printBoard(turn, board);
	
	// game loop
	while(true)
	{
		takeTurn(turn, board, safe_checkers, checks_on_bar);
		if(checkWin(board)) break;
		turn = !turn;
	}


	return EXIT_SUCCESS;
} // end main()

void takeTurn(bool turn, short int board[SPACES], short int safe_checkers[2], short int checks_on_bar[2])
{
	// roll dice
	// -account for double rolls
	short int rolls[4] = {0};
	rolls[0] = rand() % 6 + 1;
	rolls[1] = rand() % 6 + 1;
	
	if(rolls[0] == rolls[1])
	{
		rolls[2] = rolls[3] = rolls[0];
	}
	
	// ask player for moves
	printBoard(turn, board);
	
	cout << endl << endl << "Checkers Safe: ";
	if(turn)
		cout << safe_checkers[0] << endl;
	else
		cout << safe_checkers[1] << endl;
	cout << " —————————————————————————————————————————" << endl;
	cout << "Dice: ";
	for(int i = 0; i < 4; i++)
	{
		if(rolls[i] != 0)
		{
			cout << rolls[i] << " ";
		}
	}
	cout << endl;
	
	
	choose_piece:
	
	// check if there are any rolls left to use, if not return
	for(int i = 0; i < 5; i++)
	{
		if(i == 4) return;
		if(rolls[i] != 0) break;
	}
	
	// check if any checkers on bar
	if((turn && checks_on_bar[0] > 0) || (!turn && checks_on_bar[1] > 0))
	{
		// check if there are any legal moves for checkers on the bar
		
	}
		
	// select piece
	cout << "Choose a piece to move: ";
	
	int piece = 0;
	while(true)
	{
		// ensure selected piece is in the correct range and the right colour
		cin >> piece;
		
		if((piece >= 1 && piece <= 24) && ((turn && board[piece] > 0) || (!turn && board[25-piece] < 0))) break;
		
		cout << "That is not a valid piece. Please select a valid piece: ";
	}
	
	cout << "Piece " << piece << " selected." << endl;
	if(!turn) piece = 25-piece;
	
	select_roll:
	// select which dice roll to use
	int roll_ind = 1;
	for(int i = 0; i < 4; i++)
	{
		if(rolls[i] != 0)
		{
			cout << roll_ind << ". - " << rolls[i] << endl;
			roll_ind++;
		}
	}
	int roll_choice;
	cout << "Select dice roll to use (type b to choose different piece): ";
	while(true)
	{
		cin >> roll_choice;
		if(roll_choice == 98 || roll_choice == 66) goto choose_piece;
		if(roll_choice < roll_ind && roll_choice > 0) break;
		cout << "That is not a valid roll. Please choose a valid roll:";
	}
	
	roll_ind = 0;
	int move_val = 0;
	for(int i = 0; i < 4; i++)
	{
		if(rolls[i] != 0) roll_ind++;
		if(roll_ind == roll_choice)
		{
			move_val = rolls[i];
			rolls[i] = 0;
			break;
		}
	}
	
	// check if move is legal
	
	
	
	checkLegalMove(turn, 
	// -if not make player choose new move
	// -if no legal moves, skip players turn, however inform player and make them press enter to continue
	
	// make move
	// -if checker is taken off board, add to safe_checkers
} // end takeTurn()

void printBoard(bool turn, short int board[SPACES]) // TODO check board inversion works
{
	cout << endl;
	cout << " 13 14 15 16 17 18      19 20 21 22 23 24" << endl;
	cout << " ————————————————————————————————————————" << endl;
	
	if(turn)
	{
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
	}
	else
	{
		for(int row = 1; row <= 5; row++)
		{
			for(int col = SPACES/2; col > 0; col--)
			{
				if(board[col-1] >= row)
					cout << "  0";
				
				else if(board[col-1] <= -row)
					cout << "  O";
				
				else if(row == 5 && col%2 == 1) // check if this is right
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
		
		cout << "                     |" << endl;
		
		for(int row = 5; row >= 1; row--)
		{
			for(int col = SPACES/2 + 1; col <= SPACES; col++)
			{
				
				if(board[col-1] >= row)
					cout << "  0";
				
				else if(board[col-1] <= -row)
					cout << "  O";
				
				else if(row == 5 && col%2 == 1) // check this is right as well
					cout << "   ";
				
				else
					cout << "  |";
					
				if(col == SPACES*3/4)
					cout << "   | ";
				
			}
			cout << endl;
		}
		
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

void copyBoard(short int board[SPACES], short int new_board[SPACES])
{
	for(int i = 0; i < SPACES; i++)
	{
		new_board[i] = board[i];
	}
} // end copyBoard()
