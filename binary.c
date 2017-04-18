#include "binary.h"

int super_modulo(int n, int mod)
//renvoie entre 1 et n
{
	return (n-1)%mod+1;
}

void init_Binary(Binary* binary)
{
	*binary = malloc(sizeof(struct Binary));
	init_List(&((*binary)->byte), sizeof(Byte), init_Byte, free, equal_Byte, noOrder_Byte);
	(*binary)->size = 0;
}

void init_fromByte_Binary(Binary* binary, Byte* byte, size_t size)
{
	init_Binary(binary);
	size_t sizeByte = (size == 0) ? size : (size/CHAR_BIT+(size%CHAR_BIT != 0));
	
	for(int iByte = 0; iByte < sizeByte; iByte++)
		add_List((*binary)->byte, &byte[iByte]);
	
	(*binary)->size = size;
}

void destruct_Binary(Binary* binary)
{
	destroy_List(&((*binary)->byte));
	free(*binary);
	*binary = NULL;
}

void equal_Binary(Binary* a, Binary b)
{
	if (a != NULL)
		destruct_Binary(a);
	init_Binary(a);
	if (b->size != 0)
	{
		Cell copy = b->byte->cell;
		while (copy != NULL)
		{
				add_List((*a)->byte, copy->data);
				copy = copy->next;
		}
	}
	//Then size
	(*a)->size = b->size;
}

void swap_Binary(Binary a, Binary b)
{
	struct Binary tmp = *a;
	*a = *b;
	*b = tmp;
}

void concatenate_Binary(Binary dest, Binary source)
{
	left_shift_Binary(dest, source->size);
	or_Binary(&dest, source);
}

void concatenate_bis_Binary(Binary dest, Binary source)
{
	size_t sizeDest = dest->size;
	int shift = super_modulo(source->size, CHAR_BIT);
	Byte frontByte = back_Byte_Binary(dest);
	frontByte <<= shift;
	Byte backByte = front_Byte(source);
	backByte <<= (CHAR_BIT - shift);
	backByte >>= (CHAR_BIT - shift);
	*(Byte*)source->byte->cell->data = backByte | frontByte;
	
	right_shift_Binary(dest, CHAR_BIT-shift);
	
	if (sizeDest + source->size > CHAR_BIT)
	{
		//Ceci est sense aller dans le module list
		Cell cell = dest->byte->cell;
		while (cell != NULL)	//Tant qu'on est pas a la fin
		{
			if (cell->next == NULL)
			{
				cell->next = source->byte->cell;
				break;
			}
			cell = cell->next;
			
		}
		if (cell != NULL)
			source->byte->cell = dest->byte->cell;
	}
	dest->byte->cell = NULL;
	source->size += sizeDest;
	swap_Binary(dest, source);
}

int compar_Binary(Binary a, Binary b)
{
	if(a->size != b->size)
		return (a->size < b->size)*2-1;
	
	Cell cellA = a->byte->cell;
	Cell cellB = b->byte->cell;
	while(cellA != NULL)
	{
		if (*(Byte*)cellA->data != *(Byte*)cellB->data)
			return (*(Byte*)cellA->data < *(Byte*)cellB->data)*2-1;
		cellA = cellA->next;
		cellB = cellB->next;
	}
	return 0;
}


void add_zero_Binary(Binary binary)
{
	left_shift_Binary(binary, 1);
}

void add_one_Binary(Binary binary)
{
	Binary unBinary = un_Binary();
	concatenate_Binary(binary, unBinary);
	destruct_Binary(&unBinary);
}

void write_Binary(Binary binary, FILE* file)
{
	if (file != NULL)
		while (binary->size >= CHAR_BIT)
		{
			Binary front = front_Binary(binary);
			fprintf(file, "%c", front_Byte(front));
			destruct_Binary(&front);
			pop_front_Binary(binary);
		}
}

size_t size_in_Byte(Binary binary)
{
	return binary->size/CHAR_BIT + (binary->size%CHAR_BIT != 0);
}

void fit_size_Binary(Binary binary)
{
	while (binary->size != 0 && front_Byte(binary) == 0)
		pop_front_Byte(binary);

	Byte frontByte = front_Byte(binary);
	size_t highByte = 0;
	while (frontByte != 0)
	{
		highByte++;
		frontByte >>= 1;
	}
	
	if (size_List(binary->byte) == 0)
		binary->size = 0;
	else
		binary->size = (size_List(binary->byte)-1)*CHAR_BIT + highByte;
}

