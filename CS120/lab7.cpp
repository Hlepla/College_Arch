/* Hayden Lepla
   10/21/15
   CS120-06
   Lab7
   assignment: 7.1
*/

#include <iostream>

using namespace std ;


void get_value () ;

void print_value(int , float) ;

float calculate_sum() ;

float calculate_average( int) ; 

int array[10] ;
int a ;


int main()
{
  int totalsum ;

  float totalaverage ;

  get_value() ;

 totalsum = calculate_sum() ;

 totalaverage = calculate_average(totalsum) ;

 print_value( totalsum , totalaverage) ;

 return 0 ;
}


void get_value() 
{

  cout <<"Enter 10 values into the array: " ;

  for ( int i; i < 10 ; i++){

  cin >> array[a] ;

  }

  cout << "The values inputed into the array are: " << array[a] << endl ;

  return ;

}


float calculate_sum() 
{
  int total ;

  for (int j; j < 10 ; j++ ){
       
  total += array[a] ;
  
  }
  
  return total ;


}


float calculate_average(int totalsum)
{

  float average ;

  average =  totalsum / 10.00 ;

  return average ;



}


void print_value(int totalsum , float totalaverage)
{

  cout << "The sum of the array is: " << totalsum << endl ;

  cout << "The average of the array is: " << totalaverage << endl ;

  return ;


}
