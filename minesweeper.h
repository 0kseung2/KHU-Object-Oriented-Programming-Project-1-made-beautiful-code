#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void _load_(ofstream&, string, char array[8][8]);
char _touch_(ofstream&, string, char array[8][8], int&);
void _display_(ofstream&, char array[8][8]);

/*_load_함수 시작*************************************************************************************************************************************/
void _load_(ofstream& output_file, string line, char array[8][8]) //test#commands.txt 파일 open -> 첫 문장에서 load와 test#board.txt 분리해서 매개변수에 저장
{
	string board_file;

	board_file = line.substr(5); // board_file에 test#board.txt를 저장한다.
	output_file << "Command: " << line << endl; // load 함수가 실행 되었을 때, output file에 첫줄을 작성해준다. (ex. Command: load test1board.txt)


	// board_file에 저장된 test#board.txt를 open해서 64개의 점들을 하나의 character(dot)에 저장해서 불러오기. (8x8의 2차원배열 만들기 위함)
	char dot;
	ifstream open_board_file; // command 파일에서 test#board.txt를 복사하여 이후 test#board.txt 파일을 열어주기에 ifstream을 두 번 사용하게 된다.
	open_board_file.open(board_file);


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			open_board_file >> dot; // open_board_file.get(dot)으로 문자를 읽어왔을 때는 개행문자 '\n'이 있어서 한칸씩 밀려서 dot에 저장되었다.
			array[i][j] = dot; // 2차원 배열의 각 요소에 board 파일의 요소들을 할당시킨다.

		}
	}
	open_board_file.close();

}
/*_load_함수 끝*******************************************************************************************************************************************/


/*_touch_함수 시작************************************************************************************************************************************/
char _touch_(ofstream& output_file, string line, char array[8][8], int& spaces_touched)
{
	spaces_touched++; // 몇 번 점을 터치하였는지 횟수를 세기 위해 touch 명령(함수)이 실행될 때마다 1씩 더해준다.

	output_file << "Command: " << line << endl; // output file에 요구조건에 맞게 라인을 출력해준다. (ex. Command: touch 6 1)
	// 두번째 라인(x, y)부터 읽기
	int x_coordinate; // 지뢰 board의 x 좌표
	int y_coordinate; // 지뢰 board의 y 좌표
	char bomb = '*'; // 지뢰 모양
	char unopened_bomb = '@'; // 밟지 않은 상태에서 게임 종료가 되었을 때, 표시될 지뢰 모양(불발탄)
	char dot = '.'; // touch가 이루어지지 않은 board의 점
	/*touch 함수에서 지뢰를 밟으면 밟지 않은 지뢰들은 @ 모양으로 바꾸어야 하는데
	보통의 경우라면 상관없지만 완벽히 10개의 지뢰를 피해 54개의 점을 touch하는 경우가 존재하므로
	문제의 요구조건에 맞게 10개의 지뢰를 불발탄으로 표시하기 위해 밟은 지뢰의 값을
	주어진 범위에서 배열의 요소들이 가질 수 없는 값(variables_to_finally_display_as_bomb)으로 설정하여
	이후에 minesweeper 함수에서 추가적으로 밟은 지뢰만 * 모양으로 바꾸어 주는 과정을 거친다*/
	char variables_to_finally_display_as_bomb = 't';

	// command 파일에서 touch 함수를 제외하고 x와 y좌표를 각각 추출하기 위한 과정
	// command 파일에 텍스트가 string이기 때문에 stoi를 사용하여 string type을 int로 바꾸어준다.
	line = line.substr(6);
	x_coordinate = stoi(line.substr(0, line.find(" ")));
	y_coordinate = stoi(line.substr(line.find(" ") + 1, line.length()));


	char num = '0';
	if (array[x_coordinate - 1][y_coordinate - 1] == bomb) // touch한 점이 지뢰인 경우
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (array[i][j] == bomb)
					array[i][j] = unopened_bomb; // 게임 종료 후 밟지 않은 지뢰를 불발탄으로 표시하기 위해 모든 지뢰를 @로 바꾼다.
			}
		}
		// 밟은 지뢰만 다시 *로 바꾸기 위해서 밟은 지뢰를 variables_to_finally_display_as_bomb로 저장한다.
		array[x_coordinate - 1][y_coordinate - 1] = variables_to_finally_display_as_bomb;
		return array[x_coordinate - 1][y_coordinate - 1]; // 지뢰를 밟았을 때, minesweeper 함수에서 while문을 braek하기 위해 return값으로 touch한 점의 모양을 준다.

	}
	else if (array[x_coordinate - 1][y_coordinate - 1] == dot) // 제대로 지뢰를 피해서 밟은 경우
	{
		// 주변 사각형에서 지뢰가 총 몇개가 있는지 찾는 과정
		for (int i = x_coordinate - 2; i <= x_coordinate; i++) // 3가지
		{
			for (int j = y_coordinate - 2; j <= y_coordinate; j++) // 3가지
			{
				if (i >= 0 && i < 8 && j >= 0 && j < 8) // 배열의 범위를 넘어가는 것을 방지하는 조건문, index 0~7에서만 배열이 형성됨.
				{
					if (array[i][j] == bomb) // 만약 본인을 제외한 주변 8개의 칸 중에 지뢰가 있는 경우 1씩 더하기
					{
						num += 1;
					}
				}
			}
		}
		array[x_coordinate - 1][y_coordinate - 1] = num;
		return array[x_coordinate - 1][y_coordinate - 1]; // 지뢰를 밟았을 때, minesweeper 함수에서 while문을 braek하기 위해 return값으로 touch한 점의 모양을 준다.
	}
}
/*_touch_함수 끝******************************************************************************************************************************************/


