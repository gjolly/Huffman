#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//-D NB_TESTS
//-D NB_CARACS
#define TAILLE_ALPHABET 26

void gen_test1(size_t nbTest)
{
	int typeCarac = 0;
	char* nomTestBase = "test1";
	char nomTest[8];
	char numTestStr[3];
	unsigned char caractere;
	
	for (int numTest = 0; numTest < nbTest; numTest++)
	{
		sprintf(numTestStr, "%d", numTest);
		
		strcpy(nomTest, nomTestBase);
		
		strcat(nomTest, numTestStr);
		strcat(nomTest, ".txt");
		
		FILE* fichierTest = fopen(nomTest, "w");
		typeCarac = rand()%3;
		if (typeCarac == 0)
			caractere = 'A' + rand()%(TAILLE_ALPHABET);
		else if (typeCarac == 1)
			caractere = 'a' + rand()%(TAILLE_ALPHABET);
		else
			caractere = '0' + rand()%10;
		
		fprintf(fichierTest, "%c", caractere);
		fclose(fichierTest);
	}
}

void gen_test2(size_t nbTest, size_t nbCaractere)
{
	int typeCarac;
	char* nomTestBase = "test2";
	char nomTest[8];
	char numTestStr[3];
	unsigned char caractere;
	
	for (int numTest = 0; numTest < nbTest; numTest++)
	{
		sprintf(numTestStr, "%d", numTest);
		
		strcpy(nomTest, nomTestBase);
		
		strcat(nomTest, numTestStr);
		strcat(nomTest, ".txt");
		
		FILE* fichierTest = fopen(nomTest, "w");
		
		for (int iCaractere = 0; iCaractere < nbCaractere; iCaractere++)
		{
			typeCarac = rand()%3;
			if (typeCarac == 0)
				caractere = 'A' + rand()%(TAILLE_ALPHABET);
			else if (typeCarac == 1)
				caractere = 'a' + rand()%(TAILLE_ALPHABET);
			else
				caractere = '0' + rand()%10;
			fprintf(fichierTest, "%c", caractere);
		}
		
		fclose(fichierTest);
	}
}

void gen_test3(size_t nbTest, size_t nbCaractere)
{
	char* nomTestBase = "test3";
	char nomTest[8];
	char numTestStr[3];
	unsigned char caractere;
	
	for (int numTest = 0; numTest < nbTest; numTest++)
	{
		sprintf(numTestStr, "%d", numTest);
		
		strcpy(nomTest, nomTestBase);
		
		strcat(nomTest, numTestStr);
		strcat(nomTest, ".txt");
		
		FILE* fichierTest = fopen(nomTest, "w");
		
		for (int iCaractere = 0; iCaractere < nbCaractere; iCaractere++)
		{
			caractere = rand()%(UCHAR_MAX + 1);
			fprintf(fichierTest, "%c", caractere);
		}
		 
		fclose(fichierTest);
	}
}

void gen_test4(size_t nbCaractere, char* numTestStr)
{
	char* nomTestBase = "test-";
	char nomTest[40];
	unsigned char caractere;
	
	strcpy(nomTest, nomTestBase);
	strcat(nomTest, numTestStr);
	strcat(nomTest, ".txt");
	
	FILE* fichierTest = fopen(nomTest, "w");
	
	for (int iCaractere = 0; iCaractere < nbCaractere; iCaractere++)
	{
		caractere = rand()%(UCHAR_MAX + 1);
		fprintf(fichierTest, "%c", caractere);
	}
	 
	fclose(fichierTest);
}

int main(int argc, char** argv)
{
	int nbCaracs = atoi(argv[1]);
	char* numTest = argv[2];
	//gen_test1(NB_TESTS);
	//gen_test2(NB_TESTS, nbCaracs);
	gen_test4(nbCaracs, numTest);
	return 0;
}
