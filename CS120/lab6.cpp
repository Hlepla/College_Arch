/* Hayden Lepla
   CS120-06
   10/14/15
   Lab6
   Assign: 6.1
*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std ;


int schedule_1 (double) ;

int schedule_11 ( double, double) ;

int schedule_12 (double, double, char) ;

int schedule_21 (double, double, char) ;

void printRevenue() ;

void getinput() ;


int customID; // sets the amout of digits in customer number

int sch_num ;

double energyrate , demandrate ;

float revenue = 0 , total_cost = 0 ;

char voltage_discount , answer ;

ifstream Infile ;

ofstream Outfile ;

string filename ;

int main() 
{
        
    cout << "Enter input file: " ;
    cin >> filename ;
     
    Infile.open (filename.c_str());

    if ( Infile.fail()) {

      cout << "An error has occurred with opening the file: " << endl ;
      return 0;
    }

    cout << "Do you wish to create an output file? (Y/N): " ;

    cin >> answer ;


    if ( answer == 'Y' || answer == 'y') {

      cout << " Enter output file name: " ;

	cin >> filename ;

      Outfile.open (filename.c_str());

    }
    
    
    getinput(); // calls the input function 
    printRevenue(); // prints the total cost of all the customers
    
  return 0 ;
}

void getinput()
{
  
  while (1) {
    
    Infile >> customID ;
    if (customID == 0 ) { break ; }  
    
    Infile >> sch_num ;
    
    Infile >> energyrate ; 
    
    if ( sch_num == 11 || sch_num == 12 || sch_num == 21 )
      {
		
	Infile >> demandrate ;

      }
    
    if ( sch_num == 12 || sch_num == 21)
    
      {
	
	Infile >> voltage_discount ;
	
      }
    
    switch (sch_num)  // calls to specific function depending on schedule number
      {
	
	
    case 1:
      
      total_cost =  schedule_1( energyrate) ;
      
      break ;
      
    case 11:
      
      total_cost = schedule_11( energyrate , demandrate) ;
      
      break ;
      
    case 12:
      
      total_cost = schedule_12(energyrate, demandrate, voltage_discount) ;
      
      break ;
      
    case 21:
      
      total_cost = schedule_21(energyrate, demandrate, voltage_discount) ;
      
      break ;
      
    default :
      
      cout << "Unrecognized schedule number, please try again: " << endl ;
      
      break ;
      
    }
  
  
  revenue = revenue + total_cost ;

  cout << "Total cost is: " << total_cost << endl ;
  
  Outfile << "Total cost is: " << total_cost << endl ;

  }
  


  }
  
  void printRevenue()
  {
    
    cout <<"Total revenue is: " << revenue << endl ;
    
    Outfile << "Total revenue is: " << revenue << endl ;
    
    Outfile.close() ;

    Infile.close();

    return ;
    
  }
  
  int schedule_1(double energyrate)
  {
    
    double final ;
    
    if (energyrate <= 600) {
      
      final = 4 + energyrate * 0.05255 ;
      
    }
    
    else {
      
      final = 4 + (energyrate - 600 ) * 0.06156 + 600 * 0.0525 ;
      
      return final ;
      
    }
    
  }
  
  int schedule_11(double energyrate, double demandrate)
  {
    
    double final ;
    
    if (demandrate <= 20) {
      
      final = 6 + energyrate * .07971 ;
      
    } else { 
      
      final = (demandrate -20) * 3.5 + 6 + energyrate * .07971 ;
    }
    
    return final ;
    
  }
  
  
  
  int schedule_12(double energyrate , double demandrate , char voltage_discount )
  {
    
    double final ;
    
    if (demandrate <= 20) {
      
      final = 6 + energyrate * .07719 ;
      
    }
    
    else {
      
      final = (demandrate - 20) * 3.5 + 6 + energyrate * .07719 ;
      
    }
    
    if (voltage_discount == 'Y' || voltage_discount == 'y') {
      
      double discount ;
      
      discount = demandrate * 0.20000 ;
      
      final = final - discount ;
    }
    
    return final ;
    
  }
  
  
  int schedule_21(double energyrate, double demandrate , char voltage_discount)
  {
    
    double final ;
    
    if (demandrate <=50) {
      
      final = energyrate * .05022 + 255 ;
    }
    
    else {
      
      final = ( demandrate - 50 ) * 2.75 + energyrate * .05022 + 225.000000 ;
      
    }
    
    if (voltage_discount == 'Y' || voltage_discount == 'y') {
      
      double discount ;
      
      discount = demandrate * 0.20000 ;
      
      final = final - discount ;
    }
    
  }
  
  
  
