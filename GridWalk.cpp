//============================================================================
// Name        : GridWalk.cpp
// Author      : Martin Sardin, BSEE/MSCS
// Email       : Martin.Sardin@gmail.com
// Date        : March 2012
//
// Description :
//   CodeEval Challenge -  Grid Walk
//   There is a monkey which can walk around on a planar grid. The monkey can
//   move one space at a time left, right, up or down. That is, from (x, y)
//   the monkey can go to (x+1, y), (x-1, y), (x, y+1), and (x, y-1). Points
//   where the sum of the digits of the absolute value of the x coordinate plus
//   the sum of the digits of the absolute value of the y coordinate are lesser
//   than or equal to 19 are accessible to the monkey. For example, the point
//   (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30, which is greater
//   than 19.  Another example, the point (-5, -7) is accessible because
//   abs(-5) + abs(-7) = 5 + 7 = 12, which is less than 19. How many points
//   can the monkey access if it starts at (0, 0), including (0, 0) itself?
//   Input sample:
//     There is no input for this program.
//   Output sample:
//     Print out the how many points can the monkey access. (The number should
//     be printed as an integer whole number eg. if the answer is 10, print
//     out 10, not 10.0 or 10.00 etc
//
// Development Environment:
//   Eclipse IDE and the MinGW GCC Tool chain
//============================================================================

#include <cstdio>	// printf, sprintf
#include <cstdlib>	// abs
#include <cstring>  // strlen
using namespace std;

const static int  intMaxGridSize  = 600;
const static int  intGridMidPoint = intMaxGridSize / 2;

//============================================================================

class GridWalk {
public:
	GridWalk ( void );
	int  validGridPoints ( int intXStart, int intYStart );

private:
	int  sumOfDigits ( int intX, int intY  );
	void path (int intX_Start, int intY_Start);

	int  intGridArray[intMaxGridSize][intMaxGridSize];
	int  intValidGridPoints;
};

//============================================================================

GridWalk :: GridWalk (void)
{
	// Initialize Grid Array; 0 = Monkey has not entered
	for ( int i=0; i < intMaxGridSize; i++)
		for ( int j=0; j < intMaxGridSize; j++) intGridArray[i][j] = 0;

	intValidGridPoints = 0;
}

//============================================================================
// int GridWalk :: sumOfDigits ( int intX, int intY )
//
// Description:
//   Sum the digits of the integers and ignore the negative sign
//============================================================================

int GridWalk :: sumOfDigits ( int intX, int intY )
{
	char   charXY_Point[10];
	sprintf ( charXY_Point, "%d%d", abs(intX), abs(intY) );

	int intSum = 0;
	for ( int i = 0; i < (int)strlen(charXY_Point); i++ )
		intSum += charXY_Point[i] - '0';

	return intSum;
}

//============================================================================
// void GridWalk :: path (int intX, int intY)
//
// Description:
//   Recursively find all possible valid walking paths from a starting point
//   in a planar grid.  Return the number of valid grid points which doesn't
//   violate the boundary conditions.
//============================================================================

void GridWalk :: path (int intX, int intY)
{
	// Test if proposed new grid move is Grid Array out-of-bounds
	if ( (intX + intGridMidPoint) < 0 ||  (intX + intGridMidPoint) >= intMaxGridSize)  {
		printf("Error: Grid Array Out-Of-Bounds: (%d,%d)\n", intX, intY);
		return;
	}

	int intXmod = intGridMidPoint + intX;
	int intYmod = intGridMidPoint + intY ;

	// Test if new grid move has been entered before
	if ( intGridArray[intXmod] [intYmod] == 1 ) return;

	// Test if the proposed new grid move is Sum of Digits is > 19
	if ( sumOfDigits(intX, intY) > 19 )  return;

	// Add new Grid Move;  1 = Monkey has entered Grid Point
	intGridArray[intXmod] [intYmod] = 1 ;
	intValidGridPoints++;

	// Generate new possible Grid moves
	path ( intX - 1, intY     );
	path ( intX + 1, intY     );
	path ( intX    , intY - 1 );
	path ( intX    , intY + 1 );
}

//============================================================================

int  GridWalk :: validGridPoints (int intXStart, int intYStart)
{
	intValidGridPoints = 0;
	path ( intXStart, intYStart );
	return intValidGridPoints;
}

//============================================================================

int main() {
	GridWalk gw;

	printf("%d\n", gw.validGridPoints(0,0));

	return 0;
}
