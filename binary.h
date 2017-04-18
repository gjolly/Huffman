#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>
#include <stdbool.h>
#include "byte.h"
#include "list.h"

struct Binary
{
	List byte;		//Le debut de la liste correspond aux bits de poid fort
	size_t size;	//Taille en bits
};
typedef struct Binary* Binary;

void init_Binary(Binary* binary);
/*
 * Procedure init_Binary(binary: Binaire out)
 * 
 * Initialise binary comme un Binaire
 * 
 * Necessite:
 * binary un pointeur valide
 * 
 * Assure:
 * binary->byte : liste vide initialisee
 * binary->size = 0
 */

void init_fromByte_Binary(Binary* binary, Byte* byte, size_t size);
/*
 * Procedure init_fromByte_Binary(binary: Binaire out, byte: Tableau de Byte in, size : Entier non signe in)
 * 
 * Initialise binary comme un Binaire a partir d'un tableau de bits
 * 
 * Necessite:
 * binary un pointeur valide
 * byte de taille inferieure a (size/BITSPERBYTE)+1
 * 
 * Assure:
 * byte et size_t non modifiee
 * binary->byte : liste contenant les elements de byte initialisee
 * binary->size adaptee au nombre de bits du binaire
 */

void destruct_Binary(Binary* binary);
/*
 * Procedure destruct_Binary(binary: Binaire out)
 * 
 * Libere la memoire prise par un binaire
 * 
 * Necessite:
 * binary un pointeur valide
 * 
 * Assure:
 * *binary libere et valant NULL
 */

void equal_Binary(Binary* a, Binary b);
/*
 * Procedure equal_Binary(a: Binaire out, b: Binaire in)
 * 
 * Met la valeur de b dans *a
 * 
 * Necessite:
 * a pointe vers un Binaire
 * b valide
 * 
 * Assure:
 * b non modifie
 * *a vaut b
 */

void swap_Binary(Binary a, Binary b);
/*
 * Procedure swap_Binary(a: Binaire in, b: Binaire in)
 * 
 * Echange la valeur de deux binaires
 * 
 * Necessite:
 * a et b des binaires valides
 * 
 * Assure:
 * a_nouveau = b_ancien
 * b_nouveau = a_ancien
 */

void concatenate_Binary(Binary dest, Binary source);
/*
 * Procedure concatenate_Binary(dest: Binaire in/out, source: Binaire in)
 * 
 * Met source a la fin de dest
 * 
 * Necessite:
 * source et dest des binaires valides
 * 
 * Assure:
 * Les bits de source sont places a la fin dest
 */

void concatenate_bis_Binary(Binary dest, Binary source);
/*
 * Procedure concatenate_bis_Binary(dest: Binaire in/out, source: Binaire in)
 * 
 * Pareil qu'au dessus mais en plus rapide
 * 
 * Necessite:
 * source et dest des binaires valides
 * 
 * Assure:
 * Les bits de source sont places a la fin dest
 */

int compar_Binary(Binary a, Binary b);
/*
 * Fonction compar_Binary(a: Binaire in, b: Binaire in)
 * 
 * Compare deux Binaire
 * 
 * Necessite:
 * a et b valides
 * 
 * Assure:
 * Renvoie -1 si a<b, 0 si a=b , 1 sinon
 */

void add_zero_Binary(Binary binary);
/*
 * Procedure add_zero_Binary(binary: Binaire in/out)
 * 
 * Met un 0 a la fin de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Un nouveau bit valant 0 est place a la fin de binary
 */

void add_one_Binary(Binary binary);
/*
 * Procedure add_one_Binary(binary: Binaire in/out)
 * 
 * Met un 1 a la fin de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Un nouveau bit valant 1 est place a la fin de binary
 */

void write_Binary(Binary binary, FILE* file);	//Non written bits are let inside binary
/*
 * Procedure write_Binary(binary: Binaire in/out, file: Fichier in/out)
 * 
 * Ecrit le maximum d'octet complet de binary dans le file
 * 
 * Necessite:
 * binary valide
 * file un fichier ouvert
 * 
 * Assure:
 * binary->size < BITSPERBYTE
 * Les octets sont ecrits dans file
 */

size_t size_in_Byte(Binary binary);
/*
 * Fonction size_in_Binary(binary: Binaire in)
 * 
 * Renvoie la taille en octet d'un fichier
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * binary non modifie
 * Le retour est superieur a zero
 */

void fit_size_Binary(Binary binary);
/*
 * Procedure fit_size_Binary(binary: Binaire in/out)
 * 
 * Modifie la taille de binary pour supprimer les bits de poid fort valant 0
 * 
 * Necessite:
 * binary valide (la taille peut etre trop grande)
 * 
 * Assure:
 * binary correspond a la definition (bit de poid fort valant 1 (ou 0 si nul))
 */

Byte back_Byte_Binary(Binary binary);
/*
 * Fonction front_Byte(binary: Binaire in)
 * 
 * Retourne les bits composant l'octet de poids faible de binary (dans la liste)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie un Octet
 */

