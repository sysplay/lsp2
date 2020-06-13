#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "fifo"

int main(void)
{
	FILE *fp;
	char readbuf[80];

        //TODO 1: Create the FIFO using library function

	printf("\nWaiting for writer clients ...\n");
        //TODO 2: Open the FIFO file
        //TODO 3: Read & print until EOF
	
	fclose(fp);

	return 0;
}
