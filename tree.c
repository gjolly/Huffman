#include "tree.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>

void init_void_Tree(void** tree)
{
	*(Tree*)tree = malloc(sizeof(struct Tree));
	init_Couple(&(*(Tree*)tree)->couple, 0, '\0');
	(*(Tree*)tree)->left = NULL;
	(*(Tree*)tree)->right = NULL;
}

void init_Tree(Tree* tree){
	init_void_Tree((void*)tree);
}

void destruct_Tree(void* tree)
{
	Tree* treeTree = (Tree*)tree;
	if(treeTree != NULL && *treeTree != NULL && !empty_Tree(*(treeTree)))
	{
		if (!is_leaf_Tree(*treeTree))
		{
			destruct_Tree(&((*treeTree)->left));
			destruct_Tree(&((*treeTree)->right));
		}
		free(*treeTree);
		*treeTree = NULL;
	}
}

int compar_Tree(void* c1, void* c2)
{
	size_t freq1 = ((Tree)c1)->couple.freq;
	size_t freq2 = ((Tree)c2)->couple.freq;
	Value car1 = ((Tree)c1)->couple.value;
	Value car2 = ((Tree)c2)->couple.value;
	if (freq1 != freq2)
		return (freq1 < freq2) ? -1 : (freq1 > freq2);
	else
		return (car1 < car2) ? -1 : (car1 > car2);
}

bool empty_Tree(Tree tree)
{
	return tree == NULL;
}

size_t size_Tree(Tree tree)
{
	if (empty_Tree(tree))
		return 0;
	return 1 + size_Tree(tree->left) + size_Tree(tree->right);
}

bool has_key_Tree(Tree tree, int freq)
{
	if (empty_Tree(tree))
		return false;
	
	return tree->couple.freq == freq || has_key_Tree(tree->left, freq) || has_key_Tree(tree->right, freq);
}

bool is_leaf_Tree(Tree tree)
{
	return tree->right == NULL && tree->left == NULL;
}

Value get_value_Tree(Tree tree, int freq)
{
	if (empty_Tree(tree))
		return (char)0;
	
	if (tree->couple.freq == freq)
		return tree->couple.value;
	
	return has_key_Tree(tree->left, freq) | has_key_Tree(tree->right, freq);
}

static void print_tab(size_t n)
{
	for (int iTab = 0; iTab < n; iTab++)
		printf(" ");
}

static void print_deep_Tree(Tree tree, size_t depth)
{
	print_tab(depth);
	
	printf("(%lu)", tree->couple.freq);
	if (is_leaf_Tree(tree))
		printf(" '%c'\n", tree->couple.value);
	if (tree->left != NULL)
	{
		printf("\n");
		print_tab(depth+2);
		printf("\\--0--\n");
		print_deep_Tree(tree->left, depth+8);
	}
	if (tree->right != NULL)
	{
		if (tree->left == NULL)
			printf("\n");
		print_tab(depth+2);
		printf("\\--1--\n");
		print_deep_Tree(tree->right, depth+8);
	}
}

void print_Tree(Tree tree){
	if (empty_Tree(tree))
		printf("(0)\n");
	else {
		print_deep_Tree(tree, 0);
	}
}

void couple_to_Tree(Tree* tree, Couple couple)
{
	(*tree)->couple = couple;
}

void concatenate_Tree(Tree* dest, Tree source)
{
	Tree tree;
	init_Tree(&tree);
	tree->couple.value = ' ';
	tree->couple.freq =  (*dest)->couple.freq + source->couple.freq;
	tree->left = *dest;
	tree->right = source;
	*dest = tree;
	//print_Tree(*dest);
}

void add_subTree(Tree father, Tree fils, bool right)
{
	if (right)
		father->right = fils;
	else
		father->left = fils;
}

void equal_Tree(void* dest, void* source)
{
	puts("source in equal");
	print_Tree((Tree)source);
	**(Tree*)dest = *(Tree)source;
	puts("dest in equal");
	print_Tree(*(Tree*)dest);
}

void print_list_tree(List list)
{
	Cell cell = list->cell;
	while (cell != NULL)
	{
		//printf("%lu : ", ((Tree)(cell->data))->couple.freq);
		//printf("%c\t|", ((Tree)(cell->data))->couple.value);
		print_Tree((Tree)(cell->data));
		cell = cell->next;
	}
	printf("\n");
}

void fusion_List_Tree(List listTree)
{
	Tree tree0; //premier arbre de la liste
	Tree tree1; //deuxième arbre de la liste
	while (listTree->cell->next != NULL)
	{
		tree0 = (Tree)front_List(listTree);
		tree1 = (Tree)get_i_List(listTree, 1);
		
		concatenate_Tree(&tree1, tree0);
		add_List(listTree, (void*)(tree1));
		
		puts("tree1:");
		print_Tree(tree1);
		
		pop_front_List(listTree);
		pop_front_List(listTree);
	}
}

void replace_Tree(Tree tree, Tree* trees, int sizeTree)
{
	int iTree = 0;
	while (iTree+1 < sizeTree && compar_Tree(trees[iTree + 1], tree) != 1)
	{
		trees[iTree] = trees[iTree + 1];
		iTree++;
	}
	trees[iTree] = tree;
}

void fusion_tab_Tree(Tree* trees, int sizeTree)
{
	int firstTree = 0; //premier arbre alloué du tableau
	while (firstTree < sizeTree - 1) //on itère tant qu'il reste plus d'un arbre dans le tableau
	{
		concatenate_Tree(&(trees[firstTree + 1]), trees[firstTree]);
		
		replace_Tree(trees[firstTree + 1], trees + firstTree, sizeTree - firstTree);
		firstTree++;
	}
}
