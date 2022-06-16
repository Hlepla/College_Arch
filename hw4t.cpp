/* Hayden Lepla
   Cs 120
   03/25/15
   hw4
*/

#include <iostream>
#include <string> 
#include <sstream>
using namespace std ;

string str = " " ;
void forage() ;
void Rforage() ;
void NUM() ;
void resources() ;


int bee = 8 ;
int worker = 8, forager = 8, nurse, guard, Queen = 1 ;
float Pollen = 0, Nectar = 0.05, Water = 0, Propolis = 0 ;
float Pollen1, Nectar1, Water1, Propolis1 ;
float tpollen, tnectar, twater, tpropolis ;
int simday = 1 ;
char a,b,c ;
double num = 0;

int main() {
  cout<< ")8( The Hundred-Acre Apiary Hive Simulator )8(" << endl ;
 do {
 Label1:
  str = " " ;
 cout<< "Enter command: ";
 cin>> str ;
 
 if (str == "?"){
  cout<<"Error: ? command requires 1 operand."<< endl ;
 goto Label1 ;
 }
 
 if (str == "??" || str == "?f" || str == "?w" || str == "?t") {
  cout<<"Error: Operand to ? must be one of (FTW)." << endl ;
 goto Label1 ;
 }
 if (str == "?F" ) {
  resources() ;
        goto Label1 ;
 }
 if (str == "?W") {
  NUM() ;
        goto Label1 ;
 }
 if (str == "T") {
  simday += 1 ;
        forage() ;
        Rforage() ;
        goto Label1 ;
 }
 if (str == "?T") {
  cout<<"It is sim-day " << simday << "." << endl ;
        goto Label1 ;
 }
 if (str[0] == 'W') {
  if (str == "W"){
	  cout<<"Error: W command requires 2 operands>" << endl;
 goto Label1 ;
        }
        if (str[1] == '+' || str[1] == '-'){
	  istringstream buf(str.substr(2)) ;
        buf >> num ;
        bee = num ;
        if ( num <=0 || num  >= 1000001){
	  cout<< "Error: Operand must be greater than 0 and less than 1000001." << endl ;
        num = 0 ;
        }
        if (str[1] == '-'){
          num = -1 * num ;
        }
        }
 }
 else
   cout<<"Error: Operand to W command must be greater than 0 or less than 1000001." << endl;
 NUM() ;
 goto Label1 ;
 }
 while (str == "X") ; {
  return 0 ;
 }
 if (str != "X") {
	  cout<<"Error: Unrecognized command>" << endl ;
	}
	if (bee <= 0) {
	  cout<<"The hive has perished on sim-day "<< simday<< "." << endl;
	  return 0 ;
	}
}

void NUM() {
  worker = num ;
  if (worker <= 12){
    cout<<"#Workers: 8 " << endl ;
    cout<<"#Foragers: 8 " << endl;
  }
  
  else {
    forager = worker - (worker * 0.65) ;
    nurse = worker - (worker * 0.35) ;
    guard = worker - (nurse + forager ) ;
    
    cout<<"#Workers: "<<worker<< "."<< endl ;
    cout<<"#Foragers: " << forager << "."<<endl  ;
    cout<<"#Nurses: " << nurse << "." << endl ;
    cout<<"#Guard: " << guard << "." << endl ;
  }
}

void forage() {
  Pollen1 = (0.1 * forager) ;
  Nectar1 = (.05 * forager ) ;
  Water1 = ( 0.2 * forager ) ;
  Propolis1 = (.03 * forager ) ;
}

void Rforage() {
  Pollen =  Pollen1 -0.4 ;
  Nectar = 0.18 + (0.3 * worker) ;
  Water = 0.2 + (0.1 * worker ) ;
  Propolis = .06 ;
}

void resources() {
  tpollen = Pollen ;
  tnectar = Nectar ;
  twater = Water ;
  tpropolis = Propolis ;
  
  cout<<"Pollen: "<<tpollen<<"micrograms" << endl;
  cout<<"Nectar: "<<tnectar<<"micrograms" << endl;
  cout<<"Water: "<<twater<<"microliters" << endl;
  cout<<"Propolis: "<<tpropolis<<"microliters" << endl;
}


