#include "House.h"

//setHouse: Set house data members, including validation check relative to house conditions
void House::setHouse(char ** myHouse, int _rows, int _cols)
{
	int dockingCounter = 0;
	overallDirtLevel = 0;

	rows = _rows;
	cols = _cols;
	house = new char*[rows];
	for (int i = 1; i < rows - 1; i++)
	{
		house[i] = new char[cols + 1];
		for (int j = 1; j < cols - 1; j++)
		{
			house[i][j] = myHouse[i][j];
			if (house[i][j] == DOCK_LETTER)
			{
				dockingCounter++;
				setDockingPosition(j, i);
			}
			if (house[i][j] > (MIN_DIRT_LEVEL + '0') && house[i][j] <= (MAX_DIRT_LEVEL + '0'))
				overallDirtLevel += (int)(house[i][j] - '0');
		}
		//house[i][cols] = '\0';
	}
	fillSurroundingWalls();
	currentPosition = dockingPosition;
	if (dockingCounter != 1)
	{
		validHouseFlag = false;
		endGameForInvalidNumOfDocking();
	}	
}

//getValueFromPoint: return the character in a specifiec point.
char House::getValueFromPoint(_204032031_Point p)
{
	return house[p.getY()][p.getX()];
}

//getValueFromPoint: return the character in a x,y coordinations.
char House::getValueFromPoint(int x, int y)
{
	return house[y][x];
}

//reduceValueAtPoint: reduce value by 1 to a specific point.
void House::reduceValueAtPoint(_204032031_Point p)
{
	int value = (int)(house[p.getY()][p.getX()] - '0');
	if (value == 1)
		house[p.getY()][p.getX()] = ' '; //to Print nothing instead of 0.
	else
		house[p.getY()][p.getX()] = (char)((value - 1) + '0');
}

//setDockingPosition: set dockingPosition data member.
void House::setDockingPosition(int x, int y)
{
	dockingPosition.setPoint(x, y);
}

//getDockingPosition: return dockingPosition.
_204032031_Point House::getDockingPosition()
{
	return dockingPosition;
}

//reduceOverallDirtLevel: reduce overallDirtLevel by 1.
void House::reduceOverallDirtLevel()
{
	overallDirtLevel--;
}

//getOverallDirtLevel: return overallDirtLevel.
int House::getOverallDirtLevel()
{
	return overallDirtLevel;
}

void House::setOverallDirtLevel(int _overallDirtLevel)
{
	overallDirtLevel = _overallDirtLevel;
}

//endGameForInvalidNumOfDocking: Print a message for invalid number of docking stations.
void House::endGameForInvalidNumOfDocking()
{
	system("cls");
	cout << "Invalid house:" << endl;
	cout << "Reason: More or less than one docking station" << endl;
}

//fillSurroundingWalls: This function make sure the surrounding walls of the house are complete, so the robot won't escape and eat ice cream.
void House::fillSurroundingWalls()
{
	int i;
	house[0] = new char[cols];
	house[rows-1] = new char[cols];
	for (i = 0; i < cols; i++)//Fill first and last rows
	{
		house[0][i] = WALL_LETTER;
		house[rows-1][i] = WALL_LETTER;
	}
		
	for (i = 0; i < rows; i++)//Fill first and last cols
	{
		house[i][0] = WALL_LETTER;
		house[i][cols-1] = WALL_LETTER;
	}
}
//freeHouseMemory: frees the memory allocated for the house array.
void House::freeHouseMemory()
{

	for (int i = 0; i < rows; i++)
	{
		delete [] house[i];
	}
	delete[] house;
	house = nullptr;
}
//copyHouseData: gets house variable and copies all its content to the current house data member.
void House::copyHouseData(House houseToCopy)
{
	rows = houseToCopy.rows;
	cols = houseToCopy.cols;
	dockingPosition = houseToCopy.dockingPosition;
	overallDirtLevel = houseToCopy.overallDirtLevel;
	validHouseFlag = houseToCopy.validHouseFlag;
	maxSteps = houseToCopy.maxSteps;
	note = houseToCopy.note;
	currentPosition = houseToCopy.currentPosition;
	houseName = houseToCopy.houseName;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			house[i][j] = houseToCopy.house[i][j];
		}
	}
}
//createCopyHouse: create a new house which is a copy of the current house
House House::createCopyHouse()
{
	House tempHouse;
	char** houseArray = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		houseArray[i] = new char[cols];
		for (int j = 0; j < cols; j++)
		{
		}
	}
	tempHouse.setHouseArray(houseArray);
	tempHouse.copyHouseData(*this);
	return tempHouse;
}

