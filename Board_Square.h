#pragma once
#include<memory>
#include"Chess_Piece.h"

class Board_Square {
public:
	// Default constructor will simply construct an empty board square of undefined (EMPTY) color
	Board_Square()
	{
		square_color = Chess_Side::EMPTY;
		piece_info = NULL;
	}
	// Parametrized constructor allows caller to specify board square contents, within chess's rules
	Board_Square(Chess_Side board_color, Chess_Side piece_side, Chess_Piece_Type piece, bool prev_mov) : square_color(board_color)
	{
		if (piece_side == Chess_Side::EMPTY || piece == Chess_Piece_Type::EMPTY)
		{
			piece_info = NULL;
			return;
		}
		piece_info = std::shared_ptr<Chess_Piece>(new Chess_Piece(piece, piece_side, prev_mov));
	}
	// returns the color of the square
	Chess_Side get_square_color() const
	{
		return square_color;
	}
	// sets the actual color of the square
	void set_square_color(Chess_Side in_color)
	{
		square_color = in_color;
	}
	// returns the actual piece in that square
	Chess_Piece_Type get_square_piece() const
	{
		if (piece_info == NULL)
		{
			return Chess_Piece_Type::EMPTY;
		}
		return piece_info->get_piece_type();
	}
	// returns the side the piece in that square is on, or empty if the square is empty
	Chess_Side get_square_side() const
	{
		if (piece_info == NULL)
		{
			return Chess_Side::EMPTY;
		}
		return piece_info->get_piece_side();
	}
	// spicy smart pointers, modern C++ voodoo magic
	void set_square_piece(std::shared_ptr<Chess_Piece> new_piece)
	{
		piece_info = new_piece;
	}
	// is there a piece in this square?
	bool is_occupied() const
	{
		return (piece_info != NULL);
	}
	// has the piece in that square been moved yet this game?
	bool get_piece_moved()
	{
		if (piece_info == NULL) // not sure if I want this or an assert
		{
			return false;
		}
		return piece_info->has_moved();
	}

private:
	Chess_Side square_color; 
	std::shared_ptr<Chess_Piece> piece_info; // will always be set to NULL if a space is unoccupied
};