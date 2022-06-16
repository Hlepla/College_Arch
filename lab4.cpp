/* Hayden Lepla
2/10/15
cs120
*/

#include <iostream> 

using namespace std ; 

int i , j ;

int main() 

{

cout << "    0  1  2  3  4  5  6  7  8  9  " << endl;

for (i=40 ; i < 120 ; i += 10 )
{

cout << i << "  " ;

	for ( j=0 ; j < 10 ; j++ ) 
	{
		cout << char( i +j )<< "  " ;
	}
cout << endl; 
}
 return 0; 
}

