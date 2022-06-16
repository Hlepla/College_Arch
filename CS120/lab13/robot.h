using namepspace std ;

class Robot

{

 private:

  int id; //must be > 0 and < 2000000000

  char type; //must be either M or S

  bool deployed;

  int numOfDeployments;

  string manufacturer;

  int quadrant;  //must be either 1,2,3 or 4

 public:

  Robot();

  Robot(int id,char type,string manufacturer);

  void setID(int id);

  void setType(char type);

  void setDeployed(bool deployed);

  void setManufacturer(string manufacturer);

  void setQuadrant(int quadrant);



  //This function should print the RObot information in the format below

  // Robot <RobotNumber>

  //     type: <RobotType>

  //     status: <Status>

  //     num-deployments: X

  //     manufacturer: <ManufacturerName>

  void print();



  //This function should just return the variable id

  int getID();



  //This function should just return the variable quadrant

  int getQuadrant();



  //This function should increase the variable numOfDeployments by 1.

  void incNumOfDeployments();



  //This function should just return the varaible numOfDeployments

  int getNumOfDeployments();



  //This function should just return the variable deployed

  bool isDeployed();

};
