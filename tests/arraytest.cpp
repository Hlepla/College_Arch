#include <iostream>

using namespace std;

int main()
{

  int *array ;

  array = new int [5] ;
  cin >> array[2] ;

  for (int i=0 ; i < 5 ; i++)
    {
      // cin >> array[i] ;
      
  cout << array[i] << endl ;
    }

  return 0 ;


}
