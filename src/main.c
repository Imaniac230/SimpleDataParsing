#include "dataparser.h"


int main(int argc, char **argv)
	{
	if (argc > 3)
		{
		fprintf(stderr, "%s: Too many input arguments.\n\n", argv[0]);
		CloseProgram(NULL, NULL);
		return EWrongArgs;
		}

	char *input = NULL;
	if (FileNameAlloc(&input))
		{
		fprintf(stderr, "%s: ERROR! Could not allocate input file name.\n\n", argv[0]);
		CloseProgram(NULL, NULL);
		return EBadAlloc;
		}

	char *output = NULL;
	if (FileNameAlloc(&output))
		{
		fprintf(stderr, "%s: ERROR! Could not allocate output file name.\n\n", argv[0]);
		CloseProgram(&input, NULL);
		return EBadAlloc;
		}

	FILE *fin = NULL;
	int e = OpenInputFile(input, &fin);
	if (e)
		{
		if (e == EBadScan)
			fprintf(stderr, "%s: ERROR! Could not scan input file name.\n\n", argv[0]);

		if (e == EBadOpen)
			fprintf(stderr, "%s: ERROR! Could not open input file \"%s\".\n\n", argv[0], input);

		CloseProgram(&input, &output);
		return e;
		}

	FILE *fout = NULL;
	e = OpenOutputFile(output, &fout);
	if (e)
		{
		if (e == EBadScan)
			fprintf(stderr, "%s: ERROR! Could not scan output file name.\n\n", argv[0]);
		if (e == EBadOpen)
			fprintf(stderr, "%s: ERROR! Could not open output file \"%s\".\n\n", argv[0], output);

		CloseFile(&fin, NULL);
		CloseProgram(&input, &output);
		return e;
		}

	if (ParseFile(fin, fout))
		{
		fprintf(stderr, "%s: Error scanning file \"%s\".\n\n", argv[0], input);
		CloseFile(&fin, &fout);
		CloseProgram(&input, &output);
		return EBadScan;
		}

	fprintf(stdout,"\n%s: File \"%s\" parsed to csv (\"%s\").\n\n", argv[0], input, output);
	CloseFile(&fin, &fout);
	CloseProgram(&input, &output);
	
	return EOk;
	}