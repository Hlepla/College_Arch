/* Hayden Lepla
   12/11/15
   cs120-06
   Homework 5
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std ;


struct category {

  string val ;
  category *next ;
  
  category(const std::string& input_val){
    val = input_val ;

    next = NULL ;
  };

};

void addfunc(const std:: string&,category*);
int numfunc(const std :: string&);
int specfunc(const std :: string&);

void printlist(category*);



int main(){

  ifstream infile ;
  string filename , temp ;
  category *speclist , *numlist , *normlist ;
  
  cout << "Enter file name: " ;
  cin >> filename ;

  infile.open(filename.c_str());

  if (infile.fail())
    {
      cout << "An error has occured opening the file, terminating... " << endl ;
      return 0 ;
    }
  cout << "categorizing... " ;

  speclist = new category("Special");
  normlist = new category("Normal");
  numlist = new category("Numbers");
 
  
  while (infile.eof()==false)
    {

      infile >> temp ;

      if ( numfunc(temp)){
	addfunc (temp , numlist);
      }

      else if (specfunc(temp)){
	addfunc(temp, speclist) ;
      }

      else {
	addfunc(temp , normlist);

      }
    }

  cout << "finished." << endl << endl ;


  printlist(speclist);
  printlist(normlist);
  printlist(numlist);

  return 0 ;
           
}


void addfunc( const std:: string& inputval , category* linkedlist){

  category * add ;

  add = linkedlist ;

  while ( add->next != NULL) {

    add = add->next ; // walks down list till NULL 

  }

  add->next = new category(inputval);

}

int numfunc(const std :: string& Iarray){

  for (int i = 0 ; i < Iarray.length() ; i++){
    
    if (Iarray[i] < 48 || Iarray[i] > 57 ) {
      return 0 ;
    }
  }
  return 1 ;
}


int specfunc( const std:: string& input){

  string specialwords[] = {"integer" , "real" , "accessor" , "mutator" , "function" , "limited" , "if" ,  "loop", "delta", "range", "type", "abs", "constant", "else", "interface", "of", "select", "while", "array", "do", "is", "end", "procedure", "not", "to"};

  if(input.length()>256){
    return 0 ;
  }

  for (int i = 0 ; i < 25 ; i++){

    if(input.length() == specialwords[i].length()){

      for (int j = 0 ; j < input.length(); j++) {

	if (tolower(input[j]) != tolower(specialwords[i][j])){

	  goto nextword ; // break from the two nested loops ;

	}
      }
      return 1 ;
    }
  nextword: NULL ;

    return 0 ;

  }

}


  void printlist(category* Linkedlist){

    category *p = Linkedlist ;

    if (Linkedlist->val=="Numbers"){
      cout << "Numbers" << endl ;

    } else if ( Linkedlist->val == "Special") {
      cout << "Special Words" << endl ;
    }

    else if (Linkedlist->val == "Normal") {
      cout << "Normal Words" << endl ;

    }

    int temp = 0 ;

    while (p->next != NULL){
      temp++ ;
      p = p->next;
    }

    cout << p->next << endl ;

    p = Linkedlist ;

    cout << p->val << " " ;

  

  cout << endl << endl ;

  }
