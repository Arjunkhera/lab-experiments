#include <stdio.h>

#define  EVER   ;;

int main(){
  int process;
  char line[81];

  for (EVER){
      fprintf(stderr, "cmd: ");
      if ( gets (line) == (char *) NULL) exit (0);

      process = fork ();
      if(process > 0)  wait ((int *) 0);
      else if (process == 0){
        execlp (line, line, (char *) NULL);
        fprintf (stderr, "Can't execute %s\n", line);
        exit (1);
      }
      else if ( process == -1){
        fprintf (stderr, "Can't fork!\n");
        exit (2);
      }
  }
}
