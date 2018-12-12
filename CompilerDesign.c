#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

int main(){

	int AX, BX, CX, DX, EX, FX, GX, HX;
	int B;
	int A;
	int C[4];
	int D;
	int E = 0;

	printf("\nEnter a value : ");
	scanf("%d", &AX);
	printf("\nEnter a value : ");
	scanf("%d", &BX);
	A = AX;
	B = BX;
	CX = AX + BX;
	printf("\nEnter a value : ");
	scanf("%d", &AX);
	DX = AX - BX;
	printf("%d\n", DX);
	printf("%d\n", CX);
	C = CX;
	printf("%d\n", C);
