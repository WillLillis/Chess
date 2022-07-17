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
	Chess_Piece()
	{
		piece = Chess_Piece_Type::EMPTY;
		side = Chess_Side::EMPTY;
		moved = false;
	}
	Chess_Piece(Chess_Piece_Type in_piece, Chess_Side in_side, bool in_moved) : piece(in_piece), side(in_side), moved(in_moved)
	{
	}
	Chess_Piece_Type get_piece_type()
	{
		return piece;
	}
	void set_piece_type(Chess_Piece_Type new_piece_type) 
	{
		piece = new_piece_type;
	}
	Chess_Side get_piece_side()
	{
		return side;
	}
	void set_piece_side(Chess_Side new_side)
	{
		side = new_side;
	}
	bool has_moved() const
	{
		return moved;
	}
	static bool opposite_sides(Chess_Side side1, Chess_Side side2)
	{
		if (side1 == Chess_Side::Black && side2 == Chess_Side::White)
		{
			return true;
		}
		else if (side1 == Chess_Side::White && side2 == Chess_Side::Black)
		{
			return true;
		}
		return false;
	}
	
	//bool check_legal_move(Chess_Piece_Type in_piece, uint8_t src_row, uint8_t src_col, uint8_t dest_row, uint8_t dest_col)
	//{
	//	// pass in all necessary info, even if we're not going to use it? (i.e. board history only needed for en passant)
	//	// best way to do this...?
	//}

private:
	Chess_Piece_Type piece;
	Chess_Side side;
	bool moved;
};


