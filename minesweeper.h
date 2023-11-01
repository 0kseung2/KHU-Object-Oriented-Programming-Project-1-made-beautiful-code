#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void _load_(ofstream&, string, char array[8][8]);
char _touch_(ofstream&, string, char array[8][8], int&);
void _display_(ofstream&, char array[8][8]);

/*_load_�Լ� ����*************************************************************************************************************************************/
void _load_(ofstream& output_file, string line, char array[8][8]) //test#commands.txt ���� open -> ù ���忡�� load�� test#board.txt �и��ؼ� �Ű������� ����
{
	string board_file;

	board_file = line.substr(5); // board_file�� test#board.txt�� �����Ѵ�.
	output_file << "Command: " << line << endl; // load �Լ��� ���� �Ǿ��� ��, output file�� ù���� �ۼ����ش�. (ex. Command: load test1board.txt)


	// board_file�� ����� test#board.txt�� open�ؼ� 64���� ������ �ϳ��� character(dot)�� �����ؼ� �ҷ�����. (8x8�� 2�����迭 ����� ����)
	char dot;
	ifstream open_board_file; // command ���Ͽ��� test#board.txt�� �����Ͽ� ���� test#board.txt ������ �����ֱ⿡ ifstream�� �� �� ����ϰ� �ȴ�.
	open_board_file.open(board_file);


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			open_board_file >> dot; // open_board_file.get(dot)���� ���ڸ� �о���� ���� ���๮�� '\n'�� �־ ��ĭ�� �з��� dot�� ����Ǿ���.
			array[i][j] = dot; // 2���� �迭�� �� ��ҿ� board ������ ��ҵ��� �Ҵ��Ų��.

		}
	}
	open_board_file.close();

}
/*_load_�Լ� ��*******************************************************************************************************************************************/


/*_touch_�Լ� ����************************************************************************************************************************************/
char _touch_(ofstream& output_file, string line, char array[8][8], int& spaces_touched)
{
	spaces_touched++; // �� �� ���� ��ġ�Ͽ����� Ƚ���� ���� ���� touch ���(�Լ�)�� ����� ������ 1�� �����ش�.

	output_file << "Command: " << line << endl; // output file�� �䱸���ǿ� �°� ������ ������ش�. (ex. Command: touch 6 1)
	// �ι�° ����(x, y)���� �б�
	int x_coordinate; // ���� board�� x ��ǥ
	int y_coordinate; // ���� board�� y ��ǥ
	char bomb = '*'; // ���� ���
	char unopened_bomb = '@'; // ���� ���� ���¿��� ���� ���ᰡ �Ǿ��� ��, ǥ�õ� ���� ���(�ҹ�ź)
	char dot = '.'; // touch�� �̷������ ���� board�� ��
	/*touch �Լ����� ���ڸ� ������ ���� ���� ���ڵ��� @ ������� �ٲپ�� �ϴµ�
	������ ����� ��������� �Ϻ��� 10���� ���ڸ� ���� 54���� ���� touch�ϴ� ��찡 �����ϹǷ�
	������ �䱸���ǿ� �°� 10���� ���ڸ� �ҹ�ź���� ǥ���ϱ� ���� ���� ������ ����
	�־��� �������� �迭�� ��ҵ��� ���� �� ���� ��(variables_to_finally_display_as_bomb)���� �����Ͽ�
	���Ŀ� minesweeper �Լ����� �߰������� ���� ���ڸ� * ������� �ٲپ� �ִ� ������ ��ģ��*/
	char variables_to_finally_display_as_bomb = 't';

	// command ���Ͽ��� touch �Լ��� �����ϰ� x�� y��ǥ�� ���� �����ϱ� ���� ����
	// command ���Ͽ� �ؽ�Ʈ�� string�̱� ������ stoi�� ����Ͽ� string type�� int�� �ٲپ��ش�.
	line = line.substr(6);
	x_coordinate = stoi(line.substr(0, line.find(" ")));
	y_coordinate = stoi(line.substr(line.find(" ") + 1, line.length()));


	char num = '0';
	if (array[x_coordinate - 1][y_coordinate - 1] == bomb) // touch�� ���� ������ ���
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (array[i][j] == bomb)
					array[i][j] = unopened_bomb; // ���� ���� �� ���� ���� ���ڸ� �ҹ�ź���� ǥ���ϱ� ���� ��� ���ڸ� @�� �ٲ۴�.
			}
		}
		// ���� ���ڸ� �ٽ� *�� �ٲٱ� ���ؼ� ���� ���ڸ� variables_to_finally_display_as_bomb�� �����Ѵ�.
		array[x_coordinate - 1][y_coordinate - 1] = variables_to_finally_display_as_bomb;
		return array[x_coordinate - 1][y_coordinate - 1]; // ���ڸ� ����� ��, minesweeper �Լ����� while���� braek�ϱ� ���� return������ touch�� ���� ����� �ش�.

	}
	else if (array[x_coordinate - 1][y_coordinate - 1] == dot) // ����� ���ڸ� ���ؼ� ���� ���
	{
		// �ֺ� �簢������ ���ڰ� �� ��� �ִ��� ã�� ����
		for (int i = x_coordinate - 2; i <= x_coordinate; i++) // 3����
		{
			for (int j = y_coordinate - 2; j <= y_coordinate; j++) // 3����
			{
				if (i >= 0 && i < 8 && j >= 0 && j < 8) // �迭�� ������ �Ѿ�� ���� �����ϴ� ���ǹ�, index 0~7������ �迭�� ������.
				{
					if (array[i][j] == bomb) // ���� ������ ������ �ֺ� 8���� ĭ �߿� ���ڰ� �ִ� ��� 1�� ���ϱ�
					{
						num += 1;
					}
				}
			}
		}
		array[x_coordinate - 1][y_coordinate - 1] = num;
		return array[x_coordinate - 1][y_coordinate - 1]; // ���ڸ� ����� ��, minesweeper �Լ����� while���� braek�ϱ� ���� return������ touch�� ���� ����� �ش�.
	}
}
/*_touch_�Լ� ��******************************************************************************************************************************************/


