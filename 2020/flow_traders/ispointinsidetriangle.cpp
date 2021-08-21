/* Find if given  points A(x,y1), B(x2,y2) and C(x3,y3) are forming i
 * a triangle, return 0 if not, add 1 to the total score score otherwise.
 * Find if point P(xp, yp) is inside the triangle. Add 1 to total
 * score if it is.
 * Find if point Q(xq, yq) is inside the triangle. Add 2 to total
 * score if it is.
 * Return the total score.
 */

#include <unistd.h>
#include <math.h>
#include <iostream>
using namespace std;

double computeArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return abs(y1 * (x2 - x3) + y2 * (x3 - x1) + y3 * (x1 - x2))/2.0;
}

int arepointsinsidetriangle(int x1, int y1, int x2, int y2, int x3, int y3,
		            int xp, int yp, int xq, int yq)
{
       int s(0);
       double a(computeArea(x1, y1, x2, y2, x3, y3));
       if (a > 0.)
       {
           s = 1;
           double ap1(computeArea(xp, yp, x2, y2, x3, y3));
           double ap2(computeArea(x1, y1, xp, yp, x3, y3));
           double ap3(computeArea(x1, y1, x2, y2, xp, yp));
	   if (a == ap1 + ap2 + ap3)
	   {
              ++s;
	   }
	   s = 1;
           double aq1(computeArea(xq, yq, x2, y2, x3, y3));
           double aq2(computeArea(x1, y1, xq, yq, x3, y3));
           double aq3(computeArea(x1, y1, x2, y2, xq, yq));
           if (a == aq1 + aq2 + aq3)
           {
              s += 2;
           }
       }
       return s;
}

void test(int diag)
{
   srand(time(NULL));
   int nt(diag * diag);
   for (int i(0); i < nt; ++i)
   {
       int x1(rand() % diag);
       int y1(rand() % diag);
       int x2(rand() % diag);
       int y2(rand() % diag);
       int x3(rand() % diag);
       int y3(rand() % diag);
       int xp(rand() % diag);
       int yp(rand() % diag);
       int xq(rand() % diag);
       int yq(rand() % diag);
       int s(arepointsinsidetriangle(x1, y1, x2, y2, x3, y3, xp, yp, xq, yq));
       switch(s) 
       {
           case 0:
               cout << "Invalid triangle!" << endl
	            << "A(" << x1 << ',' << y1
	            << "); B(" << x2 << ',' << y2
	            << "); C(" << x3 << ',' << y3 << ')' << endl;
	       break;
	   case 1:
               cout << "Both p and q points are out!" << endl;
	       break;
	   case 2:
               cout << "Point p is in, point q is out!" << endl;
	       break;
	   case 3:
               cout << "Point p is out, point q is in!" << endl;
	       break;
	   case 4:
               cout << "Both p and q points are in!" << endl;
	       break;
           default:
               cout << "Invalid score value: " << s << endl;
	       exit(-1);
       }
   }
}

int main()
{
   test(10);
}
