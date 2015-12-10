#include <stdio.h>
#include <iostream>

int Distance = 0;  // Acquired from Owen

char directionToRover(int Direction);
int getType(int left, int right, int forward);
char new_DetermineDirection(char left, char right, char forward, int xcoor, int ycoor, int Distance);
char traversedAdjacentPath(char left, char right, char forward, int xcoor, int ycoor, int intersection, int Distance, int exploredArray[], int typeArray[], int pointArray[], int point, int getXCoor[], int getYCoor[]);
char old_DetermineDirection(char left, char right, char forward, int xcoor, int ycoor, int intersection, int Distance, int exploredArray[], int typeArray[], int pointArray[], int point, int getXCoor[], int getYCoor[]);
char approachIntersection(char left, char right, char forward, int Distance);
int updateCoordinate(int xcoor, int ycoor, int point, bool update);
int updateDirection(int Direction, bool update);
int updateXCOOR(int Distance, bool update);
int updateYCOOR(int Distance, bool update);

// Function is called by Owen to return next rover direction
char approachIntersection(char left, char right, char forward, int Distance) {
	static int Total_Points = 1;
	static int intersection = 0;
	static int point = 1;
	static int xcoor = 10;
	xcoor = updateXCOOR(0, false);
	static int ycoor = 10;
	ycoor = updateYCOOR(0, false);
	int Coordinate = updateCoordinate(xcoor, ycoor, point, false);

	static int getXCoor[50];
	static int getYCoor[50];
	static int pointArray[50];
	static int typeArray[50];
	static int exploredArray[50];

	static bool initialize = true;
	while (initialize == true) {
		exploredArray[0] = 1;
		getXCoor[0] = xcoor;
		getYCoor[0] = ycoor;
		initialize = false;
	}

	intersection++;
	typeArray[intersection] = getType(left, right, forward);

	if (Coordinate > 0) {
		// Previous node identified
		pointArray[intersection] = Coordinate;
		exploredArray[Coordinate]++;
		exploredArray[intersection] = exploredArray[Coordinate] + 1;

		return old_DetermineDirection(left, right, forward, xcoor, ycoor, intersection, Distance, exploredArray, typeArray, pointArray, point, getXCoor, getYCoor);
	}
	else {
		// New node identified
		pointArray[intersection] = Total_Points;
		exploredArray[intersection]++;
		Total_Points++;

		// Save Coordinate
		updateCoordinate(xcoor, ycoor, point, true);
		//Coordinate[xcoor][ycoor] = point;
		getXCoor[point] = xcoor;
		getYCoor[point] = ycoor;
		point++;

		//Determine next direction
		return new_DetermineDirection(left, right, forward, xcoor, ycoor, Distance);
	}
}

// Analyzes previous direction and next direction in order
//	to send a turn signal that the rover can interperet.
//  Directions can be l, f , r, t
char directionToRover(int Direction) {
	static int prevDirection = 2;
	char newDirection = ' ';

	if (prevDirection == 1 && Direction == 1) {
		newDirection = 'f';
		prevDirection = 1;
	}
	else if (prevDirection == 1 && Direction == 2) {
		newDirection = 'l';
		prevDirection = 2;
	}
	else if (prevDirection == 1 && Direction == 3) {
		newDirection = 't';
		prevDirection = 3;
	}
	else if (prevDirection == 1 && Direction == 4) {
		newDirection = 'r';
		prevDirection = 4;
	}
	else if (prevDirection == 2 && Direction == 1) {
		newDirection = 'r';
		prevDirection = 1;
	}
	else if (prevDirection == 2 && Direction == 2) {
		newDirection = 'f';
		prevDirection = 2;
	}
	else if (prevDirection == 2 && Direction == 3) {
		newDirection = 'l';
		prevDirection = 3;
	}
	else if (prevDirection == 2 && Direction == 4) {
		newDirection = 't';
		prevDirection = 4;
	}
	else if (prevDirection == 3 && Direction == 1) {
		newDirection = 't';
		prevDirection = 1;
	}
	else if (prevDirection == 3 && Direction == 2) {
		newDirection = 'r';
		prevDirection = 2;
	}
	else if (prevDirection == 3 && Direction == 3) {
		newDirection = 'f';
		prevDirection = 3;
	}
	else if (prevDirection == 3 && Direction == 4) {
		newDirection = 'l';
		prevDirection = 4;
	}
	else if (prevDirection == 4 && Direction == 1) {
		newDirection = 'l';
		prevDirection = 1;
	}
	else if (prevDirection == 4 && Direction == 2) {
		newDirection = 't';
		prevDirection = 2;
	}
	else if (prevDirection == 4 && Direction == 3) {
		newDirection = 'r';
		prevDirection = 3;
	}
	else if (prevDirection == 4 && Direction == 4) {
		newDirection = 'f';
		prevDirection = 4;
	}
	return newDirection;
}

