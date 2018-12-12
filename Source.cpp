#define _CRT_SECURE_NO_WARNINGS
#define STRING_SIZE 255
#define MAX_SIZE 1024
#define OFFSET 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "Utils.h"

/*void createCFile(){

	FILE *fp = fopen("CompilerDesign.c", "w");

	printHeaderFiles(fp);

	fprintf(fp, "\tint AX, BX, CX, DX, EX, FX, GX, HX;\n");

	for (int i = 0; i < symbolTableIndex; ++i){
		if (symbolTable[i]->constValue == INT_MIN){
			if (symbolTable[i]->size == 1)
				fprintf(fp, "\tint %s;\n", symbolTable[i]->paramName);
			else
				fprintf(fp, "\tint %s[%d];\n", symbolTable[i]->paramName, symbolTable[i]->size);
		}
		else{
			fprintf(fp, "\tint %s = %d;\n", symbolTable[i]->paramName, symbolTable[i]->constValue);
		}
	}
	fprintf(fp, "\n");
	
	for (int i = 0; i < 13; ++i){
		switch (iLangTable[i]->opCode){
		case 3: fprintf(fp, "\t%s = %s;\n", getParameterName(iLangTable[i]->params[0]), getParameterName(iLangTable[i]->params[1]));
			break;
		case 4: fprintf(fp, "\t%s = %s + %s;\n", getParameterName(iLangTable[i]->params[0]), getParameterName(iLangTable[i]->params[1]), getParameterName(iLangTable[i]->params[2]));
			break;
		case 5: fprintf(fp, "\t%s = %s - %s;\n", getParameterName(iLangTable[i]->params[0]), getParameterName(iLangTable[i]->params[1]), getParameterName(iLangTable[i]->params[2]));
			break;
		case 6: fprintf(fp, "\t%s = %s * %s;\n", getParameterName(iLangTable[i]->params[0]), getParameterName(iLangTable[i]->params[1]), getParameterName(iLangTable[i]->params[2]));
			break;
		case 7: fprintf(fp, "\tprintf(\"\\nEnter a value : \");\n");
			fprintf(fp, "\tscanf(\"%%d\", &%s);\n", getParameterName(iLangTable[i]->params[0]));
			break;
		case 8: fprintf(fp, "\tprintf(\"%%d\\n\", %s);\n", getParameterName(iLangTable[i]->params[0]));
			break;
		/*case 9: i = iLangTable[i]->params[0] - 2;
			break;
		case 10: if (iLangTable[i]->params[1] == 14){
					 if (memory[iLangTable[i]->params[0]] == memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				}
				 else if (iLangTable[i]->params[1] == 15){
					 if (memory[iLangTable[i]->params[0]] < memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				 }
				 else if (iLangTable[i]->params[1] == 16){
					 if (memory[iLangTable[i]->params[0]] > memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				 }
				 else if (iLangTable[i]->params[1] == 17){
					 if (memory[iLangTable[i]->params[0]] <= memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				 }
				 else if (iLangTable[i]->params[1] == 18){
					 if (memory[iLangTable[i]->params[0]] >= memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				 }
				 break;
		case 11: i = iLangTable[i]->params[0] - 1;
			break;
		case 12: break;
		case 13: break;
		}
	}
	fclose(fp);
}*/

