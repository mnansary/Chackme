#include <sys/types.h>


struct header
{
	char		name[32];
	int32_t		count;
};

struct record
{
	int64_t		timestamp;
	int64_t		subject;
	int64_t		object;
	char		description[32];
	char		location[32];
};
