#include <iostream>
#include <string>

using namespace std ;

class linkedlist {

 private:

  int count;

  Node *head;

 public:

  LinkedList();

  //The insert and remove function has been done for you in the text book or the links provided

  void insert(Robot *);

  void remove(int);



  //this function should return a Node which contains the Robot with id=id

  Node* getNode(int id);

  //this function should return any Node in the list which is not deployed yet 

  //return null if there are no more Robots to be depployed

  //you need to iterate through the list and find the Node with the Robot that has not been deployed

  Node* getNodeToDispatch();

  //this function should print all robots in the list

  //you need to iterate or traverse over every Node in the list and print each Robot

  void print();

  //this function should print the robot with id = id

  //you should first get the Node with Robot have id=id and then print that Robot

  void print(int id);

  //this function returns the count of Node in list

  int getCount();

  //this function should return number of robot undeployed

  //you should iterate over the List and count the Node with undeployed Robot.

  int getUndeployedCount();

  //this function should return number of robot deployed

  //you should iterate over the List and count the Node with deployed Robot.

  int getDeployedCount();

};
