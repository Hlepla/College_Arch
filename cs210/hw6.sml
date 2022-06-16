(* Hayden Lepla (lepl1529) *)

val outfile = TextIO.openOut("lepl1529.txt")
val _ = TextIO.output(outfile, "lep1529\n")
val prompt = CommandLine.arguments() ;

fun writetofile [] = TextIO.output(outfile,"lepl1529\n")
  | writetofile (args::end_args) = (TextIO.output(outfile,args ^ "\n"); writetofile end_args)

val result = writetofile(prompt) ;
 val endfile = TextIO.closeOut outfile ;
 val _ = OS.Process.exit(OS.Process.success) ;
