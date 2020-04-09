#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/* displays all printed chars as HEX values on console */
//#define DEBUG_MODE

/* input file character macros */
#define DECIMAL_SEPARATOR_ORIG '.'

/* output csv character macros */
#define CSV_FILE_HEADER "I\tX\tY\tB0\tB1\tB01\tB11"
#define CSV_SEPARATOR TAB
#define DECIMAL_SEPARATOR_NEW ','

/* data section specifying characters */
#define STARTING_CHAR '_'
#define ENDING_CHAR_1 'G'
#define ENDING_CHAR_2 'B'

/* white characters definitions */
#define TAB 9
#define NEW_LINE '\n'
#define SPACE ' '

#endif /* __SETTINGS_H__ */