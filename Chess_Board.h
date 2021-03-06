#pragma once
#include<string>
#include<vector>
#include<array>
#include<assert.h>
#include"Board_Square.h"
#include <iostream>


/* 
*
* The board is represented internally with the following rows and cols
* 
*      1  2  3  4  5  6  7  8
* 1 |  0  1  2  3  4  5  6  7 | 1
* 2 |  8  9 10 11 12 13 14 15 | 2
* 3 | 16 17 18 19 20 21 22 23 | 3
* 4 | 24 25 26 27 28 29 30 31 | 4
* 5 | 32 33 34 35 36 37 38 39 | 5
* 6 | 40 41 42 43 44 45 46 47 | 6
* 7 | 48 49 50 51 52 53 54 55 | 7
* 8 | 56 57 58 59 60 61 62 63 | 8
*      1  2  3  4  5  6  7  8
* 
* Rows and Columns are externally represented to user in the typical chess fashion(?), as shown below
* 
*      A  B  C  D  E  F  G  H
* 8 |  0  1  2  3  4  5  6  7 | 8
* 7 |  8  9 10 11 12 13 14 15 | 7
* 6 | 16 17 18 19 20 21 22 23 | 6
* 5 | 24 25 26 27 28 29 30 31 | 5
* 4 | 32 33 34 35 36 37 38 39 | 4
* 3 | 40 41 42 43 44 45 46 47 | 3
* 2 | 48 49 50 51 52 53 54 55 | 2
* 1 | 56 57 58 59 60 61 62 63 | 1
*      A  B  C  D  E  F  G  H
* 
*/

class Chess_Board {
public:
	const uint8_t num_rows = 8;
	const uint8_t num_cols = 8;

	const uint8_t white_prom_row = 1; // row # that a white pawn must advance to in order to gain a "promotion" (internal representation)
	const uint8_t black_prom_row = 8; // row # that a black pawn must advance to in order to gain a "promotion" (internal representation)

	const int8_t white_pawn_dir = -1; // a white pawn moving in the legal direction decreases its row number (internal representation)
	const int8_t black_pawn_dir = 1; // a black pawn moving in the legal direction increases its row number (internal representation)

	// point values for when a piece is captured
	const uint8_t pawn_pts = 1;
	const uint8_t rook_pts = 5;
	const uint8_t knight_pts = 3;
	const uint8_t bishop_pts = 3;
	const uint8_t queen_pts = 9;