Binary back_Binary(Binary binary)
{
	Binary r;
	Byte byte = *(Byte*)back_List(binary->byte);
	size_t size = CHAR_BIT;
	if (binary->size < CHAR_BIT)
	{
		size = binary->size;
		byte <<= CHAR_BIT-size;
		byte >>= CHAR_BIT-size;
	}
	init_fromByte_Binary(&r, &byte, size);
	print_hexa_Binary(r);
	return r;
}

Byte back_Byte_Binary(Binary binary)
{
	return (binary->size == 0) ? 0 : *(Byte*)back_List(binary->byte);
}

Byte front_Byte(Binary binary)
{
	if (binary != NULL && binary->byte->cell != NULL)
		return *(Byte*)binary->byte->cell->data;
	return 0;
}

Binary front_Binary(Binary binary)
{
	if (binary->size == 0)
		return zero_Binary();
	Byte begin = *(Byte*)front_List(binary->byte);
	Byte end;
	size_t shift;
	size_t size = (binary->size <= CHAR_BIT) ? binary->size : CHAR_BIT;
	
	if (binary->size <= CHAR_BIT)
	{
		end = 0;
		shift = CHAR_BIT;
	}
	else
	{
		end = *(Byte*)get_i_List(binary->byte, 1);
		shift = super_modulo(binary->size, CHAR_BIT);
	}
	
	begin <<= CHAR_BIT - shift;
	end >>= shift;
	
	Byte* res = malloc(CHAR_BIT);
	*res = begin | end;
	
	Binary r;
	init_fromByte_Binary(&r, res, size);
	free(res);
	
	return r;
}

void pop_front_Byte(Binary binary)
{
	if (binary->size != 0)
	{
		pop_front_List(binary->byte);
		binary->size -= super_modulo(binary->size, CHAR_BIT);
	}
}

void pop_front_Binary(Binary binary)
{
	if (binary->size <= CHAR_BIT)
	{
		pop_front_List(binary->byte);
		binary->size = 0;
	}
	else
	{
		size_t shift = super_modulo(binary->size, CHAR_BIT);
		Byte* front = get_i_List(binary->byte, 1);
		
		*front <<= CHAR_BIT - shift;
		*front >>= CHAR_BIT - shift;
		
		pop_front_List(binary->byte);
		binary->size -= CHAR_BIT;
	}
}

bool front_Bit_Byte(Binary binary)
{
	return (front_Byte(binary) >> (super_modulo(binary->size, CHAR_BIT)-1)) & 1;
}

bool back_Bit_Byte(Binary binary)
{
	if (binary->size == 0)
		return 0;
	Byte backByte = *(Byte*)back_List(binary->byte);
	return backByte & 1;
}

void pop_back_Binary(Binary binary)
{
	pop_back_List(binary->byte);
	if (binary->size < CHAR_BIT)
		binary->size = 0;
	else
		binary->size -= 8;
}

void pop_front_Bit_Binary(Binary binary)
{
	if (binary->size == 0)
		return;
	int superModulo = super_modulo(binary->size, CHAR_BIT);	//modulo entre 1 et 8
	if (superModulo == 1)
		pop_front_Byte(binary);
	else
	{
		//Erase first bit
		*(Byte*)binary->byte->cell->data <<= CHAR_BIT-(superModulo-1);
		*(Byte*)binary->byte->cell->data >>= CHAR_BIT-(superModulo-1);
		binary->size--;
	}
}

void left_shift_Binary(Binary binary, int n)
{
	Byte zeroByte = 0;
	Cell cell = binary->byte->cell;
	bool firstCell = true;
	while (cell != NULL)
	{
		//if first cell, need to create a new one to put the shift in
		if (firstCell && super_modulo(n+binary->size, CHAR_BIT) < super_modulo(binary->size, CHAR_BIT))
		{
			push_front_List(binary->byte, &zeroByte);
			firstCell = false;
			cell = binary->byte->cell;
		}
		
		Byte* highByte = cell->data;
		*highByte <<= n%CHAR_BIT;
		
		if (cell->next != NULL)
		{
			Byte* lowByte = cell->next->data;
			Byte secondPart = *lowByte;
			
			secondPart >>= CHAR_BIT - n%CHAR_BIT;
			*highByte |= secondPart;
		}
		cell = cell->next;
	}
	
	size_t nToAddByte =  n/CHAR_BIT + (binary->size == 0);
	for (int iByte = 0; iByte < nToAddByte; iByte++)
		push_back_List(binary->byte, &zeroByte);
	//Then remove unused part at the beginning
	binary->size += n;
}

