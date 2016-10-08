#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int MAX_WIDTH_LABYRINTH = 102;
const int MAX_HEIGHT_LABYRINTH = 102;

using namespace std;
typedef array <array <char, MAX_WIDTH_LABYRINTH>, MAX_HEIGHT_LABYRINTH> LabyrinthChar;
typedef array <array <int, MAX_WIDTH_LABYRINTH>, MAX_HEIGHT_LABYRINTH> LabyrinthInt;

struct Size
{
	size_t width = 0;
	size_t height = 0;
};

struct Coordinates
{
	size_t i = 0;
	size_t j = 0;
};

void PrintLabyrinth(ofstream & output, LabyrinthChar & labyrinth, const Size & size)
{
	for (size_t i = 0; i < size.height; ++i)
	{
		for (size_t j = 0; j < size.width; ++j)
		{
			output << labyrinth[i][j];
		}
		output << "\n";
	}
}

void InitLabyrinth(LabyrinthInt & labyrinth)
{
	for (size_t i = 0; i < MAX_HEIGHT_LABYRINTH; ++i)
	{
		for (size_t j = 0; j < MAX_WIDTH_LABYRINTH; ++j)
		{
			labyrinth[i][j] = -1;
		}
	}
}

void InitLabyrinth(LabyrinthChar & labyrinth)
{
	for (size_t i = 0; i < MAX_HEIGHT_LABYRINTH; ++i)
	{
		for (size_t j = 0; j < MAX_WIDTH_LABYRINTH; ++j)
		{
			labyrinth[i][j] = ' ';
		}
	}
}

void ConvertLabyrintIntToChar(LabyrinthChar & labyrinth, LabyrinthInt & labyrinthInt, Size & size)
{
	for (size_t i = 0; i < size.height; ++i)
	{
		for (size_t j = 0; j < size.width; ++j)
		{
			switch (labyrinth[i][j])
			{
				case '#': 
					labyrinth[i + 1][j + 1] = -1;
					break;
				case ' ':
					labyrinth[i + 1][j + 1] = 0;
					break;
			}
		}
	}
}

void GetStartAndFinishCoordinate(LabyrinthChar & labyrinth, Size & size, Coordinates & startPoint, Coordinates & finishPoint)
{
	for (size_t i = 0; i < size.height; ++i)
	{
		for (size_t j = 0; j < size.width; ++j)
		{
			if ((labyrinth[i][j] == 'A') || (labyrinth[i][j] == 'B'))
			{
				if ((startPoint.i == 0) && (startPoint.j == 0))
				{
					startPoint.i = i + 1;
					startPoint.j = j + 1;
				}
				else
				{
					finishPoint.i = i + 1;
					finishPoint.j = j + 1;
				}
			}
		}
	}
}

bool FindWay(LabyrinthInt & labyrinth, Size & size, Coordinates finalPoint)
{
	size_t currentNumber = 1;
	bool isIteration = false;
	while ((labyrinth[finalPoint.i][finalPoint.j] == 0) && (!isIteration))
	{
		isIteration = true;
		for (size_t i = 1; i <= size.height; ++i)
		{
			for (size_t j = 1; j <= size.width; ++j)
			{
				if (labyrinth[i][j] == currentNumber)
				{
					++currentNumber;
					if (labyrinth[i + 1][j] == 0)
					{
						labyrinth[i + 1][j] = currentNumber;
						isIteration = false;
					}
					if (labyrinth[i - 1][j] == 0)
					{
						labyrinth[i - 1][j] = currentNumber;
						isIteration = false;
					}
					if (labyrinth[i][j + 1] == 0)
					{
						labyrinth[i][j + 1] = currentNumber;
						isIteration = false;
					}
					if (labyrinth[i][j - 1] == 0)
					{
						labyrinth[i][j - 1] = currentNumber;
						isIteration = false;
					}
				}
			}
		}
	}

	if (isIteration)
	{
		return false;
	}

	return true;
}

bool FindWayLabyrinth(LabyrinthChar & labyrinth, Size & labyrinthSize)
{
	LabyrinthInt  labyrinthInt;
	Coordinates startPoint;
	Coordinates finishPoint;
	InitLabyrinth(labyrinthInt);
	ConvertLabyrintIntToChar(labyrinth, labyrinthInt, labyrinthSize);
	GetStartAndFinishCoordinate(labyrinth, labyrinthSize, startPoint, finishPoint);
	labyrinthInt[startPoint.i][startPoint.j] = 1;
	if (!FindWay(labyrinthInt, labyrinthSize, finishPoint))
	{
		return false;
	}

	return true;
}

bool CanReadLabyrinthFromFile(ifstream & input, LabyrinthChar & labyrinth, Size & size)
{
	string line;
	size_t i = 0;
	int countPoint = 0;
	while (getline(input, line))
	{
		if (i > 100)
		{
			return false;
		}
		if (size.width < line.size())
		{
			size.width = line.size();
			if (size.width > 100)
			{
				return false;
			}
		}
		for (size_t j = 0; j < size.width; ++j)
		{
			if ((line[j] == 'A') || (line[j] == 'B') || (line[j] == '#') || (line[j] == ' '))
			{
				labyrinth[i][j] = line[j];
				if ((labyrinth[i][j] == 'A') || (labyrinth[i][j] == 'B'))
				{
					++countPoint;
				}
			} 
			else
			{
				return false;
			}
			
		}
		++i;
	}
	size.height = i;

	if (countPoint != 2)
	{
		return false;
	}

	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: labyrinth.exe <input file> <output file>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for writing\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	LabyrinthChar labyrinth;
	InitLabyrinth(labyrinth);
	Size labyrinthSize;
	
	if (!CanReadLabyrinthFromFile(input, labyrinth, labyrinthSize))
	{
		cout << "Failed to read labyrinth\n"
			<< "Labyrinth have not 1 start point and 1 finish point\n"
			<< "or Labyrinth's size invalid\n";
		return 1;
	}

	if (!FindWayLabyrinth(labyrinth, labyrinthSize))
	{
		cout << "Labyrinth has no access\n";
		return 1;
	}

	PrintLabyrinth(output, labyrinth, labyrinthSize);

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}