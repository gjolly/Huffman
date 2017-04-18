#ifndef UNCOMPRESS_H
#define UNCOMPRESS_H

#include <stdio.h>
#include "tree.h"
#include "couple.h"
#include "byte.h"
#include "binary.h"
#include "compress-commun.h"
/*
 * 
 * */

void add_empty_subTree(Tree tree, bool right);
/* Procedure add_empty_subTree(tree: in out, right: in)
 * 
 * Initialise le fils droit ou gauche de tree avec un arbre vide
 * 
 * Necessite:
 * tree initialisé, empty_Tree(tree->fd) && empty_Tree(tree->fg)
 * */

void read_forhead(FILE* input, size_t* sizeText, char* sizeTree, Value** caracsTree);
/* Procedure read_forhead(input: in out, sizeText: in out, sizeTree: in out, caracsTree: in out)
 * 
 * Lit l'entête d'un fichier compressé
 * 
 * Necessite:
 * input est un fichier compressé
 * 
 * Assure:
 * sizeText contient la taille du texte, sizeTree contient le nombre de feuilles de l'arbre, caracsTree contient la liste de caractères de l'arbre
 * */

int indice_tableau_Binary(Binary elmt, Binary* tableau, size_t sizeTab);
/* Fonction indice_tableau_Binary(elmt: in, tableau: in, sizeTab: in)
 * 
 * renvoit l'indice de elmt dans le tableau
 * 
 * Necessite:
 * Binary initialisé, sizeTab est la taille de tableau
 * 
 * Assure:
 * renvoit -1 si l'elmt n'est pas dans le tableau
 * */

void update_tampon(Binary binary, FILE* file);
/* Procedure update_tampon(binary: in out, file: in out)
 * 
 * Supprime le premier bit de binary et si binary est vide, lit un caractère dans le texte
 * 
 * Necessite:
 * Binary initialisé, binary non nul,!eof(file)
 * 
 * */

void reconstruct_Tree(FILE* input, Tree tree, Binary tamponLecture, size_t sizeTree, size_t* nbLeaf, Value* caracsTree);
/* Procedure reconstruct_Tree(input: in out, tree: in out, tamponLecture: in out, sizeTree: in, nbLeaf: in, caracsTree: in)
 * 
 * reconstruit l'arbre à partir du fichier compressé
 * 
 * Necessite:
 * input est un fichier compressé, tree est initialisé, tamponLecture est initialisé, *nbLeaf = 0, caracsTree contient les caractères de l'arbre
 * 
 * Assure:
 * L'arbre construit est identique à celui qui a servit à la compression de input
 * */


void write_body_uncompress(FILE* input, FILE* output, size_t sizeText, Binary* tableCorresp, size_t sizeTree ,Binary tamponLecture);
/* Procedure write_body_uncompress(input: in out, output: in out, sizeText: in, tableCorresp: in, sizeTree: in, tamponLecture: in out)
 * 
 * Décode le corps du texte
 * 
 * Necessite:
 * input est un fichier compressé et input != NULL, output != NULL, sizeText contient le nombre de caractères du fichier d'origine, tableCorresp[i] = code du caractère numéro i
 * de la table ascii, sizeTree est le nombre de feuilles de l'arbre de huffman ayant servi à la compression, tamponLecture ...
 * 
 * Assure:
 * Ecrit les caractère que ceux du fichier d'origine
 * */

void uncompress(FILE* input, FILE* output);
/* Procedure uncompress(input: in out, output: in out)
 * 
 * Décompresse un fichier (d'où le nom...)
 * 
 * Necessite:
 * input != NULL et un fichier compressé
 *
 * */


#endif
