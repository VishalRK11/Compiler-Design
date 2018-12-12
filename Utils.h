#define MIN_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "Structs.h"

void initializeSymbolTable(){
	symbolTable = (SymbolTable **)malloc(sizeof(SymbolTable *)* MIN_SIZE);
	symbolTableIndex = 0;
}

void initializeLabelTable(){
	labelTable = (LabelTable **)malloc(sizeof(LabelTable *)* MIN_SIZE);
	labelTableIndex = 0;
}

void initializeILangTable(){
	iLangTable = (ILangTable **)malloc(sizeof(ILangTable *)* MIN_SIZE);
	iLangTableIndex = 0;
}

void initializeStack(){
	stack = (Stack *)malloc(sizeof(Stack));
	stack->arr = (int *)malloc(sizeof(int)* MIN_SIZE);
	stack->top = -1;
}

int isLabel(char *command){
	for (int i = 0; command[i] != '\0' && command[i] != '\n'; ++i){
		if (command[i] == ':')
			return 1;
	}
	return 0;
}

int isDigit(char ch){
	return (ch >= 48 && ch <= 57);
}

int isAlpha(char ch){
	return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

int getNumericData(char *command, int index){
	int size = 0, flag = 1;
	for (; command[index] != '\n' && command[index] != '\0'; ++index){
		if (command[index] == ',')
			break;
		else if (isDigit(command[index])){
			flag = 0;
			size = (size * 10) + command[index] - 48;
		}
	}
	if (flag)
		return -1;
	return size;
}

char *getParamName(char *command, int index){
	
	int j = 0;
	char *param = (char *)malloc(sizeof(char)* STRING_SIZE);

	for (; command[index] != '\n' && command[index] != '\0'; ++index){
		if (command[index] == '=' || command[index] == '[' || command[index] == ','){
			param[j] = '\0';
			break;
		}
		else if (isAlpha(command[index]))
			param[j++] = command[index];
	}
	param[j] = '\0';
	return param;
}

char *getParamNameSpaceDelimiter(char *command, int index){

	int j = 0;
	char *param = (char *)malloc(sizeof(char)* STRING_SIZE);

	for (; command[index] != '\n' && command[index] != '\0'; ++index){
		if (command[index] == ' ' || command[index] == '['){
			param[j] = '\0';
			break;
		}
		else if (isAlpha(command[index]))
			param[j++] = command[index];
	}
	param[j] = '\0';
	return param;
}

char *getLabelName(char *command, int index){

	int j = 0;
	char *label = (char *)malloc(sizeof(char)* STRING_SIZE);

	for (; command[index] != '\n' && command[index] != '\0'; ++index){
		if (command[index] == ':'){
			label[j] = '\0';
			break;
		}
		else if (isAlpha(command[index]))
			label[j++] = command[index];
	}
	return label;
}

int* initMemory(int size){
	return (int *)malloc(sizeof(int)* size);
}

void printHeaderFiles(FILE *fp){
	fprintf(fp, "#define _CRT_SECURE_NO_WARNINGS\n");
	fprintf(fp, "#include <stdio.h>\n");
	fprintf(fp, "#include <stdlib.h>\n");
	fprintf(fp, "#include <string.h>\n");
	fprintf(fp, "#include <math.h>\n");
	fprintf(fp, "#include <limits.h>\n");
	fprintf(fp, "\nint main(){\n\n");
}

char *getParameterName(int location){
	if (location < 8){
		switch (location){
		case 0: return "AX";
		case 1: return "BX";
		case 2: return "CX";
		case 3: return "DX";
		case 4: return "EX";
		case 5: return "FX";
		case 6: return "GX";
		case 7: return "HX";
		}
	}

	for (int i = 0; i < symbolTableIndex; ++i){
		if (symbolTable[i]->constValue == INT_MIN){
			if (location == symbolTable[i]->location)
				return symbolTable[i]->paramName;
		}
	}
}

int getMemorySize(){
	return symbolTable[symbolTableIndex - 1]->location + symbolTable[symbolTableIndex - 1]->size;
}

