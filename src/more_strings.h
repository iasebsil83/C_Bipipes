#ifndef MORE_STRINGS_H
#define MORE_STRINGS_H




















// -------------------------------- STRINGS --------------------------------

//utilities
int str_indexOf(char* s, char c);




















// -------------------------------- STRING ARRAYS --------------------------------

//utilities
int strArr_len(char** sa);
void strArr_free(char** sa);
char** strArr_split(char* s, char c);




















#endif
