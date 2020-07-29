#include <sys/mman.h>

#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include "log.h"


int open_log(const char *filename, struct header*, size_t *datalen);


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage:  hackme <filename>\n");
		return 1;
	}

	struct header head;
	size_t datalen;

	int fd = open_log(argv[1], &head, &datalen);
	assert(fd >= 0);

	printf("Log '%s' has %i records:\n\n", head.name, head.count);

	char buffer[datalen];
	if (read(fd, buffer, datalen) != datalen)
		err(-1, "error reading records");

	for (size_t i = 0; i < head.count; i++)
	{
		struct record *r = ((struct record*) buffer) + i;

		printf("Record %zu: %s", i, ctime(&r->timestamp));
		printf("  '%s' @ %s\n", r->description, r->location);
		printf("  subject:  %li\n", r->subject);
		printf("  object:   %li\n", r->object);

		printf("\n");
	}

	return 0;
}


int open_log(const char *filename, struct header *head, size_t *datalen)
{
	assert(datalen);

	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		err(-1, "error opening '%s'", filename);

	struct stat s;
	if (fstat(fd, &s) != 0)
		err(-1, "error getting file statistics");

	if (read(fd, head, sizeof(*head)) != sizeof(*head))
		err(-1, "error reading header");

	*datalen = s.st_size - sizeof(*head);

	return fd;
}
