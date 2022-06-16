#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std ;

/* This program is designed to read in a Hex file using a dynamaically allocated array  and convert the Hex numbers to 
   Binary numbers and to export the output to another file
*/


void ReadInputFile(); // reads in hex file and calls the Allocate Array function

int** AllocateArray(string filename); // Stores file into a dynmaically allocated array 

int** OutputToFile(int** OutfileArray , int &rows , int &cols ); // Takes the printed binary output and saves it to a file


int main()
{


  ReadInputFile(); // calls function to read in hex file 
    
  return 0;
  
}


void ReadInputFile()
{
  string filename ;

  cout <<"Input data file: " ;
  cin >> filename ;

  AllocateArray(filename) ;  // file is passed to the AllocateArray function to be stored in a 2d array                                                                                                      

}



int** AllocateArray(string filename)
{
  
  int  nRows,nCols ;
  int **Array2D ;    // declares array
  ifstream Infile;
  
  
  Infile.open(filename.c_str()) ; // opens the file                                                                    
  if (Infile.fail())                                                                                 
    {                                                                                                
      cout <<"An error has occurred opening the file, terminating... " << endl ;                     
      return 0 ;                                                                                     
    } 
  
  
  Infile >> nRows >> nCols ; // input first lines of file
  
  
  Array2D = new int *[nRows] ; // allocates the dynamic 2darray
  
  for (int i = 0 ; i < nRows ; i++)
    {
      
      Array2D[i] = new int [nCols] ;
      
      if ( Array2D[i] == NULL)
	{
	  
	  cout <<"An Error has occurred... " << endl ;
	  
	}
      
      
    }
  
  
  for (int i = 0 ; i < nRows ; i++) // Runs through array and stores hex values 
    {
      for (int j = 0 ; j < nCols ; j++)
	{
	  Infile >> std::hex >> Array2D[i][j] ; // Reads in hex vaules to array
	  
	  cout << bitset<4>(Array2D[i][j]).to_string() << endl ; // Prints out Hex numbers as 4 bit binary numbers
	}
        
    }
  

  OutputToFile(Array2D,nRows,nCols) ; // sends Array to the outfile function

  Infile.close();
}


int** OutputToFile( int** OutfileArray, int &rows , int &cols)
{
  ofstream Outfile ; 
  string outputfile ;

  cout << "Enter name for output file: " ; // user inputs name of output file
  cin >> outputfile ;

  Outfile.open(outputfile.c_str()) ;

  if (Outfile.fail())
    {

      cout<< "An error has occured with creating the output file.Terminating...: " << endl ;
      
      return 0 ;
    }

  OutfileArray[rows][cols] ;

  for (int i = 0 ; i < rows ; i++) // Runs through array and stores hex values                                                                                                                              
    {
      for (int j = 0 ; j < cols ; j++)
        {
	  int temp[rows][cols] ;

          temp[i][j] = bitset<4>(OutfileArray[i][j])  ; // writes the binary to the outputfile file 
	  
	  if ( cols < 10 )
	    Outfile << temp[i][j] << endl ; 

	}
      
      
      
    }
  
  Outfile.close(); // closes ouput file 
 }
