/* Hayden Lepla
   CS120-06
   10/7/15
   Lab5
   Assign: 5.1
*/


#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std ;


int schedule_1 (double) ;

int schedule_11 ( double, double) ;

int schedule_12 (double, double, char) ;

int schedule_21 (double, double, char) ;

void printRevenue() ;

void getinput(int ) ;


int customID; // sets the amout of digits in customer number
int sch_num ;

double energyrate , demandrate ;

float revenue = 0 , total_cost = 0 ;

char voltage_discount ;

int main() 
{
  
  do{
      
    cout << "Enter customer number: " ;
    cin >> customID ;
    
    // while ( customID != 0 ) {  
      
    getinput(customID); // calls the input function 
    
  } while ( customID != 0 )  ;
  
  printRevenue(); // prints the total cost of all the customers
  
  return 0 ;
}

  void getinput( int customID)
  {
    
    //  Label1: ;
  
    //  cout << "Enter customer number: " ; 
    //cin >> customID ;
    
    /* if (strlen(customID) > 6 || strlen(customID) < 6) // checks for correct number of digits in customer number
       {
       
       cout << "Customer number input is invalid, please enter a 6 digit number: " << endl ;
       
       goto Label1 ;
       }
    */
    
  Label2: ;  
    
  cout << "Enter schedule number: " ;
  cin >> sch_num ;
  
  
  cout << "Enter energy charge: " ;
  cin >> energyrate ; 
  
  if ( sch_num == 11 || sch_num == 12 || sch_num == 21 )
    {
      
      cout << "Enter demand rate: " ;
      
      cin >> demandrate ;
    }
  
  if ( sch_num == 12 || sch_num == 21)
    
    {
      cout <<"Enter voltage discount (if eligible): " ;
      
      cin >> voltage_discount ;
      
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
      
      goto Label2 ;
      
      break ;
      
    }
  
  
  revenue = revenue + total_cost ;

  cout << "Total cost is: " << total_cost << endl ;
  
  }
  
  void printRevenue()
  {
    
    cout <<"Total revenue is: " << revenue << endl ;

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
  
  
  
