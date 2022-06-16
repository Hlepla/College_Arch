/* Readme.txt */

NAME:

  msh (my shell)

DESCRIPTION:

  Basic shell that runs various programs and limited shell operations.
  The shell now features history, piping, aliasing,substitution,path editing and file execution.

INSTALLATION AND EXECUTION:

  To complie source file, type  "gcc msh.c -o msh" without the quotes.
  To run the executable, type "./msh" without the quotes.
  To run the file execution of mshrc, type "read" into the command line
  with out the quotes.
  To delete alias, type"delete" with name of alias.

RELEASED VERSIONS:

  V 1.0
  V 1.5
  V 1.75
  V 2.0

AUTHOR:

  Created by Hayden Lepla

KNOWN BUGS:
  .Using the delete function for removing an alias may resolve a segmentation fault.

  .When using alias, alias may not work the first time. Please re-enter alias if so.

  .Correct syntax must be used for many of the functions. Incorrect syntax may result
  in unexpected output.

REPORTING BUGS:

  Report all bugs to lepl1529@vandals.uidaho.edu

COPYRIGHT:

  This is free software: you are free to change and redistribute it.
  There is NO WARRANTY, to the extent permitted by law.
