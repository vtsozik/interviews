-------------------------------------------------------------------------------- 
DESCRIPTION (problem1: ecc5a3ff-5646-4460-bddb-19305fe936d7)

John likes to ride his bike down hill and hates to push pedal climbing up hill. There are few buses 
running along the same routes John usually rides. Naturally John prefers to use bus to skip the most 
unpleasant part of his ride. Based on his many years of experience he has rated segments of the road 
in between bus stops, using positive values for downhill roads and negative for up hill or flat (no zeros).

John wants to plan/select his trips such that the combined cycling rating is maximized and positive.
This could result that he may need to bicycle along a part he does not like, provided that it joins
with other part(s) he enjoys enough to compensate. It may be that no part of the route is suitable 
for cycling so that John takes the bus for its entire route. Conversely, it may be that the whole 
route is so good that John will not use the bus at all.

Create a computer program to help John to identify the best longest continuous part 
to bicycle for a given bus route.

-------------------------------------------------------------------------------- 
ASSIGNMENT:

1. Create a high-performance program modifying provided files: "main.cpp" and "solver.h".
2. Use "main.cpp" as your "main" module.
3. Use "solver.h" implement the following function:
   // iterator and value_type of *It
   // out.first  - starting stop number or -1
   // out.second - ending stop number or -1
   template<class It, class T>
   void solver(It begin, It end, std::pair<int, int> &out);
4. Return zipped/tared copy of this directory with your answers coded-in.
5. No 3rd party libraries are allowed to be used.   STL can be used if desired.
6. Results of this is based on correct functional behavior, code quality/cleaniness and based on fastest performance
7. Please indicate how long the application to you to create when you return the code.
8. Code must be written in C/C++ and run on Linux

-------------------------------------------------------------------------------- 
INPUT:

Program takes one argument: input file name. That file may contain information on several bus routes:
- The first line of the file is a single integer N representing the total number of bus routes to process
- Each route description begins with the number of bus stops on the route (an integer S)
- Followed by S - 1 lines containing John's road rating between corresponding stops

-------------------------------------------------------------------------------- 
OUTPUT:

Using standard out, print a line for each bus route, containing the route number, starting 
and ending bus stop numbers, that identify the continuous segment of the route which yields 
the maximal positive rate sum:

         rsum = r(i) + r(i+1) + ... + r(j-1)

If more than one solution exist use the first one. In case of no solution: print "no cycling"

---------------------------------
SAMPLE INPUT:

3
3
  -3
   7
10
   12
  -15
   12
  -9
   12
   12
  -12
   12
  -15
4
  -7
  -2
  -8

---------------------------------
SAMPLE OUTPUT: 

route 1: cycle between stops 2 and 3
route 2: cycle between stops 3 and 9
route 3: no cycling
