#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct SymbolTable{
	char *paramName;
	int location;
	int size;
	int constValue;
}SymbolTable;

SymbolTable **symbolTable;
int symbolTableIndex;

typedef struct LabelTable{
	char *labelName;
	int location;
}LabelTable;

LabelTable **labelTable;
int labelTableIndex;

typedef struct ILangTable{
	int instNo;
	int opCode;
	int *params;
}ILangTable;

ILangTable **iLangTable;
int iLangTableIndex;

typedef struct Stack{
	int top;
	int *arr;
}Stack;

Stack *stack;

void push(int value){
	stack->arr[++(stack->top)] = value;
}

int pop(){
	return stack->arr[stack->top--];
}

void insertIntoSymbolTable(char *paramName, int size, int constValue){
	symbolTable[symbolTableIndex] = (SymbolTable *)malloc(sizeof(SymbolTable));
	symbolTable[symbolTableIndex]->paramName = (char *)malloc(sizeof(char)* STRING_SIZE);
	
	strcpy(symbolTable[symbolTableIndex]->paramName, paramName);
	symbolTable[symbolTableIndex]->size = size;
	symbolTable[symbolTableIndex]->constValue = constValue;

	if (symbolTableIndex == 0)
		symbolTable[symbolTableIndex]->location = OFFSET;
	else
		symbolTable[symbolTableIndex]->location = symbolTable[symbolTableIndex - 1]->location + symbolTable[symbolTableIndex-1]->size;

	symbolTableIndex += 1;
}

int getOpCode(char *command){
	if (strcmp("DATA", command) == 0)
		return 1;
	if (strcmp("CONST", command) == 0)
		return 2;
	if (strcmp("MOV", command) == 0)
		return 3;
	if (strcmp("ADD", command) == 0)
		return 4;
	if (strcmp("SUB", command) == 0)
		return 5;
	if (strcmp("MUL", command) == 0)
		return 6;
	if (strcmp("READ", command) == 0)
		return 7;
	if (strcmp("PRINT", command) == 0)
		return 8;
	if (strcmp("JUMP", command) == 0)
		return 9;
	if (strcmp("IF", command) == 0)
		return 10;
	if (strcmp("ELSE", command) == 0)
		return 11;
	if (strcmp("THEN", command) == 0)
		return 12;
	if (strcmp("ENDIF", command) == 0)
		return 13;
	if (strcmp("EQ", command) == 0)
		return 14;
	if (strcmp("LT", command) == 0)
		return 15;
	if (strcmp("GT", command) == 0)
		return 16;
	if (strcmp("LTEQ", command) == 0)
		return 17;
	if (strcmp("GTEQ", command) == 0)
		return 18;
	return -1;
}


int getIndex(char *paramName){
	if (strcmp("AX", paramName) == 0)
		return 0;
	if (strcmp("BX", paramName) == 0)
		return 1;
	if (strcmp("CX", paramName) == 0)
		return 2;
	if (strcmp("DX", paramName) == 0)
		return 3;
	if (strcmp("EX", paramName) == 0)
		return 4;
	if (strcmp("FX", paramName) == 0)
		return 5;
	if (strcmp("GX", paramName) == 0)
		return 6;
	if (strcmp("HX", paramName) == 0)
		return 7;
	for (int i = 0; i < symbolTableIndex; ++i){
		if (strcmp(symbolTable[i]->paramName, paramName) == 0)
			return symbolTable[i]->location;
	}
	return INT_MAX;
}

int getParameterSize(int opCode){
	switch (opCode){
	case 1: return 1;
	case 2: return 1;
	case 3: return 2;
	case 4: return 3;
	case 5: return 3;
	case 6: return 3;
	case 7: return 1;
	case 8: return 1;
	case 9: return 1;
	case 10: return 4;
	case 11: return 0;
	case 12: return 0;
	case 13: return 0;
	}
	return -1;
}

int getLabelIndex(char *param){
	for (int i = 0; i < labelTableIndex; ++i){
		if (strcmp(labelTable[i]->labelName, param) == 0)
			return labelTable[i]->location;
	}
	return -1;
}

