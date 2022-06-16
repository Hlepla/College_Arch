/*
  Hayden Lepla
  9/23/15
  CS120-06
  Lab 3
  Assgn num: 3.1

*/

#include <iostream>
#include <cmath>


using namespace std;


int main() {




  double a , b , total ;

  double pi = 3.14 ;

  cout <<"Welcome to the ellipse calculator." << endl ;


  cout <<"Please enter a value for diameter A: " << endl ;
  cin >> a ;


  if( a <= 0 ){  // will check for invalid inputs for value a, if true, the program will terminate
    
    cout << "The input is invalid ( less than or equal to zero) please try again: " << endl ;
    
    return 0 ;
    
  }
  
  
  cout << "Please enter a value for diameter B: " << endl ;
  cin >> b ;


  if ( b <= 0 ){ // checking for invalid inputs for value b, if true, program will terminate

    cout << "The input is invalid ( less than or equal to zero) please try again: " << endl ;

    return 0 ;

  }


  if ( a == b || b == a ){  // verifies if both inputs are the same 

    cout << "The elipse is a circle! " << endl ;

  }

  
  total = ( 2 * pi) * ( sqrt (   ( ( pow (a,2) + pow (b,2)) / 2 ) )  )    ;


  cout << "The circumference of the ellipse with the values " << a << " " << "and " <<  b << " is the total: " << total << endl ;


  return 0 ;

}

