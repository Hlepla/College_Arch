/* Hayden Lepla
   CS120-06
   12/02/15
   Lab12
   Assign:12.1
*/

#include <iostream>

using namespace std ;

class color {

private:

  int red  ;
  int green ;
  int blue ;

public:

  color(){

     red = 0  ;
     green = 0 ;
     blue = 0 ;
  }

  color(int,int,int);
  void add( color );
  void mix( color );
  void set(int,int,int);
  int R()const{
    return red ;
  }
  int G()const{ 
    return green;
  }
  int B()const{
    return blue;
  }

};

int main(){

  const color Black ;
  const color White(255 , 255 , 255);
  const color SkyBlue(135,206,235);
  const color SeaGreen(46,139,87);
  const color Gold(255,215,0);
  const color Chocolate(210,105,30);
  const color DarkGrey(75,75,75);

  color Custom (White);
  Custom.mix(DarkGrey);
  Custom.mix(SkyBlue);

  color CreamyMix(White);
  CreamyMix.mix(SkyBlue);
  CreamyMix.mix(SeaGreen);
  CreamyMix.mix(White);
  CreamyMix.mix(White);

  color mixes[5];
  mixes[0] = SkyBlue;
  mixes[0].add(SeaGreen);
  mixes[0].mix(Black);

  mixes[1].set( Chocolate.B(),SeaGreen.R(),DarkGrey.G() );
  mixes[1].mix(Gold);

  mixes[2] = White;
  mixes[2].add(Black);
  mixes[2].add(Gold);

  mixes[3].set(Chocolate.R(),Gold.G(),SeaGreen.B());
  mixes[3].add(SkyBlue);

  mixes[4] = mixes[3];
  mixes[4].mix(Black);
  mixes[4].mix(Black);

  cout << "Black: " << Black.R() << " " << Black.G() << " " << Black.B() << endl ;
  cout << "Gold: " << Gold.R() << " " << Gold.G() << " " << Gold.B() << endl ;
  cout << "Custom: " << Custom.R() << " " << Custom.G()<< " " << Custom.B() << endl;
  cout << "CreamyMix: " << CreamyMix.R()<< " " << CreamyMix.G() << " " << CreamyMix.B() << endl;
  cout << "Mixes[0]: " << mixes[0].R() << " " << mixes[0].G() << " " << mixes[0].B() << endl ;
  cout << "Mixes[1]: " << mixes[1].R() << " " << mixes[1].G() << " " << mixes[1].B() << endl ;
  cout << "Mixes[2]: " << mixes[2].R() << " " << mixes[2].G() << " " << mixes[2].B() << endl ;
  cout << "Mixes[3]: " << mixes[3].R() << " " << mixes[3].G() << " " << mixes[3].B() << endl ;
  cout << "Mixes[4]: " << mixes[4].R() << " " << mixes[4].G() << " " << mixes[4].B() << endl ; 


  return Black.R();

}


color :: color( int r , int g, int b ){

  red = r ;
  green = g ;
  blue = b ;

}
 void color :: set( int Red, int Green, int Blue){

  red = Red;
  green = Green;
  blue = Blue ;
}


void color :: add( color sumcolor){


  red = max( red, sumcolor.R()); 
  green = max(green ,sumcolor.G());
  blue = max(blue,sumcolor.B());
}


void color :: mix ( color mixcolor){

  red = ( red + mixcolor.R())/2 ;
  green = (green + mixcolor.G())/2;
  blue = (blue + mixcolor.B())/2;


}



