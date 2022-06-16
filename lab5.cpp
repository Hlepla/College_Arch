/* Hayden Lepla
 Lab 5
Cs120
2/17/15
*/

#include <iostream>

using namespace std;

double sch1( double energyrate  )
{

 	double final;

  if ( energyrate <= 600) { 
	
	final = 4 +  energyrate * 0.05255 ; 
	}
	else{
	final = 4 + (energyrate - 600) * 0.06156 + 600 * 0.0525 ;
}
	return final ;
} 

double sch11( double energyrate , double demand );


double sch12( double energyrate , double demand , char h );


double sch21( double energyrate , double demand , char h );


double cusNUM , schedule , rate ;

int schNUM;

char h ;
const char Y = 'Y';
const char N = 'N';
float rev = 0;
float totalcost = 0;
double demand;


int main() {
 

cout << " Enter customer number: " ;
cin >> cusNUM ;
if (cusNUM == 0){ break;}

cout << " Enter schedule number: " ;
cin >> schNUM ;

cout << " Enter energy rate : " ;
cin >> rate ;

if ( schNUM == 11 || schNUM == 12 || schNUM == 21 ) {

cout << " Enter demand rate : " ;


if ( schNUM == 12 || schNUM == 21 ) {

cout << " Discout rate? for yes type Y and for no type N : " ;
cin >> h ;
}

}
switch (schNUM) {

case 1: totalcost = sch1 ( rate );
	break; 
case 11: totalcost = sch11 ( rate , demand );
	break;
case 12: totalcost = sch12 ( rate , demand , h);
	break;
case 21: totalcost = sch21 ( rate , demand , h);
	break;
default: cout << "Input inalid" << endl;

}
rev  =  rev + totalcost;
cout << "Your total cost is: " << totalcost << endl ;

}while (1);

cout << "Total revenue is: " << rev << endl ;
return 0;
}


double sch11 ( double energyrate , double demand ) {

double total ;

if ( demand <= 20) {

total = 6 + energyrate * .07971 ;

}

else { 

total = (demand - 20) * 3.5 + 6 + energyrate * .07971 ;

}

return total ;

}

double sch12 ( double energyrate , double demand , char h ) {

double total ;

if ( demand <= 20 ) {

total = 6 + energyrate * .07719 ;
}

else {

total = ( demand - 20) * 3.0 + 6 + energyrate * .07719 ;

}

if ( h == Y ) {

double voltd ;

voltd = demand * 0.2 ;

total = total - voltd ; 
}

return total ;

}

double sch21 ( double energyrate , double demand , char h ) {

double total ;

if ( demand <= 50 ) { 

total = energyrate * .05022 + 255 ;
}

else {

total = ( demand -50 ) * 2.75 + energyrate * .05022 + 225.000000 ;
}

if ( h == Y ) {

double voltd ;

voltd = demand * 0.2 ;

total = total - voltd ;
}

return total ;

}


