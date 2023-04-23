#include <stdio.h>

struct date
{
	int month;
	int day;
	int year;
};


int main()
{
	struct date today;

	printf_s("\t Enter date: mm/dd/yyyy \n");
	scanf_s("%d %d %d", &today.month, &today.day, &today.year);
	printf_s("\t %d/%d/%d \n" ,today.month, today.day, today.year);

	struct date* ptrdate = &today;
	printf_s("\t ref date %d/%d/%d \n", ptrdate->month, ptrdate->day, ptrdate->year);
	(*ptrdate).month = 01;
	(*ptrdate).day = 01;
	(*ptrdate).year = 1970;
	printf_s("\t ref date %d/%d/%d \n", ptrdate->month, ptrdate->day, ptrdate->year);
}