# Direction-Simulation Code:

This code has two functions:
	1.  It determines the next directon for the rover to take at an intersection
	2.  It simulates the rover moving through an unknown map
	
The method for determining the rover's next direction was taken from the article,
"Maze solving algorithm for line following robot and derivation of linear path distance from nonlinear path"
by Sakib, S. ; Chowdhury, A. ; Ahamed, S.T. ; Hasan, S.I.
	Link: http://ieeexplore.ieee.org/xpl/abstractAuthors.jsp?reload=true&tp=&arnumber=6997314&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6997314
	
In order to simlate the rover, a bitmap was created.  The "rover" drew a red line
behind itself as it moved through the bitmap.  In order to create and update the 
bitmap, the EasyBMP library was used.