//getRows: get house rows.
int House::getRows()
{
	return rows;
}
//getCols: get house cols.
int House::getCols()
{
	return cols;
}
//setRows: set house rows.
void House::setRows(int _rows)
{
	rows = _rows;
}
//setCols: set house cols.
void House::setCols(int _cols)
{
	cols = _cols;
}
//setHouseArray: set house array.
void House::setHouseArray(char** arr)
{
	house = arr;
}

//getMaxSteps: return maxSteps
int House::getMaxSteps()
{
	return maxSteps;
}
//setMaxSteps: set maxSteps.
void House::setMaxSteps(int _maxSteps)
{
	maxSteps = _maxSteps;
}

//setHouseName: set houseName.
void House::setHouseName(string name)
{
	houseName = name;
}

//getHouseName: return houseName.
string House::getHouseName()
{
	return houseName;
}

string House::getNote()
{
	return note;
}
//getHouse: get house array.
char ** House::getHouse()
{
	return house;
}
//checkRowsAndColsValidationAndUpdateNote: gets rows and cols values, validates if it in the wanted range, if it doesn't the function saves to a note variable that the value is not acceptable
//and updates the valid house flag
void House::checkRowsAndColsValidationAndUpdateNote(int _rows, int _cols)
{
	if (_rows < MIN_ROWS)
	{
		note = "less rows than minimum required";
		validHouseFlag = false;
		return;
	}

	if (_rows > MAX_ROWS)
	{
		note += "more rows than maximum required\n";
		validHouseFlag = false;
		return;
	}

	if (_cols < MIN_COLS)
	{
		note += "less cols than minimum required\n";
		validHouseFlag = false;
		return;
	}
	if (_cols > MAX_COLS)
	{
		note += "more cols than maximum required\n";
		validHouseFlag = false;
		return;
	}
	validHouseFlag = true;

}
//checkDockingValidationAndUpdateNote: gets counter of dockings, checks if it exceed 1 or if it equals to 0, if so, it updates the house's note with an error message and update the validation house flag.
void House::checkDockingValidationAndUpdateNote(int dockingCounter)
{
	if (dockingCounter == 0)
	{
		note += "missing docking station (no D in house)\n";
		validHouseFlag = false;
		return;
	}
	if (dockingCounter > 1)
	{
		note += "too many docking stations (more than one D in house)\n";
		validHouseFlag = false;
		return;
	}
	validHouseFlag = true;
}
//getCurrentPosition: returns the current position of the robot in the house.
_204032031_Point& House::getCurrentPosition()
{
	return currentPosition;
}
//setCurrentPosition: gets position and sets the current position to be the given position
void House::setCurrentPosition(_204032031_Point position)
{
	currentPosition = position;
}
//getSensorInformation: creates and updates sensor information object with current information and then returns it.
SensorInformation House::getSensorInformation()
{
	SensorInformation sensorInfo;

	char char_currDirtLevel;

	char_currDirtLevel = getValueFromPoint(currentPosition);
	if (char_currDirtLevel > (MIN_DIRT_LEVEL + '0') && char_currDirtLevel <= (MAX_DIRT_LEVEL + '0'))
		sensorInfo.dirtLevel = (int)(char_currDirtLevel - '0');
	else
		sensorInfo.dirtLevel = 0;

	sensorInfo.isWall[3] = (getValueFromPoint(currentPosition.getX(), currentPosition.getY() - 1) == WALL_LETTER); //UP
	sensorInfo.isWall[0] = (getValueFromPoint(currentPosition.getX() + 1, currentPosition.getY()) == WALL_LETTER); //RIGHT
	sensorInfo.isWall[2] = (getValueFromPoint(currentPosition.getX(), currentPosition.getY() + 1) == WALL_LETTER); //DOWN
	sensorInfo.isWall[1] = (getValueFromPoint(currentPosition.getX() - 1, currentPosition.getY()) == WALL_LETTER); //LEFT

	return sensorInfo;
}