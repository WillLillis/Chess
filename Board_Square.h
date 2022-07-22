#pragma once
#include<memory>
#include"Chess_Piece.h"

class Board_Square {
public:
	/****************************************************************************
	* Board_Square
	*
	* - Default constructor will simply construct an empty board square of undefined 
	* (Chess_Side::EMPTY) color
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	Board_Square()
	{
		square_color = Chess_Side::EMPTY;
		piece_info = NULL;
	}
	/****************************************************************************
	* Board_Square
	*
	* - Parametrized constructor, creates a board square of the specified color, 
	* with the specified piece inside of it
	*
	* Parameters :
	* - board_color : the color of the board square
	* - piece_side : the color of the chess piece
	*	- can be Chess_Side::EMPTY if there is no piece
	* - piece : the chess piece type to place in the square
	*	- can be Chess_Piece_Type::EMPTY if there is no piece
	* - prev_move : indicates whether the piece being placed within the square has
	* been moved from its starting location yet
	*
	* Returns :
	* - none
	****************************************************************************/
	Board_Square(Chess_Side board_color, Chess_Side piece_side, Chess_Piece_Type piece, bool prev_mov) : square_color(board_color)
	{
		if (piece_side == Chess_Side::EMPTY || piece == Chess_Piece_Type::EMPTY)
		{
			piece_info = NULL;
			return;
		}
		piece_info = std::shared_ptr<Chess_Piece>(new Chess_Piece(piece, piece_side, prev_mov));
	}
	/****************************************************************************
	* get_square_color
	*
	* - returns the private data member square_color 
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Side : the color of the board square of the current class instance
	****************************************************************************/
	Chess_Side get_square_color() const
	{
		return square_color;
	}
	/****************************************************************************
	* set_square_color
	*
	* - sets the private data member square_color 
	*
	* Parameters :
	* - in_color : the color to set the data member to
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_square_color(Chess_Side in_color)
	{
		square_color = in_color;
	}
	/****************************************************************************
	* get_square_piece
	*
	* - returns the type of chess piece held in the current square
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Piece_Type : the piece type in the square
	****************************************************************************/
	Chess_Piece_Type get_square_piece() const
	{
		if (piece_info == NULL)
		{
			return Chess_Piece_Type::EMPTY;
		}
		return piece_info->get_piece_type();
	}
	/****************************************************************************
	* get_square_side
	*
	* - returns the side the piece in that square is on, or empty if the square is empty
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Side : the side (Chess_Side::White or Chess_Side::Black) of the 
	* piece in the square, if there is one
	****************************************************************************/
	Chess_Side get_square_side() const
	{
		if (piece_info == NULL)
		{
			return Chess_Side::EMPTY;
		}
		return piece_info->get_piece_side();
	}
	/****************************************************************************
	* set_square_piece
	*
	* - sets the piece held in the square
	* - spicy smart pointers, modern C++ voodoo magic
	*
	* Parameters :
	* - new_piece : pointer to an already constructed Chess_Piece class instance
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_square_piece(std::shared_ptr<Chess_Piece> new_piece)
	{
		piece_info = new_piece;
	}
	/****************************************************************************
	* set_square_piece
	*
	* - sets the piece held in the square
	* - spicy smart pointers, modern C++ voodoo magic
	*
	* Parameters :
	* - piece_side : the side of the chess piece to place in the square
	* - piece : the type of chess piece to place in the square
	* - prev_move : indicates whether the piece being placed within the square has
	* been moved from its starting location yet
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_square_piece(Chess_Side piece_side, Chess_Piece_Type piece, bool prev_mov)
	{
		piece_info = std::shared_ptr<Chess_Piece>(new Chess_Piece(piece, piece_side, prev_mov));
	}
	/****************************************************************************
	* is_occupied
	*
	* - indicates whether the board square is occupied by a piece
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - bool : true if the square is occupied, and false otherwise
	****************************************************************************/
	bool is_occupied() const
	{
		return (piece_info != NULL);
	}
	/****************************************************************************
	* get_piece_moved
	*
	* - indicates whether the piece within the square has moved yet this game
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - bool : true if the piece has moved, and false otherwise
	****************************************************************************/
	bool get_piece_moved()
	{
		if (piece_info == NULL) // not sure if I want this or an assert
		{
			return false;
		}
		return piece_info->has_moved();
	}

private:
	Chess_Side square_color; // color of the actual square
	std::shared_ptr<Chess_Piece> piece_info; // will always be set to NULL if a space is unoccupied
};