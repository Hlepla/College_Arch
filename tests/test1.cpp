#include <iostream>
#include <string>
int buzz, name ;

using namespace std;

int main() {
  int i;
  string Justin ;
  
  cout << "Welcome to Sotts Buzz! Enter player name: " ;
  
  cin >> name ;
  
  if (name == 'Hayden'|| name == 'Braydon' ){
    
    cout << " Error, your name should be 'Justin', please try again"<< endl ;
    return 0;
    
  }

  if ( name == 'Justin') {
    cout << "Enter the correct buzz number: " ;
    cin >> buzz ;
  }
    if (buzz != 1 ){
      cout << " Wow you lost on the first try, you must be smashed" ;
    }
    else {
      
      cout << "2 " << endl ;
    }
  }
  
