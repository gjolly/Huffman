#ifndef COMPRESS_COMMUN_H
#define COMPRESS_COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tree.h"
#include "binary.h"
#include "byte.h"

void construct_table_corresp(Tree tree, Binary output[CHAR_MAX+1], Binary curCode);
/* Procedure construct_table_corresp(tree: in, output: out, curCode: in/out)
 * 
 * Etablit la table de correspondance a partir de l'arbre
 * 
 * Necessite:
 * tree initialisé
 * 
 * Assure:
 * output est une table de coreespondance
 * */

void print_table_corresp(Binary tableCorresp[UCHAR_MAX+1]);
/* Procedure print_table_corresp(tableCorresp: in)
 * 
 * Affiche la table de correspondance d'un arbre
 * 
 * Necessite:
 * tableCorresp initialisé
 * 
 * Assure:
 * N'affiche pas les caracteres non utilises
 * */

bool empty_file(FILE* file);
/* Fonction empty_file(file: in)
 * 
 * Determine si un fichier est vide
 * 
 * Necessite:
 * file un flux valide
 * 
 * Assure:
 * Renvoie 1 si le fichier est vide, 0 sinon
 * */

void loadBar(int x, int n, int r, int w);
/* Procedure loadBar(x: in, n: in, r: in, w: in)
 * 
 * Dessine une bar de chargement sur le terminal
 * 
 * 
 * Necessite:
 * x, n, r, w des entiers
 * x < n
 * 
 * Source:
 * https://www.ross.click/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/
 * */

#endif
