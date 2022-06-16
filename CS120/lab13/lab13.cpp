/* Hayden Lepla
   CS120-06
   12/9/15
   Lab13
*/

#include <iostream>
#include <fstream>
#include <string>
#include "linkedlist.h" 
#include "node.h" 
#include "robot.h"
using namespace std ;


int main(){

  //LinkedList to maintain the list of Scout Robots.

  LinkedList ScoutsList; 

  //LinkedList to maintain the list of Miner Robots.

  LinkedList MinersList;



  Robot *robot_ptr;

  ifstream fin;

  int id,quadrant;

  char type,command;

  string manufacturer;



  //open the file

  fin.open("manifest.txt");

  if(fin.fail())

    {

      cout <<"Error opening file\n";

      return 0;

    }

  //read the data from the file

  while(!fin.eof())

    {

      fin>>id>>type>>manufacturer;

      robot_ptr = new Robot(id,type,manufacturer);

      if(type=='M'){

        MinersList.insert(robot_ptr);

      }

      else if(type=='S'){

        ScoutsList.insert(robot_ptr);

      }

      else{

        cout<<"Invalid robot type: "<<type<<endl;

      }

    }

  //close the file

  fin.close();



  MinersList.print();

  ScoutsList.print();

  cout<<"Press D to dispatch the scout robot"<<endl;

  cout<<"Press d to dispatch the miner robot"<<endl;

  cout<<"Press R to retrieve the scout robot"<<endl;

  cout<<"Press r to retrieve the miner robot"<<endl;

  cout<<"Press ? to get an info of the robot"<<endl;

  cout<<"Press s to get the number of the scout robot deployed"<<endl;

  cout<<"Press S to get the number of the scout robot in holding bay"<<endl;

  cout<<"Press m to get the number of the miner robot deployed"<<endl;

  cout<<"Press M to get the number of the miner robot in holding bay"<<endl;

  cout<<"Press q to exit"<<endl;

  do{

    cout<<"Enter command: ";

    cin>>command;

    switch(command){

    case 'D':{  

      //dispatch the Scout Robot if available

    }

    case 'd':{

      //dispatch the Miner Robot if available

    }

    case 'R':{

      cout<<"Enter id of the robot to retrieve:";

      cin>>id;

      //retrieve the Scout robot with id=id if already deployed

      case 'r':{

	cout<<"Enter id of the robot to retrieve:";

	cin>>id;

	//retrieve the Miner robot with id=id if already deployed

	break;

      }

      case '?':{

	cout<<"Enter the robot id: ";

	cin>>id;

	//print the information of the Robot with id=id

	break;

      }

      case 's':{

	//display the number of Scout robots deployed

	break;

      }

      case 'S':{

	//display the number of Scout robots in holding bay

	break;

      }

      case 'm':{

	//display the number of Miner robots deployed

	break;

      }

      case 'M':{

	//display the number of Scout robots in holding bay

	break;

      }

      case 'q':{

	break;

      }

      default:{

	cout<<"Invalid Command"<<endl;

      }

    }

    }while(command!='q');  



     MinersList.print();

     ScoutsList.print();

    return 0;

  }
  node::node(){  // constructor
    next = NULL;
    data = NULL;
  }

  void node::print(){
    data->print();
    cout << endl;
    if(next != NULL)
      next -> print();
  }

  void node::turnLeft(){
    data -> turnLeft();
    if(next != NULL)
      next -> turnLeft();
    data -> print();
    cout << endl;
  }
  int node::remove(int n){
    if(next != NULL){
      if((next -> data) -> getID() == n){ // found the right ID
	node *temp;
	temp = next;
	next = next -> next;
	temp -> remove_data();
	delete temp;
	return(1);  // successfully removed
      }
      else{
	return(next -> remove(n));  // try the next node
      }
    }
    return 0;     // given robot was never found
  }



  linkedlist::linkedlist(){
    head = NULL;
    count = 0;
  }
  void linkedlist::insert(robot *rp){
    node *n;
    n = new node;
    n->set_data(rp);
    n->set_next(head); 
    head = n;
    count++;
  }

  void linkedlist::remove(int n){
    if(head == NULL)
      return;
    if((head->get_data())->getID() == n){
      node *temp;
      temp = head;
      head = head->get_next();
      temp -> remove_data();
      delete temp;
      count--;
    }
    else{
      if(head->remove(n) == 1)
	count--;    
    }
  }
  void linkedlist::print(){
    cout << "There are " << count;
    cout << " robots in the list: \n";
    if(head != NULL)
      head->print();
  }
  void linkedlist::turnLeft(){
    if(head != NULL)
      head->turnLeft();
  }
