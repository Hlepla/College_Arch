/* Hayden Lepla
   10/29/15
   CS120-06
   Lab 9
   Assign: 9.1
*/

#include <iostream>
#include <curses.h>
#include <stdlib.h>

using namespace std ;

class Robot
{
  
private:
  int id;
  int rowpos;
  int colpos;
  
public:
  
  void update( int r , int c)
  {
    rowpos = r ;
    colpos = c ;
  }
  
  
  Robot(int i , int r, int c)
  {
    id = i ;
    rowpos = r ;
    colpos = c ;
    
  }
  
  int getrow()
  {
    
    return rowpos ;
    
  }
  int getcol()
  {
    
    return colpos;
    
  }
  
  Robot(){
  }
  
  void action(char);
  
};


const int NUMCOLS = 70 ;
const int NUMROWS = 20 ;

void setup();

void Robot::action(char d){

  move(rowpos,colpos);
  addch(' ');
  refresh();
  
  switch(d){
    
  case 'N':
  case 'n':
    move(rowpos-1, colpos);
    if (inch() == ' ' ){
      rowpos-=1;;
    }
    break;
    
  case 'S':
  case 's':
    move(rowpos+1,colpos);
    if (inch() == ' '){
      rowpos+=1;
    }
    break;
    
  case 'E':
  case 'e':
    move(rowpos,colpos+1);
    if(inch() == ' '){
      colpos+=1;
    }
    break;
    
  case 'W':
  case 'w':
    move(rowpos,colpos-1);
    if(inch() == ' '){
      colpos-=1;
    }
    break;
  }
  
  move(rowpos,colpos);
  addch('R');
  refresh();

}

int main()
{
  
  Robot robot0(0,1,1) ;
  Robot robot1(1,1,NUMCOLS-2) ;
  Robot robot2(2,NUMROWS-2,NUMCOLS-2) ;
  Robot robot3(3,NUMROWS-2,1) ;
  
  
  
  char c ,d ;
  WINDOW *wnd ;
  
  // use curses library function to initalize the curses window
  wnd = initscr();
  
  // use curses library function to clear the window
  clear();
  
  // use curses library to update the window
  refresh();
  
  //draw room with 4 robots
  setup();
  
  // wait until uses presses 'q' key
  while (1) {
    
    cin >> c ;
    if ( c == 'q')
      break;
    
    cin >> d ;
    if ( d == 'q')
      break;
    
    switch(c) {
      
    case '0':
      robot0.action(d);
      break;
      
    case '1':
      robot1.action(d);
      break;
      
    case '2':
      robot2.action(d);
      break;
      
    case '3':
      robot3.action(d);
      break;
      
    default:
      endwin();
      cout << "Invalid input, exiting...." << endl;
      exit(1);
      
      
    }
    
    
  }
  
  
  // use curses library function to free the screen for normal use
  endwin();
  
}

// Draw a 70x20 room containing a robot in each corner
void setup()
{
  
  int i ;
  
  // draw north and south walls
  for ( i=0 ; i<NUMCOLS; i++){
    move(0,i) ;
    delch();
    insch('-');
    move(NUMROWS-1, i);
    delch();
    insch('-');
  }
  
  // draw east and west walls
  for ( i=0; i<NUMROWS; i++){
    move(i,0);
    delch();
    insch('|');
    move(i,NUMCOLS-1);
    delch();
    insch('|');
  }
  
  //draw robot 0
  move(1,1);
  delch();
  insch('R');
  
  //draw robot 1 
  move(1,NUMCOLS-2);
  delch();
  insch('R');
  
  //draw robot 2 
  move(NUMROWS-2,NUMCOLS-2);
  delch();
  insch('R');
  
  // draw robot 3 
  move(NUMROWS-2,1);
  delch();
  insch('R');
  
  refresh();
  
}


