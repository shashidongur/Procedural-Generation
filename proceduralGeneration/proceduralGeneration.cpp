// proceduralGeneration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdexcept>

using namespace std;

struct blockBox{
	int box;
	char boxType;
};
struct solutionPath {
	blockBox* box;
	solutionPath* next;
};

//Initialize 16 blocks in the level
extern std::vector<std::vector<int> > levelBlocks = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } };
extern std::vector<int> visitedBoxes(1, 0);
extern std::vector<char> levelTemplate_row(69, '#');
extern std::vector<std::vector<char> > lelvelTemplate(69, levelTemplate_row);
int** levelDesign = new int*[12];
bool nopossiblemoves = false;

void AssignLevelTemplate();
void CreateLevelTemplate(int x_min, int y_min);
void AssignNextBox(blockBox &current, blockBox &next);
bool IsVisited(int boxNumber);
bool NoPossibleMoves(int column, int row);
void CreateLevelDoors();
void CreatePlatformsAndEnemies();
void CreatePlatformsAndEnemies(int x_min, int y_min, bool IsFinishBox);


int _tmain(int argc, _TCHAR* argv[])
{
	int casd;
	srand(time(NULL));
	blockBox start;
	solutionPath path;
	path.box = &start;
	int row = 0, column = 0, randomIndex;
	start.box = 0;
	blockBox current = start;
	
	blockBox next;
	blockBox finish;

	// Pick the final box. Atleast distance 2 from starting box '0'
	do{
		finish.box = std::rand() % 16;
		cout << finish.box << endl;
	} while (finish.box == 0 || finish.box == 1 || finish.box == 4 || finish.box == 5 || finish.box == 2 || finish.box == 8);

	// Building the solution path and storing it in 
	do{
		
		AssignNextBox(current, next);
		if (nopossiblemoves)
		{
			current = start;
			nopossiblemoves = false;
			continue;
		}
		cout << current.box << "->";
		current = next;
	} while (current.box != finish.box ); // repeat till you reach finish box.
	cout << finish.box << endl;
	AssignLevelTemplate();

	for (int k = 0; k<lelvelTemplate.size(); k++) {
		for (int l = 0; l<lelvelTemplate[k].size(); l++)
			cout << lelvelTemplate[k][l] << " ";
		cout << endl;
	}
	std::cin >> casd;
	return 0;
}


void AssignLevelTemplate()
{
	int boxNumber;
	for (int i = 0; i < visitedBoxes.size(); i++)
	{
		int x_min, y_min;
		int boundary_1 = 1, boundary_2 = 18, boundary_3 = 35, boundary_4 = 52;
		boxNumber = visitedBoxes.at(i);
		switch (boxNumber)
		{
		case 0:
			x_min = boundary_1; y_min = boundary_1;
			break;
		case 1:
			x_min = boundary_2; y_min = boundary_1;
			break;
		case 2:
			x_min = boundary_3; y_min = boundary_1;
			break;
		case 3:
			x_min = boundary_4; y_min = boundary_1;
			break;
		case 4:
			x_min = boundary_1; y_min = boundary_2;
			break;
		case 5:
			x_min = boundary_2; y_min = boundary_2;
			break;
		case 6:
			x_min = boundary_3; y_min = boundary_2;
			break;
		case 7:
			x_min = boundary_4; y_min = boundary_2;
			break;
		case 8:
			x_min = boundary_1; y_min = boundary_3;
			break;
		case 9:
			x_min = boundary_2; y_min = boundary_3;
			break;
		case 10:
			x_min = boundary_3;  y_min = boundary_3;
			break;
		case 11:
			x_min = boundary_4; y_min = boundary_3;
			break;
		case 12:
			x_min = boundary_1; y_min = boundary_4;
			break;
		case 13:
			x_min = boundary_2; y_min = boundary_4;
			break;
		case 14:
			x_min = boundary_3; y_min = boundary_4;
			break;
		case 15:
			x_min = boundary_4; y_min = boundary_4;
			break;
		}
		CreateLevelTemplate(x_min, y_min);
		CreateLevelDoors();
		CreatePlatformsAndEnemies(x_min, y_min, (i + 1 == visitedBoxes.size()));
	}
}

