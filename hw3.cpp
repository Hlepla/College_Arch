/* this program is designed to keep track of the number of generations of bees

Hayden Lepla
Wilder
cs120
hw2.cpp
2/20/2015

 */

#include <iostream>

using namespace std ;

int bee = 1, prebee = 0 , gen , final , total , beecount[25] ;

char command ;

const char C = 'C' ;

const char S = 'S' ;

const char E = 'E' ;

int func() ; // prototype



int main() // beginning of the program

{
  int a ;

  command = C; // declaration of c

  cout << " ** The Hundred-Acre Apiary Analysis Tool ** " << endl ;
  a = func();
}

int func () {

 Label1:

  while ( command == C || command == S || command == E ) {

    cout << " Enter a command : " ;

    cin >> command ;

    if ( command != 'S' && command != 'C' && command != 'E') { 
      cout <<"Invalid command  "<<endl;
      return 0;
    }
    if ( command == 'S' || command == 'C' ) {
    cout << " Enter ancestral generation number: ";

    cin >> gen;
    }

    if ( gen <= -1 || gen >= 26 ) {

      cout << " Error: input is less than 0 or greater than 25 " << endl;

      goto Label1;
    }

    if ( gen == 0 && command != 'E' ) { 
      cout << " ancestral generation " << gen << " contains 1 honeybee " << endl ;

    }

    if ( command == 'C' ) {
      bee = 1;
      prebee = 0;
      if ( gen > 0 && gen <= 25) { 
	
	for ( int i = 0 ; i < gen ; i++ ) {
			
	  final = bee + prebee ;
			
	  prebee = bee ;

	  bee = final ;
	}
      }

	
      cout << "ancestral generation " << gen << " contains " << final << " honeybee" << endl;
    }

    if ( command == 'S' ) {
      bee = 1;
      prebee = 0;
      if ( gen > 0 && gen <= 25 ) {
	  
       	for ( int i = 0 ; i < gen + 2; i++ ) {

	  final = bee + prebee ;
		
	  prebee = bee ;
		
	  bee = final ;
	}
      }

      cout << " Generations 1.. " << gen << " contain " << final - 2 << " ancestors " << endl ;

    }

    if ( command == 'E' ){
      bee = 1 ;
      prebee = 0 ;
      int beecount[25] , count ;

      cout << "Enter the number of bees to find: " ;
      cin >> count ;  

      if ( count <= -1 || count > 121393 ) {

	cout << " Error: input is less than 0 or greater than 25 " << endl;

	goto Label1;
      }
      
      if ( count > 0 && count <= 121393) {

	for ( int i = 0 ; i < 25 ; i++ ){
	  
	  final = bee + prebee ;

          prebee = bee ;

          bee = final ;
	  
	  beecount[i] = bee ;
	}
	int check = 0 ;

	for (int i = 0 ; i < 25 ; i++) {

	  if ( beecount[i]== count ){
	    check = 1 ;
	cout << "Ancestral generation " << i+1  << " contains " << count << " bees " << endl ;
	  }
	  
   
	}
	if ( check ==0 ){
	  cout << "No ancestral generation contains " << count << endl ;
	}
      }


  

    }
  
  }
  return 0;

}
