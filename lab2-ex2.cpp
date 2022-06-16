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

r= pow(a, 2);
s= pow(b,2);
sum =( s+r)/2;
d=sqrt(sum);

c=d*2*pie;

cout<< "the total equals: "<< c << endl;

return 0;
}