// Determines the type on intersection based on IR sensor data
int getType(int left, int right, int forward) {
	int type = 0;
	if (left) {
		type++;
	}
	if (right) {
		type++;
	}
	if (forward) {
		type++;
	}
	return type;
}

int updateDirection(int Direction, bool update) {
	static int currentDirection = 2;
	if (update == true) {
		currentDirection = Direction;
	}
	return currentDirection;
}

int updateCoordinate(int xcoor, int ycoor, int point, bool update) {
	static int Coordinate[50][50];
	if (update == true) {
		Coordinate[xcoor][ycoor] = point;
		return 0;
	}
	else if (update == false) {
		return Coordinate[xcoor][ycoor];
	}
}

int updateXCOOR(int Distance, bool update) {
	static int currentX = 10;
	if (update == true) {
		currentX += Distance;
	}
	return currentX;
}

int updateYCOOR(int Distance, bool update) {
	static int currentY = 10;
	if (update == true) {
		currentY += Distance;
	}
	return currentY;
}

char new_DetermineDirection(char left, char right, char forward, int xcoor, int ycoor, int Distance) {
	char nextDirection = ' ';
	int Direction = updateDirection(0, false);

	if (Direction == 1) {
		if (!left && !right && !forward) {
			Direction = updateDirection(3, true);
			updateXCOOR((-1 * Distance), true);
		}
		else if (forward) {
			Direction = updateDirection(1, true);
			updateXCOOR(Distance, true);
		}
		else if (left) {
			Direction = updateDirection(2, true);
			updateYCOOR((-1 * Distance), true);
		}
		else if (right) {
			Direction = updateDirection(4, true);
			updateYCOOR(Distance, true);
		}
		nextDirection = directionToRover(Direction);
	}
	else if (Direction == 2) {
		if (!left && !right && !forward) {
			Direction = updateDirection(4, true);
			updateYCOOR(Distance, true);
		}
		else if (right) {
			Direction = updateDirection(1, true);
			updateXCOOR(Distance, true);
		}
		else if (forward) {
			Direction = updateDirection(2, true);
			updateYCOOR((-1 * Distance), true);
		}
		else if (left) {
			Direction = updateDirection(3, true);
			updateXCOOR((-1 * Distance), true);
		}
		nextDirection = directionToRover(Direction);
	}
	else if (Direction == 3) {
		if (!left && !right && !forward) {
			Direction = updateDirection(1, true);
			updateXCOOR(Distance, true);
		}
		else if (right) {
			Direction = updateDirection(2, true);
			updateYCOOR((-1 * Distance), true);
		}
		else if (forward) {
			Direction = updateDirection(3, true);
			updateXCOOR((-1 * Distance), true);
		}
		else if (left) {
			Direction = updateDirection(4, true);
			updateYCOOR(Distance, true);
		}
		nextDirection = directionToRover(Direction);
	}
	else if (Direction == 4) {
		if (!left && !right && !forward) {
			Direction = updateDirection(2, true);
			updateYCOOR((-1 * Distance), true);
		}
		else if (left) {
			Direction = updateDirection(1, true);
			updateXCOOR(Distance, true);
		}
		else if (right) {
			Direction = updateDirection(3, true);
			updateXCOOR((-1 * Distance), true);
		}
		else if (forward) {
			Direction = updateDirection(4, true);
			updateYCOOR(Distance, true);
		}
		nextDirection = directionToRover(Direction);
	}
	return nextDirection;
}

