#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uncompress.h"

void get_nameOutput(char**nameOutput, int argc, char** argv)
{
	if (argc >= 3)
		*nameOutput = argv[2];
	else
	{
		size_t size = strlen(argv[1]) - strlen(".hf");
		*nameOutput = malloc((size+5)*sizeof(char));
		strncpy(*nameOutput, argv[1], size);
		(*nameOutput)[size] = '\0';
		strcat(*nameOutput, ".nhf");
	}
}

int main(int argc, char** argv)
{
	FILE* input = fopen(argv[1], "rb");
	if (input == NULL)
	{
		printf("Il n'y a pas de fichier de ce nom dans le dossier\n");
		return 1;
	}
	
	char* nameOutput;
	get_nameOutput(&nameOutput, argc, argv);
	
	FILE* output = fopen(nameOutput, "w");
	
	if (argc < 3)
		free(nameOutput);
	
	if (!empty_file(input))
		uncompress(input, output);
	
	fclose(input);
	fclose(output);
	
	printf("Decompression terminée avec succes\n");
	return 0;
}
