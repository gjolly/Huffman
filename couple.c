#include "couple.h"

void init_Couple(Couple* couple, size_t freq, Value value)
{
	couple->freq = freq;
	couple->value = value;
}

int compar_Couple(const void* c1, const void* c2)
{
	size_t freq1 = ((Couple*)c1)->freq;
	size_t freq2 = ((Couple*)c2)->freq;
	return (freq1 < freq2) ? -1 : (freq1 > freq2);
}
