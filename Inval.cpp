#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "Inval.h"


using namespace std;

void Inval ::  PrintAsBase (){

  int rem , i=0 , result = 0, tempData ;

  tempData = decimaldata ;

  // rem = tempData % inbase 
  // tempData = tempData / inbase ; 
  // rem = tempData % rem ;
  
   while(1) {
    
    rem = tempData % inbase ;
    tempData = tempData / inbase ;
    if ( i == 0 ){

      result = rem ;
      i++ ;
    }

    else{
      result = result * 10 + rem ;
    }

    if ( tempData < inbase)
      break ;
      }
  cout << "    " << result << " (base " << inbase << ")" << endl ;

}

void Inval :: setinput_base( int value){

  inbase = value ;

}

void Inval :: setinput_Num(string d){

  data = d ;

}

void Inval :: convertdecimal(){

  int size = data.length();
  int sum = 0 ;
  int digit ;

  for (int i=0 ; i < size ; i++ ){

    digit = (int)data[i] - '0' ;
 
    sum += digit * pow(inbase,(size-(i+1))); 				 
  
  }
  
  decimaldata = sum ;
  //return;

}
