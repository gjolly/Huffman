#include "byte.h"
#include <stdlib.h>

void init_Byte(void** a)
{
	*a = malloc(sizeof(char));
	*(Byte*)(*a) = '\0';
}

void equal_Byte(void* a, void* b)
{
	*(Byte*)a = *(Byte*)b;
}

int compar_Byte(void* a, void* b)
{
	return (*(Byte*)a < *(Byte*)b)? -1 : (*(Byte*)a > *(Byte*)b);
}

int noOrder_Byte(void* a, void* b)
{
	return (*(Byte*)a == *(Byte*)b)? 0 : -1;
}

int reverse_order_Byte(void* a, void* b)
{
	return -noOrder_Byte(a, b);
}
