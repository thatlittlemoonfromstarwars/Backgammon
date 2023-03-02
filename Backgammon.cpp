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

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const short int SPACES = 24;

void printBoard(bool const &turn, short int const board[SPACES], short int const checks_on_bar[2]);
void setupBoard(short int board[SPACES]);
bool checkWin(short const int board[SPACES]);
void takeTurn(bool &turn, short int board[SPACES], short int safe_checkers[2], short int checks_on_bar[2]);
bool checkLegalMove(bool const &turn, int piece, int roll, short int board[SPACES]);
void copyBoard(short int board[SPACES], short int new_board[SPACES]);

int main()
{
	bool turn = true;
	short int board[SPACES] = {0}; // makes up board
	// positive integers correspond to white pieces
	// negative integers correspond to red pieces

	short int safe_checkers[2] = {0};
	short int checks_on_bar[2] = {1,1};
	srand((int)time(0));

	// for testing
	setupBoard(board);
	// printBoard(turn, board, checks_on_bar);

	// game loop
	while(true)
	{
		takeTurn(turn, board, safe_checkers, checks_on_bar);
		if(checkWin(board))
			break;
		turn = !turn;
	}
	cout << "Congratulations!" << endl << "Player ";
	if(turn)
		cout << "0 ";
	else
		cout << "O ";
	cout << "Wins!" << endl;

	return EXIT_SUCCESS;
} // end main()

void takeTurn(bool &turn, short int board[SPACES], short int safe_checkers[2], short int checks_on_bar[2])
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

	print_info:
		
	// check if there are any rolls left to use, if not return
	for(int i = 0; i <= 4; i++)
	{
		if(i == 4)
			return;

		if(rolls[i] != 0)
			break;
	}
		
	// print player info
	cout << endl << "Player ";
	if(turn)
		cout << "0" << endl;
	else
		cout << "O" << endl;

	printBoard(turn, board, checks_on_bar);

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
			cout << rolls[i] << " ";
	}
	cout << endl;

	choose_piece:

	int piece = 0;

	// check if any checkers on bar
	if((turn && checks_on_bar[0] > 0) || (!turn && checks_on_bar[1] > 0))
	{
		cout << "You have checkers on the bar. You must move these to continue." << endl;

		// check if there are any legal moves for checkers on the bar
		for (int i = 0; i < 4; i++)
		{
			if(rolls[i] != 0 && checkLegalMove(turn, 25, rolls[i], board))
			{
				// if there is a piece on the bar, piece = 25
				piece = 25;
				goto select_roll;
			}
		}

		cout << "There are no valid moves. Press enter to skip your turn.";
		while(cin.get() != '\n');
		// end turn if there are no valid moves to get checker(s) off the bar
		return;
	}

	// select piece
	cout << "Choose a piece to move: ";

	while(true)
	{
		// ensure selected piece is in the correct range and the right colour
		cin >> piece;
		piece--;
		if((piece >= 0 && piece <= 23) && ((turn && board[piece] > 0) || (!turn && board[23 - piece] < 0)))
			break;

		cout << "That is not a valid piece. Please select a valid piece: ";
	}

	cout << "Piece " << piece + 1 << " selected." << endl;
	if(!turn)
		piece = 23 - piece;

	select_roll:
	// select which dice roll to use
	int roll_ind = 1;
	for(int i = 0; i < 4; i++)
	{
		if(rolls[i] != 0)
		{
			cout << roll_ind << ". " << rolls[i] << endl;
			roll_ind++;
		}
	}
	char roll_choice;
	cout << "Select dice roll to use (type b to choose different piece): ";
	while(true)
	{
		cin >> roll_choice;
		if(roll_choice == 'b' || roll_choice == 'B')
			goto choose_piece;
			
		if((int)(roll_choice - '0') < roll_ind && (int)(roll_choice - '0') > 0)
			break;
		cout << "That is not a valid roll. Please choose a valid roll: ";
	}

	roll_ind = 0;
	int move_val = 0;
	for(int i = 0; i < 4; i++)
	{
		if(rolls[i] != 0)
			roll_ind++;
		if(roll_ind == roll_choice - '0')
		{
			move_val = rolls[i];
			rolls[i] = 0;
			break;
		}
	}

	// check if move is legal
		
	if(checkLegalMove(turn, piece, move_val, board))
	{
		if(turn)
		{
			
			if(piece == 25)
			{
				// if piece is on the bar
				board[-1+move_val]++;
				checks_on_bar[0]--;
			}
			else
			{
				// make move
				board[piece]--;
				if(piece+move_val >= SPACES)
				{
					// if checker coming off board
					safe_checkers[0]++;
				}
				else if(board[piece+move_val] == -1)
				{
					// if checker gets hit
					board[piece+move_val] += 2;
					checks_on_bar[1]++;
				}
				else
				{
					board[piece+move_val]++;
				}
			}
		}
		else
		{
			if(piece == 25)
			{
				// if piece is on the bar
				board[24-move_val]--;
				checks_on_bar[1]--;
			}
			else
			{
				board[piece]++;
				if(piece-move_val < 0)
				{
					// if checker coming off board
					safe_checkers[1]++;
				}
				else if(board[piece-move_val] == 1)
				{
					// if checker gets hit
					board[piece-move_val] -= 2;
					checks_on_bar[0]++;
				}
				else
				{
					board[piece-move_val]--;
				}
			}
		}
	}
	else
	{
		cout << "That is not a legal move. Please choose a different move." << endl;
		for(int i = 0; i < 4; i++)
		{
			if(rolls[i] == 0)
			{
				rolls[i] = move_val;
				break;
			}
		}
		goto select_roll;
		// -if not make player choose new move
		// -if no legal moves, skip players turn, however inform player and make them
		// press enter to continue
	}
	goto print_info;

  
} // end takeTurn()

