#include <cmath>
#include <iostream>

using namespace std;

int main()

{

double a, b, c, d, r, s, sum;
double pie= 3.14;
cout <<" Enter number for a: " << flush;

cin >> a;

cout << " Enter number for b: " << flush;

cin >> b;


if (a <= 0 || b <= 0)
{

cout << " Invalid input, please try again" << endl ;

return 0;

}


r= pow(a, 2);
s= pow(b,2);
sum =( s+r)/2;
d=sqrt(sum);

c=d*2*pie;

if (a==b)
{

cout << "The total of the circumference of the two radii " << a << " and " << b ; 

cout << " is " << c << endl ;
}

else
{
cout << " The total of the elipse of " << a << " and " << b ;

cout << " is " << c<< endl ;
}

return 0;
}


