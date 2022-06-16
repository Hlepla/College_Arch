#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std ;


class Linkedlist {

 private:

  struct node {
    int RN ;
    char RT ;
    string RM ;
    node *next ; 
    int NumDeployed ;
    int quad;
    bool deployed ;
  };
  node *head ;
  node *tail ;
  int totalRobots;
  int totalScouts;
  int totalMiners;
  int scoutsDeployed;
  int minersDeployed;


 public:


  Linkedlist();
  
  void  Add ( int RN , char RT, string RM ) ;
  void deploy ( char RT, int quad);
  void undeploy(char , int);
  void status(int RN);
  int getScoutsDeployed(){ return scoutsDeployed;};
  int getMinersDeployed(){ return minersDeployed;};
  int robots(){return totalRobots;};
  int scoutsInBay(){return totalScouts - scoutsDeployed;};
  int minersInBay(){return totalMiners - minersDeployed;};
};