// Determines what to do if all adjacent paths have already been traversed
char traversedAdjacentPath(char left, char right, char forward, int xcoor, int ycoor, int intersection, int Distance, int exploredArray[], int typeArray[], int pointArray[], int point, int getXCoor[], int getYCoor[]) {
	int stop = 1;
	int Direction = updateDirection(0, false);
	int Coordinate = updateCoordinate(xcoor, ycoor, point, false);
	static bool endMap = false;
	int isDeadEnd = getType(left, right, forward);
	if (isDeadEnd == 1) {
		return new_DetermineDirection(left, right, forward, xcoor, ycoor, Distance);
	}
	else {
		int i = 0;
		while (i < intersection) {
			stop = 1;
			if (pointArray[i] == Coordinate) {
				if (exploredArray[i - 1] < typeArray[i - 1]) {
					if (ycoor == getYCoor[pointArray[i - 1]]) {
						if (xcoor > getXCoor[pointArray[i - 1]]) {
							Direction = updateDirection(3, true);
							updateXCOOR((-1 * Distance), true);
						}
						else if (xcoor < getXCoor[pointArray[i - 1]]) {
							Direction = updateDirection(1, true);
							updateXCOOR(Distance, true);
						}
					}
					else if (xcoor == getXCoor[pointArray[i - 1]]) {
						if (ycoor > getYCoor[pointArray[i - 1]]) {
							Direction = updateDirection(2, true);
							updateYCOOR((-1 * Distance), true);
						}
						else if (ycoor < getYCoor[pointArray[i - 1]]) {
							Direction = updateDirection(4, true);
							updateYCOOR(Distance, true);
						}
					}
					stop--;
				}
				else if (exploredArray[i + 1] < typeArray[i + 1]) {
					if (ycoor == getYCoor[pointArray[i + 1]]) {
						if (xcoor > getXCoor[pointArray[i + 1]]) {
							Direction = updateDirection(3, true);
							updateXCOOR((-1 * Distance), true);
						}
						else if (xcoor < getXCoor[pointArray[i + 1]]) {
							Direction = updateDirection(1, true);
							updateXCOOR(Distance, true);
						}
					}
					else if (xcoor == getXCoor[pointArray[i + 1]]) {
						if (ycoor > getYCoor[pointArray[i + 1]]) {
							Direction = updateDirection(2, true);
							updateYCOOR((-1 * Distance), true);
						}
						else if (ycoor < getYCoor[pointArray[i + 1]]) {
							Direction = updateDirection(4, true);
							updateYCOOR(Distance, true);
						}
					}
					stop--;
				}
				else if ((exploredArray[i - 1] >= typeArray[i - 1]) && (exploredArray[i + 1] >= typeArray[i + 1])) {
					stop++;
				}
			}
			i++;
		}
	}
	if (stop == 2) {
		// DONE MAPPING!!!!
		return 'E';
	}
	else {
		return directionToRover(Direction);
	}
}

// This is the function that makes the algorith work!!!
//	Determines the direction to take after coming to an intersection
//  North=2, South=4, East=1, West=3
char old_DetermineDirection(char left, char right, char forward, int xcoor, int ycoor, int intersection, int Distance, int exploredArray[], int typeArray[], int pointArray[], int point, int getXCoor[], int getYCoor[]) {
	int Direction = updateDirection(0, false);
	bool directionNew = true;
	int compareType = 0;
	int Coordinate = updateCoordinate(xcoor, ycoor, point, false);

	if (Direction == 1) {
		if (forward) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor < getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(1, true);
				updateXCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (left) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (ycoor > getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(2, true);
				updateYCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (right) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (ycoor < getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(4, true);
				updateYCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType(left, right, forward)) {
			return traversedAdjacentPath(left, right, forward, xcoor, ycoor, intersection, Distance, exploredArray, typeArray, pointArray, point, getXCoor, getYCoor);
		}
	}

	else if (Direction == 2) {
		if (right) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor < getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(1, true);
				updateXCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (forward) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (ycoor > getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(2, true);
				updateYCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (left) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor > getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(3, true);
				updateXCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType(left, right, forward)) {
			return traversedAdjacentPath(left, right, forward, xcoor, ycoor, intersection, Distance, exploredArray, typeArray, pointArray, point, getXCoor, getYCoor);
		}
	}
	else if (Direction == 3) {
		if (right) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (ycoor > getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(2, true);
				updateYCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (forward) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor > getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] > 0 && typeArray[i] != 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(3, true);
				updateXCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (left) {
			directionNew = true;
			int i = 0;
			while ( i < intersection) {
				if (ycoor < getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(4, true);
				updateYCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType(left, right, forward)) {
			return traversedAdjacentPath(left, right, forward, xcoor, ycoor, intersection, Distance, exploredArray, typeArray, pointArray, point, getXCoor, getYCoor);
		}
	}
	else if (Direction == 4) {
		if (left) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor < getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(1, true);
				updateXCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (right) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (xcoor > getXCoor[i] && ycoor == getYCoor[i]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(3, true);
				updateXCOOR((-1 * Distance), true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (forward) {
			directionNew = true;
			int i = 0;
			while (i < intersection) {
				if (ycoor < getYCoor[i] && xcoor == getXCoor[i]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
				i++;
			}
			if (directionNew == true) {
				Direction = updateDirection(4, true);
				updateYCOOR(Distance, true);
				return directionToRover(Direction);
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType(left, right, forward)) {
			return traversedAdjacentPath(left, right, forward, xcoor, ycoor, intersection, Distance, exploredArray, typeArray, pointArray, point, getXCoor, getYCoor);
		}
	}
}