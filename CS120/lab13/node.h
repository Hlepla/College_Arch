using namespace std ;

class Node{

 private:

  Node *next;

  Robot *data;

 public:

  Node();

  void set_next(Node *n) {next = n;}

  void set_data(Robot *d) {data = d;}

  Node *get_next() {return next;}

  Robot *get_data() {return data;}

  void print();

  int remove(int);

  void remove_data() {delete data;}

};

