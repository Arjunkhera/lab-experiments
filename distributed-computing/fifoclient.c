#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "./fifofile"

int main() {

   int fd,end_process,stringlen;
   char readbuf[80],end_str[5];
   // store the ending string
   strcpy(end_str,"stop");

   printf("Send messages and to stop enter \"stop\"\n");
   // create the fifo file
   // mkfifo(FIFO_FILE,06);
   // open the named pipe
   fd = open(FIFO_FILE,O_CREAT|O_WRONLY);

   while (1) {
      printf("Enter string: ");

      // read the contents into the buffer
      fgets(readbuf, sizeof(readbuf), stdin);
      stringlen = strlen(readbuf);
      readbuf[stringlen-1] = '\0';
      // check if the user asked to stop
      end_process = strcmp(readbuf, end_str);

      if(end_process != 0){
         write(fd, readbuf, strlen(readbuf));
         printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
      }else{
         write(fd, readbuf, strlen(readbuf));
         printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }

   return 0;
}
