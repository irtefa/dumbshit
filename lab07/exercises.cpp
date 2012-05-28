#include "exercises.h"

int sumDigits(int n)
{
	if(n%10==n)
		return n;
	return n%10 + sumDigits(n/10);
	//return -1; // Replace this with your code
}

int triangle(int rows)
{
	if(rows==0)
		return 0;
	return rows + triangle(rows-1);
	//return -1; // Replace this with your code
}