Byte front_Byte(Binary binary);
/*
 * Fonction front_Byte(binary: Binaire in)
 * 
 * Retourne les bits composant l'octet de poids fort de binary (dans la liste)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie un Octet
 */

Binary front_Binary(Binary binary);
/*
 * Fonction front_Binary(binary: Binaire in)
 * 
 * Retourne les bits composant l'octet de poid fort de binary (au sens mathematique)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie un Binaire
 */

void pop_front_Byte(Binary binary);
/*
 * Procedure pop_front_Byte(binary: Binaire in/out)
 * 
 * Supprime le premier element de binary->byte (dans la liste)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * binary toujours valide
 * Les bits stocke dans le premier octet sont supprimes
 */

void pop_front_Binary(Binary binary);
/*
 * Procedure pop_front_Binary(binary: Binaire in/out)
 * 
 * Supprime l'octet de poid fort de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * binary toujours valide
 * L'octet de poid fort est supprime
 */

bool front_Bit_Byte(Binary binary);
/*
 * Fonction front_Bit_Byte(binary: Binaire in)
 * 
 * Retourne le bit de poid fort de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie 1 si binary est le bit le bit de poids fort est 1, 0 sinon
 */

bool back_Bit_Byte(Binary binary);
/*
 * Fonction back_Bit_Byte(binary: Binaire in)
 * 
 * Retourne le bit de poid faible de binary (sa parite)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie 0 si binary est pair, 1 sinon
 */


Binary back_Binary(Binary binary);
/*
 * Fonction back_Binary(binary: Binaire in)
 * 
 * Retourne les bits composant l'octet de poid faible de binary (au sens mathematique)
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * Renvoie un Binaire
 */
 
void pop_back_Binary(Binary binary);
/*
 * Procedure pop_back_Binary(binary: Binaire in/out)
 * 
 * Supprime l'octet de poids faible de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * binary toujours valide
 * L'octet de poids faible est supprime
 */

void pop_front_Bit_Binary(Binary binary);
/*
 * Procedure pop_back_Binary(binary: Binaire in/out)
 * 
 * Supprime le bit de poids fort de binary
 * 
 * Necessite:
 * binary valide
 * 
 * Assure:
 * binary toujours valide
 * Le bit de poids fort est supprime
 */

void left_shift_Binary(Binary binary, int n);
/*
 * Procedure left_shift_Binary(binary: Binaire in/out, n: Entier in)
 * 
 * Effectue un decalage de n a gauche sur binary
 * 
 * Necessite:
 * binary valide
 * n positif
 * 
 * Assure:
 * binary a ete decale de n bits vers la gauche en inserant des 0
 */

void right_shift_Binary(Binary binary, int n);
/*
 * Procedure right_shift_Binary(binary: Binaire in/out, n: Entier in)
 * 
 * Effectue un decalage logique de n a droit sur binary
 * 
 * Necessite:
 * binary valide
 * n positif
 * 
 * Assure:
 * binary a ete decale de n bits vers la droite
 */

void or_Binary(Binary* dest, Binary source);
/*
 * Procedure or_Binary(dest: Binaire in/out, source: Binaire in)
 * 
 * Effectue un ou logique entre *dest et source et stocke le resultat dans dest
 * 
 * Necessite:
 * dest et source valides
 * 
 * Assure:
 * Le resultat est stocke dans dest
 * Si les deux binaires sont de taille differente, le ou se fait avec 0 pour les bits manquants
 */

void and_Binary(Binary* dest, Binary source);
/*
 * Procedure or_Binary(dest: Binaire in/out, source: Binaire in)
 * 
 * Effectue un et logique entre *dest et source et stocke le resultat dans dest
 * 
 * Necessite:
 * dest et source valides
 * 
 * Assure:
 * Le resultat est stocke dans dest
 * Si les deux binaires sont de taille differente, le et se fait avec 0 pour les bits manquants
 */

void print_hexa_Binary(Binary binary);
/*
 * Procedure print_hexa_Binary(binary: Binaire in)
 * 
 * Affiche binary en hexadecimal
 * 
 * Necessite:
 * bianry valide
 * 
 * Assure:
 * Le resulat est affiche sur la sortie standard
 */

void print_Binary(Binary binary);
/*
 * Procedure print_Binary(binary: Binaire in)
 * 
 * Affiche binary en binaire
 * 
 * Necessite:
 * bianry valide
 * 
 * Assure:
 * Le resulat est affiche sur la sortie standard
 */

Binary zero_Binary();
/*
 * Procedure zero_Binary()
 * 
 * Renvoie un binaire valant 0
 * 
 * Assure:
 * Le binaire retournee est utilisable et vaut 0
 * 
 * Remarque:
 * Le binaire renvoye n'a pas besoin d'etre libere
 */

Binary un_Binary();
/*
 * Procedure un_Binary()
 * 
 * Renvoie un binaire valant 1
 * 
 * Assure:
 * Le binaire retournee est utilisable et vaut 1
 * 
 * Remarque:
 * Le binaire renvoye a besoin d'etre libere
 */

#endif
