#ifndef COMPRESS_H
#define COMPRESS_H

#include "tree.h"
#include "binary.h"
#include "couple.h"
#include "compress-commun.h"

void print_tab_Couple(Couple* couples, int size);

void init_freq(Couple* couples);
/*
 * Procedure init_freq(couples: Tableau de Couple, in out)
 * 
 * Initialise un taleau de couples
 *
 * Assure: couples[i].value == (ième caractère de l'ascii) et couple[i].freq == 0
 */

int frequence(FILE* fichier, Couple* couples); 
/*
 * Fonction frequence(fichier: Fichier, in; couples: Tableau de Couple, in out): Entier
 * 
 * Retourne la taille du fichier decompressé et détermine la fréquence de chaque caractère des couples
 * 
 * Necessite:
 * 		couples est initialisé
 * 
 */
 
void tri_Couple(Couple* couples);
/*
 * Procedure tri_Couple(couples: in out)
 * 
 * Tri un tableau de couples par ordre croissant de fréquence
 * 
 * Necessite:
 * tous les couples du tableau sont initialisés
 * */

size_t build_Tree(Couple* couples, Tree* tree);
/*
 * Fonction build_Tree(couples: in, tree: in out)
 * 
 * construit l'arbre de Huffman à partir d'un tableau trié de couple et retourn le nombre de feuilles de l'arbre
 * 
 * Necessite:
 * Tous les couples sont initialisés et le tableau de couples est trié par ordre croissant de féquence
 * */

void description_Tree(Tree tree, Binary descriptions, Value** caracs); //taille de caracts = taille de l'arbre
/*
 * Procedure description_Tree(tree: in, description: in out, caracs: in out)
 * 
 * Construit la description de l'arbre de Huffman et liste les caractères de l'arbre dans l'ordre infix
 * 
 * Necessite:
 * tree est un arbre de huffman, binary est initialisé
 * */

void mise_en_forme_description(Binary descriptionTree);
/*
 * Procedure mise_en_forme_description(descriptionTree: in out)
 * 
 * Necessite:
 * Binary est initialisé et est une description d'arbre de huffman
 * 
 * Assure:
 * descriptionTree ne se termine que par un seul 1
 * */

void write_forhead(FILE* output, size_t sizeText, size_t sizeTree, Value* caracs);
/*
 * Procedure write_forhead(output: in out, sizeText: in, sizeTree: in, caracs: in)
 * 
 * Écrit l'entête du fichier compressé
 * 
 * Necessite:
 * output != NULL, sizeText, sizeTree et caracs sont correctement initialisé avec les fonctions précédentes
 * 
 * Assure:
 * L'entête est bien conformes aux spécifications demandées
 * */

int indice_tableau(Value elmt, Value* tableau, size_t sizeTab);
/*
 * Fonction indice_tableau(elmt: in, tableau: in, sizeTab: in)
 * 
 * Retourne l'indice du tableau auquel apparait elmt et -1 s'il n'y apparait pas
 * 
 * Necessite
 * sizeTab est bien la taille du tableau
 * */

void write_body(FILE* input, FILE* output, Binary descriptionTree, Binary* tableCorresp, size_t sizeTree);
/*
 * Procedure write_body(input: in out, output: in out, descriptionTree: in, tableCorresp: in, caracs: in, sizeTree: in)
 * 
 * Code le corps du texte
 * 
 * Necessite
 * les arguments sont correctement initialisé avec les fonctions précédentes
 * 
 * */

void compress(FILE* input, FILE* output);
/*
 * Procedure compress(input: in out, output: in out)
 * 
 * Compile toutes les fonctions précédentes pour coder un fichier input
 * 
 * Necessite
 * input et output != NULL
 * 
 * */

#endif