void right_shift_Binary(Binary binary, int n)
{
	if (binary->size <= n)	//Place binary to zero
	{
		clear_List(binary->byte);
		binary->size = 0;
	}
	else
	{
		size_t shift = n%CHAR_BIT;
		
		//This is in O(n2)  --> NEED TO BE LINEAR !!!!
		for (int iByte = size_in_Byte(binary) - 1; iByte > 0; iByte--)
		{
			Byte* curByte = get_i_List(binary->byte, iByte);

			if (iByte < size_in_Byte(binary) - (binary->size-n)/CHAR_BIT-1)
			{
				*curByte = 0;
				continue;
			}
			Byte* highByte = get_i_List(binary->byte, iByte-1 - n/CHAR_BIT);
			Byte firstPart = (highByte == NULL) ? 0 : *highByte;
			firstPart <<= (CHAR_BIT - shift)%CHAR_BIT;
			
			Byte* lowByte = get_i_List(binary->byte, iByte - n/CHAR_BIT);
			Byte secondPart = *lowByte;
			secondPart >>= shift%CHAR_BIT;
			
			*curByte = firstPart | secondPart;
		}
		//Shift for the front byte
		*(Byte*)(binary->byte->cell->data) >>= shift;
		
		//Then remove unused part at the beginning
		size_t shiftByte = size_in_Byte(binary) - ((binary->size-n)/CHAR_BIT+((binary->size-n)%CHAR_BIT != 0));
		for (int iRemove = 0; iRemove < shiftByte; iRemove++)
		{
			n -= super_modulo(binary->size, CHAR_BIT);
			pop_front_Byte(binary);
		}
		binary->size -= n;
	}
}

void or_Binary(Binary* dest, Binary source)
{
	
	//Align dest n source bytes
	int shift = size_in_Byte(*dest) - size_in_Byte(source);
	if (shift < 0)
	{
		swap_Binary(*dest, source);
		shift *= -1;
	}
	
	Cell cellDest = (*dest)->byte->cell;
	Cell cellSource = source->byte->cell;
	
	while (shift != 0)
	{
		cellDest = cellDest->next;
		shift--;
	}
	
	//Or on each byte
	while (cellDest != NULL && cellSource != NULL)
	{
		*(char*)cellDest->data |= *(char*)cellSource->data;
		cellDest = cellDest->next;
		cellSource = cellSource->next;
	}
}

void and_Binary(Binary* dest, Binary source)
{
	//Align dest n source bytes
	int shift = size_in_Byte(*dest) - size_in_Byte(source);
	if (shift > 0)
		swap_Binary(*dest, source);
	
	Cell cellSource = source->byte->cell;
	while (shift > 0)
	{
		cellSource = cellSource->next;	//first bytes : & with 0
		shift--;
	}
	
	//And on each byte
	Cell cellDest = (*dest)->byte->cell;
	
	while (cellDest != NULL)
	{
		*(char*)cellDest->data &= *(char*)cellSource->data;
		cellDest = cellDest->next;
		cellSource = cellSource->next;
	}
}

void print_hexa_Binary(Binary binary)
{
	printf("size: %lu | ", binary->size);
	if (binary->size == 0)
		printf("00");
	else
	{
		Cell cell = binary->byte->cell;
		while (cell != NULL)
		{
			printf("%02x ", *(Byte*)cell->data);
			cell = cell->next;
		}
	}
	printf("\n");
}

void print_Binary(Binary binary)
{
	size_t size = binary->size;
	if (size == 0)
		printf("0");
	else
	{
		Cell cell = binary->byte->cell;
		size_t maxBit = super_modulo(size, CHAR_BIT);	//size%CHAR_BIT;
		while (cell != NULL)
		{
			Byte byte = *(Byte*)cell->data;
			for (int iBit = maxBit-1; iBit >= 0  && size != 0; iBit--)
			{
				printf("%c", ((byte<<(CHAR_BIT-1-iBit) & 128) == 128)+'0');
				size--;
			}
			maxBit = CHAR_BIT;
			printf(" ");
			cell = cell->next;
		}
	}
	printf("\n");
}

Binary zero_Binary()
{
	Binary zeroBinary;
	init_Binary(&zeroBinary);
	
	return zeroBinary;
}

Binary un_Binary()
{
	Binary unBinary = NULL;
	Byte un = 1;
	init_fromByte_Binary(&unBinary, &un, 1);
	
	return unBinary;
}
