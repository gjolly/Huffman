#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "compress.h"

void print_tab_Couple(Couple* couples, int size)
{
	for (int iCouple = 0; iCouple < size; iCouple++)
		printf("%c: %lu\n", couples[iCouple].value, couples[iCouple].freq);
}

void init_freq(Couple* couples)
{
	for (int iCouple = 0; iCouple < UCHAR_MAX + 1; iCouple++)
		init_Couple(&couples[iCouple], 0, (unsigned char) iCouple);
}

int frequence(FILE* fichier, Couple* couples)
{
	int sizeFile = 0;
	while (!feof(fichier))
	{
		unsigned char iCarac;
		fscanf(fichier, "%c", &iCarac);
		couples[iCarac].freq += 1;
		sizeFile++;
	}
	
	return sizeFile-1;
}

void tri_Couple(Couple* couples)
{
	qsort(couples, UCHAR_MAX + 1, sizeof(Couple), compar_Couple);
}

size_t build_Tree(Couple* couples, Tree* tree)
{
	//on passe toutes les cellules ou la frequence est nulle
	int iCouple = 0;
	while (couples[iCouple].freq == 0)
		iCouple++;
	size_t sizeTree = UCHAR_MAX + 1 - iCouple;
	
	//on transforme la liste de cellules en liste d'arbres a un noeud
	Tree trees[sizeTree];
	for(int iTree = 0; iTree < sizeTree; iTree++)
	{
		init_Tree(trees + iTree);
		couple_to_Tree(&(trees[iTree]), couples[iCouple + iTree]);
	}
	
	fusion_tab_Tree(trees, sizeTree);
	
	//On recupere le seul arbre de la liste qui est l'arbre fusionne
	*tree = trees[sizeTree - 1];
	
	return sizeTree;
}

void description_Tree(Tree tree, Binary description, Value** caracs)
{
	if (tree != NULL)
	{
		if (is_leaf_Tree(tree))
		{
			**caracs = (unsigned char)tree->couple.value;
			(*caracs)++;
		}
		
		add_zero_Binary(description); //ajouter un zero en fin de sequence binaire
		description_Tree(tree->left, description, caracs);
		
		if (!is_leaf_Tree(tree))
			add_one_Binary(description); //ajouteur un 1 en fin de sequence binaire
		
		description_Tree(tree->right, description, caracs);
		
		if (!is_leaf_Tree(tree))
			add_one_Binary(description); //ajouteur un 1 en fin de sequence binaire
	}
}

int indice_tableau(Value elmt, Value* tableau, size_t sizeTab)
{
	for (int i = 0; i < sizeTab; i++)
		if (tableau[i] == elmt)
			return i;
	return -1;
}

void mise_en_forme_description(Binary descriptionTree)
{
	if (descriptionTree->size > 1)
		pop_front_Bit_Binary(descriptionTree);
	while (back_Bit_Byte(descriptionTree))
		right_shift_Binary(descriptionTree, 1);
	add_one_Binary(descriptionTree);
}

void write_forhead(FILE* output, size_t sizeText, size_t sizeTree, Value* caracs)
{
	unsigned int toto = sizeText;
	fwrite(&toto, sizeof(unsigned int), 1, output);
	fprintf(output, "%c", (unsigned char)sizeTree);
	for (int iChar = 0; iChar < sizeTree; iChar++)
		fprintf(output, "%c", caracs[iChar]);
}

void write_new_Char(FILE* input, FILE* output, Binary tamponBinary, Binary* tableCorresp, int iChar, size_t sizeText)
{
	loadBar(iChar+1, sizeText, (int)sqrt(sizeText)+1, 50);
	unsigned char readCaractere;
	
	if (fscanf(input, "%c", &readCaractere) == 1)
	{
		Binary binaryCaract;
		init_Binary(&binaryCaract);
		equal_Binary(&binaryCaract, tableCorresp[(int)readCaractere]);
		//concatenate_Binary(tamponBinary, binaryCaract);
		concatenate_bis_Binary(tamponBinary, binaryCaract);
		write_Binary(tamponBinary, output);
		destruct_Binary(&binaryCaract);
	}
}

void write_body_compress(FILE* input, FILE* output, Binary descriptionTree, Binary* tableCorresp, size_t sizeTree, size_t sizeText)
{
	Binary tamponBinary = descriptionTree;
	write_Binary(tamponBinary, output);
	
	
	for (int iChar = 0; !feof(input); iChar++)
		write_new_Char(input, output, tamponBinary, tableCorresp, iChar, sizeText);
	printf("\n");
	//on cloture alors le texte
	
	while (tamponBinary->size < CHAR_BIT)
		add_zero_Binary(tamponBinary);
	write_Binary(tamponBinary, output);
}

void compress(FILE* input, FILE* output)
{	
	Couple couples[UCHAR_MAX + 1];
	init_freq(couples);
	
	size_t sizeFile = frequence(input, couples);
	rewind(input);
	
	tri_Couple(couples);
	
	Tree tree;
	size_t sizeTree = build_Tree(couples, &tree);
	
	Binary descriptionTree = zero_Binary();
	Value* caracs = malloc(sizeof(Value)*sizeTree);
	Value* parcoursCarac = caracs;
	description_Tree(tree, descriptionTree, &parcoursCarac); //établit la description de l'arbre et la liste (ordonnee) des caractères qui le compose
	
	mise_en_forme_description(descriptionTree); //s'assure que descriptionTree termine par un seul 1

	Binary tableCorresp[UCHAR_MAX + 1]; //va contenir la table de correspondance (caractère -> code de huffman)
	for(int i=0; i< UCHAR_MAX + 1; i++)
		init_Binary(tableCorresp+i);
	
	Binary zeroBinary = zero_Binary();
	construct_table_corresp(tree, tableCorresp, zeroBinary); //on construit la table de correspondance
	destruct_Binary(&zeroBinary);
		
	write_forhead(output, sizeFile, sizeTree, caracs);
	write_body_compress(input, output, descriptionTree, tableCorresp, sizeTree, sizeFile);
	
	for(int i=0; i< UCHAR_MAX + 1; i++)
		destruct_Binary(&(tableCorresp[i]));
	
	destruct_Binary(&descriptionTree);
	free(caracs);
	destruct_Tree(&tree);
}
