/* Hayden Lepla
   CS 120
   Lab 9
   3/24/15
*/


#include <iostream>
#include <curses.h> // includes the curses library

using namespace std ;

const int NUMCOLS = 70 ;
const int NUMROWS = 20 ;

void setup() ; // prototype
 


class robot {
 
public :
  robot();
  int locationX;
  int locationY;
  int MoveR(char d);

};

int main() {
  
  char c , d  ;
  WINDOW *wnd;
  
  //if (Robot0.locationX < 1){ there is a problem} 
  
  robot Robot0 ;
  Robot0.locationX = 1 ;
  Robot0.locationY = 1 ;
  
  robot Robot1 ;
  Robot1.locationX = 1 ;
  Robot1.locationY = NUMCOLS-2;
  
  robot Robot2 ;
  Robot2.locationX = NUMROWS-2 ;
  Robot2.locationY = NUMCOLS-2 ;
  
  robot Robot3 ;
  Robot3.locationX = NUMROWS-2;
  Robot3.locationY = 1 ;
  
  //use curses library function to initialize the curses window
  wnd = initscr();
  // use curses library function to clear the window
  clear();
  // use curses library function to update the window
  refresh();
  // draw room with 4 robots
  setup();
  // wait until user presses 'q' key
  while (1){
    cin >> c ;
    //cout << c;
    if ( c == 'q')
      break;
    
    switch(c) {      
    case '0':
      cin >> d ;
      Robot0.MoveR(d);
      break;
      
    case '1': 
      cin >> d;
      Robot1.MoveR(d);
      break;
      
    case '2':
      cin >> d ;
      Robot2.MoveR(d);
      break; 
      
    case '3':
      cin >> d;
      Robot3.MoveR(d);
      break;
      
      
    default:
      break;
    }
    
  }
  // use curses library function to free the screen for normal use
  endwin();
}//end of main

// Draw a 70x20 room containing a robot in each corner 
void setup()
{
  
  int i ;
  
  //draw north and south walls
  for ( i=0 ; i < NUMCOLS; i++){
    move(0,i);
    delch();
    insch('-');
    move(NUMROWS-1, i);
    delch();
    insch('-');
  }
  
  // draw east and west walls
  for (i=0; i < NUMROWS; i++){
    move(i,0);
    delch();
    insch('|');
    move(i, NUMCOLS-1);
    delch();
    insch('|');
  }

  //  draw robot 0
  move (1,1);
  delch();
  insch('R');
 
    //draw robot 1
  move(1, NUMCOLS-2);
  delch();
  insch('R');

  //draw robot 2
  move (NUMROWS-2, NUMCOLS-2);
  delch();
  insch('R');

  //draw robot 3
  move (NUMROWS-2,1);
  delch();
  insch('R');

  refresh();
}



robot::robot(){

}

int robot:: MoveR(char d){

    switch(d) {

      case 'W':
	
	move(locationX, locationY-1);
       	if(inch() != ' '){
	  //do not update robot
	  }else{
	  locationY--;
	  delch();
	  insch('R');
	  move(locationX, locationY+1);
	  delch();
	  insch(' ');
	  refresh();
	}	
      break;

    case 'E':
      move(locationX, locationY+1);
      if (inch() != ' '){
      }else{
	locationY++ ;
	delch();
	insch('R');
	move(locationX , locationY-1);
	delch();
	insch(' ');
	refresh();
      }

      break;
      
    case 'S':
      move(locationX-1, locationY);
      if (inch()!= ' '){
      }else{
      locationX-- ;
      delch();
      insch('R');
      move(locationX+1, locationY);
      delch();
      insch(' ');
      refresh();

      
      break;

    case 'N':
      move(locationX+1, locationY);
      if (inch()!= ' '){
      }else{
      locationX++ ;
      delch();
      insch('R');
      locationX-- ;
      move(locationX-1, locationY);
      delch();
      insch(' ');
      refresh();

     
      break;

    default:
      break;
      return 0;
      
      }
      }
    }
}


