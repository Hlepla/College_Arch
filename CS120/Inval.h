#include <string>
using namespace std ;

class Inval{ 

 private:

  int number ;
  int inbase ;
  string decimaldata ;
 public:
  void PrintAsBase();
  void setinput_base(int);
  void setNumber(int);
  void convertdec();

};
