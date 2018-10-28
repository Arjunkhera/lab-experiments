#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "./fifofile"

int main() {

   int fd,to_end,read_bytes;
   char readbuf[80],end[10];
   // store the ending string
   strcpy(end,"stop");

   // create the name pipe
   mknod(FIFO_FILE, S_IFIFO|0666, 0);
   // open the named pipe
   fd = open(FIFO_FILE,O_CREAT|O_RDONLY);

   while(1) {

      // read the contents into the buffer
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';

      printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

      // check if the user asked to stop
      to_end = strcmp(readbuf, end);
      if(to_end == 0){
         close(fd);
         break;
      }

      sleep(10);
   }

   return 0;
}
