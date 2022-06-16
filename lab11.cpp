/* Hayden Lepla
   CS 120
   4/7/15
   Lab11
*/

#include <iostream>
#include "Inval.h"
#include <string>
#include <cstdlib>

using namespace std ;



int main(){

  int value ,outbase, base  ;
  string value2 ;
  Inval A ;
  int i;

  while(1) {
    
    cin >> value >> value2 ;

    if ( value < 2 || value > 16){

      cout << "Invalid input: " << value <<  endl ;
      cout << "Terminating.." << endl ;
      return 0 ;
    }
    A.setinput_base(value);
    A.setinput_Num(value2);
    A.convertdecimal();


    for (  i=0 ; i < 15 ; i++ ){
      cin >> outbase;
     
      if ( outbase < 2 || outbase > 16){
	
	break ;
      }
      A.setinput_base(outbase);
      A.PrintAsBase();
      
    }
  }
}