bool checkLegalMove(bool const &turn, int piece, int roll, short int board[SPACES])
{
	if(turn)
	{
		if(piece == 25) // checker on bar
			piece = -1;
		
		if(piece+roll > SPACES-1)
		{
			// scan if any pieces are not in the final quarter
			for(int i = 0; i < SPACES*3/4; i++)
			{
				if(board[i] > 0)
					return false;
			}
		}
		else if(board[piece+roll] < -1)
			return false;
		
		return true;
	}
	else
	{
		if(piece == 25)
			piece = 24;
		if(piece-roll < 0)
		{
			// scan if any pieces are not in the final quarter
			for(int i = SPACES-1; i >= SPACES/4; i--)
			{
				if(board[i] < 0)
					return false;
			}
		}
		else if(board[piece - roll] > 1)
			return false;
		
		return true;
	}
} // end checkLegalMove()

void printBoard(bool const &turn, short int const board[SPACES], short int const checks_on_bar[2]) // TODO check board inversion works
{
	cout << endl;
	cout << " 13 14 15 16 17 18      19 20 21 22 23 24" << endl;
	cout << " ————————————————————————————————————————" << endl;

	if(turn)
	{
		for(int row = 1; row <= 5; row++)
		{
			for(int col = SPACES / 2 + 1; col <= SPACES; col++)
			{
				if(board[col - 1] >= row)
				cout << "  0";

				else if(board[col - 1] <= -row)
				cout << "  O";

				else if(row == 5 && col % 2 == 1)
				cout << "   ";

				else
				cout << "  |";

				if(col == SPACES * 3 / 4)
				{
				if(checks_on_bar[1] >= 6 - row)
					cout << "   O ";
				else
					cout << "   | ";
				}
			}
			cout << endl;
		}

		if(checks_on_bar[0] != 0)
			cout << "                     0" << endl;
		else
			cout << "                     |" << endl;

		for (int row = 5; row >= 1; row--)
		{
			for(int col = SPACES / 2; col > 0; col--)
			{
				if(board[col - 1] >= row)
					cout << "  0";

				else if(board[col - 1] <= -row)
					cout << "  O";

				else if(row == 5 && col % 2 == 1)
					cout << "   ";

				else
					cout << "  |";

				if (col == SPACES / 4 + 1)
				{
					if(checks_on_bar[0] >= 7 - row)
						cout << "   0 ";
					else
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
			for(int col = SPACES / 2; col > 0; col--)
			{
				if(board[col - 1] >= row)
					cout << "  0";

				else if(board[col - 1] <= -row)
					cout << "  O";

				else if(row == 5 && col % 2 == 1) // check if this is right
					cout << "   ";

				else
					cout << "  |";

				if(col == SPACES / 4 + 1)
				{
					if(checks_on_bar[0] >= 6 - row)
						cout << "   0 ";
					else
						cout << "   | ";
				}
			}
			cout << endl;
		}

		if(checks_on_bar[1] != 0)
			cout << "                     O" << endl;
		else
			cout << "                     |" << endl;

		for(int row = 5; row >= 1; row--)
		{
			for(int col = SPACES / 2 + 1; col <= SPACES; col++)
			{
				if(board[col - 1] >= row)
					cout << "  0";

				else if(board[col - 1] <= -row)
					cout << "  O";

				else if(row == 5 && col % 2 == 1) // check this is right as well
					cout << "   ";

				else
					cout << "  |";

				if(col == SPACES * 3 / 4) {
				if(checks_on_bar[1] >= 7 - row)
					cout << "   O ";
				else
					cout << "   | ";
				}
			}
			cout << endl;
		}
  	}

	cout << " ————————————————————————————————————————" << endl;
	cout << " 12 11 10  9  8  7       6  5  4  3  2  1";
} // end printBoard()

bool checkWin(short const int board[SPACES])
{
	int white_count = 0;
	int red_count = 0;
	for(int i = 0; i < SPACES; i++)
	{
		if (board[i] < 0)
			red_count++;
		else if (board[i] > 0)
			white_count++;
	}
	if(red_count == 0 || white_count == 0)
		return true;
	return false;
}

void setupBoard(short int board[SPACES])
{
	// FOR TESTING
	// for(int i = 0; i < SPACES/2; i++)
	// {
	// 	board[i] = -5;
	// }
	// for(int i = SPACES/2; i < SPACES; i++)
	// {
	// 	board[i] = 5;
	// }
	
	// default board setup
	board[24 - 1] = -2;
	board[1 - 1] = 2;

	board[8 - 1] = -3;
	board[17 - 1] = 3;

	board[13 - 1] = -5;
	board[12 - 1] = 5;

	board[6 - 1] = -5;
	board[19 - 1] = 5;
	
} // end setupBoard()

void copyBoard(short int board[SPACES], short int new_board[SPACES])
{
	for(int i = 0; i < SPACES; i++)
	{
		new_board[i] = board[i];
	}
} // end copyBoard()
