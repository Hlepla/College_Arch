/* Hayden Lepla
   10/28/15
   CS120-06
   Lab 8
   Assign: 8.1
*/

#include <curses.h> // includes the curses library

using namespace std;


const int maxx = 40 ;

const int maxy = 20 ; // maximum size of the "room"


void setup( char[][maxy] , int x , int y ); // room setup

void print ( char r[][maxy] ) ;

int main()
{

  int c ;
  WINDOW *wnd;
  char room[maxx][maxy]; // stores the room 
  int x = maxx/2 , y = maxy/2 ; // robots initial location

  wnd = initscr(); // initializes the window

  clear(); // clears the window
  refresh(); // reprints the window

  setup(room,x,y); // setup the room with the robot

  print(room); // write this function 

  while ((c = getch()) != 'q') 
	 ; // wait for user to press 'q' key
    
	 endwin(); // frees the screen for normal use
	 
}
    	  
	 
  /* sets up the room, adding walls, and the robot */
  
  void setup(char r[][maxy] , int x , int y )
  {
    
    for ( int i = 0 ; i < maxx ; i++ )
      {
	for ( int j = 0 ; j < maxy ; j++ )
	  {
	    r[i][j] = ' ' ; // empty the room
	  }
	
      }
    
    for ( int i = 0 ; i < maxy ; i++) {
      
      r[0][i] = '|' ; // left wall
      r[maxx-1][i] = '|' ; // right wall
	
	}
    for ( int i = 0 ; i < maxx ; i++) {

      r[i][0] = '-' ; // top wall
      r[i][maxy-1] = '-' ;// bottom wall 
	}
    r[x][y] = 'R' ; // place the robot

  }

  void print( char room[][maxy])
  {

    for ( int i = 0 ; i < maxx ; i++ )
      {
	for (int j = 0 ; j < maxy ; j++)
	  {
	    move(i,j);
	    delch();
	    insch(room[i][j]);
	    refresh();
	  }
      }
  }


