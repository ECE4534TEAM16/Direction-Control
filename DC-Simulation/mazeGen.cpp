#include <stdio.h>
#include <iostream>
#include "EasyBMP.h"

// Global Variables //
#define MAX_NODES	50

int xcoor = 6;
int ycoor = 30;
int Direction = 2;
int Total_Points = 1;
int intersection = 0;
int nodeDistance = 0;
bool isMapping = true;

int fileNum = 0;
char outFile[32];

int Coordinate[MAX_NODES][MAX_NODES];
int getCoor[MAX_NODES][MAX_NODES];

int pointArray[MAX_NODES];
int typeArray[MAX_NODES];
int exploredArray[MAX_NODES];

struct pixel {
	RGBApixel current;
	RGBApixel right;
	RGBApixel left;
	RGBApixel front;
} dataIR;
// End Global Variables //

// Helper Functions //
void dataBMP(BMP img) {
	printf("Img Width: %d\n", img.TellWidth());
	printf("Img Height: %d\n", img.TellHeight());
	printf("Img Number of Colors: %d\n", img.TellNumberOfColors());
}

void getDataIR(BMP img) {
	// North=2, South=4, East=1, West=3
	if (Direction == 1) {
		dataIR.current = img.GetPixel(xcoor, ycoor);
		dataIR.right = img.GetPixel(xcoor, ycoor + 1);
		dataIR.left = img.GetPixel(xcoor, ycoor - 1);
		dataIR.front = img.GetPixel(xcoor + 1, ycoor);
	}
	else if (Direction == 2) {
		dataIR.current = img.GetPixel(xcoor, ycoor);
		dataIR.right = img.GetPixel(xcoor + 1, ycoor);
		dataIR.left = img.GetPixel(xcoor - 1, ycoor);
		dataIR.front = img.GetPixel(xcoor, ycoor - 1);
	}
	else if (Direction == 3) {
		dataIR.current = img.GetPixel(xcoor, ycoor);
		dataIR.right = img.GetPixel(xcoor, ycoor - 1);
		dataIR.left = img.GetPixel(xcoor, ycoor + 1);
		dataIR.front = img.GetPixel(xcoor - 1, ycoor);
	}
	else if (Direction == 4) {
		dataIR.current = img.GetPixel(xcoor, ycoor);
		dataIR.right = img.GetPixel(xcoor - 1, ycoor);
		dataIR.left = img.GetPixel(xcoor + 1, ycoor);
		dataIR.front = img.GetPixel(xcoor, ycoor + 1);
	}
}

