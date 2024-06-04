#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <time.h>

struct Date {
	unsigned year;
	unsigned month;
	unsigned day;
};

void print_time();

#endif
