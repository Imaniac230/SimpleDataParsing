#ifndef __DATAPARSER_H__
#define __DATAPARSER_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

/* simplifying macros */
#define TRUE 1
#define FALSE 0
#define FILE_NAME_LENGTH 256

//
/* beginning of line white character section specifying macros */
#define LEADING_WHITE_CHAR_SECTION_START(current, last) (((last == NEW_LINE) && (current == SPACE)) ? TRUE : FALSE)
#define LEADING_WHITE_CHAR_SECTION_END(current, last) (((last == SPACE) && (current != SPACE)) ? TRUE : FALSE)

/* white character section between data values specifying macros */
#define WHITE_CHAR_BETWEEN_DATA_VALUES_START(current, last) (((current == SPACE) && (last != SPACE)) ? TRUE : FALSE)
#define WHITE_CHAR_BETWEEN_DATA_VALUES_END(current, last) (((current != SPACE) && (last == SPACE)) ? TRUE : FALSE)

/* data section specifying macros */
#define IS_ENDING_CHAR(value) (((value == ENDING_CHAR_1) || (value == ENDING_CHAR_2)) ? TRUE : FALSE)
#define IS_NEW_SECTION(value) (((value == SPACE) || (value == NEW_LINE)) ? TRUE : FALSE)

#define DATA_SECTION_START(current, last) (((current_char != STARTING_CHAR) && (last_char == STARTING_CHAR)) ? TRUE : FALSE)
#define DATA_SECTION_END(current, last) ((IS_ENDING_CHAR(current) && IS_NEW_SECTION(last)) ? TRUE : FALSE)


enum TError
	{
	EWrongArgs = -1,
	EBadAlloc = -2,
	EBadScan = -3,
	EBadOpen = -4,
	EBadRead = -5,
	EOk = 0
	};

void CloseProgram(char **aIn, char **aOut);
int CloseFile(FILE **aInFile, FILE **aOutFile);

int FileNameAlloc(char ** const aName);
int OpenInputFile(char * const aFilename, FILE ** const aFile);
int OpenOutputFile(char * const aFilename, FILE ** const aFile);
int ParseFile(FILE * const aFin, FILE * const aFout);

#endif /* __DATAPARSER_H__ */
