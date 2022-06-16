/* Readme.txt */

NAME:

  sim.c

DESCRIPTION:

  Producer consumer problem that contains up to 4 producers and consumers. Producers
  generate random characters to a buffer and consumers take them.

INSTALLATION AND EXECUTION:

  To complie source file, type  "gcc sim.c -lrt -o sim" without the quotes.
  To run, please enter "./sim maxtime num_prod num_cons" where
  maxtime = how long the program should run
  num_prod = how many miliseconds for producers to generate characters
  num_cons = how many miliseconds for consumers to consumer characters

RELEASED VERSIONS:

  V 1.0
  V 1.5

AUTHOR:

  Created by Hayden Lepla

KNOWN BUGS:
  . Buffer may overflow, resulting in the hault of the program

  . arguments must be specified when executing or unexpected results may occur.

  . Average buffer is mostly broken, results will vary with this.

  . When running on wormulon, the ID's of the producers are inconsistent.
    They are running fine on other machines.

REPORTING BUGS:

  Report all bugs to lepl1529@vandals.uidaho.edu

COPYRIGHT:

  This is free software: you are free to change and redistribute it.
  There is NO WARRANTY, to the extent permitted by law.
