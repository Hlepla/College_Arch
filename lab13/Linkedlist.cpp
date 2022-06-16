#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Linkedlist.h"


using namespace std ;


Linkedlist::Linkedlist(){
  int count;
  head = NULL ;
  tail = NULL ;
  count = 0 ;
  scoutsDeployed = 0 ;
  minersDeployed = 0;
  totalRobots = 0 ;
  totalScouts = 0 ;
  totalMiners = 0 ;
  
}

void Linkedlist::deploy(char RT, int quad){

  node * n;

  for (n = head ; n->next !=NULL ; n = n->next){

    if(RT== n->RT && n->deployed == false){
      
      n->deployed = true ;
      n-> NumDeployed++ ;
      n->quad = quad; 
      if (n->RT == 'S' )
	scoutsDeployed++ ;
      if (n->RT == 'M')
	minersDeployed++;
      cout << "robot " << n->RN << " deployed to qudrant " << quad << endl;
      break;
    }
  }

}


void Linkedlist::undeploy(char type ,int RN){

  node * n ;

  for (n = head ; n->next !=NULL ; n = n->next){

    if(RN== n->RN){
      if(n->deployed == false){
	cout<<"This robot is not deployed, try again: " << endl;
	return ;
      }
      n->deployed = false ;
      

      if (n->RT == 'S' ) {

        scoutsDeployed-- ;

      cout << "robot " << n->RN << " retrieved from qudrant " << n->quad << endl;

      }

      if (n->RT == 'M') {

        minersDeployed--;

      cout << "robot " << n->RN << " retrieved from qudrant " << n->quad << endl;

      }
      n->quad = 0;
    }
  }
  
}


void Linkedlist:: Add( int BotN , char BotT , string BotR){

  node *n = new node;
  n->RN = BotN;
  n->RT = BotT ;
  n->RM = BotR ;
  n->NumDeployed = 0;
  n->quad = 0;
  n->deployed = false ;

  if ( head == NULL ){

    head = n ;
    tail = n ;
    n-> next = NULL ;
  }
  else {

  tail->next = n ;
  n->next = NULL ;
  tail = n ;
  }
  totalRobots++;
  if ( BotT =='M')
    totalMiners++ ;   

  else 
    totalScouts++ ;

}


void Linkedlist::status( int RN){

  node * n ;

  for (n = head ; n->next !=NULL ; n = n->next){
    //cout << n->RN << " ";
    if(RN == n->RN){

    cout << "Robot:" << n-> RN << endl;
    cout << "Type: " << n-> RT << endl;

    cout << "Status: " ;
    if( true == n->deployed){
      cout <<"Deployed in quadrant: " << n->quad << endl ;
    }
    else if (n->RT == 'S' )
      {
	cout << "In scout holding bay " << endl ;
      }
    else  if (n->RT == 'M')
      {
        cout <<"In miner holding bay " << endl ;
      }
  
    cout << "Num-deployments: " << n-> NumDeployed << endl ;
    cout << "Manufacturer: " << n-> RM << endl ; 
    
    return;
    }
  }
}
