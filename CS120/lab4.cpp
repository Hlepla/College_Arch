/* Hayden Lepla
   CS120-06
   9/30/15
   Lab4
   Assignment 4.1

*/


#include <iostream>


using namespace std;


int main() { 
  
  
  
  int i, j ;
  
  
  cout << "    0  1  2  3  4  5  6  7  8  9 " << endl ; // prints top row of the table
  
  for ( i = 40 ; i < 120 ; i+=10 ){
        
    
    cout << i << "  " ;
    
    for ( j = 0 ; j < 10 ; j++)  {
      
      cout << char(i+j) << "  " ; // prints ascii characters
      
    }    
    
    cout << endl ;
    
  }
  
  
  
  return 0 ;
}
