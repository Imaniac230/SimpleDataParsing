#include "dataparser.h"

void CloseProgram(char **aIn, char **aOut)
	{
	if (aIn)
		{
		free(*aIn);
		*aIn = NULL;
		}
	if (aOut)
		{
		free(*aOut);
		*aOut = NULL;
		}

	fprintf(stdout, "\n%s: Press \"enter\" to exit.", __argv[0]);
	fseek(stdin, 0, SEEK_SET);
	while ((getchar()) != NEW_LINE);
	}

int CloseFile(FILE **aInFile, FILE **aOutFile)
	{
	int outf = 0, inf = 0;
	if (aInFile)
		{
		inf = fclose(*aInFile);
		*aInFile = NULL;
		}
	if (aOutFile)
		{
		outf = fclose(*aOutFile);
		*aOutFile = NULL;
		}

	if (outf == EOF)
		fprintf(stderr, "\nWARNING! Attempting to close a non-existing output file.");
	if (inf == EOF)
		fprintf(stderr, "\nWARNING! Attempting to close a non-existing input file.\n\n");

	return ((outf == EOF || inf == EOF) ? EOF : 0);
	}

int FileNameAlloc(char ** const aName)
	{
	*aName = (char*)malloc(FILE_NAME_LENGTH * sizeof(char));
	if (!*aName)
		return EBadAlloc;
	memset(*aName, 0, FILE_NAME_LENGTH);
	return EOk;
	}

int OpenInputFile(char * const aFilename, FILE ** const aFile)
	{
	if (!__argv[1])
		{
		fprintf(stdout, "%s: Enter input file: ", __argv[0]);
		if (!fscanf(stdin, "%s", aFilename))
			return EBadScan;
		}
	else
		{
		size_t i = 0;
		while (__argv[1][i] != 0 && i < FILE_NAME_LENGTH)
			{
			aFilename[i] = __argv[1][i];
			++i;
			}
		}
	fprintf(stdout, "%s: Input file: \"%s\"\n\n", __argv[0], aFilename);

	if (fopen_s(aFile, aFilename, "r"))
		return EBadOpen;

	return EOk;
	}


int OpenOutputFile(char * const aFilename, FILE ** const aFile)
	{
	if (__argc <= 2)
		{
		fprintf(stdout, "%s: Enter output file: ", __argv[0]);
		if (!fscanf(stdin, "%s", aFilename))
			return EBadScan;
		}
	else
		{
		size_t i = 0;
		while (__argv[2][i] != 0 && i < FILE_NAME_LENGTH)
			{
			aFilename[i] = __argv[2][i];
			++i;
			}
		}
	fprintf(stdout, "%s: Output file: \"%s\"\n\n", __argv[0], aFilename);

	if (fopen_s(aFile, aFilename, "w"))
		return EBadOpen;

	return EOk;
	}

int ParseFile(FILE * const aFin, FILE * const aFout)
	{
	int current_char = 0, last_char = 0;
	int data_section = FALSE, ignore = FALSE, space = FALSE;
#ifdef DEBUG_MODE
	size_t count = 0;
#endif /* DEBUG_MODE */

	fputs(CSV_FILE_HEADER, aFout);
	while (!feof(aFin))
		{
		current_char = getc(aFin);
		if (ferror(aFin) && (current_char == EOF))
			return EBadScan;

		if (DATA_SECTION_START(current_char, last_char))
			data_section = TRUE;
		if (data_section && DATA_SECTION_END(current_char, last_char))
			data_section = FALSE;

		if (data_section)
			{
			if (LEADING_WHITE_CHAR_SECTION_START(current_char, last_char))
				ignore = TRUE;
			if (ignore && LEADING_WHITE_CHAR_SECTION_END(current_char, last_char))
				ignore = FALSE;
			if (!ignore)
				{
				if (!space && WHITE_CHAR_BETWEEN_DATA_VALUES_START(current_char, last_char))
					{
					putc(CSV_SEPARATOR, aFout);
					space = TRUE;
					}
				if (space && WHITE_CHAR_BETWEEN_DATA_VALUES_END(current_char, last_char))
					space = FALSE;
				if (!space)
					{
					if (current_char == DECIMAL_SEPARATOR_ORIG)
						putc(DECIMAL_SEPARATOR_NEW, aFout);
					else if (current_char == EOF)
						;
					else
						putc(current_char, aFout);
#ifdef DEBUG_MODE
					fprintf(stdout, "0x%X\n", current_char);
					++count
#endif /* DEBUG_MODE */
					}
				}
			}

		last_char = current_char;
		}
#ifdef DEBUG_MODE
	fprintf(stdout, "Total number of characters: %d\n", count);
#endif /* DEBUG_MODE */

	return EOk;
	}