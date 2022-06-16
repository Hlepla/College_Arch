#include <iostream>
#include <cmath>
#include <string>
#include "Inval.h"
using namespace std ;

  void Inval :: setinput_base (int base){

    inbase = base ;
  }


void Inval :: setNumber (int Inbase){


  number = Inbase;
}


void Inval :: convertdec(){

  if ( inbase < number) {

    cout << inbase ;
    return ;
  }

  int rem ;

  rem = inbase  % number ;
  convertdec( inbase / number , number);

  cout << rem ; 
}



void PrintAsBase(){

  int decval=0;
  
  for ( int i = 0 ; i < number.size();i++){

    decval += number[i] * pow(inbase , number.size()-1-i);
  }

}
