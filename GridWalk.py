'''
Name        : GridWalk.py
Author      : Martin Sardin, BSEE/MSCS
Email       : Martin.Sardin@gmail.com
Date        : March 2012

Description :
  CodeEval Challenge -  Grid Walk
  There is a monkey which can walk around on a planar grid. The monkey can
  move one space at a time left, right, up or down. That is, from (x, y)
  the monkey can go to (x+1, y), (x-1, y), (x, y+1), and (x, y-1). Points
  where the sum of the digits of the absolute value of the x coordinate plus
  the sum of the digits of the absolute value of the y coordinate are lesser
  than or equal to 19 are accessible to the monkey. For example, the point
  (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30, which is greater
  than 19.  Another example, the point (-5, -7) is accessible because
  abs(-5) + abs(-7) = 5 + 7 = 12, which is less than 19. How many points
  can the monkey access if it starts at (0, 0), including (0, 0) itself?
  Input sample:
    There is no input for this program.
  Output sample:
    Print out the how many points can the monkey access. (The number should
    be printed as an integer whole number eg. if the answer is 10, print
    out 10, not 10.0 or 10.00 etc

Development Environment:
  Eclipse IDE with PyDev and Python 2.7.2 in a Windows Vista OS environment
---------------------------------------------------------------------------
ALGORITHM NOTES:
    Utilized the symmetry of the solution in the planar grid.  This allowed
    me to save computation time by only having to compute 1/4 the solution.
---------------------------------------------------------------------------
'''

import Queue

class GridWalk :
    def __init__(self):
        self.maxGridSize  = 600
        self.gridMidPoint = self.maxGridSize / 2
        self.gridArray = [ [ 0 for i in range(self.maxGridSize) ] \
                          for j in range(self.maxGridSize) ]

        for i in range(self.maxGridSize):
            for j in range(self.maxGridSize):
                self.gridArray[i][j] = False
       
    def sumOfDigits(self, X, Y):
        X = abs(X);     Y = abs(Y)
        newGridMove = `X` + `Y`
        digitSum = 0
        for i in range(len(newGridMove)):
            digitSum += int(newGridMove[i])
        return digitSum
        
    def validGridPoints(self):
        qX = Queue.Queue(0)
        qY = Queue.Queue(0)
        numOfValidGridPoints = 0
        
        # ------------------------------------------------------
        # Compute 1/4 the solution in the planar grid.
        # ------------------------------------------------------
        qX.put(0)   # Preload the queue w/ the 1st coord to process
        qY.put(0)
        
        while not qX.empty():
            X = qX.get();   Y = qY.get()
            newX = self.gridMidPoint + X
            if newX >= 0 and newX < self.maxGridSize : 
                Ymod = self.gridMidPoint + Y
                if self.gridArray[newX][Ymod] != 1:
                    if (self.sumOfDigits(X, Y)) <= 19 :
                        self.gridArray[newX][Ymod] = 1
                        numOfValidGridPoints += 1
                        qX.put(X+1);  qY.put(Y  ) 
                        qX.put(X  );  qY.put(Y+1) 
 
        # ------------------------------------------------------
        # Compute the XY axis solution space
        # ------------------------------------------------------
        for i in range(self.maxGridSize): 
            self.gridArray[i][self.gridMidPoint] = False
        for j in range(self.maxGridSize):
            self.gridArray[self.gridMidPoint][j] = False
 
        qX.put(0);  qY.put(0)
        subtract = 0
        while not qX.empty():
            X = qX.get()
            Y = qY.get()
            newX = self.gridMidPoint + X
            if newX >= 0 and newX < self.maxGridSize : 
                Ymod = self.gridMidPoint + Y
                if self.gridArray[newX][Ymod] != 1:
                    if (self.sumOfDigits(X, Y)) <= 19 :
                        self.gridArray[newX][Ymod] = 1
                        subtract += 1
                        qX.put(X+1);  qY.put(Y  ) 
                        qX.put(X  );  qY.put(Y+1) 
 
        # Multiply the quadrant; Add the XY axis; Subtract the extra origin 
        numOfValidGridPoints = (numOfValidGridPoints-subtract)*4 + subtract*2 - 1
        
        return numOfValidGridPoints
    
# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
if __name__ == '__main__':
    gw = GridWalk()
    print gw.validGridPoints()