/* Hayden Lepla
   CS-120-06
   12/9/15
   Lab 13
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Linkedlist.h"

using namespace std ;


int main(){

  int RN;
  char RT, com;
  string RM , filename ;
  ifstream infile;
  Linkedlist robots ;
  char cm1;
  int cm2;

  cout << "Enter robot data file: " << endl;
  cin >> filename ;

  infile.open( filename.c_str());

  while ( infile.eof()== false ) {

    infile >> RN >> RT >> RM ;
    robots.Add(RN , RT , RM);
  }
  infile.close();


do
  {
    cout <<"Enter robot command: " << endl ;
    cin >> cm1 ;
    
    switch(cm1){
      
    case 'D':
      cin >> cm2 ;
      robots.deploy('S', cm2);
  
      break ;
      
    case 'd':
      cin>> cm2 ;
      robots.deploy('M', cm2);

      break;
      
    case 'R':
      cin>> cm2 ;
    robots.undeploy('S' ,cm2);

      break;
      
    case 'r':
      cin >> cm2 ;
      robots.undeploy('M' , cm2);
            
      break;
      
    case '?':
      cin >> cm2 ;
      robots.status(cm2);

      break ;
      
    case 'S' :
      cout<<"Scouts in holding bay: " << robots.scoutsInBay()<< endl ; 
      break ;
      
    case 's':
      cout <<"Scouts deployed: " << robots.getScoutsDeployed()<< endl ;
      break ;
      
    case 'M' : 
      cout << "Miners in holding bay: " << robots.minersInBay()<< endl ;
      break ;
      
    case 'm' :
      cout <<"Miners deployed: " << robots.getMinersDeployed()<< endl ; 
      break ;
      
    case 'q' :
      return 0 ;
      break ;
      
    default:
      
      cout<<"Invalid command, please try again: " << endl ;
      
      break;
     
      
    }
    
  }
 while (1) ;
 
}