void executeILangTable(SymbolTable **symbolTable, ILangTable **iLangTable, int symbolTableIndex, int iLangTableIndex){
	int *memory = initMemory(getMemorySize());

	for (int i = 0; i < symbolTableIndex; ++i){
		if (symbolTable[i]->constValue != INT_MIN)
			memory[symbolTable[i]->location] = symbolTable[i]->constValue;
	}

	for (int i = 0; i < iLangTableIndex; ++i){
		switch (iLangTable[i]->opCode){
		case 3: memory[iLangTable[i]->params[0]] = memory[iLangTable[i]->params[1]];
			break;
		case 4: memory[iLangTable[i]->params[0]] = memory[iLangTable[i]->params[1]] + memory[iLangTable[i]->params[2]];
			break;
		case 5: memory[iLangTable[i]->params[0]] = memory[iLangTable[i]->params[1]] - memory[iLangTable[i]->params[2]];
			break;
		case 6: memory[iLangTable[i]->params[0]] = memory[iLangTable[i]->params[1]] * memory[iLangTable[i]->params[2]];
			break;
		case 7: printf("\nEnter a value: ");
			scanf("%d", &memory[iLangTable[i]->params[0]]);
			break;
		case 8: printf("%d\n", memory[iLangTable[i]->params[0]]);
			break;
		case 9: i = iLangTable[i]->params[0] - 2;
			break;
		case 10: if (iLangTable[i]->params[1] == 14){
					 if (memory[iLangTable[i]->params[0]] == memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				}
				else if (iLangTable[i]->params[1] == 15){
					 if (memory[iLangTable[i]->params[0]] < memory[iLangTable[i]->params[2]])
						 break;
					 else
						 i = iLangTable[i]->params[3] - 2;
				}
				else if (iLangTable[i]->params[1] == 16){
					if (memory[iLangTable[i]->params[0]] > memory[iLangTable[i]->params[2]])
						break;
					else
						i = iLangTable[i]->params[3] - 2;
				}
				else if (iLangTable[i]->params[1] == 17){
					if (memory[iLangTable[i]->params[0]] <= memory[iLangTable[i]->params[2]])
						break;
					else
						i = iLangTable[i]->params[3] - 2;
				}
				else if (iLangTable[i]->params[1] == 18){
					if (memory[iLangTable[i]->params[0]] >= memory[iLangTable[i]->params[2]])
						break;
					else
						i = iLangTable[i]->params[3] - 2;
				}
			break;
		case 11: i = iLangTable[i]->params[0] - 1;
			break;
		case 12: break;
		case 13: break;
		}
	}
}

int getCommand(char *exp, int *index){

	char *command = (char *)malloc(sizeof(char)* STRING_SIZE);

	int j = 0;
	while (exp[*index] != ' ' && exp[*index] != '\n'){
		if (exp[*index] != '\t' && exp[*index] != '\n')
			command[j++] = exp[*index];
		(*index)++;
	}
	command[j] = '\0';

	return getOpCode(command);
}

void handleIf(int opCode, char *command, int index, int paramSize, char **paramNames, int *offsets){
	
	push(iLangTableIndex + 1);

	for (int i = 0; i < paramSize; ++i){
		paramNames[i] = (char *)malloc(sizeof(char)* STRING_SIZE);
		paramNames[i] = getParamNameSpaceDelimiter(command, index);
		offsets[i] = getNumericData(command, index);
		index += strlen(paramNames[i]) + 1;
		if (offsets[i] != -1)
			index += 3;
		else
			offsets[i] = 0;
	}
	insertIntoILangTable(opCode, paramNames, offsets, paramSize);
}

void handleJump(int opCode, char *command, int index, int paramSize, char **paramNames, int *offsets){
	for (int i = 0; i < paramSize; ++i)
		paramNames[i] = getLabelName(command, index);
	insertIntoILangTable(opCode, paramNames, offsets, paramSize);
}

void createILangTable(int opCode, char *command, int index){

	if (opCode == -1){
		if (isLabel(command)){
			char *labelName = getLabelName(command, 0);
			insertIntoLabelTable(labelName);
			return;
		}
	}

	int paramSize = getParameterSize(opCode);
	if (paramSize <= 0){
		insertIntoILangTable(opCode, NULL, NULL, paramSize);
		return;
	}

	char **paramNames = (char **)malloc(sizeof(char*)* paramSize);
	int *offsets = (int *)malloc(sizeof(int)* paramSize);
	
	if (opCode == 10){
		handleIf(opCode, command, index, paramSize, paramNames, offsets);
		return;
	}
	
	if (opCode == 14){
		handleJump(opCode, command, index, paramSize, paramNames, offsets);
		return;
	}

	for (int i = 0; i < paramSize; ++i){
		paramNames[i] = (char *)malloc(sizeof(char)* STRING_SIZE);
		paramNames[i] = getParamName(command, index);
		offsets[i] = getNumericData(command, index);
		index += strlen(paramNames[i]) + 1;
		if (command[index] == ',')
			index += 1;
		if (offsets[i] != -1)
			index += 3;
		else
			offsets[i] = 0;
	}
	insertIntoILangTable(opCode, paramNames, offsets, paramSize);
}

void createSymbolTable(int opCode, char *command, int index){
	char *paramName = (char *)malloc(sizeof(char)* STRING_SIZE);
	int constValue = INT_MIN, size = 1;

	if (opCode == 1){
		paramName = getParamName(command, index);
		size = getNumericData(command, index);
		size = size == -1 ? 1 : size;
		insertIntoSymbolTable(paramName, size, constValue);
		return;
	}
	if (opCode == 2){
		paramName = getParamName(command, index);
		constValue = getNumericData(command, index);
		constValue = constValue == -1 ? INT_MIN : constValue;
		insertIntoSymbolTable(paramName, size, constValue);
		return;
	}
}

void interpretOtherLabels(char *line){
	int index = 0;

	int opCode = getCommand(line, &index);

	createILangTable(opCode, line, index+1);
}

void interpretDataLabel(char *line){
	int index = 0;

	int opCode = getCommand(line, &index);

	createSymbolTable(opCode, line, index+1);
}

void readFile(FILE *fp){

	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);

	while (fgets(line, MAX_SIZE, fp) != '\0'){
		if (strcmp(line, "START:\n") == 0)
			break;
		interpretDataLabel(line);
	}

	while (fgets(line, MAX_SIZE, fp) != '\0'){
		interpretOtherLabels(line);
	}

	fclose(fp);
}