void insertIntoILangTable(int opCode, char **paramNames, int *offsets, int paramSize){
	iLangTable[iLangTableIndex] = (ILangTable *)malloc(sizeof(ILangTable));

	if (paramSize <= 0){
		iLangTable[iLangTableIndex]->instNo = iLangTableIndex + 1;
		iLangTable[iLangTableIndex]->opCode = opCode;
		if (opCode == 11){
			iLangTable[iLangTableIndex]->params = (int *)malloc(sizeof(int));
			int ifIndex = pop();
			iLangTable[ifIndex-1]->params[getParameterSize(10) - 1] = iLangTableIndex + 2;
			iLangTable[iLangTableIndex]->params[0] = INT_MIN;
			push(iLangTableIndex + 1);
		}
		else if (opCode == 13){
			iLangTable[iLangTableIndex]->params = (int *)malloc(sizeof(int));
			int elseIndex = pop();
			iLangTable[elseIndex-1]->params[getParameterSize(11)] = iLangTableIndex + 1;
			iLangTable[iLangTableIndex]->params[0] = 0;
			//push(iLangTableIndex + 1);
		}
		iLangTableIndex += 1;
		return;
	}

	iLangTable[iLangTableIndex]->params = (int *)malloc(sizeof(int)* paramSize);
	
	iLangTable[iLangTableIndex]->instNo = iLangTableIndex + 1;
	iLangTable[iLangTableIndex]->opCode = opCode;

	if (opCode == 9)
		iLangTable[iLangTableIndex]->params[0] = getLabelIndex(paramNames[0]);
	else{
		for (int i = 0; i < paramSize; ++i){
			if (opCode == 10){
				int conditionOpCode = getOpCode(paramNames[i]);
				if (conditionOpCode != -1){
					if (conditionOpCode == 12)
						iLangTable[iLangTableIndex]->params[i] = INT_MIN;
					else
						iLangTable[iLangTableIndex]->params[i] = conditionOpCode;
				}
				else
					iLangTable[iLangTableIndex]->params[i] = getIndex(paramNames[i]) + offsets[i];
			}
			else
				iLangTable[iLangTableIndex]->params[i] = getIndex(paramNames[i]) + offsets[i];
		}
	}
	iLangTableIndex += 1;
}

void insertIntoLabelTable(char *labelName){
	labelTable[labelTableIndex] = (LabelTable *)malloc(sizeof(LabelTable));
	labelTable[labelTableIndex]->labelName = (char *)malloc(sizeof(char)* STRING_SIZE);

	strcpy(labelTable[labelTableIndex]->labelName, labelName);
	labelTable[labelTableIndex]->location = iLangTable[iLangTableIndex-1]->instNo + 1;

	labelTableIndex += 1;
}

void printSymbolTable(){

	printf("%-15s %15s %15s %15s\n", "ParamName", "Location", "Size", "ConstValue");
	for (int i = 0; i < symbolTableIndex; ++i){
		printf("%-15s %15d %15d ", symbolTable[i]->paramName, symbolTable[i]->location, symbolTable[i]->size);
		int val = symbolTable[i]->constValue;
		if (val == INT_MIN)
			printf("%15s\n", "NA");
		else
			printf("%15d\n", symbolTable[i]->constValue);
	}
}

void printILangTable(){
	printf("%-15s %15s %15s\n", "Number", "OpCode", "ParamIndices");
	for (int i = 0; i < iLangTableIndex; ++i){
		printf("%-15d %15d ", iLangTable[i]->instNo, iLangTable[i]->opCode);
		int paramSize = getParameterSize(iLangTable[i]->opCode);
		paramSize = (iLangTable[i]->opCode == 11 || iLangTable[i]->opCode == 13) ? 1 : paramSize;
		for (int j = 0; j < paramSize; ++j){
			printf("%5d", iLangTable[i]->params[j]);
		}
		printf("\n");
	}
}

void printLableTable(){
	printf("%-15s %15s\n", "LabelName", "Location");
	for (int i = 0; i < labelTableIndex; ++i){
		printf("%-15s %15d\n", labelTable[i]->labelName, labelTable[i]->location);
	}
}