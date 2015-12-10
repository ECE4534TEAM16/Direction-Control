# Direction Implementation Code:

This codes determines the next direction for the Mapper rover to take from an intersection and is designed to be
integrated with the rover control thread.  The next direction for the rover to take is returned from the approachIntersection 
function as a char.  There are five possible directions that can be returned:
	'f' = rover to go forward
	'r' = rover to go right
	'l' = rover to go left
	't' = rover to go backwards
	'E' = rover to stop mapping
	
This direction is determined from the four inputs to the approachIntersection functions.  The four inputs include IR sensor and encoder
information.  Each inputs is received from the rover control thread.  All the functionality for the code is implemented within these functions.
There are no global variables needed.