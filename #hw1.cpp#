/* this program is designed to keep track of the number of generations of bees */

#include <iostream>

using namespace std;

int bee = 1, prebee = 0 , gen , final ;

int main() // beginning of the program

{

cout << " Enter ancestral generation number: ";

cin >> gen;

if ( gen <= -1 || gen >= 26 ) {

	cout << " Error: input is less than 0 or greater than 25 " << endl; 
}

if ( gen == 0 ) { 
	cout << " ancestral generation " << gen << " contains 1 honeybee " << endl ;

}
	
if ( gen > 0 && gen <= 25) {

	for ( int i = 0 ; i < gen; i++) {

		final = bee + prebee ;
	
		prebee = bee ;

		bee = final ;
		
	}

	cout << "ancestral generation " << gen << " contains " << final << " honeybee" << endl;


}

cin.ignore();
cout << "press enter to quit" << endl;
cin.ignore();

return 0 ;

}
