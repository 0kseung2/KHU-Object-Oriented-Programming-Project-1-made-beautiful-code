#include "minesweeper.h"

int main() {
	cout << "Testing minesweeper" << endl;
	minesweeper(".\\test1commands.txt", "test1_output_mine.txt");
	minesweeper(".\\test2commands.txt", "test2_output_mine.txt");
	minesweeper(".\\test3commands.txt", "test3_output_mine.txt");
	minesweeper(".\\test4commands.txt", "test4_output_mine.txt");
	minesweeper(".\\test5commands.txt", "test5_output_mine.txt");
	minesweeper(".\\test6commands.txt", "test6_output_mine.txt");
	minesweeper(".\\test7commands.txt", "test7_output_mine.txt");
	minesweeper(".\\test8commands.txt", "test8_output_mine.txt");
	minesweeper(".\\test9commands.txt", "test9_output_mine.txt");
	minesweeper(".\\test10commands.txt", "test10_output_mine.txt");

	return 0;
}
