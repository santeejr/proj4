#ifndef AIRPORT_H_
#define AIRPORT_H_

typedef struct __staff
{
	char name[50];
	int checked;
	struct __staff *next;
} staff;

int AirlineStaff( staff * name );
staff* read_staff_file(char *filename);

#endif /* AIRPORT_H_ */
