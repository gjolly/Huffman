#ifndef BYTE_H
#define BYTE_H
#include <limits.h>
#define BITSPERBYTE CHAR_BIT

typedef unsigned char Byte;	//Toujours positif

void init_Byte(void** a);
/*
 * Procedure init_Byte(a: Pointeur out)
 * 
 * Initialise a
 * 
 * Assure:
 * *a vaut '\0'
 */

void equal_Byte(void* a, void* b);
/*
 * Procedure equal_Byte(a: Pointeur in/out, b: Pointeur in)
 * 
 * Met la valeur de *b dans *a
 * 
 * Necessite:
 * a pointe vers un Byte
 * b pointe vers un Byte
 * 
 * Assure:
 * *b non modifie
 * *a vaut *b
 */

int compar_Byte(void* a, void* b);
/*
 * Fonction compar_Byte(a: Pointeur in, b: Pointeur in)
 * 
 * Compare deux Byte
 * 
 * Necessite:
 * a pointe vers un Byte
 * b pointe vers un Byte
 * 
 * Assure:
 * Renvoie -1 si *a<*b, 0 si *a=*b , 1 sinon
 */

int noOrder_Byte(void* a, void* b);
/*
 * Fonction noOrder_Byte(a: Pointeur in, b: Pointeur in)
 * 
 * Permet la creation d'un binaire a l'aide d'une liste de Byte
 * 
 * Necessite:
 * a pointe vers un Byte
 * b pointe vers un Byte
 * 
 * Assure:
 * Renvoie Vrai si *a=*b, Faux sinon
 */
 
 int reverse_order_Byte(void* a, void* b);
#endif
