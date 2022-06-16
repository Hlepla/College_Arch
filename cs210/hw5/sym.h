#ifndef SYMTBL_H
#define SYMTBL_H

struct sym {
  char * name;
  double value;
  struct sym *left ;
  struct sym *right ;
  int constant ;
} sym_tbl[1];

struct sym * sym_lookup(char *, int constant);
void print_tree(struct sym *);
#endif /* SYMTBL_H */
