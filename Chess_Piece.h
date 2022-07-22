#pragma once


enum class Chess_Piece_Type : char
{
	Pawn = 'P',
	Bishop = 'B',
	Knight = 'k',
	Rook = 'R',
	Queen = 'Q',
	King = 'K',
	EMPTY = ' '
};

enum class Chess_Side : char
{
	White = 'W',
	Black = 'B',
	EMPTY = ' '
};

class Chess_Piece {
public:
	/****************************************************************************
	* Chess_Piece
	*
	* - Default constructor that will simply construct an empty piece that 
	* hasn't moved
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - none
	****************************************************************************/
	Chess_Piece()
	{
		piece = Chess_Piece_Type::EMPTY;
		side = Chess_Side::EMPTY;
		moved = false;
	}
	/****************************************************************************
	* Chess_Piece
	*
	* - Parametrized constructor that will construct a piece according to the 
	* parameters
	*
	* Parameters :
	* - in_piece : the type of piece to construct
	* - in_side : the color of the piece to construct
	* - in_moved : whether or not the given piece has been moved yet
	*
	* Returns :
	* - none
	****************************************************************************/
	Chess_Piece(Chess_Piece_Type in_piece, Chess_Side in_side, bool in_moved) : piece(in_piece), side(in_side), moved(in_moved)
	{
	}
	/****************************************************************************
	* get_piece_type
	*
	* - returns the private data member piece, indicating the type of chess piece
	* 
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Piece_Type : the type of chess piece
	****************************************************************************/
	Chess_Piece_Type get_piece_type() const
	{
		return piece;
	}
	/****************************************************************************
	* set_piece_type
	*
	* - sets the private data member piece, indicating the type of chess piece
	*
	* Parameters :
	* - new_piece_type : the type of chess piece
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_piece_type(Chess_Piece_Type new_piece_type)
	{
		piece = new_piece_type;
	}
	/****************************************************************************
	* get_piece_side
	*
	* - returns the private data member side, indicating the color of the chess 
	* piece
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - Chess_Side : the side of chess piece
	****************************************************************************/
	Chess_Side get_piece_side() const
	{
		return side;
	}
	/****************************************************************************
	* set_piece_side
	*
	* - sets the private data member side, indicating the color of the chess
	* piece
	*
	* Parameters :
	* - new_side : the side of chess piece
	*
	* Returns :
	* - none
	****************************************************************************/
	void set_piece_side(Chess_Side new_side)
	{
		side = new_side;
	}
	/****************************************************************************
	* has_moved
	*
	* - returns the private data member moved, indicating whether the piece has 
	* been moved yet in the current game
	*
	* Parameters :
	* - none
	*
	* Returns :
	* - bool : true if the piece has been moved, false otherwise
	****************************************************************************/
	bool has_moved() const
	{
		return moved;
	}
	/****************************************************************************
	* opposite_sides
	*
	* - indicates whether or not the two sides are opposite of one another
	*
	* Parameters :
	* - side_1 : the first side
	* - side_2 : the second side
	*
	* Returns :
	* - bool : true if the sides are opposites (one white and one black), 
		false otherwise
	****************************************************************************/
	static bool opposite_sides(Chess_Side side_1, Chess_Side side_2)
	{
		if (side_1 == Chess_Side::Black && side_2 == Chess_Side::White)
		{
			return true;
		}
		else if (side_1 == Chess_Side::White && side_2 == Chess_Side::Black)
		{
			return true;
		}
		return false;
	}
	/****************************************************************************
	* get_opposite_side
	*
	* - Returns the opposite side of the one passed in
	*
	* Parameters :
	* - curr_side : the reference side, of which we want the opposite of
	*
	* Returns :
	* - Chess_Side : the opposite side of curr_side
	*	- Chess_Side::Black if Chess_Side::White is passed in
	*	- Chess_Side::White if Chess_Side::Black is passed in
	****************************************************************************/
	static Chess_Side get_opposite_side(Chess_Side curr_side)
	{
		assert(curr_side != Chess_Side::EMPTY);
		return curr_side == Chess_Side::White ? Chess_Side::Black : Chess_Side::White;
	}
private:
	Chess_Piece_Type piece;
	Chess_Side side;
	bool moved;
};


