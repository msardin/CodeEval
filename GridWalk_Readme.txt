2019-07-12

GridWalk Notes
--------------

For the fun of it, I solved the problem in both C++ & Python.
Both solutions used recursion.  Since the Python script was slower
and blowing the CodeEval maximum computational time limits,
I started looking into optimization techniques.  After being
unsuccessful, I then turned my attention to examining the solution
space.

Aha moment!  There is symmetry in the solution, thus I only had
to compute 1/4 the solution, then essentially multiply by 4.
FYI, I did have to adjust the solution a bit further, see the code.

* Months later, I found someone who claimed he only had to compute
1/8 of the solution.  FYI, I never confirmed the claim.