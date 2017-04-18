#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>
#include "couple.h"
#include "list.h"

struct Tree
{
	Couple couple;
	struct Tree* left;
	struct Tree* right;
};
typedef struct Tree* Tree;

void init_void_Tree(void** tree);
/*
 * Procedure init_void_Tree(tree: in out)
 * 
 * initialise un arbre
 * 
 * Necessite:
 * L'arbre n'est pas déjà initialisé
 * 
 * Assure:
 * tree->fg = NULL && tree->fd == NULL && tree->couple.freq == 0 && tree->couple.value == '/0'
 * */

void init_Tree(Tree* tree); //modifier en void** dans le .c

void destruct_Tree(void* tree);
/*
 * Procedure destruct_Tree(tree: in out)
 * 
 * Détruit un arbre
 * 
 * Necessite:
 * L'arbre est initialisé
 * 
 * Assure:
 * tree == NULL
 * */

int compar_Tree(void* c1, void* c2);
/*
 * Fonction compar_Tree(c1: tree in, c2: tree in )
 * 
 * compare deux arbres
 * 
 * Necessite:
 * c1 et c2 initialisés
 * 
 * Assure:
 * 		-1 si c1->couple.freq < c2->couple.freq
 * 		 0 si c1->couple.freq == c2->couple.freq
 * 		 1 si c1->couple.freq > c2->couple.freq
 * 
 * */

bool empty_Tree(Tree tree);
/*
 * Fonction empty_Tree(tree: in)
 * 
 * Indique si un arbre est vide
 * 
 * Necessite:
 * L'arbre initialisé
 * 
 * Assure:
 * Renvoie 1 si l'arbre est vide, 0 sinon
 * */

size_t size_Tree(Tree tree);
/*
 * Fonction size_Tree(tree: in)
 * 
 * Retourne la taille (dans le sens de hauteur) de l'arbre
 * 
 * Necessite:
 * L'arbre initialisé
 * 
 * */

bool has_key_Tree(Tree tree, int freq);
/*
 * Fonction has_key_Tree(tree: in, freq: in)
 * 
 * Test si l'arbre posséde un noeud ou une feuille dont la fequence est freq
 * 
 * Necessite:
 * L'arbre initialisé
 * 
 * Assure
 * 		1 si il existe un noeud ou une feuille dont la fequence est freq
 * 		0 sinon
 * 
 * */

bool is_leaf_Tree(Tree tree);
/*
 * Fonction is_leaf_Tree(tree: in)
 * 
 * Test si l'arbre est une feuille
 * 
 * Necessite:
 * L'arbre initialisé
 * 
 * Assure
 * 		1 si tree->right == NULL && tree->right == NULL
 * 		0 sinon
 * 
 * */

Value get_value_Tree(Tree tree, int freq);
/*
 * Fonction get_value_Tree(tree: in)
 * 
 * Retourne la valeur correspondant à une fréquence présente dans l'arbre
 * 
 * Necessite:
 * L'arbre initialisé
 * 
 * Assure
 * 		0 si l'arbre ne contient pas cette fréquence
 * 
 * */

void print_Tree(Tree tree);

void couple_to_Tree(Tree* tree, Couple couple);

void concatenate_Tree(Tree* dest, Tree source);

void add_subTree(Tree father, Tree source, bool right);

void equal_Tree(void* dest, void* source);

void print_list_tree(List list);

void fusion_List_Tree(List listTree);
//Necessite: !empty_List(listTree), listTree est triee par ordre croissant de frequence
//Assure: ListTree ne contient qu'un arbre, fusion de la liste d'origine

void replace_Tree(Tree tree, Tree* trees, int sizeTree);

void fusion_tab_Tree(Tree* trees, int sizeTree);

#endif
