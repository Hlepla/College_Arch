/* Lab #2`

Hayden Lepla
1/27/15
Assignement 2.1
*/

#include <iostream>

using namespace std;

int main()

{
double x, y;
		//declare input variables
double sum = 0, average;	// declare two more variables

cout << "Please enter a number: " << flush;

cin >> x;

cout << "Please enter another number: " << flush;

cin >> y;

sum = x + y;		// Calculate the sum

cout << " The sum of " << x << " plus " << y;

cout << " is " << sum << ".";

//Notice how the spaces are placed in the cout statement 

average = sum/2;	//Calculate the average

cout << " The average of your numbers is " ;
cout << average << "." << endl;

return 0;

}