/*_display_�Լ� ����*******************************************************************************************************************************/
void _display_(ofstream& output_file, char array[8][8])
{
	// ���� ���� ���� board �ǿ��� ������ ���� �ʰ�, �ܼ��� ������ ���带 �����ִ� display���� �ϱ� ���� ���ο� 2���� �迭�� �����.
	char** just_display_array = new char* [8];
	for (int i = 0; i < 8; i++)
	{
		just_display_array[i] = new char[8];
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			just_display_array[i][j] = array[i][j]; // ���ο� �迭�� ������ �迭�� ������ �Ҵ��Ѵ�.
		}
	}

	char bomb = '*';
	char dot = '.';
	char unopened_bomb = '@';
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// ���� ���ڸ� ���� ���� ��Ȳ�̱⿡ array[i][j]�� �����̰ų�, @�� �϶��� .���� �ٲپ��ְ�, �����̰ų� .�� ���� �״�� ����ϸ� ��
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

	// �޸� ������ ���� ���� 2���� �����Ҵ�� �迭�� ���������ش�.
	for (int i = 0; i < 8; i++)
	{
		delete[] just_display_array[i];
	}
	delete[] just_display_array;
}


/*_display_�Լ� ��*******************************************************************************************************************************/



/*_minesweeper_�Լ� ����*******************************************************************************************************************************/
void minesweeper(string commands, string output) //minesweeper �Լ��� main�Լ��� �����ϴٰ� ����, commands�� command.txt����, output�� ���� ���� ����
{

	ifstream command_file;
	ofstream output_file;

	command_file.open(commands); // command ���� �о����
	output_file.open(output); // output ���� �����ϱ�
	char array[8][8]; // �迭
	char bomb = '*'; // ����
	char unopened_bomb = '@'; // �ҹ�ź
	char variables_to_finally_display_as_bomb = 't'; // �������� ���ڷ� ǥ���ϱ� �� ���ڿ� �Ҵ�� ���
	string line;
	string load_word = "load"; // line�� load ����(��ɾ�)�� ���ԵǾ� �ִ��� Ȯ���ϱ� ����
	string display_word = "display"; // line�� display ����(��ɾ�)�� ���ԵǾ� �ִ��� Ȯ���ϱ� ����
	string touch_word = "touch"; // line�� touch ����(��ɾ�)�� ���ԵǾ� �ִ��� Ȯ���ϱ� ����
	int spaces_touched = 0; // ���� ��� touch �Ǿ����� ǥ���ϱ� ���� ����
	while (getline(command_file, line)) // �� �� �� �� command ������ �о�´�.
	{
		if (line.find(load_word) != std::string::npos) // line�� load�� ������ load �Լ� ����
		{
			_load_(output_file, line, array);
		}
		else if (line.find(touch_word) != std::string::npos) // line�� touch�� ������ touch �Լ� ����
		{
			// ���ڸ� ��Ҵ��� �ƴ��� Ȯ���Ͽ� ��� ������ �������� �������� �Ǵ��ϱ� ����
			char whether_bomb_or_not = _touch_(output_file, line, array, spaces_touched);
			if (whether_bomb_or_not == variables_to_finally_display_as_bomb)
				break;
		}
		else if (line.find(display_word) != std::string::npos) // line�� display�� ������ display �Լ� ����
		{
			output_file << "Command: " << display_word << endl; // output file�� �䱸���ǿ� �°� ������ ������ش�. (ex. Command: display)
			_display_(output_file, array);
		}
	}

	// ���� ���ڸ� * �� ���� ���� ���ڸ� @ �� ��Ÿ���� ���� �ڵ�
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

	// ���� ��� �Ǿ����� ȭ��
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
/*_minesweeper_�Լ� ��************************************************************************************************************************************/
