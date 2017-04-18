#include "tree.h"
#include "couple.h"
#include <assert.h>

void unit_init_Tree(){
	Tree tree;
	init_Tree(&tree);
	
	destruct_Tree(&tree);
}

void unit_couple_to_Tree(){
	Couple couple;
	init_Couple(&couple, 50, 'a');
	
	Tree tree;
	init_Tree(&tree);
	couple_to_Tree(&tree, couple);
	couple_to_Tree(&tree, couple);
	
	print_Tree(tree);
	
	destruct_Tree(&tree);
}

void unit_print_Tree(){
	Tree tree;
	init_Tree(&tree);
	Couple couple;
	init_Couple(&couple, 50, 'a');
	couple_to_Tree(&tree, couple);
	
	init_Tree(&(tree->left));
	init_Couple(&couple, 24, 'b');
	couple_to_Tree(&(tree->left), couple);
	
	print_Tree(tree);
	
	destruct_Tree(&tree);
}

void unit_add_subTree(){
	Couple couple1;
	init_Couple(&couple1, 50, 'a');
	Couple couple2;
	init_Couple(&couple2, 25, 'g');
	
	Tree tree1;
	init_Tree(&tree1);
	couple_to_Tree(&tree1, couple1);
	
	Tree tree2;
	init_Tree(&tree2);
	couple_to_Tree(&tree2, couple2);
	
	add_subTree(tree1, tree2, true);
	
	print_Tree(tree1);
	
	destruct_Tree(&tree1);
	//destruct_Tree(&tree2);	<-- clairement faux : on a ajoute tree2 a tree1
}

void unit_compar_Tree()
{
	Couple couple1;
	init_Couple(&couple1, 50, 'a');
	Couple couple2;
	init_Couple(&couple2, 25, 'g');
	
	Tree tree1;
	init_Tree(&tree1);
	couple_to_Tree(&tree1, couple1);
	
	Tree tree2;
	init_Tree(&tree2);
	couple_to_Tree(&tree2, couple2);
	
	bool test = compar_Tree(&tree1, &tree2);
	
	assert(test == 1);
	
	destruct_Tree(&tree1);
	destruct_Tree(&tree2);
}

void unit_equal_Tree()
{
	Tree tree1;
	init_Tree(&tree1);
	tree1->couple.freq = 2;
	tree1->couple.value = 'c';
	tree1->right = NULL;
	tree1->left = NULL;
	
	Tree tree2;
	init_Tree(&tree2);
	equal_Tree(&tree2, tree1);
	print_Tree(tree1);
	print_Tree(tree2);
	
	destruct_Tree(&tree1);
	print_Tree(tree2);
}

void tests()
{
	//unit_init_Tree();
	//unit_couple_to_Tree();
	//unit_print_Tree();
	//unit_add_subTree();
	//unit_compar_Tree();
	unit_equal_Tree();
}

int main(int argc, char** argv)
{
	tests();
	return 0;
}
