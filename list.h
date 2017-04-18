
/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Implantation de la List
 ******************************************************************************/
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Cell
{
	void* data;		// <key, value>
	struct Cell* next;	// NULL si fin de la List
};
typedef struct Cell* Cell;

struct List
{
	Cell cell;							//same as LCA
	size_t size_data;					//sizeof to do so
	void (*init_data)(void**);			//Be careful, only one parameter
	void (*destroy_data)(void*);		//Free for default
	void (*equal_data)(void*, void*);	//Set first data to the second
	int (*compar_data)(void*, void*);	//-1 if a < b, 0 if a == b, 1 if a > b
};
typedef struct List* List;

int noOrder(void* a, void* b);	//Anything added at the end
//Use it with caution : you cannot know if a key is in the List !

void init_List(List* this, size_t size_data, void (*init_data)(void**), void (*destroy_data)(void*), void (*equal_data)(void*, void*), int (*compar)(void*, void*));
/*
 * Procedure init_List(this: Liste out, size_data: Entier non signe in, init_data: Fonction in, destroy_data: Fonction in, equal_data: Fonction in, compar: Fonction in)
 * 
 * Initialise une liste
 * 
 * Necessite:
 * Tous les parametres sont valides
 * 
 * Assure:
 * *this initialise avec les parametres fournis
 */

bool empty_List(List this);
/*
 * Fonction empty_List(this: Liste in)
 * 
 * Teste si une liste est vide
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Renvoie Vrai si la liste est vide, Faux sinon
 */

size_t size_List(List this);
/*
 * Fonction size_List(this: Liste in)
 * 
 * Renvoie le nombre d'element de la liste
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Renvoie un entier positif ou nul
 */

void add_List(List this, void* data);
/*
 * Procedure add_List(this: SDA in/out, data: Donnee in)
 * 
 * Ajoute dans une liste une donnee
 * 
 * Necessite:
 * this != NULL
 * data valide
 * 
 * Assure:
 * L'ajout se fait selon la fonction de comparaison
 */

void delete_List(List this, void* data);
/*
 * Procedure delete_List(this: Liste in/out, data: Donnee in)
 * 
 * Supprimer d’une Liste une cellule contenant data
 * Si data n’est pas utilisee dans la liste, la liste n’est pas modifiee
 * 
 * Necessite:
 * this != NULL
 * data valide
 * 
 * Assure:
 * L'element est supprime si possible
 */

void* front_List(List this);
/*
 * Fonction front_List(this: Liste in)
 * 
 * Renvoie le premier element d'une liste
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Renvoie le premier element de la liste si il exite, NULL sinon
 */

void push_front_List(List this, void* data);	//for noOrder
/*
 * Procedure push_front_List(this: Liste in, data: Donnee in)
 * 
 * Ajoute data en debut de liste sans tenir compte de la fonction de comparaison
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * data est insere en debut de liste
 */

void pop_front_List(List this);
/*
 * Fonction pop_front_List(this: Liste in)
 * 
 * Supprime le debut debut de liste
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Le debut de la liste est supprime si possible
 */

void* back_List(List this);
/*
 * Fonction back_List(this: Liste in)
 * 
 * Renvoie le dernier element d'une liste
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Renvoie le premier dernier de la liste si il exite, NULL sinon
 */

void push_back_List(List this, void* data);		//for noOrder
/*
 * Procedure push_back_List(this: Liste in, data: Donnee in)
 * 
 * Ajoute data en fin de liste sans tenir compte de la fonction de comparaison
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * data est insere en fin de liste
 */

void pop_back_List(List this);
/*
 * Fonction pop_back_List(this: Liste in)
 * 
 * Supprime la fin debut de la liste
 * 
 * Necessite:
 * this une liste valide
 * 
 * Assure:
 * Le fin de la liste est supprime si possible
 */

bool has_data_List(List this, void* data);
/*
 * Fonction has_key_SDA(this: Liste in, data: Donnee in)
 * 
 * Indique si une clef est utilisee dans une liste
 * 
 * Necessite:
 * this et data valide
 * 
 * Assure:
 * Renvoie Vrai si data est dans la liste, Faux sinon
 */

void* get_i_List(List list, int i);
/*
 * Fonction get_i_List(this: Liste in, i: Entier in)
 * 
 * Renvoie le ieme element d'une liste, a la maniere d'une tableau
 * 
 * Necessite:
 * this une liste valide
 * i un entier positif
 * 
 * Assure:
 * Renvoie le ieme element si celui ci est dans la liste, NULL sinon
 */

void clear_List(List this);
/*
 * Procedure clear_SDA(this: Liste in/out)
 * 
 * Supprime toutes les donnees que contient la liste
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * this vide
 */

void destroy_List(List* this);
/*
 * Procedure destroy_SDA(this: Liste in/out)
 * 
 * Libere toutes les ressources qu’utilise la liste
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * this desallouee
 * *this = NULL
 */

#endif