FILE *loadFile(char *mode){
	char *filename = (char *)malloc(sizeof(char)* STRING_SIZE);

	printf("\nEnter the file name: ");
	gets(filename);

	return fopen(filename, mode);
}

void executeOutFile(){

	FILE *fp = loadFile("rb");

	int symTabIndex, iLangTabIndex;

	fread(&symTabIndex, sizeof(int), 1, fp);
	fread(&iLangTabIndex, sizeof(int), 1, fp);

	SymbolTable **symTable = (SymbolTable **)malloc(sizeof(SymbolTable *)* symTabIndex);
	ILangTable **iLTable = (ILangTable **)malloc(sizeof(ILangTable *)* iLangTabIndex);

	for (int i = 0; i < symTabIndex; ++i){
		symTable[i] = (SymbolTable *)malloc(sizeof(SymbolTable));
		fread(symTable[i], sizeof(SymbolTable), 1, fp);
	}
	
	for (int i = 0; i < iLangTabIndex; ++i){
		iLTable[i] = (ILangTable *)malloc(sizeof(ILangTable));
		fread(iLTable[i], sizeof(ILangTable), 1, fp);
	}

	fclose(fp);

	executeILangTable(symTable, iLTable, symTabIndex, iLangTabIndex);
}

void createOutFile(){

	FILE *fp = loadFile("wb");

	if (!fp){
		printf("\nError opening the given file.");
		system("pause");
		exit(1);
	}

	fwrite(&symbolTableIndex, sizeof(int), 1, fp);
	fwrite(&iLangTableIndex, sizeof(int), 1, fp);
	
	for (int i = 0; i < symbolTableIndex; ++i){
		fwrite(symbolTable[i], sizeof(SymbolTable), 1, fp);
	}

	for (int i = 0; i < iLangTableIndex; ++i){
		fwrite(iLangTable[i], sizeof(ILangTable), 1, fp);
	}

	fclose(fp);
}


FILE *openFile(){
	FILE *fp = fopen("Source1.txt", "r"); //loadFile();

	if (!fp){
		printf("\nError opening the given file.");
		system("pause");
		exit(1);
	}

	return fp;
}

void initialize(){
	initializeSymbolTable();
	initializeLabelTable();
	initializeILangTable();
	initializeStack();
}

int main(){

	initialize();

	FILE *fp = openFile();

	readFile(fp);

	printf("\nSymbol Table for the following code is:\n\n");
	
	printSymbolTable();

	printf("\nIntermediate Code for the following code is:\n\n");

	printILangTable();

	printf("\nLabel Table for the following code is:\n\n");

	printLableTable();

	printf("\nExecuting the intermediate language code");

	createOutFile();

	executeOutFile();

	//executeILangTable(symbolTable, iLangTable, symbolTableIndex, iLangTableIndex);

	//createCFile();

	system("pause");
	return 0;
}