#include <stdio.h>

int main()
{
	int a = 7;
	int *c = &a;

	*c = 21;
	printf ("%d\n", a);
}