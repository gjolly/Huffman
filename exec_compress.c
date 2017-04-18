#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

void get_nameOutput(char** nameOutput, int argc, char**argv)
{
	if (argc >= 3)
		*nameOutput = argv[2];
	else
	{
		*nameOutput = malloc((strlen(argv[1])+4)*sizeof(char));
		strcpy(*nameOutput, argv[1]);
		strcat(*nameOutput, ".hf");
	}
}

int main(int argc, char** argv)
{
	if (argc > 3)
	{
		printf("Arguments incorrectes\n");
		return 1;
	}
	
	char* nameInput = argv[1];
	
	FILE* input = fopen(nameInput, "r");
	
	if (input == NULL)
	{
		printf("Il n'y a pas de fichier de ce nom dans le dossier\n");
		return 1;
	}
	
	char* nameOutput;
	get_nameOutput(&nameOutput, argc, argv);

	
	FILE* output = fopen(nameOutput, "w");
	
	if (!empty_file(input))
		compress(input, output);
	
	if (input)
		fclose(input);
	if (output)
		 fclose(output);
	if (argc < 3)
		free(nameOutput);
	
	printf("Compression terminée avec succes\n");
	return 0;
}