/*_display_함수 시작*******************************************************************************************************************************/
void _display_(ofstream& output_file, char array[8][8])
{
	// 게임 종료 후의 board 판에는 영향을 주지 않고, 단순히 현재의 보드를 보여주는 display만을 하기 위해 새로운 2차원 배열을 만들다.
	char** just_display_array = new char* [8];
	for (int i = 0; i < 8; i++)
	{
		just_display_array[i] = new char[8];
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			just_display_array[i][j] = array[i][j]; // 새로운 배열에 원래의 배열의 값들을 할당한다.
		}
	}

	char bomb = '*';
	char dot = '.';
	char unopened_bomb = '@';
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// 아직 지뢰를 밟지 않은 상황이기에 array[i][j]가 지뢰이거나, @이 일때만 .으로 바꾸어주고, 숫자이거나 .인 경우는 그대로 출력하면 됨
			if (just_display_array[i][j] == bomb)
			{
				just_display_array[i][j] = dot;
			}
			else if (just_display_array[i][j] == unopened_bomb)
			{
				just_display_array[i][j] = dot;
			}
			output_file << just_display_array[i][j];
		}
		output_file << endl;
	}
	output_file << endl;

	// 메모리 누수를 막기 위해 2차원 동적할당된 배열을 삭제시켜준다.
	for (int i = 0; i < 8; i++)
	{
		delete[] just_display_array[i];
	}
	delete[] just_display_array;
}


/*_display_함수 끝*******************************************************************************************************************************/



/*_minesweeper_함수 시작*******************************************************************************************************************************/
void minesweeper(string commands, string output) //minesweeper 함수를 main함수랑 동일하다고 생각, commands는 command.txt파일, output은 새로 만들 파일
{

	ifstream command_file;
	ofstream output_file;

	command_file.open(commands); // command 파일 읽어오기
	output_file.open(output); // output 파일 생성하기
	char array[8][8]; // 배열
	char bomb = '*'; // 지뢰
	char unopened_bomb = '@'; // 불발탄
	char variables_to_finally_display_as_bomb = 't'; // 최종으로 지뢰로 표시하기 전 지뢰에 할당된 모양
	string line;
	string load_word = "load"; // line에 load 문자(명령어)가 포함되어 있는지 확인하기 위함
	string display_word = "display"; // line에 display 문자(명령어)가 포함되어 있는지 확인하기 위함
	string touch_word = "touch"; // line에 touch 문자(명령어)가 포함되어 있는지 확인하기 위함
	int spaces_touched = 0; // 최종 몇번 touch 되었는지 표시하기 위한 변수
	while (getline(command_file, line)) // 한 줄 한 줄 command 파일을 읽어온다.
	{
		if (line.find(load_word) != std::string::npos) // line에 load가 있으면 load 함수 실행
		{
			_load_(output_file, line, array);
		}
		else if (line.find(touch_word) != std::string::npos) // line에 touch가 있으면 touch 함수 실행
		{
			// 지뢰를 밟았는지 아닌지 확인하여 계속 게임을 진행할지 종료할지 판단하기 위함
			char whether_bomb_or_not = _touch_(output_file, line, array, spaces_touched);
			if (whether_bomb_or_not == variables_to_finally_display_as_bomb)
				break;
		}
		else if (line.find(display_word) != std::string::npos) // line에 display가 있으면 display 함수 실행
		{
			output_file << "Command: " << display_word << endl; // output file에 요구조건에 맞게 라인을 출력해준다. (ex. Command: display)
			_display_(output_file, array);
		}
	}

	// 밟은 지뢰를 * 로 밟지 않은 지뢰를 @ 로 나타내기 위한 코드
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (array[i][j] == bomb)
			{
				array[i][j] = unopened_bomb;
			}
			else if (array[i][j] == variables_to_finally_display_as_bomb)
			{
				array[i][j] = bomb;
			}
		}
	}

	// 최종 출력 되어진는 화면
	output_file << "Game Over" << endl;
	output_file << "~~~~~~~~~" << endl;
	output_file << "Final Board" << endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			output_file << array[i][j];
		}
		output_file << endl;
	}
	output_file << endl;

	output_file << "Spaces touched: " << spaces_touched << endl;

	command_file.close();

}
/*_minesweeper_함수 끝************************************************************************************************************************************/
