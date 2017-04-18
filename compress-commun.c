#include "compress-commun.h"

void construct_table_corresp(Tree tree, Binary output[UCHAR_MAX+1], Binary curCode)
{
	if (tree != NULL)
	{
		if (is_leaf_Tree(tree))
		{
			Binary* curBinary = output+(unsigned char)tree->couple.value;
			equal_Binary(curBinary, curCode);
		}
		else
		{
			add_zero_Binary(curCode);
			construct_table_corresp(tree->left, output, curCode);
			
			add_one_Binary(curCode);
			construct_table_corresp(tree->right, output, curCode);
		}
	}
	right_shift_Binary(curCode, 1);
}

void print_table_corresp(Binary tableCorresp[UCHAR_MAX+1])
{
	for (int iCarac = 0; iCarac < UCHAR_MAX + 1; iCarac++)
		if (tableCorresp[iCarac]->size != 0)
		{
			printf("%c: %d : ", iCarac, iCarac);
			print_hexa_Binary(tableCorresp[iCarac]);
			print_Binary(tableCorresp[iCarac]);
		}
}

bool empty_file(FILE* file)
{
	unsigned char carac = fgetc(file);
	rewind(file);
	if (carac == UCHAR_MAX)
		return true;
	return false;
}

void loadBar(int x, int n, int r, int w)
{
    // Only update r times.
    if ( x % (n/r +1) != 0 ) return;
 
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100));
 
    // Show the load bar.
    for (int x=0; x<c; x++)
       printf("=");
 
    for (int x=c; x<w; x++)
       printf(" ");
 
    printf("]\r");
    fflush(stdout);
}
