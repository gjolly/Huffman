/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Implantation de la List
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int noOrder(void* a, void* b)
{
	return 1;	//Ajoute les nouveaux elements a la fin de la liste
}

void add_Cell(List this, Cell* cell, void* data)
{
	void** nData = malloc(sizeof(int*));	//Nouvelle donnee
	(this->init_data)(nData);	//Initialisation de cette donnee
	(this->equal_data)(*nData, data);	//Copie de la donnee
	Cell nouv = malloc(sizeof(struct Cell));	//Nouvelle Cellule
	nouv->data = *nData;	//Affectation de la donnee
	nouv->next = *cell;		//Insertion dans la liste
	*cell = nouv;
	
	free(nData);	//Liberation du pointeur vers la donnee
}

void delete_Cell(List this, Cell* cell)
{
	Cell tmp = (*cell)->next;	//Memorisation la cellule suivante
	(this->destroy_data)((*cell)->data);	//Destruction de la courante
	free(*cell);
	*cell = tmp;	//Redirection
}

void init_List(List* this, size_t size_data, void (*init_data)(void**), void (*destroy_data)(void*), void (*equal_data)(void*, void*), int (*compar_data)(void*, void*))
{
	*this = malloc(sizeof(struct List));
	(*this)->cell = NULL;
	(*this)->size_data = size_data;
	(*this)->init_data = init_data;
	(*this)->destroy_data = destroy_data;
	(*this)->equal_data = equal_data;
	(*this)-> compar_data = compar_data;
}

bool empty_List(List this)
{
	return this->cell == NULL;	//Pour qu'une liste soit nulle, elle doit avoir ete affectee
}

size_t size_List(List this)
{
	Cell cell = this->cell;
	size_t size;
	for (size = 0; cell != NULL; size++)	//Denombrement
		cell = cell->next;
	
	return size;
}

void add_List(List this, void* data)
{
	Cell* cur = &(this->cell);
	
	if(this->cell == NULL || (this->compar_data)((*cur)->data, data) == 1)	//Si avant la premiere, on ajoute
		add_Cell(this, cur, data);
	else if ((this->compar_data)((*cur)->data, data) == 0)
		;	//On pourrait faire une fonction update
	else
	{
		Cell* next = &((*cur)->next);
		bool noTouch = true;
		
		while (noTouch)		//Parcours avec deux pointeurs
		{
			if(*next == NULL || (this->compar_data)((*next)->data, data) == 1)
			{
				add_Cell(this, &((*cur)->next), data);
				noTouch = false;
			}
			else if((this->compar_data)((*next)->data, data) == 0)
			{
				;	//Toujours pas de fonction update
				noTouch = false;
			}
			else
			{
				cur = next;
				next = &((*next)->next);
			}
		}
	}
}

void delete_List(List this, void* data)
{
	Cell* cur = &(this->cell);
	bool noTouch = true;

	while (*cur != NULL && noTouch)	//Tant que la donnee n'a pas ete trouvee
	{
		if ((this->compar_data)((*cur)->data, data) == 0)	//Trouvee --> Extermination
		{
			delete_Cell(this, cur);
			noTouch = false;
		}
		else
			cur = &((*cur)->next);
	}
}

void* front_List(List this)
{
	return (empty_List(this)) ? NULL : this->cell->data;	//Si vide, NULL, sinon data
}

void push_front_List(List this, void* data)
{
	add_Cell(this, &(this->cell), data);	//Ajout sur la premiere cellule
}

void pop_front_List(List this)
{
	if (!empty_List(this))
		delete_Cell(this, &(this->cell));
}

void* back_List(List this)
{
	Cell cell = this->cell;
	
	while (cell != NULL)	//Tant qu'on est pas a la fin
	{
		if (cell->next == NULL)
			return cell->data;
		cell = cell->next;
	}
	return NULL;	//Si la liste est vide
}

void push_back_List(List this, void* data)
{
	if (!empty_List(this))	//Si non vide, ajout a la fin
	{
		Cell* cur = &(this->cell);
		while ((*cur)->next != NULL)
			cur = &((*cur)->next);
		add_Cell(this, &((*cur)->next), data);
	}
	else
		add_Cell(this, &(this->cell), data);	//Ajout au debut
}

void pop_back_List(List this)
{
	if (!empty_List(this))
	{
		Cell* cur = &(this->cell);
		while ((*cur)->next != NULL)
			cur = &((*cur)->next);
		delete_Cell(this, cur);
	}
}

bool has_data_List(List this, void* data)
{
	Cell cell = this->cell;
	while (cell != NULL && (this->compar_data)(data, cell->data) != 0)
		cell = cell->next;
	return cell != NULL && (this->compar_data)(data, cell->data) == 0;	//Si donnee non trouvee, retourne 0
}

void* get_i_List(List this, int i)
{
	int iCell = 0;
	Cell cell = this->cell;
	for (iCell = 0; cell != NULL && iCell < i; iCell++)
		cell = cell->next;
	return (iCell == i) ? cell->data : NULL;	//A noter : Je retourne un pointeur vers la donnee, et non une donnee copiee
}

void clear_List(List this)
{
	while(this->cell != NULL)
		delete_Cell(this, &(this->cell));
}

void destroy_List(List* this)
{
	clear_List(*this);
	free(*this);
	*this = NULL;
}
