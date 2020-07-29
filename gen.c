#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "log.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage:  gen <filename>\n");
		return 1;
	}

	int fd = open(argv[1], O_WRONLY);
	if (fd < 0)
		err(-1, "error opening '%s'\n", argv[1]);

	struct header head;
	strncpy(head.name, "building access log", sizeof(head.name));
	head.count = 2;

	if (write(fd, &head, sizeof(head)) != sizeof(head))
		err(-1, "error writing header");

	struct record records[2];
	records[0].subject = 1000;
	records[0].object = 24927;
	records[0].timestamp = time(NULL) - 10;
	strncpy(records[0].description, "door opened", 32);
	strncpy(records[0].location, "EN3000", 32);

	records[1].timestamp = time(NULL);
	records[1].subject = 1000;
	records[1].object = 19472;
	strncpy(records[1].description, "door locked", 32);
	strncpy(records[1].location, "EN3028", 32);

	write(fd, &records, sizeof(records));

	close(fd);

	return 0;
}
