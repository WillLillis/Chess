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

	//printf("Board test:\n");
	//for (uint8_t row = 1; row <= 8; row++) // rows
	//{
	//	for (uint8_t layer = 0; layer <= 7; layer++) // layers 
	//	{
	//		for (uint8_t col = 1; col <= 8; col++) // cols
	//		{
	//			if (b_w_helper(row, col) == Chess_Side::White)
	//			{
	//				printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
	//			}
	//			else
	//			{
	//				printf("             ");
	//			}
	//		}
	//		if (layer != 7)
	//		{
	//			printf("\n");
	//		}
	//	}
	//	printf("\n");
	//}

	Chess_Board test_board;
	test_board.play_game();

	//printf("Testing Labels:\n");

	//printf("  __    __  "); // 0
	//printf("\n");
	//printf(" |  |  |  | "); // 1
	//printf("\n");
	//printf(" |  |__|  | "); // 2
	//printf("\n");
	//printf(" |        | "); // 3
	//printf("\n");
	//printf(" |   __   | "); // 4
	//printf("\n");
	//printf(" |  |  |  | "); // 5
	//printf("\n");
	//printf(" |__|  |__| "); // 6
	//printf("\n");
	//printf("            "); // 7
	//printf("\n");


	return 0;
}