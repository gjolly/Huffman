#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "uncompress.h"

void add_empty_subTree(Tree tree, bool right)
{
	Tree newTree;
	init_Tree(&newTree);
	add_subTree(tree, newTree, right);
}

int indice_tableau_Binary(Binary elmt, Binary* tableau, size_t sizeTab)
{
	for (int iElmt = 0; iElmt < sizeTab; iElmt++)
		if (compar_Binary(tableau[iElmt], elmt) == 0)
			return iElmt;
	return -1;
}

void read_forhead(FILE* input, size_t* sizeText, char* sizeTree, Value** caracsTree)
{
	unsigned int tmp;
	fread(&tmp, sizeof(unsigned int), 1, input);
	*sizeText = tmp;
	fscanf(input, "%c", sizeTree);
	int sizeT = (int) *sizeTree; 
	*caracsTree = malloc(sizeof(Value)*sizeT);
	for (int iCarac = 0; iCarac < sizeT; iCarac++)
		fscanf(input, "%c", (*caracsTree + iCarac));
}

void update_tampon(Binary binary, FILE* file)
{
	//on retire le premier bit--> taille -1
	pop_front_Bit_Binary(binary);
	//on recharge un caractere si size == 0
	if (binary->size == 0)
	{
		Byte byte;
		fscanf(file, "%c", &byte);
		add_List(binary->byte, &byte);
		binary->size = CHAR_BIT;
	}
}

void reconstruct_Tree(FILE* input, Tree tree, Binary tamponLecture, size_t sizeTree, size_t* nbLeaf, Value* caracsTree)
{
	if (*nbLeaf < sizeTree)
	{
		if (!front_Bit_Byte(tamponLecture))
		{
			update_tampon(tamponLecture, input);
			
			add_empty_subTree(tree, false);
			reconstruct_Tree(input, tree->left, tamponLecture, sizeTree, nbLeaf, caracsTree);
			
			add_empty_subTree(tree, true);
			reconstruct_Tree(input, tree->right, tamponLecture, sizeTree, nbLeaf, caracsTree);
		}
		else
		{
			tree->couple.value = caracsTree[*nbLeaf];
			(*nbLeaf)++;
			if (*nbLeaf < sizeTree)
				while (front_Bit_Byte(tamponLecture))//tout ce qu'il y a après un un est inutile (sauf si c'est le dernier 1 de la description...)
					update_tampon(tamponLecture, input);
			update_tampon(tamponLecture, input);
		}
	}
}

char read_next_Char(FILE* input, Binary tamponCarac, Binary* tableCorresp, Binary tamponLecture)
{
	do
	{
		if (front_Bit_Byte(tamponLecture))
			add_one_Binary(tamponCarac);
		else
			add_zero_Binary(tamponCarac);
		update_tampon(tamponLecture, input);
	} while (indice_tableau_Binary(tamponCarac, tableCorresp, UCHAR_MAX+1) == -1);
	
	return indice_tableau_Binary(tamponCarac, tableCorresp, UCHAR_MAX+1);
}

void write_new_Char(FILE* input, FILE* output, size_t sizeText, Binary* tamponCarac, Binary* tableCorresp, Binary tamponLecture, int iChar)
{
	destruct_Binary(tamponCarac);
	*tamponCarac = zero_Binary();
	fprintf(output, "%c", read_next_Char(input, *tamponCarac, tableCorresp, tamponLecture));
	loadBar(iChar+1, sizeText, (int)sqrt(sizeText)+1, 50);
}

void write_body_uncompress(FILE* input, FILE* output, size_t sizeText, Binary* tableCorresp, size_t sizeTree, Binary tamponLecture)
{
	Binary tamponCarac = zero_Binary();
	
	for (int iChar = 0; iChar < sizeText; iChar++)
		write_new_Char(input, output, sizeText, &tamponCarac, tableCorresp, tamponLecture, iChar);
	printf("\n");
	destruct_Binary(&tamponCarac);
}

void uncompress(FILE* input, FILE* output)
{
	size_t sizeText;
	char sizeTree;
	Value* caracs;
	
	read_forhead(input, &sizeText, &sizeTree, &caracs);
	
	size_t nbLeaf = 0;
	Tree tree;
	init_Tree(&tree);
	Binary tamponLecture;
	Byte byte;
	fscanf(input, "%c", &byte);
	
	init_fromByte_Binary(&tamponLecture, &byte, CHAR_BIT);
	
	reconstruct_Tree(input, tree, tamponLecture, sizeTree, &nbLeaf, caracs);
	
	Binary tableCorresp[UCHAR_MAX + 1];
	for(int i=0; i< UCHAR_MAX + 1; i++)
		init_Binary(tableCorresp+i);
	
	Binary zeroBinary = zero_Binary();
	construct_table_corresp(tree, tableCorresp, zeroBinary); //on construit la table de correspondance
	destruct_Binary(&zeroBinary);
	
	write_body_uncompress(input, output, sizeText, tableCorresp, sizeTree , tamponLecture);
	
	for(int i=0; i< UCHAR_MAX + 1; i++)
		destruct_Binary(&(tableCorresp[i]));
	
	destruct_Binary(&tamponLecture);
	destruct_Tree(&tree);
	free(caracs);
}
