#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "airport.h"
#include <string.h>
#include <time.h>

extern pthread_mutex_t locker;
extern int pass;
int tidx = 0;
pthread_t tr[100];

void * createStaff( void * arg )
{
	staff *itr = (staff*)arg;
	printf("%s service has begun!\n", itr->name);
	while (pass > 0)
	{
		printf("Traveler %d presents ticket to staff %s.\n", pass, itr->name);
		itr->checked++;
		if (itr->checked % 5 == 0)
		{
			int j = 0;
			for (j; j < 1000000000; j++)
				;
		}
		pthread_mutex_lock(&locker);
		pass--;
		pthread_mutex_unlock(&locker);
	}
}

int AirlineStaff( staff * name )
{
	int rs;
	staff * itr = (staff *) malloc(sizeof(staff*));
	itr = name;
	while (itr != NULL)
	{
		rs = pthread_create(&tr[tidx], NULL, createStaff, (void *)itr);
		tidx++;
		if (rs != 0)
		{
			printf("Error creating thread\n");
			return -1;
		}
		itr = itr->next;
	}

	while (pass > 0);
	return 0;
}

staff * read_staff_file( char * filename )
{
	staff *start;
	staff *prev;
	staff *current = NULL;
	FILE *file = fopen( filename, "r");
	char name[50];

	if (!file)
	{
		printf("Error reading file...\n");
		return NULL;
	}

	while (fscanf(file, "%s", name) != EOF)
	{
		prev = current;
		current = (staff*)malloc(sizeof(staff));
		strcpy( current->name, name );
		current->checked = 0;
		current->next = NULL;
		if (prev == NULL)
			start = current;
		else
			prev->next = current;
	}

	fclose(file);
	return start;
}
