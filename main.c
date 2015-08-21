#include <pthread.h>
#include <stdio.h>
#include "airport.h"
#include <stdlib.h>

staff * names;
pthread_mutex_t locker;
int pass = 100000;

int main(int argc, char * args[])
{
	pthread_mutex_init(&locker, NULL);
	names = (staff*)malloc(sizeof(staff));

	if (argc == 2)
		names = read_staff_file(args[1]);
	else {
		printf("Wrong number of arguments\n");
		return -1;
	}

	// Just adding this comment to test some git
	AirlineStaff( names );

	pthread_mutex_destroy(&locker);
	free(names);
	return 0;
}
