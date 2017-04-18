#ifndef COUPLE_H
#define COUPLE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef char Value;

struct Couple
{
	size_t freq;	//Positif ou nul
	Value value;	//Vaut '\0' si aucun element
};
typedef struct Couple Couple;

void init_Couple(Couple* couple, size_t freq, Value value);
/*
 * Procedure init_Couple(couple: Couple* out, freq: Entier non signe in, value: Value in)
 * 
 * Initialise couple a partir de freq et value
 * 
 * Necessite:
 * freq et value initialisees
 * 
 * Assure:
 * couple initialise avec freq et value
 */


int compar_Couple(const void* c1, const void* c2);
/*
 * Fonction compar_Couple(c1: Pointeur in, c2: Pointeur in)
 * 
 * Compare deux Couple
 * 
 * Necessite:
 * c1 pointe vers un Couple
 * c2 pointe vers un Couple
 * 
 * Assure:
 * c1 et c2 non modifies
 * Renvoie 	-1 si la frequence de *c1 < celle de *c2
 * 			0 si elles sont egales
 * 			1 sinon
 */

#endif
