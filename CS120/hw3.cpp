/* Hayden Lepla
   9/21/15
   CS120-06  
   hw2.cpp
*/


/* This program is intended to calculate the diameter, cost and weight for 3D printed  washers. */


#include <iostream>
#include <cmath>


using namespace std;



int main() {

  int batch ;

  float material_cost ;
    
  float inn_dia , out_dia , thickness , density , surface_area , weight , total_cost , sum  ;
  
  float pi = 3.14159 ;

  char command ;

  do {

    toplabel:

  cout << "Enter a command ( B, ? , X ): " ;
  cin >> command ;


  switch (command) {

  case 'B' :

  cout << "Inner diameter (in centimeters): " ; // user inputs dimensions
  cin >> inn_dia ;
  cout << endl ;

  cout << "Outer diameter (in centimeters): " ;
  cin >> out_dia ;
  cout << endl ;


  cout <<"Thickness (in centimeters): "  ;
  cin >> thickness ;
  cout << endl ;


  cout <<"Material density (in grams per cubic centimeters): " ;
  cin >> density ;
  cout << endl ;


  cout << "Material cost (in cents per gram): " ;
  cin >>  material_cost ;
  cout << endl ;


  cout << "Quantity in current batch: " ;
  cin >> batch ;
  cout << endl ;



  surface_area = ( pi * (pow ((out_dia / 2 ) , 2) )) - ( pi * (pow ((inn_dia / 2) , 2 ))) ; // calculats surface area of washer  


  weight = surface_area * thickness * density * batch ; // calculates weight of the washer in grams


  total_cost = ( material_cost / 100) * weight  ; // calculates totalcost for batch of washers 


  sum = sum + total_cost ; // calculates the running sum of the total cost


  cout << "Expected weight: " << weight << " grams." << endl ;


  cout.precision(2); // sets the decimal in 2 places, ensures the output is a real number
  cout.setf(ios::fixed);


  cout << "Expected cost: " << "$ " << total_cost << endl ;

  break ;

  case '?' :

    cout << "Total cost of all washers so far: " << "? " << sum << endl ;

    break ;


  case 'X' :

    cout << "Session terminated. " << endl ;

    return 0 ;


  default :

    cout << "Invalid command, please try again " << endl ;

    goto toplabel ;

    break ;


  }

 
  } while (1) ;


} 
