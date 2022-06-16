/* Hayden Lepla
   cs120
   lab 7
   3/9/15
*/

#include <iostream>

using namespace std ;

void inputArrayElements(int iArray[10]);
float calculate_sum(int iArray[10]);
float calculate_average(int iArray[10]);
void PrintArrayElements(int iArray[10]);
void AccessNthElement(int iArray[10] , int N);

int main(){

  int iArray[10] ;
  
  inputArrayElements(iArray);
  calculate_sum(iArray);
  calculate_average(iArray);
  PrintArrayElements(iArray);
  AccessNthElement(iArray , 11);
  AccessNthElement(iArray, 10000);
  return 0 ;
}


void inputArrayElements(int iArray[10]) {

  int i ;

  cout << "Input 10 values for i: " ;

  for ( int i=0 ; i < 10 ; i++ ){

    cin >> iArray[i] ;

    cout << "Element:" << iArray[i] << endl ;
      }
  return ;
}

float calculate_sum( int iArray[10]){

  int i , sum =0 ;

  for ( int i=0 ; i < 10 ; i++ ) {

    sum += iArray[i];
  }
  cout << "The Sum is " << sum<< endl;
  return sum ;


}
float calculate_average(int iArray[10]){
  int sum ;
  float final ;

  final = sum / 10.0 ;

  cout << "The average is: " << final << endl ;

  return final ;
}

void PrintArrayElements( int iArray[10]){


}

void AccessNthElement( int iArray[10] , int N ){

  cout << iArray[N-1] << endl;

}