void CreateLevelTemplate(int x_min, int y_min)
{
	for (int i = x_min; i <= (x_min + 15); i++)
	{
		for (int j = y_min; j <= (y_min + 15); j++)
		{
			lelvelTemplate[i][j] = ' ';
		}
	}
}

void CreateLevelDoors()
{
	int box_1, box_2;
	int devide_box_1, remainder_box_1;
	int devide_box_2, remainder_box_2;
	int doorRandom;
	for (int f = 0; f < visitedBoxes.size(); f++)
	{
		box_1 = visitedBoxes[f];
		devide_box_1 = box_1 / 4;
		remainder_box_1 = box_1 % 4;
		doorRandom = std::rand() % 10 + 1;
		try
		{
			box_2 = visitedBoxes.at(f + 1);
			devide_box_2 = box_2 / 4;
			remainder_box_2 = box_2 % 4;
			if (devide_box_1 == devide_box_2)
			{
				if (box_2 > box_1){
					for (int i = 17 * devide_box_2 + 5; i <= (17 * devide_box_2 + 10); i++)
					{
						for (int j = 17 * remainder_box_2; j <= (17 * remainder_box_2); j++)
						{
							lelvelTemplate.at(j).at(i) = ' ';
						}
					}
				}
				else
				{
					for (int i = 17 * devide_box_1 + 5; i <= (17 * devide_box_1 + 10); i++)
					{
						for (int j = 17 * remainder_box_1; j <= (17 * remainder_box_1); j++)
						{
							lelvelTemplate.at(j).at(i) = ' ';
						}
					}
				}
			}
			else if (remainder_box_1 == remainder_box_2)
			{
				if (box_2 > box_1)
				{
					for (int i = 17 * remainder_box_2 + 5 ; i <= (17 * remainder_box_2 + 10); i++)
					{
						for (int j = 17 * devide_box_2; j <= (17 * devide_box_2); j++)
						{
							lelvelTemplate.at(i).at(j) = ' ';
						}
					}
				}
				else
				{
					for (int i = 17 * remainder_box_1 + 5; i <= (17 * remainder_box_1 + 10); i++)
					{
						for (int j = 17 * devide_box_1; j <= (17 * devide_box_1); j++)
						{
							lelvelTemplate.at(i ).at(j) = ' ';
						}
					}
				}
			}

		}catch (exception ex){}
	}
	
}

