#include <iostream>
#include <bitset>


using namespace std ;


int main()
{

  int number = 0x0 ;


  cout << bitset<4>(number).to_string() ;

  return 0 ;

}
