#include "binary.h"
#include <assert.h>

void unit_init_Binary()
{
	Binary binary;
	init_Binary(&binary);
	
	destruct_Binary(&binary);
}

void unit_init_fromByte_Binary()
{
	Binary binary;
	Byte* unByte = malloc(sizeof(Byte));
	*unByte = 1;
	init_fromByte_Binary(&binary, unByte, 1);
	
	print_hexa_Binary(binary);
	
	free(unByte);
	
	destruct_Binary(&binary);
}

void unit_left_shift_Binary()
{
	Binary binary;
	Byte* unByte = malloc(sizeof(Byte));
	*unByte = 3;
	init_fromByte_Binary(&binary, unByte, 2);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 7);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 1);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 15);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 16);
	print_hexa_Binary(binary);
	
	free(unByte);
	
	destruct_Binary(&binary);
}

void unit_right_shift_Binary()
{
	Binary binary;
	Byte* unByte = malloc(sizeof(Byte));
	*unByte = 3;
	init_fromByte_Binary(&binary, unByte, 2);
	
	right_shift_Binary(binary, 1);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 8);
	print_hexa_Binary(binary);
	
	right_shift_Binary(binary, 1);
	print_hexa_Binary(binary);
	
	left_shift_Binary(binary, 10);
	print_hexa_Binary(binary);
	
	right_shift_Binary(binary, 15);
	print_hexa_Binary(binary);
	
	print_Binary(binary);
	
	free(unByte);
	
	Byte deuxByte[] = {2, 22, 75, 200, 183};
	init_fromByte_Binary(&binary, deuxByte, 35);
	print_hexa_Binary(binary);
	
	right_shift_Binary(binary, 1);
	print_hexa_Binary(binary);
	
	destruct_Binary(&binary);
}

void unit_or_Binary()
{
	Binary binary;
	Byte* unByte = malloc(sizeof(Byte));
	*unByte = 2;
	init_fromByte_Binary(&binary, unByte, 2);
	
	left_shift_Binary(binary, 8);
	
	Binary unBinary = un_Binary();
	or_Binary(&binary, unBinary);
	print_hexa_Binary(binary);
	
	or_Binary(&unBinary, binary);
	print_hexa_Binary(unBinary);
	
	free(unByte);
	destruct_Binary(&unBinary);
	
	destruct_Binary(&binary);
}

void unit_and_Binary()
{
	Binary binary = un_Binary();
	left_shift_Binary(binary, 8);
	
	Binary unBinary = un_Binary();
	or_Binary(&binary, unBinary);
	and_Binary(&binary, unBinary);
	print_hexa_Binary(binary);
	
	Binary binary2 = un_Binary();
	left_shift_Binary(binary2, 8);
	
	or_Binary(&binary2, unBinary);
	
	left_shift_Binary(unBinary, 8);
	
	and_Binary(&binary2, unBinary);
	print_hexa_Binary(binary2);
	
	destruct_Binary(&unBinary);
	
	destruct_Binary(&binary);
	destruct_Binary(&binary2);
}

void unit_write_Binary()
{
	;
}

void unit_add_Binary()
{
	Binary binary = un_Binary();
	
	add_one_Binary(binary);
	print_hexa_Binary(binary);
	
	add_one_Binary(binary);
	print_hexa_Binary(binary);
	
	add_zero_Binary(binary);
	print_hexa_Binary(binary);
	
	add_one_Binary(binary);
	print_hexa_Binary(binary);
	
	destruct_Binary(&binary);
}

void tests()
{
	//unit_init_Binary();
	//unit_init_fromByte_Binary();
	//unit_left_shift_Binary();
	unit_right_shift_Binary();
	//unit_or_Binary();
	//unit_and_Binary();
	//unit_write_Binary();
	//unit_add_Binary();
}

int main(int argc, char** argv)
{
	tests();
	return 0;
}