void CreatePlatformsAndEnemies(int x_min, int y_min, bool IsFinishBox)
{
	int number_of_platforms; //Between 3 - 5 platforms.
	int platform_location; //location of each platform from left wall.
	int platform_1_y, platform_2_y, platform_3_y, platform_4_y, platform_5_y; //Y cordinates for playforms
	int platform_1_x;
	std::vector<int> platforms_y_list( 5, NULL );

	number_of_platforms = rand() % 3 + 3;

	switch (number_of_platforms)
	{
	case 3:
		platforms_y_list.at(0) = rand() % 3 + 3;
		platforms_y_list.at(1) = rand() % 3 + 7;
		platforms_y_list.at(2) = rand() % 3 + 11;
		platforms_y_list.at(3) = NULL;
		platforms_y_list.at(4) = NULL;
		break;
	case 4:
		platforms_y_list.at(0) = rand() % 2 + 2;
		platforms_y_list.at(1) = rand() % 2 + 5;
		platforms_y_list.at(2) = rand() % 2 + 8;
		platforms_y_list.at(3) = rand() % 2 + 11;
		platforms_y_list.at(4) = NULL;
		break;
	case 5:
		platforms_y_list.at(0) = rand() % 1 + 2;
		platforms_y_list.at(1) = rand() % 1 + 5;
		platforms_y_list.at(2) = rand() % 1 + 7;
		platforms_y_list.at(3) = rand() % 1 + 9;
		platforms_y_list.at(4) = rand() % 1 + 12;
		break;
	}

	//Loop for each platform. 
	for (int k = 0; k < number_of_platforms; k++)
	{
		
		platform_1_x = rand() % 8;
		for (int j = y_min + platform_1_x; j < y_min + platform_1_x + 5; j++)
		{
			lelvelTemplate[platforms_y_list.at(k) + x_min][j] = '=';
		}
		//Insert enemies and goal
		if (IsFinishBox && (number_of_platforms - k == 1))
		{
			lelvelTemplate[platforms_y_list.at(k) + x_min + 1][y_min + platform_1_x + 1] = 'G';
			lelvelTemplate[platforms_y_list.at(k) + x_min + 1][y_min + platform_1_x + 2] = 'O';
			lelvelTemplate[platforms_y_list.at(k) + x_min + 1][y_min + platform_1_x + 3] = 'A';
			lelvelTemplate[platforms_y_list.at(k) + x_min + 1][y_min + platform_1_x + 4] = 'L';
		}
		else
		{
			lelvelTemplate[platforms_y_list.at(k) + x_min + 1][y_min + platform_1_x + 2] = 'E';
		}
	}
}
void AssignNextBox(blockBox &current, blockBox &next)
{
	//To assign next box. We need to make sure it is inside the range of 16 boxes. It connects with
	int currentBoxNumber = current.box;
	int column = (current.box) % 4;
	int row = ((current.box) - column) / 4;
	bool cont = true;
	int randomIndex;
	do{
		randomIndex = rand() % 4;
		try{
			switch (randomIndex)
			{
			case 0:
				if ((levelBlocks.at(row).at(column + 1) > 0) && !IsVisited(levelBlocks.at(row).at(column + 1)))
				{
					next.box = levelBlocks.at(row).at(column + 1);
					cont = false;
				}
				break;
			case 1:
				if ((levelBlocks.at(row + 1).at(column) > 0) && !IsVisited(levelBlocks.at(row + 1).at(column)))
				{
					next.box = levelBlocks.at(row + 1).at(column);
					cont = false;
				}
				break;
			case 2:
				if ((levelBlocks.at(row).at(column - 1) > 0) && !IsVisited(levelBlocks.at(row).at(column - 1)))
				{
					next.box = levelBlocks.at(row).at(column - 1);
					cont = false;
				}
				break;
			case 3:
				if ((levelBlocks.at(row - 1).at(column) > 0) && !IsVisited(levelBlocks.at(row - 1).at(column)))
				{
					next.box = levelBlocks.at(row - 1).at(column);
					cont = false;
				}
				break;
			}
		}
		catch (exception ex){
		}
		if (NoPossibleMoves(row, column))
		{
			cout << endl << "No possible moves" << endl;
			cout << "Resetting moves" << endl;
			cont = false;
			visitedBoxes.clear();
			visitedBoxes.push_back(0);
			current.box = 0;
			next.box = -1;
			nopossiblemoves = true;
		}

	} while (cont);
	if (!nopossiblemoves)
		visitedBoxes.push_back(next.box);
}

bool IsVisited(int boxNumber)
{
	std:vector<int>::iterator it;
	it = find(visitedBoxes.begin(), visitedBoxes.end(), boxNumber);
	if (it != visitedBoxes.end())
		return true;
	else
		return false;

}

bool NoPossibleMoves(int row, int column)
{
	bool toptemp, righttemp, bottomtemp, lefttemp;
	try{
		toptemp = IsVisited(levelBlocks.at(row).at(column + 1));
	}
	catch (exception ex){ toptemp = true; }
	try{
		righttemp = IsVisited(levelBlocks.at(row + 1).at(column));
	}
	catch (exception ex){ righttemp = true; }
	try{
		bottomtemp = IsVisited(levelBlocks.at(row - 1).at(column));
	}
	catch (exception ex){ bottomtemp = true; }
	try{
		lefttemp = IsVisited(levelBlocks.at(row).at(column - 1));
	}
	catch (exception ex){ lefttemp = true; }
	
	if (toptemp && bottomtemp && lefttemp && righttemp)
		return true;
	else
		return false;
}