void directionToRover() {
	static int prevDirection = 2; // Directions can be l, f , r, t
	if (prevDirection == 1 && Direction == 1) {
		printf("ROVER DIRECTION IS: f\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'f');
		nodeDistance = 0;
		prevDirection = 1;
	}
	else if (prevDirection == 1 && Direction == 2) {
		printf("ROVER DIRECTION IS: l\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'l');
		nodeDistance = 0;
		prevDirection = 2;
	}
	else if (prevDirection == 1 && Direction == 3) {
		printf("ROVER DIRECTION IS: t\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 't');
		nodeDistance = 0;
		prevDirection = 3;
	}
	else if (prevDirection == 1 && Direction == 4) {
		printf("ROVER DIRECTION IS: r\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'r');
		nodeDistance = 0;
		prevDirection = 4;
	}
	else if (prevDirection == 2 && Direction == 1) {
		printf("ROVER DIRECTION IS: r\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'r');
		nodeDistance = 0;
		prevDirection = 1;
	}
	else if (prevDirection == 2 && Direction == 2) {
		printf("ROVER DIRECTION IS: f\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'f');
		nodeDistance = 0;
		prevDirection = 2;
	}
	else if (prevDirection == 2 && Direction == 3) {
		printf("ROVER DIRECTION IS: l\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'l');
		nodeDistance = 0;
		prevDirection = 3;
	}
	else if (prevDirection == 2 && Direction == 4) {
		printf("ROVER DIRECTION IS: t\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 't');
		nodeDistance = 0;
		prevDirection = 4;
	}
	else if (prevDirection == 3 && Direction == 1) {
		printf("ROVER DIRECTION IS: t\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 't');
		nodeDistance = 0;
		prevDirection = 1;
	}
	else if (prevDirection == 3 && Direction == 2) {
		printf("ROVER DIRECTION IS: r\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'r');
		nodeDistance = 0;
		prevDirection = 2;
	}
	else if (prevDirection == 3 && Direction == 3) {
		printf("ROVER DIRECTION IS: f\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'f');
		nodeDistance = 0;
		prevDirection = 3;
	}
	else if (prevDirection == 3 && Direction == 4) {
		printf("ROVER DIRECTION IS: l\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'l');
		nodeDistance = 0;
		prevDirection = 4;
	}
	else if (prevDirection == 4 && Direction == 1) {
		printf("ROVER DIRECTION IS: l\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'l');
		nodeDistance = 0;
		prevDirection = 1;
	}
	else if (prevDirection == 4 && Direction == 2) {
		printf("ROVER DIRECTION IS: t\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 't');
		nodeDistance = 0;
		prevDirection = 2;
	}
	else if (prevDirection == 4 && Direction == 3) {
		printf("ROVER DIRECTION IS: r\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'r');
		nodeDistance = 0;
		prevDirection = 3;
	}
	else if (prevDirection == 4 && Direction == 4) {
		printf("ROVER DIRECTION IS: f\n");
		printf("SENDING PACKET TO TYLER: %d %d %d %d %c\n", nodeDistance, dataIR.left.Red, dataIR.front.Red, dataIR.right.Red, 'f');
		nodeDistance = 0;
		prevDirection = 4;
	}
}

void displayDataIR() {
	printf("Direction: %d\n", Direction);
	printf("Front Pixel: %d\n", (int)dataIR.front.Red);
	printf("Line Sensor: %d %d %d\n", (int)dataIR.left.Red, (int)dataIR.current.Red, (int)dataIR.right.Red);
}

void displayDataArrays() {
	// Point Array
	printf("Point Array:      ");
	for (int i = 0; i < intersection + 1; i++) {
		printf("%2d ", pointArray[i]);
	}
	printf("\n");

	// Type Array
	printf("Type Array:       ");
	for (int i = 0; i < intersection + 1; i++) {
		printf("%2d ", typeArray[i]);
	}
	printf("\n");

	// Explored Array
	printf("Explored Array:   ");
	for (int i = 0; i < intersection + 1; i++) {
	printf("%2d ", exploredArray[i]);
	}
	printf("\n");
}

void displayDataMovement() {
	printf("\nCurrent Coordinates: (%d,%d)\n", xcoor, ycoor);
	printf("Total Nodes: %d\n", Total_Points);
	printf("Intersection Number: %d\n", intersection);
}

void saveCoordinate() {
	// X coordinate of point is found in 0
	// Y coordinate of point is found in 1
	static int point = 0;
	Coordinate[xcoor][ycoor] = point;
	getCoor[point][0] = xcoor;
	getCoor[point][1] = ycoor;

	printf("POINT: %d\n", point);
	printf("GET COOR:  X = %d, Y = %d\n", getCoor[point][0], getCoor[point][1]);
	point++;
	printf("NEW NODE LOCATED!\n");
	printf("COORDINATE SAVED (%d, %d)\n", xcoor, ycoor);

	fileNum++;
	snprintf(outFile, sizeof(char) * 32, "mapped%i.bmp", fileNum);
}

void travel() {
	// North=2, South=4, East=1, West=3
	// Initial direction is regarded as North
	if (Direction < 1 || Direction > 4) {
		printf("ERROR: INVALID DIRECTION GIVEN");
	}
	else if (Direction == 1){
		xcoor++;
	}
	else if (Direction == 2) {
		ycoor--;
	}
	else if (Direction == 3) {
		xcoor--;
	}
	else if (Direction == 4) {
		ycoor++;
	}
}

int getType() {
	int type = 0;
	if ((int)dataIR.left.Red != 255) {
		type++;
	}
	if ((int)dataIR.right.Red != 255) {
		type++;
	}
	if ((int)dataIR.front.Red != 255) {
		type++;
	}
	return type;
}

void new_DetermineDirection() {
	printf("PATH THAT IS NOT TRAVERSED\n");
	if (Direction == 1) {
		if ((int)dataIR.left.Red == 255 && (int)dataIR.right.Red == 255 && (int)dataIR.front.Red == 255) {
		// Dead end, turn around!
		printf("DEAD END\n");
		Direction = 3;
		xcoor--;
		}
		else if (dataIR.front.Red != 255) {
			Direction = 1;
			xcoor++;
		}
		else if (dataIR.left.Red != 255) {
			Direction = 2;
			ycoor--;
		}
		else if (dataIR.right.Red != 255) {
			Direction = 4;
			ycoor++;
		}
		printf("NEW DIRECTION: %d\n", Direction);
		directionToRover();
	}
	else if (Direction == 2) {
		if ((int)dataIR.left.Red == 255 && (int)dataIR.right.Red == 255 && (int)dataIR.front.Red == 255) {
			// Dead end, turn around!
			printf("DEAD END\n");
			Direction = 4;
			ycoor++;
		}
		else if ((int)dataIR.right.Red != 255) {
			Direction = 1;
			xcoor++;
		}
		else if ((int)dataIR.front.Red != 255) {
			Direction = 2;
			ycoor--;
		}
		else if ((int)dataIR.left.Red != 255) {
			Direction = 3;
			xcoor--;
		}
		printf("NEW DIRECTION: %d\n", Direction);
		directionToRover();
	}
	else if (Direction == 3) {
		if ((int)dataIR.left.Red == 255 && (int)dataIR.right.Red == 255 && (int)dataIR.front.Red == 255) {
			// Dead end, turn around!
			printf("DEAD END\n");
			Direction = 1;
			xcoor++;
		}
		else if (dataIR.right.Red != 255) {
			Direction = 2;
			ycoor--;
		}
		else if (dataIR.front.Red != 255) {
			Direction = 3;
			xcoor--;
		}
		else if (dataIR.left.Red != 255) {
			Direction = 4;
			ycoor++;
		}
		printf("NEW DIRECTION: %d\n", Direction);
		directionToRover();
	}
	else if (Direction == 4) {
		if ((int)dataIR.left.Red == 255 && (int)dataIR.right.Red == 255 && (int)dataIR.front.Red == 255) {
			// Dead end, turn around!
			printf("DEAD END\n");
			Direction = 2;
			ycoor--;
		}
		else if (dataIR.left.Red != 255) {
			Direction = 1;
			xcoor++;
		}
		else if (dataIR.right.Red != 255) {
			Direction = 3;
			xcoor--;
		}
		else if (dataIR.front.Red != 255) {
			Direction = 4;
			ycoor++;
		}
		printf("NEW DIRECTION: %d\n", Direction);
		directionToRover();
	}
}

void traversedAdjacentPath() {
	// All adjacent paths have already been traversed, look for nodes that still need to be visited!
	printf("ALL PATHS TRAVERSED\n");
	int stop = 1;
	static bool endMap = false;
	int isDeadEnd = getType();
	if (isDeadEnd == 1) {
		new_DetermineDirection();
	}
	else {
		for (int i = 0; i <= intersection; i++) {
			stop = 1;
			if (pointArray[i] == Coordinate[xcoor][ycoor]) {
				printf("COMPARING: %d TO %d\n", Coordinate[xcoor][ycoor], pointArray[i]);
				if (exploredArray[i - 1] < typeArray[i - 1]) {
					printf("FOUND NODE THAT STILL NEEDS TO BE EXPLORED. NODE IS: %d\n", pointArray[i - 1]);
					printf("XCOOR: %d\n", xcoor);
					printf("YCOOR: %d\n", ycoor);
					printf("GETXCOOR: %d\n", getCoor[pointArray[i - 1]][0]);
					printf("GETYCOOR: %d\n", getCoor[pointArray[i - 1]][1]);
					// Determine Direction
					if (ycoor == getCoor[pointArray[i - 1]][1]) {
						if (xcoor > getCoor[pointArray[i - 1]][0]) {
							Direction = 3;
						}
						else if (xcoor < getCoor[pointArray[i - 1]][0]) {
							Direction = 1;
						}
					}
					else if (xcoor == getCoor[pointArray[i - 1]][0]) {
						if (ycoor > getCoor[pointArray[i - 1]][1]) {
							Direction = 2;
						}
						else if (ycoor < getCoor[pointArray[i - 1]][1]) {
							Direction = 4;
						}
					}
					travel();
					stop--;
				}
				else if (exploredArray[i + 1] < typeArray[i + 1]) {
					printf("FOUND NODE THAT STILL NEEDS TO BE EXPLORED. NODE IS: %d\n", pointArray[i + 1]);
					printf("XCOOR: %d\n", xcoor);
					printf("YCOOR: %d\n", ycoor);
					printf("GETXCOOR: %d\n", getCoor[pointArray[i + 1]][0]);
					printf("GETYCOOR: %d\n", getCoor[pointArray[i + 1]][1]);
					// Determine Direction
					if (ycoor == getCoor[pointArray[i + 1]][1]) {
						if (xcoor > getCoor[pointArray[i + 1]][0]) {
							Direction = 3;
						}
						else if (xcoor < getCoor[pointArray[i + 1]][0]) {
							Direction = 1;
						}
					}
					else if (xcoor == getCoor[pointArray[i + 1]][0]) {
						if (ycoor > getCoor[pointArray[i + 1]][1]) {
							Direction = 2;
						}
						else if (ycoor < getCoor[pointArray[i + 1]][1]) {
							Direction = 4;
						}
					}
					travel();
					stop--;
				}
				else if ((exploredArray[i - 1] >= typeArray[i - 1]) && (exploredArray[i + 1] >= typeArray[i + 1])) {
					stop++;
				}
			}
		}
	}
	// Sketchy code for sketchy mazes
	/*if (isDeadEnd == 3) {
	// Backtrack just in case
	// uhh
	if (Direction = 1) {
	Direction = 3;
	}
	else if (Direction = 2) {
	Direction = 4;
	}
	else {
	Direction = Direction - 2;
	}
	travel();
	}
	else */
	if (stop == 2) {
		isMapping = false;
		printf("ROVER DIRECTION IS: e\n");
		directionToRover();
	}
	else {
		printf("NEW DIRECTION: %d\n", Direction);
		directionToRover();
	}
}

void old_DetermineDirection() {
	// North=2, South=4, East=1, West=3
	bool directionNew = true; // place at top
	int compareType = 0; // place at top

	if (Direction == 1) {
		if ((int)dataIR.front.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor < getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 1;
				xcoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.left.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor > getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 2;
				ycoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.right.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor < getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 4;
				ycoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType()) {
			traversedAdjacentPath();
		}
	}
	else if (Direction == 2) {
		if ((int)dataIR.right.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor < getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 1;
				xcoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.front.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor > getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 2;
				ycoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.left.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor > getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] >= typeArray[i] && Coordinate[xcoor][ycoor] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 3;
				xcoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType()) {
			traversedAdjacentPath();
		}
	}
	else if (Direction == 3) {
		if ((int)dataIR.right.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor > getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 2;
				ycoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.front.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor > getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] > 0 && typeArray[i] != 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 3;
				xcoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.left.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor < getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 4;
				ycoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType()) {
			traversedAdjacentPath();
		}
	}
	else if (Direction == 4) {
		if ((int)dataIR.left.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor < getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 1;
				xcoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.right.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (xcoor > getCoor[i][0] && ycoor == getCoor[i][1]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 3;
				xcoor--;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if ((int)dataIR.front.Red != 255) {
			directionNew = true;
			for (int i = 0; i <= intersection; i++) {
				if (ycoor < getCoor[i][1] && xcoor == getCoor[i][0]) {
					if (exploredArray[i] > 0) {
						directionNew = false;
					}
				}
			}
			if (directionNew == true) {
				Direction = 4;
				ycoor++;
				printf("NEW DIRECTION: %d\n", Direction);
				directionToRover();
				return;
			}
			else if (directionNew == false) {
				compareType++;
			}
		}
		if (compareType == getType()) {
			traversedAdjacentPath();
		}
	}
}

// End Helper Functions //

void main() {
	BMP img, imgTemp;
	snprintf(outFile, sizeof(char) * 32, "mapped%i.bmp", fileNum);
	img.ReadFromFile("grid_Actual.bmp");
	imgTemp.ReadFromFile("grid_Actual.bmp");
	imgTemp.WriteToFile(outFile);
	dataBMP(img);

	// Declare States
	enum states {
		getBearing, moveRover, finishedMapping
	}systemstate;
	systemstate = getBearing;

	// Local Variables //
	// Assign Red Pixel to Variable
	RGBApixel pixelRed;
	pixelRed.Red = 250;
	pixelRed.Blue = 0;
	pixelRed.Green = 0;
	RGBApixel pixelGreen;
	pixelGreen.Red = 0;
	pixelGreen.Blue = 0;
	pixelGreen.Green = 255;
	// Pixel Colors: (Red,Green,Blue)
	//		Black: 0,0,0
	//		White: 255,255,255
	//		Red:   255,0,0
	// End Local Variables //

	while (1) {
		getDataIR(imgTemp);
		nodeDistance++;  // Node Distance to simulate encoder data

		// Mark spot on map where rover has been
		imgTemp.SetPixel(xcoor, ycoor, pixelRed);
		imgTemp.WriteToFile(outFile);

		switch (systemstate) {
		case getBearing:
			// Rover begins at a starting point '0' and sets initial values
			// Sends node data to pi
			// (6,30) is starting coordinate for bmp
			nodeDistance--;
			pointArray[intersection] = 0;
			exploredArray[intersection]++;

			displayDataMovement();
			displayDataIR();
			displayDataArrays();

			imgTemp.SetPixel(xcoor, ycoor, pixelGreen);
			imgTemp.WriteToFile(outFile);

			saveCoordinate();
			printf("ROVER DIRECTION IS: s\n");

			travel();
			systemstate = moveRover;
			break;
		case moveRover:
			// Move rover in set direction until it comes to an intersection
			if ((int)dataIR.right.Red == 255 && (int)dataIR.left.Red == 255 && (int)dataIR.front.Red != 255) {
				travel();
			}
			else {
				intersection++;
				typeArray[intersection] = getType();

				// Assuming that rover will never go back to the starting point
				if (Coordinate[xcoor][ycoor] > 0) {
					// Previous node identified
					pointArray[intersection] = Coordinate[xcoor][ycoor];
					exploredArray[Coordinate[xcoor][ycoor]]++;
					exploredArray[intersection] = exploredArray[Coordinate[xcoor][ycoor]] + 1;
					//exploredArray[Coordinate[xcoor][ycoor]]++;

					displayDataMovement();
					displayDataIR();
					displayDataArrays();
					printf("OLD POINT\n");

					// Write to pixel map
					imgTemp.SetPixel(xcoor, ycoor, pixelGreen);
					imgTemp.WriteToFile(outFile);
					imgTemp.SetPixel(xcoor, ycoor, pixelRed);
					fileNum++;
					snprintf(outFile, sizeof(char) * 32, "mapped%i.bmp", fileNum);

					old_DetermineDirection();
					if (isMapping == false) {
						systemstate = finishedMapping;
					}
				}
				else {
					// New node identified
					pointArray[intersection] = Total_Points;
					exploredArray[intersection]++;
					Total_Points++;
					displayDataMovement();
					displayDataIR();
					displayDataArrays();

					imgTemp.SetPixel(xcoor, ycoor, pixelGreen);
					imgTemp.WriteToFile(outFile);
					imgTemp.SetPixel(xcoor, ycoor, pixelRed);

					saveCoordinate();

					// Determine Direction and break
					new_DetermineDirection();
					if (isMapping == false) {
						systemstate = finishedMapping;
					}
				}
			}
			break;
		case finishedMapping:
			printf("MAPPING COMPLETE!!!\n");
			imgTemp.SetPixel(xcoor, ycoor, pixelGreen);
			imgTemp.WriteToFile(outFile);
			return;
			break;
		}
	}
}