	/****************************************************************************
	* Chess_Board
	*
	* - Chess_Board class's default constructor, sets board up in the normal 
	* starting configuration
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	Chess_Board()
	{
		// Setting up the board from the top (black side) down...

		// set up black's back row
		set_board_square(black_white_helper(1, 1), Chess_Side::Black, Chess_Piece_Type::Rook, false, 1, 1);
		set_board_square(black_white_helper(1, 2), Chess_Side::Black, Chess_Piece_Type::Knight, false, 1, 2);
		set_board_square(black_white_helper(1, 3), Chess_Side::Black, Chess_Piece_Type::Bishop, false, 1, 3);
		set_board_square(black_white_helper(1, 4), Chess_Side::Black, Chess_Piece_Type::Queen, false, 1, 4);
		set_board_square(black_white_helper(1, 5), Chess_Side::Black, Chess_Piece_Type::King, false, 1, 5);
		set_board_square(black_white_helper(1, 6), Chess_Side::Black, Chess_Piece_Type::Bishop, false, 1, 6);
		set_board_square(black_white_helper(1, 7), Chess_Side::Black, Chess_Piece_Type::Knight, false, 1, 7);
		set_board_square(black_white_helper(1, 8), Chess_Side::Black, Chess_Piece_Type::Rook, false, 1, 8);

		// Set up the the black pawns
		for (uint8_t col = 1; col <= num_cols; col++)
		{
			set_board_square(black_white_helper(2, col), Chess_Side::Black, Chess_Piece_Type::Pawn, false, 2, col);
		}

		// Set the middle empty squares 
		for (uint8_t row = 3; row <= 6; row++)
		{
			for (uint8_t col = 1; col <= 8; col++)
			{
				set_board_square(black_white_helper(row, col), Chess_Side::EMPTY, Chess_Piece_Type::EMPTY, false, row, col);
			}
		}

		// Set up the the white pawns
		for (uint8_t col = 1; col <= num_cols; col++)
		{
			set_board_square(black_white_helper(7, col), Chess_Side::White, Chess_Piece_Type::Pawn, false, 7, col);
		}

		// set up black's back row
		set_board_square(black_white_helper(8, 1), Chess_Side::White, Chess_Piece_Type::Rook, false, 8, 1);
		set_board_square(black_white_helper(8, 2), Chess_Side::White, Chess_Piece_Type::Knight, false, 8, 2);
		set_board_square(black_white_helper(8, 3), Chess_Side::White, Chess_Piece_Type::Bishop, false, 8, 3);
		set_board_square(black_white_helper(8, 4), Chess_Side::White, Chess_Piece_Type::Queen, false, 8, 4);
		set_board_square(black_white_helper(8, 5), Chess_Side::White, Chess_Piece_Type::King, false, 8, 5);
		set_board_square(black_white_helper(8, 6), Chess_Side::White, Chess_Piece_Type::Bishop, false, 8, 6);
		set_board_square(black_white_helper(8, 7), Chess_Side::White, Chess_Piece_Type::Knight, false, 8, 7);
		set_board_square(black_white_helper(8, 8), Chess_Side::White, Chess_Piece_Type::Rook, false, 8, 8);

		clear_player_score(Chess_Side::White);
		clear_player_score(Chess_Side::Black);
		set_player_check(Chess_Side::White, false);
		set_player_check(Chess_Side::Black, false);
		set_player_name(Chess_Side::White, "Player 1");
		set_player_name(Chess_Side::Black, "Player 2");
		set_curr_turn(Chess_Side::White);// white starts by default
		add_game_state_hist();
	}
	/****************************************************************************
	* Chess_Board
	* 
	* TO BE IMPLEMENTED
	*
	* - Parametrized constructor for the Chess_Board class, sets the game up in 
	* a specified state according to the inputted FEN string
	*
	* Parameters :
	* - FEN_string : a string containing the chess board's state encoded in 
	* Forsyth?Edwards Notation 
	*	- (https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation)
	*
	* Returns :
	* - none
	****************************************************************************/
	Chess_Board(std::string FEN_string)
	{
		// to be implemented...
		// Piece placement data
			// fill in the board
		// active color
			// set the curr_turn
		// castling availability
			// has_moved data members for kings and rooks
				// should take some thought in seeing which to set (none, one, both, etc.)
		// en passant target square
			// might have to add a "past" state to the game_hist vector here
		// halfmove clock
			// ?-> might want to change internal data members to reflect this "time keeping"
		// fullmove number
			// same as halfmove clock
			
		// with the now initialized board...
		// calculate point values for each player based off of what isn't there for the other player
	}
	/****************************************************************************
	* test_draw
	*
	* - Public wrapper function for the private draw_Board function, to ease
	* testing
	*
	* Parameters :
	* - draw_labels : indicates whether to print labels at the start of each row
	* (1-8) and column (A-H)
	*
	* Returns :
	* - none
	****************************************************************************/
	void test_draw(bool draw_labels) const
	{
		draw_board(draw_labels);
	}
	/****************************************************************************
	* get_player_name
	*
	* - Returns the private data member p1_name or p2_name by value
	*
	* Parameters :
	* - player : specifies whether which name to return 
	*	- p1_name (Chess_Side::White) 
	*	- p2_name (Chess_Side::Black)
	*
	* Returns :
	* - std::string : a copy of the specified player's name
	****************************************************************************/
	std::string get_player_name(Chess_Side player) const
	{
		assert(player != Chess_Side::EMPTY);
		return player == Chess_Side::White ? p1_name : p2_name;
	}
	/****************************************************************************
	* set_player_name
	*
	* - Returns the private data member p1_name or p2_name by value
	*
	* Parameters :
	* - player : specifies whether which name to return
	*	- p1_name (Chess_Side::White)
	*	- p2_name (Chess_Side::Black)
	*
	* Returns :
	* - std::string : a copy of the specified player's name
	****************************************************************************/
	void set_player_name(Chess_Side player, std::string name)
	{
		assert(player != Chess_Side::EMPTY);
		if (player == Chess_Side::White)
		{
			p1_name = name;
		}
		else
		{
			p2_name = name;
		}
	}
	/****************************************************************************
	* play_game
	*
	* - Main driver function to play a game of chess once after setup has been 
	* completed
	*
	* Parameters :
	* - none 
	*
	* Returns :
	* - none
	****************************************************************************/
	void play_game()
	{
		uint8_t src_row, src_col, dest_row, dest_col, capt_row, capt_col;
		bool castling_flag, promotion_flag;

		char src_row_choice, src_col_choice, dest_row_choice, dest_col_choice;

		while (true) // loop will spin until a user decides to resign
		{
			draw_board(true); // display the current board

			do
			{
				printf("%s, it is your turn.\n", get_player_name(get_curr_turn()).c_str());
				//printf("In order to resign, enter an 'R' for the first requested move location.\n");
				if (get_player_check(get_curr_turn()))
				{
					printf("You are in check!\n");
				}
				printf("Enter the column of the piece you would like to move, or an 'r'/'R' if you would like to resign: ");
				std::cin >> src_col_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (toupper(src_col_choice) == 'R')
				{
					printf("%s resigned!\n", get_player_name(get_curr_turn()).c_str());
					printf("Congratulations, %s, you win!\n", get_player_name(get_curr_turn() == Chess_Side::White ? Chess_Side::Black : Chess_Side::White).c_str());
					return;
				}
				src_col = lettered_col_translation(src_col_choice);

				printf("Enter the row of the piece you would like to move: ");
				std::cin >> src_row_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				src_row = char_to_num(src_row_choice);
				src_row = external_to_internal_row(src_row); // translation we have to do because I'm bad at planning ahead

				printf("Enter the column of the square you would like to move to: ");
				std::cin >> dest_col_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				dest_col = lettered_col_translation(dest_col_choice);

				printf("Enter the row of the square you would like to move to: ");
				std::cin >> dest_row_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				dest_row = char_to_num(dest_row_choice);
				dest_row = external_to_internal_row(dest_row);

				if (!valid_row(src_row) || !valid_col(src_col) || !valid_row(dest_row) || !valid_col(dest_col))
				{
					continue; // bad user input?-> Back to the top of the loop with ya
				}

			} while (!check_move(src_row, src_col, dest_row, dest_col, &capt_row, &capt_col, &castling_flag, &promotion_flag, false));

			enact_move(get_curr_turn(), src_row, src_col, dest_row, dest_col, capt_row, capt_col);

			while (castling_flag) // if the first move was a castling move...
			{
				draw_board(true);

				printf("%s, it is still your turn.\n", get_player_name(get_curr_turn()).c_str());
				printf("You are in a castling manuever.\n");
				printf("Enter the column of the piece you would like to move: ");
				std::cin >> src_col_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				src_col = lettered_col_translation(src_col_choice);

				printf("Enter the row of the piece you would like to move: ");
				std::cin >> src_row;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				src_row = char_to_num(src_row_choice);
				src_row = external_to_internal_row(src_row); 

				printf("Enter the column of the square you would like to move to: ");
				std::cin >> dest_col_choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				dest_col = lettered_col_translation(dest_col_choice);

				printf("Enter the row of the square you would like to move to: ");
				std::cin >> dest_row;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				dest_row = char_to_num(dest_row_choice);
				dest_row = external_to_internal_row(dest_row);

				if (check_move(src_row, src_col, dest_row, dest_col, &capt_row, &capt_col, &castling_flag, &promotion_flag, true))
				{
					enact_move(get_curr_turn(), src_row, src_col, dest_row, dest_col, capt_row, capt_col);
					castling_flag = false;
				}
			}
			while (promotion_flag) // if there's a pawn promotion in order
			{
				uint8_t promotion_choice;
				printf("\n%s, choose what piece to promote your pawn to.\n", get_player_name(get_curr_turn()).c_str());
				printf("[1] Queen\n");
				printf("[2] Rook\n");
				printf("[3] Bishop\n");
				printf("[4] Knight\n");

				std::cin >> promotion_choice;

				if (promotion_choice >= 1 && promotion_choice <= 4)
				{
					Chess_Piece_Type promotion_piece;
					switch (promotion_choice) {
					case 1:
						promotion_piece = Chess_Piece_Type::Queen;
						break;
					case 2: 
						promotion_piece = Chess_Piece_Type::Rook;
						break;
					case 3:
						promotion_piece = Chess_Piece_Type::Bishop;
						break;
					case 4:
						promotion_piece = Chess_Piece_Type::Knight;
						break;
					default: // should never reach this but I guess we'll add a default just to be safe
						promotion_piece = Chess_Piece_Type::Queen;
						break;
					}
					
					insert_piece(dest_row, dest_col, get_curr_turn(), promotion_piece, true);
					break; // breaks us out of the while loop
				}
			}

			add_game_state_hist(); // add the new board state to the game history
			update_player_check(Chess_Side::White); // update the 'check' state variables
			update_player_check(Chess_Side::Black); // ^
			flip_curr_turn(); 
			
			printf("Move completed.\n\n\n");

			//system("cls"); // not sure if we'll want this for debugging, stylistically later tho 
		}
	}
	/****************************************************************************
	* get_piece_val
	*
	* - Returns the point value that would be rewarded for capturing a specified 
	* chess piece type
	*
	* Parameters :
	* - in_piece : the type of piece to return the point value for
	*
	* Returns :
	* - uint8_t : the number of points awarded for capturing a chess piece of 
	* type in_piece
	****************************************************************************/
	uint8_t get_piece_val(Chess_Piece_Type in_piece) const
	{
		switch (in_piece)
		{
		case Chess_Piece_Type::Pawn:
			return pawn_pts;
			break;
		case Chess_Piece_Type::Rook:
			return rook_pts;
			break;
		case Chess_Piece_Type::Knight:
			return knight_pts;
			break;
		case Chess_Piece_Type::Bishop:
			return bishop_pts;
			break;
		case Chess_Piece_Type::Queen:
			return queen_pts;
			break;
		default:
			return 0;
			break;
		}
	}
	/****************************************************************************
	* get_num_moves
	* 
	* TO BE REWORKED
	*
	* - Returns the point value that would be rewarded for capturing a specified
	* chess piece type
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - uint8_t : the number of moves completed so far in the game
	****************************************************************************/
	uint8_t get_num_moves()
	{
		// this needs to get changed
		// casting size_t down to uint8_t shouldn't matter as "The longest possible chess game is 8848.5 moves long" (https://wismuth.com/chess/longest-game.html#:~:text=Abstract,34082%20according%20to%20a%20calculation.)
		return (uint8_t)game_hist.size() - (uint8_t)1; // minus 1 as the board's initial state is the first entry in that vector
	}
	/****************************************************************************
	* get_board_square_info
	*
	* - Returns the a copy of the instance of the Board_Square class held at the 
	* specified row, column location on the board
	*
	* Parameters :
	* - row : the row that the board square is in
	* _ col : the column that the board square is in
	*
	* Returns :
	* - Board_Square : a copy of the Board_Square class instance at the specified 
	* location
	****************************************************************************/
	Board_Square get_board_square_info(uint8_t row, uint8_t col) const
	{
		assert(row >= 1 && row <= 8);
		assert(col >= 1 && col <= 8);

		return board[row_and_col_to_index(row, col)];
	}
	/****************************************************************************
	* get_curr_turn
	*
	* - Returns the the private data member curr_turn, which holds which player's 
	* turn it is in the game currently
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Side : the player who is currently eligible to make a move
	****************************************************************************/
	Chess_Side get_curr_turn() const
	{
		return curr_turn;
	}
	/****************************************************************************
	* get_curr_turn
	*
	* - Returns the the private data member white_score or black_score, which holds 
	* the specified player's score in the current chess game thus far
	*
	* Parameters :
	* - player : specifies which player's score to fetch
	*
	* Returns :
	* - uint8_t : the specified player's score in the current chess game thus far
	****************************************************************************/
	uint8_t get_player_score(Chess_Side player) const
	{
		assert(player != Chess_Side::EMPTY);
		return player == Chess_Side::White ? white_score : black_score;
	}
	/****************************************************************************
	* get_player_check
	*
	* - Returns the private data member white_check or black_check, which holds
	* the most recently updated indication of whether the specified player is in check
	*
	* Parameters :
	* - player : specifies which player's check status to fetch
	*
	* Returns :
	* - bool : true if the specified player is in check, false otherwise
	****************************************************************************/
	bool get_player_check(Chess_Side player) const
	{
		assert(player != Chess_Side::EMPTY);
		return player == Chess_Side::White ? white_check : black_check;
	}
	/****************************************************************************
	* get_past_game_state
	*
	* - Returns an entry of the game_hist array, which holds a past board state
	* - If an invalid index is passed in, an empty board is passed back
	*
	* Parameters :
	* - num_moves_back : specifies how many moves back from the current move to 
	* fetch the state from
	*
	* Returns :
	* - std::array<Board_Square, 64> : the chess board at the specified point in 
	* the game
	****************************************************************************/
	std::array<Board_Square, 64> get_past_game_state(uint8_t num_moves_back)
	{
		std::array<Board_Square, 64> prev_game_state;

		assert(num_moves_back > 0);
		assert(!game_hist.empty()); // should never be empty, as first entry is placed within constructor
		if (game_hist.size() < num_moves_back) // replace this with an assert?
		{
			// create an empty board...
			for (uint8_t row = 1; row <= num_rows; row++)
			{
				for (uint8_t col = 1; col <= num_cols; col++)
				{
					set_board_square(black_white_helper(row, col), Chess_Side::EMPTY, Chess_Piece_Type::EMPTY, false, row, col);
				}
			}
			
			return prev_game_state; // and return it
		}
		
		return game_hist[game_hist.size() - num_moves_back]; // otherwise return the desired state
	}
	/****************************************************************************
	* is_in_check
	*
	* - Returns whether the specified side is currently in check
	* - Begings by finding the specified player's king, and then checking if any 
	* pieces from the opposite side can legally attack it
	*
	* Parameters :
	* - player : the side of interest (in regards to its check status)
	*
	* Returns :
	* - bool : true if the specified player is in check, false otherwise
	****************************************************************************/
	bool is_in_check(Chess_Side player)
	{
		assert(player != Chess_Side::EMPTY);
		uint8_t king_row = 0;
		uint8_t king_col = 0;
		
		// first find where the player's king is 
		for (uint8_t curr_row = 1; curr_row <= num_rows; curr_row++)
		{
			for (uint8_t curr_col = 1; curr_col <= num_cols; curr_col++)
			{
				if (get_board_square_info(curr_row, curr_col).get_square_side() == player
					&& get_board_square_info(curr_row, curr_col).get_square_piece() == Chess_Piece_Type::King)
				{
					king_row = curr_row;
					king_col = curr_col;
					goto King_Loop_Exit; // in lieu of a double break...
				}
			}
		}
	King_Loop_Exit:

		assert(king_row != 0 && king_col != 0); // if we can't find the king we're in trouble...

		return is_threatening(Chess_Piece::get_opposite_side(player), king_row, king_col);
	}
	/****************************************************************************
	* check_move
	*
	* - Takes in a (typically user-supplied) move and checks whether it is 
	* permissible in the current game state
	* - Begins with some simple checks before calling simple_move_check to 
	* make the final checks on the move
	*
	* Parameters :
	* - src_row : the source row of the piece being moved
	* - src_col : the source column of the piece being moved
	* - dest_row : the destination row of the piece being moved
	* - dest_col : the destination column of the piece being moved
	* - capt_row : used to indicate to the caller when a piece is captured that is 
	* in a different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the row of the captured piece
	*	- (only happens with an "en-passant" move)
	* - capt_col : used to indicate to the caller when a piece is captured that is 
	* in a different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the column of the captured piece
	*	- (only happens with an "en-passant" move)
	* - castling_out : used to indicate to the caller whether a castling maneuver was 
	* sucessfully initiated (the king was moved two squares towards a rook)
	* - prom_out : used to indicate to the caller whether a pawn promotion is in order
	* - castling_in :  used to indicate to the function whether the second "leg" 
	* of a castling maneuver is required (king has been moved, now time for the rook)
	* 
	* Returns :
	* - bool : true if the given move is legal, false otherwise
	****************************************************************************/
	bool check_move(uint8_t src_row, uint8_t src_col, uint8_t dest_row, uint8_t dest_col, 
		uint8_t* capt_row, uint8_t* capt_col, bool* castling_out, bool* prom_out, bool castling_in = false)
	{
		assert(capt_row != NULL);
		assert(capt_col != NULL);
		assert(castling_out != NULL); 
		assert(prom_out != NULL);
		*capt_row = 0;
		*capt_col = 0;
		*castling_out = false;
		*prom_out = false;

		// first make sure the input parameters are in bounds
		if (src_row < 1 || src_row > 8)
		{
			return false;
		}
		if (src_col < 1 || src_col > 8)
		{
			return false;
		}
		if (dest_row < 1 || dest_row > 8)
		{
			return false;
		}
		if (dest_col < 1 || dest_col > 8)
		{
			return false;
		}

		// can't "move" to where you already are
		if (src_row == dest_row && src_col == dest_col)
		{
			return false;
		}
		
		// make sure there's actually a piece to move in the src square
		if (get_board_square_info(src_row, src_col).get_square_piece() == Chess_Piece_Type::EMPTY)
		{
			return false;
		}
		// make sure that piece getting moved is on the correct side
		if (get_board_square_info(src_row, src_col).get_square_side() != get_curr_turn())
		{
			return false;
		}
		// and you're not attacking one of your own pieces at the destination
		if (get_board_square_info(dest_row, dest_col).get_square_side() == get_curr_turn())
		{
			return false;
		}

		// check to make sure that only the rook is moved after the initial 
		// movement of a king during a "castling" move
		if (castling_in && (get_board_square_info(src_row, src_col).get_square_piece() != Chess_Piece_Type::Rook))
		{
			return false;
		}

		// save the dest square's contents so we can restore it after the checks below
		Board_Square dest_square = get_board_square_info(dest_row, dest_col);

		// make sure move doesn't place player into check
		move_piece(false, src_row, src_col, dest_row, dest_col); // as long as the move is in bounds we can try it out
		if (is_in_check(get_curr_turn())) // illegal to place yourself in check
		{
			move_piece(false, dest_row, dest_col, src_row, src_col); // place the moved piece back in the src square
			if (dest_square.is_occupied()) // if there was a piece in the dest square, put it back
			{
				insert_piece(dest_row, dest_col, dest_square.get_square_side(),
					dest_square.get_square_piece(), dest_square.get_piece_moved());
			}
			return false; // return back to the call either way that the move isn't allowed
		}
		else // otherwise we're fine to undo that virtual move and check if it was actually legal to make
		{
			// issue with wiping out contents of board with check?
			move_piece(false, dest_row, dest_col, src_row, src_col); // place the moved piece back in the src square
			if (dest_square.is_occupied()) // if there was a piece in that square, put it back
			{
				insert_piece(dest_row, dest_col, dest_square.get_square_side(),
					dest_square.get_square_piece(), dest_square.get_piece_moved());
			}
		}

		// check if the move is actually legal
		return simple_move_check(get_curr_turn(), src_row, src_col, dest_row, dest_col, capt_row, capt_col, castling_out, prom_out, castling_in);
	}

private:
	std::array<Board_Square, 64> board; // board array containing the actual pieces, their locations, etc.
	Chess_Side curr_turn; // which player's turn it is
	std::vector<std::array<Board_Square, 64>> game_hist; // array of board arrays, keeps track of the game history
	uint8_t white_score; // player scores...
	uint8_t black_score; // ^
	bool white_check; // indicates whether a player is in check...
	bool black_check; // ^
	std::string p1_name; // player names (requesting them to be implemented)
	std::string p2_name; // 
	/*
	* Whole lotta definitions for the drawing functions...
	*/
	const uint8_t num_layers = 8;
	const uint8_t draw_width = 12;
	const char background_char = 0x1A;
	// Using the ASCII "substitute" (SUB) character to indicate a "background" part of the piece's definition
		// this choice in character is entirely arbitrary beyond that it's a non-printable character 
	// Pawns 
	// Black Pawn
	const std::string black_pawn[8] = {
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A__\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A/  \\\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A/    \\\x1A\x1A\x1A",
		"\x1A\x1A\x1A\\    /\x1A\x1A\x1A",
		"\x1A\x1A\x1A/    \\\x1A\x1A\x1A",
		"\x1A\x1A|______|\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Pawn
	const std::string white_pawn[8] = {
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A__\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A//\\\\\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A//||\\\\\x1A\x1A\x1A",
		"\x1A\x1A\x1A\\\\||//\x1A\x1A\x1A",
		"\x1A\x1A\x1A///\\\\\\\x1A\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// Rooks
	// Black Rooks
	const std::string black_rook[8] = {
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A||_||_||\x1A\x1A",
		"\x1A\x1A|      |\x1A\x1A",
		"\x1A\x1A\\      /\x1A\x1A",
		"\x1A\x1A\x1A|    |\x1A\x1A\x1A",
		"\x1A\x1A\x1A|    |\x1A\x1A\x1A",
		"\x1A\x1A|______|\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Rooks
	const std::string white_rook[8] = {
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A||_||_||\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\\\\\\||///\x1A\x1A",
		"\x1A\x1A\x1A||||||\x1A\x1A\x1A",
		"\x1A\x1A\x1A||||||\x1A\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// Knights
	// Black Knights
	const std::string black_knight[8] = {
		"\x1A\x1A\x1A\x1A/\\__\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A/    \\\x1A\x1A\x1A",
		"\x1A\x1A/      \\\x1A\x1A",
		"\x1A\x1A\\__/\\   \\\x1A",
		"\x1A\x1A\x1A\x1A\x1A/    /\x1A",
		"\x1A\x1A\x1A\x1A/    |\x1A\x1A",
		"\x1A\x1A\x1A|______|\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Knights
	const std::string white_knight[8] = {
		"\x1A\x1A\x1A\x1A/\\__\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A///\\\\\\\x1A\x1A\x1A",
		"\x1A\x1A////\\\\\\\\\x1A\x1A",
		"\x1A\x1A\\\\//\\\\\\\\\\\x1A",
		"\x1A\x1A\x1A\x1A\x1A//////\x1A",
		"\x1A\x1A\x1A\x1A/////|\x1A\x1A",
		"\x1A\x1A\x1A||||||||\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// Bishops
	// Black Bishops
	const std::string black_bishop[8] = {
		"\x1A\x1A\x1A\x1A/|\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A/ |\x1A|\\\x1A\x1A\x1A",
		"\x1A\x1A/  |\x1A| \\\x1A\x1A",
		"\x1A|   \\_| |\x1A\x1A",
		"\x1A\x1A\\      /\x1A\x1A",
		"\x1A\x1A\x1A\\    /\x1A\x1A\x1A",
		"\x1A\x1A|______|\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Bishops
	const std::string white_bishop[8] = {
		"\x1A\x1A\x1A\x1A/|\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A//|\x1A|\\\x1A\x1A\x1A",
		"\x1A\x1A///|\x1A||\\\x1A\x1A",
		"\x1A|\\\\\\\\\x1A|||\x1A\x1A",
		"\x1A\x1A\\\\\\\\////\x1A\x1A",
		"\x1A\x1A\x1A\\\\\\///\x1A\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// Queens
	// Black Queens
	const std::string black_queen[8] = {
		"\x1A\x1A\x1A\x1A_||_\x1A\x1A\x1A\x1A",
		"\x1A\x1A___||___\x1A\x1A",
		"\x1A/ __  __ \\\x1A",
		"\x1A\\ \\\x1A||\x1A/ /\x1A",
		"\x1A\x1A\\ \\||/ /\x1A\x1A",
		"\x1A\x1A\x1A\\    /\x1A\x1A\x1A",
		"\x1A\x1A|______|\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Queens
	const std::string white_queen[8] = {
		"\x1A\x1A\x1A\x1A_||_\x1A\x1A\x1A\x1A",
		"\x1A\x1A___||___\x1A\x1A",
		"\x1A///||||\\\\\\\x1A",
		"\x1A\\\\\\\x1A||\x1A///\x1A",
		"\x1A\x1A\\\\\\||///\x1A\x1A",
		"\x1A\x1A\x1A\\\\\\///\x1A\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// Kings
	// Black Kings
	const std::string black_king[8] = {
		"\x1A\x1A\x1A\x1A_/\\_\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\\__/\x1A\x1A\x1A\x1A",
		"\x1A/\\\x1A\x1A||\x1A\x1A/\\\x1A",
		"\x1A\\ \\\x1A||\x1A/ /\x1A",
		"\x1A\x1A\\ \\||/ /\x1A\x1A",
		"\x1A\x1A\x1A\\    /\x1A\x1A\x1A",
		"\x1A\x1A|______|\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// White Kings
	const std::string white_king[8] = {
		"\x1A\x1A\x1A\x1A_/\\_\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\\\\//\x1A\x1A\x1A\x1A",
		"\x1A/\\\x1A\x1A||\x1A\x1A/\\\x1A",
		"\x1A\\\\\\\x1A||\x1A///\x1A",
		"\x1A\x1A\\\\\\||///\x1A\x1A",
		"\x1A\x1A\x1A\\\\\\///\x1A\x1A\x1A",
		"\x1A\x1A||||||||\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};
	// 'Empty' Piece
	const std::string empty_piece[8] = {
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A",
		"\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A\x1A"
	};

	/*
	* Some more definitions for the labels at the beginning of each row, and at the foot of each column...
	*/
	// Row Labels
	// 1
	const std::string label_one[8] = {
		"     __     ",
		"   /   |    ",
		"  /_|  |    ",
		"    |  |    ",
		"    |  |    ",
		"   _|  |_   ",
		"  |______|  ",
		"            "
	};
	// 2
	const std::string label_two[8] = {
		"    ___     ",
		"   / _ \\    ",
		"  /_/ \\ \\   ",
		"      / /   ",
		"     / /    ",
		"    / /__   ",
		"   |_____|  ",
		"            "
	};
	// 3
	const std::string label_three[8] = {
		"    ____    ",
		"   / __ \\   ",
		"  /_/ / /   ",
		"     < <    ",
		"  _   \\ \\   ",
		"  \\\\__/ /   ",
		"   \\___/    ",
		"            "
	};
	// 4
	const std::string label_four[8] = {
		"   _   _    ",
		"  | | | |   ",
		"  | | | |   ",
		"  | |_| |_  ",
		"  |___   _| ",
		"      | |   ",
		"      |_|   ",
		"            "
	};
	// 5
	const std::string label_five[8] = {
		"   _______  ",
		"  |  _____| ",
		"  | |____   ",
		"  |_____ \\  ",
		"        \\ \\ ",
		"   _____/ / ",
		"  |______/  ",
		"            "
	};
	// 6
	const std::string label_six[8] = {
		"      _     ",
		"     //     ",
		"    //      ",
		"   //___    ",
		"  //   \\\\   ",
		"  ||    ||  ",
		"   \\\\__//   ",
		"            "
	};
	// 7
	const std::string label_seven[8] = {
		"   _______  ",
		"  |____  /  ",
		"      / /   ",
		"     / /    ",
		"    / /     ",
		"   / /      ",
		"  /_/       ",
		"            "
	};
	// 8
	const std::string label_eight[8] = {
		"      __    ",
		"    //  \\\\  ",
		"   ||    || ",
		"    \\\\__//  ",
		"    //  \\\\  ",
		"   ||    || ",
		"    \\\\__//  ",
		"            "
	};
	// Column Labels
	// A
	const std::string label_a[8] = {
		"     _      ",
		"    /_\\     ",
		"   // \\\\    ",
		"  //___\\\\   ",
		"  ||   ||   ",
		"  ||   ||   ",
		"  ||   ||   ",
		"            "
	};
	// B
	const std::string label_b[8] = {
		"  _____     ",
		" ||    \\\\   ",
		" ||     ||  ",
		" ||____//   ",
		" ||    \\\\   ",
		" ||     ||  ",
		" ||____//   ",
		"            "
	};
	// C
	const std::string label_c[8] = {
		"   ______   ",
		"  / _____|  ",
		" //         ",
		" ||         ",
		" ||         ",
		" \\\\______   ",
		"  \\______|  ",
		"            "
	};
	// D
	const std::string label_d[8] = {
		"  ______    ",
		" ||     \\\\  ",
		" ||      \\\\ ",
		" ||      || ",
		" ||      || ",
		" ||      // ",
		" ||_____//  ",
		"            "
	};
	// E
	// Couldn't find a good way to get this to match the other letters' heights without it looking wonky
	const std::string label_e[8] = {
		"            ",
		"   _______  ",
		"  |  _____| ",
		"  | |_____  ",
		"  |  _____| ",
		"  | |_____  ",
		"  |_______| ",
		"            "
	};
	// F
	const std::string label_f[8] = {
		"   _______  ",
		"  |  _____| ",
		"  | |_____  ",
		"  |  _____| ",
		"  | |       ",
		"  | |       ",
		"  |_|       ",
		"            "
	};
	// G
	const std::string label_g[8] = {
		"    ______  ",
		"   / _____| ",
		"  / /       ",
		" / /   ___  ",
		" | |  |__ | ",
		"  \\ \\___| | ",
		"   \\______/ ",
		"            "
	};
	// H
	const std::string label_h[8] = {
		"  __    __  ",
		" |  |  |  | ",
		" |  |__|  | ",
		" |        | ",
		" |   __   | ",
		" |  |  |  | ",
		" |__|  |__| ",
		"            "
	};
	/****************************************************************************
	* set_board_square
	*
	* - creates an instance of the Board_Square class based off of the input 
	* parameters and places it in the specified square in the board array
	*
	* Parameters :
	* - in_board_color : the color of the square being created/placed
	* - in_piece_color : the color of the piece being placed within the square
	*	- can be Chess_Side::EMPTY if there is no piece
	* - in_piece_type : the type of the piece being placed within the square
	*	- can be Chess_Side::EMPTY if there is no piece
	* - prev_move : indicates whether the piece being placed within the square has
	* been moved from its starting location yet
	*	- value doesn't matter if there isn't a piece
	* - row : the row where the square is to be placed within the board array
	* - col : the column where the square is to be placed within the board array
	* 
	* Returns :
	* - none
	****************************************************************************/
	void set_board_square(Chess_Side in_board_color, Chess_Side in_piece_color, 
		Chess_Piece_Type in_piece_type, bool prev_move, uint8_t row, uint8_t col)
	{
		// should we call a destructor here for the previous instance of the Board_Square?-> is that needed since we're using smart pointers?
		board[row_and_col_to_index(row, col)] = Board_Square(in_board_color, in_piece_color, in_piece_type, prev_move);
	}
	/****************************************************************************
	* move_piece
	*
	* - moves a piece from the source square to the destination square
	* - if the source square is empty, an assert is triggered
	* - if the destination square has a piece in it, it will be overwritten
	*
	* Parameters :
	* - real_move : indicates whether this move should alter the value of the piece's
	* has_moved data member
	*	- actual moves performed by players (real moves) change this value to true 
		if it was previously set to false
		- virtual moves performed by the classes functions to complete various tasks 
		do not alter the has_moved data member of the piece
	* - src_row : the source row of the piece being moved
	* - src_col : the source column of the piece being moved
	* - dest_row : the destination row of the piece being moved
	* - dest_col : the destination column of the piece being moved
	*
	* Returns :
	* - none
	****************************************************************************/
	void move_piece(bool real_move, uint8_t src_row, uint8_t src_col, uint8_t dest_row, uint8_t dest_col)
	{
		Board_Square src_square = get_board_square_info(src_row, src_col);

		assert(src_square.is_occupied());
		
		bool has_moved_new = real_move || src_square.get_piece_moved(); // if the piece has already been moved OR if this is a move for real

		// set the destination square with the source square's piece info, as well as the normal stuff
		set_board_square(black_white_helper(dest_row, dest_col), src_square.get_square_side(), src_square.get_square_piece(), has_moved_new, dest_row, dest_col); // set the destination square
		// then set the source square to be empty
		set_board_square(black_white_helper(src_row, src_col), Chess_Side::EMPTY, Chess_Piece_Type::EMPTY, false, src_row, src_col);
	}
	/****************************************************************************
	* insert_piece
	*
	* - creates a piece and places it in the specified square on the board
	* - acts as a wrapper for the set_board_square function
	*
	* Parameters :
	* - row : the destination row of the piece being moved
	* - col : the destination column of the piece being moved
	* - in_piece_color : the color of the piece being placed within the square
	* - in_piece_type : the type of the piece being placed within the square
	* - prev_move : indicates whether the piece being placed within the square has
	* been moved from its starting location yet
	*
	* Returns :
	* - none
	****************************************************************************/
	void insert_piece(uint8_t row, uint8_t col, Chess_Side in_piece_color, Chess_Piece_Type in_piece_type, bool prev_move)
	{
		assert(in_piece_color != Chess_Side::EMPTY);
		assert(in_piece_type != Chess_Piece_Type::EMPTY);
		set_board_square(black_white_helper(row, col), in_piece_color, in_piece_type, prev_move, row, col);
	}
	/****************************************************************************
	* clear_piece
	*
	* - removes a piece from the specified square by placing an empty piece in 
	* its place
	* - acts as a wrapper for the insert_piece function
	*
	* Parameters :
	* - row : the destination row of the piece being moved
	* - col : the destination column of the piece being moved
	*
	* Returns :
	* - none
	****************************************************************************/
	void clear_piece(uint8_t row, uint8_t col)
	{
		insert_piece(row, col, Chess_Side::EMPTY, Chess_Piece_Type::EMPTY, false);
	}
	/****************************************************************************
	* row_and_col_to_index
	*
	* - translates the internal row and col index (1-8 x 1-8 labeling) to the 
	* actual index in the board array
	*
	* Parameters :
	* - row : the destination row of the piece being moved
	* - col : the destination column of the piece being moved
	*
	* Returns :
	* - uint8_t : the index in the board array for the specified row, col square
	****************************************************************************/
	uint8_t row_and_col_to_index(uint8_t row, uint8_t col) const
	{
		assert(row >= 1 && row <= 8);
		assert(col >= 1 && col <= 8);

		return ((row - 1) * num_cols) + (col - 1);
	}
	/****************************************************************************
	* get_pawn_dir
	*
	* - gives a signed indication of the correct direction for a pawn to move 
	* depending on its side
	* - matches the change in row number for a given pawn move in the correct 
	* direction (destination row = source_row + pawn_dir)
	*
	* Parameters :
	* - curr_side : the side of the pawn direction in question
	*
	* Returns :
	* - int8_t : the direction of the correct vertical pawn movement for the 
	* specified side
	*	- -1 for white pawns moving "up" the board
	*	- +1 for black pawns moving "down" the board
	****************************************************************************/
	int8_t get_pawn_dir(Chess_Side curr_side)
	{
		assert(curr_side != Chess_Side::EMPTY);
		return curr_side == Chess_Side::White ? white_pawn_dir : black_pawn_dir;
	}
	/****************************************************************************
	* is_threatening
	*
	* - indicates whether the specified side is threatening (could legally attack) 
	* the specified target square
	*
	* Parameters :
	* - attacking_side : the side potentially threatening the target square
	* - target_row : the row of the target square 
	* - target_col : the column of the target square
	*
	* Returns :
	* - bool : true if the attacking side is threatening the target square, false
	* otherwise
	****************************************************************************/
	bool is_threatening(Chess_Side attacking_side, uint8_t target_row, uint8_t target_col)
	{
		assert(attacking_side != Chess_Side::EMPTY);

		bool dumby_castle_flag;
		bool dumby_prom_flag;
		uint8_t dumby_capt_row;
		uint8_t dumby_capt_col;
		for (uint8_t curr_row = 1; curr_row <= num_rows; curr_row++)
		{
			for (uint8_t curr_col = 1; curr_col <= num_cols; curr_col++)
			{
				if (Chess_Piece::opposite_sides(Chess_Piece::get_opposite_side(attacking_side), get_board_square_info(curr_row, curr_col).get_square_side()))
				{
					if (simple_move_check(attacking_side, curr_row, curr_col, target_row, target_col, &dumby_capt_row, &dumby_capt_col, &dumby_castle_flag, &dumby_prom_flag, false))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	/****************************************************************************
	* simple_move_check
	*
	* - verifies that the specified move can be physically performed by the piece 
	* in the source square
	* - performs a lot of the work for the check_move function
	*
	* Parameters :
	* - curr_turn : the side executing the move in question
	* - src_row : the source row of the piece being moved
	* - src_col : the source column of the piece being moved
	* - dest_row : the destination row of the piece being moved
	* - dest_col : the destination column of the piece being moved
	* - capt_row : used to indicate to the caller when a piece is captured that is 
	* in a different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the row of the captured piece
	*	- (only happens with an "en-passant" move)
	* - capt_col : used to indicate to the caller when a piece is captured that is 
	* in a different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the column of the captured piece
	*	- (only happens with an "en-passant" move)
	* - castling_out : used to indicate to the caller whether a castling maneuver was 
	* sucessfully initiated (the king was moved two squares towards a rook)
	* - prom_out : used to indicate to the caller whether a pawn promotion is in order
	* - castling_in :  used to indicate to the function whether the second "leg" 
	* of a castling maneuver is required (king has been moved, now time for the rook)
	*
	* Returns :
	* - bool : true if the given move is legal, false otherwise
	****************************************************************************/
	bool simple_move_check(Chess_Side curr_turn, uint8_t src_row, uint8_t src_col, uint8_t dest_row, uint8_t dest_col, 
		uint8_t* capt_row, uint8_t* capt_col, bool* castling_out, bool* prom_out, bool castling_in = false)
	{
		assert(curr_turn != Chess_Side::EMPTY);

		// calculate some useful values first...
		int8_t up_down = dest_row - src_row; // positive means moving down, negative means moving up (unfortunate internal row order convention I don't feel like changing now)
		int8_t left_right = dest_col - src_col; // positive means moving right, negative means moving left
		uint8_t delta = std::abs(up_down) > std::abs(left_right) ? std::abs(up_down) : std::abs(left_right); // max displacement out of both directions
		int8_t dir_up_down = up_down == 0 ? 0 : (up_down > 0 ? 1 : -1); // merely indicates direction (or lack-thereof)
		int8_t dir_left_right = left_right == 0 ? 0 : (left_right > 0 ? 1 : -1); // ^

		uint8_t castling_row = get_castling_row(curr_turn); // if it's a castling move, this is the row in which it should take place

		Board_Square src_square = get_board_square_info(src_row, src_col);
		Board_Square dest_square = get_board_square_info(dest_row, dest_col);
		Chess_Piece_Type src_piece = src_square.get_square_piece();
		
		// still want this in here, even though it's checked within the check_move function
		if (src_square.get_square_side() != curr_turn)
		{
			return false;
		}

		// huge mess, this is where most/ all of the bugs are
		// en-passant move is allowed, but piece is not captured
		switch (src_piece) {
		case Chess_Piece_Type::Pawn:
			// just moving forward, non capture
			if (src_col == dest_col)
			{
				// normal "1-forward" move
				if (dest_row == src_row + get_pawn_dir(curr_turn))
				{
					// space must be unoccupied
					if (!dest_square.is_occupied())
					{
						// a pawn reaching the opposite end of the board means that pawn gets promoted
						if ((curr_turn == Chess_Side::White && dest_row == white_prom_row)
							|| (curr_turn == Chess_Side::Black && dest_row == black_prom_row))
						{
							*prom_out = true;
							return true;
						}
						else // otherwise the non-promotion, default case
						{
							return true;
						}
					}
					else
					{
						return false;
					}

				}
				// "2-forward" move allowed as pawn's first move
				else if (dest_row == (int8_t)src_row +
					(2 * get_pawn_dir(curr_turn))) // casting on src_row necessary here?
				{
					// a pawn can only move two spaces in its first move
					if (!src_square.get_piece_moved())
					{
						// intermediate square must be unoccupied
						if (!get_board_square_info(dest_row - get_pawn_dir(curr_turn), dest_col).is_occupied())
						{
							// dest square must be unoccupied as well
							if (!dest_square.is_occupied())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}

					}
					else
					{
						return false;
					}
				}
				// otherwise the move is illegal
				else
				{
					return false;
				}
			}
			// otherwise it may be a "sideways" capture move, or "en passant"
			else if (std::abs(left_right) == 1)
			{
				// first make sure the pawn is moving in the correct direction
				if (dest_row != (int8_t)src_row + get_pawn_dir(curr_turn)) // casting on src_row necessary here?
				{
					return false;
				}
				// if you're attacking, it's a piece on the other side
				if (Chess_Piece::opposite_sides(dest_square.get_square_side(), curr_turn))
				{
					return true;
				}
				// otherwise maybe it's an "en passant"
				else if (!dest_square.is_occupied())// destination square must be empty
				{
					// a pawn of the opposite side must be in the spot directly behind the destination square of the moved pawn
					if (get_board_square_info(dest_row - get_pawn_dir(curr_turn), dest_col).get_square_piece() == Chess_Piece_Type::Pawn) // is a pawn
					{
						if (Chess_Piece::opposite_sides(get_board_square_info(dest_row - get_pawn_dir(curr_turn), dest_col).get_square_side(), curr_turn)) // pawn is on opposite side
						{ 
							// finally, make sure that the pawn being captured moved to that spot just last turn
							std::array<Board_Square, 64> last_state = get_past_game_state(2); // grab the board state from 1 move back
							bool is_pawn = last_state[row_and_col_to_index(dest_row + get_pawn_dir(curr_turn), dest_col)].get_square_piece() == Chess_Piece_Type::Pawn; // there was a pawn just moved out of its starting square
							bool pawn_moved = last_state[row_and_col_to_index(dest_row + get_pawn_dir(curr_turn), dest_col)].get_piece_moved(); // and it hadn't been moved before
							if (is_pawn && !pawn_moved)
							{
								// need to indicate which pawn to capture
								*capt_row = dest_row - get_pawn_dir(curr_turn); 
								*capt_col = dest_col;
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			break;
		case Chess_Piece_Type::Bishop:
			// quick check for a dumb edge case
			if ((dest_row == src_row) || (dest_col == src_col))
			{
				return false;
			}

			// make sure they actually moved in a 1-1 diagonal
			if (std::abs(up_down) != std::abs(left_right))
			{
				return false;
			}

			// next make sure the path was clear up until the destination square
			for (int8_t offset = 1; offset < delta; offset++)
			{
				if (get_board_square_info(src_row + (offset * dir_up_down), src_col + (offset * dir_left_right)).is_occupied())
				{
					return false;
				}
			}

			// if we've gotten to this point the move is legal
			return true;
			break;
		case Chess_Piece_Type::Knight:
			if ((std::abs(up_down) == 2 && std::abs(left_right) == 1) // that famous "L" movement pattern that everyone knows and loves
				|| (std::abs(up_down) == 1 && std::abs(left_right) == 2))
			{
				return true;
			}
			else // not that famous "L" movement pattern that everyone knows and loves
			{
				return false;
			}

			break;
		case Chess_Piece_Type::Rook:
			// - if this is the second leg of a castling move
			// - we'll assume the first call to this function (in which the king was moved)
			// made sure that everything was legal, so we'll make sure they're actually moving 
			// the rook to the correct square and enact the move
			if (castling_in)
			{
				// see which side the king was moved towards, and then move the corresponding rook to the other side of the king
					// determine if the castling was done to the kingside or queenside
				if (get_board_square_info(castling_row, 7).get_square_piece() == Chess_Piece_Type::King) // king side castling
				{
					if (src_row == castling_row && src_col == 8)
					{
						if (dest_row == castling_row && dest_col == 6)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else if (get_board_square_info(castling_row, 3).get_square_piece() == Chess_Piece_Type::King) // queen side castling
				{
					if (src_row == castling_row && src_col == 1)
					{
						if (dest_row == castling_row && dest_col == 4)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else // we should never reach this
				{
					return false;
				}
			}
			else // normal movement otherwise
			{
				if ((src_col == dest_col) || (src_row == dest_row)) // up-down/ side-to-side movement
				{
					// next make sure the path was clear up until the destination square
					for (int8_t offset = 1; offset < delta; offset++)
					{
						if (get_board_square_info(src_row + (offset * dir_up_down), src_col + (offset * dir_left_right)).is_occupied())
						{
							return false;
						}
					}

					return true;
				}
				else
				{
					return false;
				}
			}
			break;
		case Chess_Piece_Type::Queen:
			if ((src_col == dest_col) || (src_row == dest_row)) // up-down/ side-to-side movement
			{
				// next make sure the path was clear up until the destination square
				for (int8_t offset = 1; offset < delta; offset++)
				{
					if (get_board_square_info(src_row + (offset * dir_up_down), src_col + (offset * dir_left_right)).is_occupied())
					{
						return false;
					}
				}

				return true;
			}
			else if (std::abs(up_down) == std::abs(left_right)) // diagonal movement
			{
				// next make sure the path was clear up until the destination square
				for (int8_t offset = 1; offset < delta; offset++)
				{
					if (get_board_square_info(src_row + (offset * dir_up_down), src_col + (offset * dir_left_right)).is_occupied())
					{
						return false;
					}
				}

				return true;
			}
			else // anything else is illegal
			{
				return false;
			}
			break;
		case Chess_Piece_Type::King:
			if ((std::abs(up_down) <= 1) && (std::abs(left_right) <= 1))
			{
				return true;
			}
			// castling
				// determine which rook is being castled
				// make sure the rook and king haven't been moved yet
				// no pieces between the two
				// king isn't in check rn
				// none of the king's intermediate squares are under attack
			else if (!src_square.get_piece_moved()) // king hasn't been moved yet
			{
				// determine if we're doing king or queen-side castling
				uint8_t rook_col;
				Board_Square target_rook_square;
				if (dest_row == castling_row && dest_col == 7) // king side castling
				{
					target_rook_square = get_board_square_info(castling_row, 8); // determine which rook is being "castled"
					rook_col = 8;
				}
				else if (dest_row == castling_row && dest_col == 3) // queen side castling
				{
					target_rook_square = get_board_square_info(castling_row, 1); // determine which rook is being "castled"
					rook_col = 1;
				}
				else
				{
					return false;
				}

				if (target_rook_square.get_square_piece() == Chess_Piece_Type::Rook) // make sure there's actually a rook there
				{
					if (target_rook_square.get_square_side() == curr_turn) // and that it's on the correct side
					{
						if (!target_rook_square.get_piece_moved()) // and that it hasn't been moved yet
						{
							if (!get_player_check(curr_turn)) // and the current player isn't in check
							{
								// now we need to check that the intermediate squares are empty
								for (int8_t curr_col = src_col + dir_left_right; curr_col != rook_col; curr_col += dir_left_right)
								{
									if (get_board_square_info(castling_row, curr_col).is_occupied())
									{
										return false;
									}
								}

								// now make sure the king isn't passing over any intermediate squares that are under attack
								for (int8_t curr_col = src_col + dir_left_right; curr_col != rook_col; curr_col += dir_left_right)
								{
									if (is_threatening(Chess_Piece::get_opposite_side(curr_turn), src_row, curr_col))
									{
										return false;
									}
								}

								*castling_out = true;
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
			else
			{
				return false;
			}
			break;
		default:
			return false;
			break;
		}

	}
	/****************************************************************************
	* enact_move
	*
	* - performs a move on the board once it has been deemed legally
	* - moves the appropriate pieces and adds the necessary points to the 
	* appropriate player's score if a piece is captured
	*
	* Parameters :
	* - curr_turn : the side executing the move in question
	* - src_row : the source row of the piece being moved
	* - src_col : the source column of the piece being moved
	* - dest_row : the destination row of the piece being moved
	* - dest_col : the destination column of the piece being moved
	* - capt_row : used to indicate when a piece is captured that is in a 
	* different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the row of the captured piece
	*	- (only happens with an "en-passant" move)
	* - capt_col : used to indicate when a piece is captured that is in a 
	* different location than the dest square 
	*	- its value is 0 if the destination and capture locations are the same
	*	- if they are different, it holds the column of the captured piece
	*	- (only happens with an "en-passant" move)
	*
	* Returns :
	* - none
	****************************************************************************/
	void enact_move(Chess_Side player, uint8_t src_row, uint8_t src_col, 
		uint8_t dest_row, uint8_t dest_col, uint8_t capt_row = 0, uint8_t capt_col = 0)
	{
		// if a piece is being captured, we add it's value to the player's score
		// going to assume all the necessary checking was done before hand and that the piece is on the opposite side
		if (get_board_square_info(dest_row, dest_col).is_occupied())
		{
			modify_player_score(player, get_piece_val(get_board_square_info(dest_row, dest_col).get_square_piece()));
		}
		else if (capt_row != 0) // an en-passant took place, could also test for capt_col != 0
		{
			modify_player_score(player, get_piece_val(get_board_square_info(capt_row, capt_col).get_square_piece()));
			clear_piece(capt_row, capt_col);
		}

		move_piece(true, src_row, src_col, dest_row, dest_col);
	}
	/****************************************************************************
	* set_curr_turn
	*
	* - sets the value of the private data member curr_turn, used to indicate 
	* which player's move it is in the current game
	*
	* Parameters :
	* - curr_turn : the side to set the curr_turn value to
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_curr_turn(Chess_Side turn)
	{
		curr_turn = turn;
	}
	/****************************************************************************
	* flip_curr_turn
	*
	* - sets the value of the private data member curr_turn to the opposite side
	* - used as a wrapper for the set_curr_turn function
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	void flip_curr_turn()
	{
		assert(get_curr_turn() != Chess_Side::EMPTY);
		set_curr_turn(Chess_Piece::get_opposite_side(get_curr_turn()));
	}
	/****************************************************************************
	* clear_player_score
	*
	* - sets the private data member white_score or black_score to 0, depending on 
	* the input
	*
	* Parameters :
	* - player : which player's score to set to 0
	*
	* Returns :
	* - none
	****************************************************************************/
	void clear_player_score(Chess_Side player)
	{
		assert(player != Chess_Side::EMPTY);
		if (player == Chess_Side::White)
		{
			white_score = 0;
			return;
		}
		else
		{
			black_score = 0;
			return;
		}
	}
	/****************************************************************************
	* clear_player_score
	*
	* - modifies the private data member white_score or black_score by a specified 
	* amount
	*
	* Parameters :
	* - player : which player's score to modify
	* - delta_score : the amount to change the specified player's score by
	*
	* Returns :
	* - none
	****************************************************************************/
	void modify_player_score(Chess_Side player, uint8_t delta_score)
	{
		assert(player != Chess_Side::EMPTY);
		if (player == Chess_Side::White)
		{
			white_score += delta_score;
			return;
		}
		else
		{
			black_score += delta_score;
			return;
		}
	}
	/****************************************************************************
	* set_player_check
	*
	* - sets the private data member white_check or black_check
	*
	* Parameters :
	* - player : which player's check status to modify
	* - check_val : the value to set the check status to
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_player_check(Chess_Side player, bool check_val)
	{
		assert(player != Chess_Side::EMPTY);
		if (player == Chess_Side::White)
		{
			white_check = check_val;
		}
		else
		{
			black_check = check_val;
		}
	}
	/****************************************************************************
	* update_player_check
	*
	* - sees if a player is in check, and updates their check variable accordingly
	*
	* Parameters :
	* - player : which player's check status to update
	*
	* Returns :
	* - none
	****************************************************************************/
	void update_player_check(Chess_Side player)
	{
		assert(player != Chess_Side::EMPTY);
		set_player_check(player, is_in_check(player));
	}
	/****************************************************************************
	* update_player_check
	*
	* - adds the current board state to the end of the game_hist vector
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	void add_game_state_hist()
	{
		game_hist.emplace_back(board);
	}
	/****************************************************************************
	* lettered_col_translation
	*
	* - translate the external lettered column labels of the chess board (A-H) to
	* the internal (1-8) labeling scheme
	*
	* Parameters :
	* - col_in : the external column label to be translated
	*
	* Returns :
	* - uint8_t : the translated column label
	****************************************************************************/
	static uint8_t lettered_col_translation(char col_in)
	{
		col_in = toupper(col_in);

		switch (col_in) {
		case 'A':
			return 1;
			break;
		case 'B':
			return 2;
			break;
		case 'C':
			return 3;
			break;
		case 'D':
			return 4;
			break;
		case 'E':
			return 5;
			break;
		case 'F':
			return 6;
			break;
		case 'G':
			return 7;
			break;
		case 'H':
			return 8;
			break;
		default:
			return 0;
			break;
		}
	}
	/****************************************************************************
	* char_to_num
	*
	* - takes in a character and if that character represents a number, translate 
	* it to said number
	* - if the character doesn't represent a number, just return the character's 
	* value back out
	*
	* Parameters :
	* - char_in : the character inputted (hopefully a number)
	*
	* Returns :
	* - uint8_t : the translated character in the form of a number
	****************************************************************************/
	static uint8_t char_to_num(char char_in)
	{
		if (std::isdigit(char_in)) // if it's a number, translate it
		{
			return char_in - '0';
		}
		return char_in; // otherwise, garbage in->garbage out
	}
	/****************************************************************************
	* external_to_internal_row
	*
	* - translates the typical chess board's labeling scheme and translates it to 
	* the class's internal labeling scheme
	*	- unfortunately these schemes run in opposite directions
	*
	* Parameters :
	* - row : the external row label to be translated
	*
	* Returns :
	* - uint8_t : the translated row label
	****************************************************************************/
	static uint8_t external_to_internal_row(uint8_t row)
	{
		switch (row) {
		case 1:
			return 8;
			break;
		case 2:
			return 7;
			break;
		case 3:
			return 6;
			break;
		case 4:
			return 5;
			break;
		case 5:
			return 4;
			break;
		case 6:
			return 3;
			break;
		case 7:
			return 2;
			break;
		case 8:
			return 1;
			break;
		default:
			return 0;
			break;
		}
	}
	/****************************************************************************
	* internal_to_external_row
	*
	* - translates the class's internal row labeling scheme to the typical chess 
	* board's labeling scheme
	*	- unfortunately these schemes run in opposite directions
	* - redundant, but the name helps the code make more sense
	*
	* Parameters :
	* - row : the internal row label to be translated
	*
	* Returns :
	* - uint8_t : the translated row label
	****************************************************************************/
	static uint8_t internal_to_external_row(uint8_t row)
	{
		return external_to_internal_row(row); 
	}
	/****************************************************************************
	* valid_row
	*
	* - checks if the inputted number is a valid row in the class's internal 
	* representation
	*
	* Parameters :
	* - in_row : the row label to be checked
	*
	* Returns :
	* - bool : true if the row is valid, false otherwise
	****************************************************************************/
	bool valid_row(uint8_t in_row)
	{
		if (in_row >= 1 && in_row <= num_rows)
		{
			return true;
		}
		return false;
	}
	/****************************************************************************
	* valid_col
	*
	* - checks if the inputted number is a valid column in the class's internal
	* representation
	*
	* Parameters :
	* - in_col : the row label to be checked
	*
	* Returns :
	* - bool : true if the col is valid, false otherwise
	****************************************************************************/
	bool valid_col(uint8_t in_col)
	{
		if (in_col >= 1 && in_col <= num_cols)
		{
			return true;
		}
		return false;
	}
	/****************************************************************************
	* get_castling_row
	*
	* - returns the row (internal representation) that the given player can 
	* perform a castling manuever within
	*
	* Parameters :
	* - side : the side to be castling
	*
	* Returns :
	* - uint8_t : the row to castle in
	****************************************************************************/
	static uint8_t get_castling_row(Chess_Side side)
	{
		assert(side != Chess_Side::EMPTY);
		return side == Chess_Side::White ? 8 : 1;
	}
	/****************************************************************************
	* black_white_helper
	*
	* - returns whether the specified square should be black or white
	*
	* Parameters :
	* - row : the row of the square in question
	* - col : the column of the square in question
	*
	* Returns :
	* - Chess_Side : the color (Chess_Side::White or Chess_Side::Black) of the 
	* square in question
	****************************************************************************/
	static Chess_Side black_white_helper(uint8_t row, uint8_t col)
	{
		assert(row >= 1 && row <= 8);
		assert(col >= 1 && col <= 8);

		// Odd row, odd col is white
		if ((row % 2 == 1) && (col % 2 == 1))
		{
			return Chess_Side::White;
		}
		// Odd row, even col is black
		else if ((row % 2 == 1) && (col % 2 == 0))
		{
			return Chess_Side::Black;
		}
		// Even row, odd col is black
		else if((row % 2 == 0) && (col % 2 == 1))
		{
			return Chess_Side::Black;
		}
		// Even row, even col is white
		else if ((row % 2 == 0) && (col % 2 == 0))
		{
			return Chess_Side::White;
		}

		// if somehow none of those cases hit we'll return this as garbage
		return Chess_Side::EMPTY;
	}
	/****************************************************************************
	* get_num_layers
	*
	* - returns the number of layers (lines) that our drawing functions utilize 
	* for a given big character/ chess row
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - uint8_t : the number of layers
	****************************************************************************/
	uint8_t get_num_layers() const
	{
		return num_layers;
	}
	/****************************************************************************
	* get_draw_width
	*
	* - returns the draw width (number of characters) that our drawing functions 
	* utilize for a given big character/ chess row
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - uint8_t : the drawing width
	****************************************************************************/
	uint8_t get_draw_width() const
	{
		return draw_width;
	}
	/****************************************************************************
	* get_piece_layer
	*
	* - returns the specified layer of big character representation of the 
	* specified chess piece 
	* - for our drawing functions
	*
	* Parameters :
	* - piece : the chess piece 
	* - side : the chess piece's side
	* - layer : the layer of the piece's big character representation
	*
	* Returns :
	* - std::string : the requested big character layer
	****************************************************************************/
	std::string get_piece_layer(Chess_Piece_Type piece, Chess_Side side, uint8_t layer) const
	{
		assert(layer >= 0 && layer <= 8);

		if (side == Chess_Side::White)
		{
			switch (piece) {
			case Chess_Piece_Type::Pawn:
				return white_pawn[layer];
				break;
			case Chess_Piece_Type::Rook:
				return white_rook[layer];
				break;
			case Chess_Piece_Type::Knight:
				return white_knight[layer];
				break;
			case Chess_Piece_Type::Bishop:
				return white_bishop[layer];
				break;
			case Chess_Piece_Type::Queen:
				return white_queen[layer];
				break;
			case Chess_Piece_Type::King:
				return white_king[layer];
				break;
			default:
				return empty_piece[layer];
				break;
			}
		}
		else if (side == Chess_Side::Black)
		{
			switch (piece) {
			case Chess_Piece_Type::Pawn:
				return black_pawn[layer];
				break;
			case Chess_Piece_Type::Rook:
				return black_rook[layer];
				break;
			case Chess_Piece_Type::Knight:
				return black_knight[layer];
				break;
			case Chess_Piece_Type::Bishop:
				return black_bishop[layer];
				break;
			case Chess_Piece_Type::Queen:
				return black_queen[layer];
				break;
			case Chess_Piece_Type::King:
				return black_king[layer];
				break;
			default:
				return empty_piece[layer];
				break;
			}
		}
		else
		{
			return empty_piece[layer];
		}
	}
	/****************************************************************************
	* draw_ScoreBoard
	* 
	* TO BE REWORKED
	*
	* - draws the "scoreboard" for the current chess game, displaying the scores
	* for each player
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	void draw_scoreboard() const
	{
		printf("%s: %hhu\n", get_player_name(Chess_Side::White).c_str(), get_player_score(Chess_Side::White));
		printf("%s: %hhu\n", get_player_name(Chess_Side::Black).c_str(), get_player_score(Chess_Side::Black));
	}
	/****************************************************************************
	* get_col_label_layer
	*
	* - returns the specified layer of big character representation of the
	* specified column label
	* - for our drawing functions
	*
	* Parameters :
	* - col : the column we want a label for
	* - layer : the layer of the column label's big character representation
	*
	* Returns :
	* - std::string : the requested big character layer
	****************************************************************************/
	std::string get_col_label_layer(uint8_t col, uint8_t layer) const
	{
		assert(col >= 1 && col <= 8);
		assert(layer >= 0 && layer < get_num_layers());

		switch (col) {
		case 1:
			return label_a[layer];
			break;
		case 2:
			return label_b[layer];
			break;
		case 3:
			return label_c[layer];
			break;
		case 4:
			return label_d[layer];
			break;
		case 5:
			return label_e[layer];
			break;
		case 6:
			return label_f[layer];
			break;
		case 7:
			return label_g[layer];
			break;
		case 8:
			return label_h[layer];
			break;
		default: // should never be reached
			return "";
			break;
		}
	}
	/****************************************************************************
	* draw_column_labels
	*
	* - draws the A-H column labels lined up with the board's squares
	*
	* Parameters :
	* - draw_labels : indicates whether to account for space taken up by the row labels
	*
	* Returns :
	* - none
	****************************************************************************/
	void draw_column_labels(bool draw_labels) const
	{
		for (uint8_t layer = 0; layer < get_num_layers(); layer++) // for each layer...
		{
			if (draw_labels)
			{
				printf("            "); // padding to account for the row labels
			}
			for (uint8_t col = 1; col <= num_cols; col++) // for each column
			{
				printf("%s", get_col_label_layer(col, layer).c_str());
			}
			printf("\n");
		}
	}
	/****************************************************************************
	* get_row_label_layer
	*
	* - returns the specified layer of big character representation of the
	* specified row label
	* - for our drawing functions
	*
	* Parameters :
	* - row : the row we want a label for
	* - layer : the layer of the row label's big character representation
	*
	* Returns :
	* - std::string : the requested big character layer
	****************************************************************************/
	std::string get_row_label_layer(uint8_t row, uint8_t layer) const
	{
		assert(row >= 1 && row <= 8);
		assert(layer >= 0 && layer < get_num_layers());

		switch (row) {
		case 1:
			return label_one[layer];
			break;
		case 2:
			return label_two[layer];
			break;
		case 3:
			return label_three[layer];
			break;
		case 4:
			return label_four[layer];
			break;
		case 5:
			return label_five[layer];
			break;
		case 6:
			return label_six[layer];
			break;
		case 7:
			return label_seven[layer];
			break;
		case 8:
			return label_eight[layer];
			break;
		default: // should never be reached
			return "";
			break;
		}
	}
	/****************************************************************************
	* draw_Row
	*
	* - draws a specified row of the board
	*
	* Parameters :
	* - row : the row we want to draw
	* - draw_labels : indicates whether to print the labels (1-8) at the beginning 
	* of each row
	*
	* Returns :
	* - std::string : the requested big character layer
	****************************************************************************/
	void draw_Row(uint8_t row, bool draw_labels) const
	{
		Chess_Piece_Type temp_piece;
		Chess_Side temp_side;
		std::string temp_layer;

		for (uint8_t layer = 0; layer < get_num_layers(); layer++) // for each layer...
		{
			if (draw_labels)
			{
				printf("%s", get_row_label_layer(internal_to_external_row(row), layer).c_str());
			}
			for (uint8_t col = 1; col <= num_cols; col++) // each column in the row
			{
				temp_piece = get_board_square_info(row, col).get_square_piece();
				temp_side = get_board_square_info(row, col).get_square_side();
				temp_layer = get_piece_layer(temp_piece, temp_side, layer);
				for (uint8_t curr = 0; curr < get_draw_width(); curr++) // each character in each square
				{
					if (temp_layer[curr] == (char)0x1A) // 0x1A is interpreted as empty space-> print the underlying square's color
					{
						printf("%c", black_white_helper(row, col) == Chess_Side::White ? 0xDB : 32);
					}
					else // otherwise just print the piece's character
					{
						printf("%c", temp_layer[curr]);
					}
				}
			}
			printf("\n");
		}
	}
	/****************************************************************************
	* draw_Board
	*
	* - draws the current state of the chess board to the console
	*
	* Parameters :
	* - draw_labels : indicates whether to print the row and column lables 
	*	- (1-8 and A-H, respectively)
	*
	* Returns :
	* - none
	****************************************************************************/
	void draw_board(bool draw_labels) const
	{
		draw_scoreboard();

		for (uint8_t row = 1; row <= num_rows; row++)
		{
			draw_Row(row, draw_labels);
		}
		
		draw_column_labels(draw_labels);
	}
};