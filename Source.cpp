#include"Chess_Board.h"
//#include<stdlib.h>
#include <fcntl.h>
#include<io.h>

Chess_Side b_w_helper(uint8_t row, uint8_t col)
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
	else if ((row % 2 == 0) && (col % 2 == 1))
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

int main(void)
{

	printf("Testing...\n");

	Chess_Board test_board;
	test_board.play_game();

	return 0;
}