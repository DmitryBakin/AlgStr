#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
void RandMatrD(int** matr, int m, int n, int lf, int rt)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				matr[i][j] = 0;
			else
				matr[i][j] = rand() % (rt - lf + 1) + lf;
		}
}
void InputMatrD(int** matr, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) scanf_s(" %d", &matr[i][j]);
}
void OutputMatrD(int** matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) printf(" % 4d", matr[i][j]);
		printf("\n");
	}
}
int main()
{
	int** matrix;
	int Gorod;
	std::cout << "Vvedite Kolichestvo gorodov - ";
	std::cin >> Gorod;
	puts("");
	matrix = new int* [Gorod];
	for (int i = 0; i < Gorod; i++)
		matrix[i] = new int[Gorod];
	RandMatrD(matrix, Gorod, Gorod, 1, 100);
	//InputMatrD(matrix, Gorod, Gorod);
	OutputMatrD(matrix, Gorod, Gorod);
}