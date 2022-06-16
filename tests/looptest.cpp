#include <iostream>

using namespace std;


int main(){


  int i , j ;


  for ( i = 0 ; i < 4 ; i++)
    {

      for ( j = i ; j < 3 ; j++ )
	{
	  if ( j < 2 )
	    cout << i << "  " << j << endl ;
	  else
	    cout << j << endl ;
	}
    }



}
