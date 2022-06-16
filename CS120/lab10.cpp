/* Hayden Lepla
   11/11/15
   CS120-06
   Lab10
   Assign: 10.1
*/


#include <iostream>
#include <fstream>
#include <cmath>
#include <string>


using namespace std ;

class studenttype{

private:
  int test0 ,test1, test2;
  float Average ;
  char Grade ;
  int sid;

public:
  void set_test( int t[3]);
  int get_test0();
  int get_test1();
  int get_test2();
  float PrintGrade( float A , float B, float  C , float D);
  void calculate_Average();
  int get_Average() ;
  void set_sid(int id);
  int get_sid();
};

int MAX = 128;

int main(){

  studenttype st[MAX];
  int id , t[3];
  string filename;
  ifstream infile ;
  float mean, ivar, var, Sdev, sumvar = 0;
  cout << "Enter file Name " << endl;
  cin >> filename;
  infile.open ( filename.c_str());
  float sum = 0.0 ;
  int i;

  for (i=0 ; i < MAX,infile.eof()==false  ; i++){

    infile >> id >> t[0] >> t[1] >> t[2] ;

    st[i].set_sid(id);
    st[i].set_test(t);
    st[i].calculate_Average();
    sum += st[i].get_Average();
  }
  MAX = i - 1;
  mean = (sum / MAX);
  cout << "total of number of students: " << MAX << endl;
  cout << "Mean value is: " << mean << endl;

  for (i =0; i < MAX ; i++){
    ivar = pow((st[i].get_Average() - mean), 2);
    sumvar += ivar;
  }
  var = (sumvar / MAX);
  Sdev = sqrt(var);

  cout << "Standard deviation is: " << Sdev << endl ;

  float A = (mean + (1.5)*Sdev);
  float B = (mean + (0.5)*Sdev);
  float C = (mean - (0.5)*Sdev);
  float D = (mean - (1.5)*Sdev);

  cout <<"Student ID  Grade" << endl ;

  for (i = 0; i< MAX ; i++){
    st[i].PrintGrade(A, B, C, D);

  }
}

void studenttype :: set_test( int t[3]){
  // values are now stored into test0 ,test1 ,test2

  test0 = t[0];
  test1 = t[1];
  test2 = t[2];
}
void studenttype:: set_sid(int id){
  // id values are now stored into sid

  sid = id ;
}

int studenttype :: get_sid(){

  return sid ;
}


int studenttype:: get_test0(){

  return test0;
}


int studenttype:: get_test1 () {
  return test1;
}

int studenttype:: get_test2(){
  return test2 ;

}

int studenttype:: get_Average(){

  return Average ;
}

void studenttype:: calculate_Average(){

  Average = ( test0 + test1 + test2) / 3.0 ;
}

float studenttype :: PrintGrade( float A , float B , float C , float D){

  if (Average > A)
    Grade = 'A';
  else if (Average >= B)
    Grade = 'B';
  else if (Average >= C)
    Grade = 'C' ;
  else if (Average >= D)
    Grade = 'D' ;
  else
    Grade = 'F';
  cout << sid << "          " << Grade << endl ;
}


