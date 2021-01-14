// -------------------------------- IMPORTATIONS --------------------------------

//standard
#include <stdio.h>
#include <stdlib.h>



//own header
#include "more_strings.h"




















/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ More strings [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                 More strings by I.A.

        More strings is just an utility program that offers some utility functions
    for strings & string arrays.

    13/01/2021 > [0.1.0] :
    - Created more_strings.c/.h.
    - Created demonstration program.

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
******************************************************************************************

    LICENCE :

    C_MoreStrings
    Copyright (C) 2021  Sebastien SILVANO
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




















// ---------------- STRINGS ----------------

//utilities
int str_indexOf(char* s, char c){
	//error case
	if(s == NULL){
		printf("RUNTIME_ERROR > more_strings.c : str_indexOf() : Input string is NULL.\n");
		return -1;
	}

	//count until character "c" found
	int cnt = 0;
	int index = 0;
	while(s[index] != c && s[index++] != '\0'){
		cnt++;
	}

	return cnt;
}




















// ---------------- STRING ARRAYS ----------------

//utilities
int strArr_len(char** sa){

	//error case
	if(sa == NULL){
		printf("RUNTIME ERROR > more_strings.c : strArr_len() : Input string array is NULL.\n");
		return -1;
	}

	//increase len until NULL is detected
	int len = 0;
	while(sa[len] != NULL){
		len++;
	}

	return len;
}

void strArr_free(char** sa){

	//error case
	if(sa == NULL){
		printf("RUNTIME ERROR > more_strings.c : strArr_free() : Input string array is NULL.\n");
		return;
	}

	//free all contained strings
	for(int s=0; s < strArr_len(sa); s++){
		free(sa[s]);
	}
	free(sa);
}

char** strArr_split(char* s, char c){

	//error case
	if(s == NULL){
		printf("RUNTIME ERROR > more_strings.c : strArr_split() : Input string is NULL.\n");
		return NULL;
	}

	//count how many occurences of #c# exists in #s# (+1 to have the number of words in the final result)
	int word_cnt = 1;
	int index = 0;
	while(s[index] != '\0'){
		if(s[index++] == c)
			word_cnt++;
	}

	//create result string
	char** result = malloc( (word_cnt+1) * sizeof(char*) );
	if(result == NULL){
		printf("FATAL ERROR > more_strings.c : strArr_split() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}

	//for each word
	index = 0;
	int word_len;
	for(int word_index=0; word_index < word_cnt; word_index++){

		//get word len
		word_len = str_indexOf(s+index, c);

		//create new word
		result[word_index] = malloc(word_len+1);
		if(result[word_index] == NULL){
			printf("FATAL ERROR > more_strings.c : strArr_split() : Computer refuses to give more memory.\n");
			exit(EXIT_FAILURE);
		}

		//fill new word
		for(int w=0; w < word_len; w++){
			result[word_index][w] = s[index++];
		}
		result[word_index][word_len] = '\0'; //each word needs its own end character

		//skip the separation character
		index++;
	}

	//append a NULL pointer to significate the end
	result[word_cnt] = NULL;

	return result;
}
