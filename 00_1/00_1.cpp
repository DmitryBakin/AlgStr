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
void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}
int factorial(int a)
{
	int k;
	for (k = 1; a > 1; a--)
		k = k * a;
	return k;
}
void Perebor(int** matr, int n, int begin)
{
	int m = 1, min = 0, sum = 0;
	int* massiv;
	massiv = new int[n-1];
	for (int i = 0; m <= n;m++)
	{
		if (begin != m)
		{
			massiv[i] = m;
			//std::cout << massiv[i] << " ";
			i++;
		}
	}
	for(int i=0;i<n-1;i++)
		std::cout << massiv[i] << " ";
	for (int k=1;/*k != 1 + factorial(n)*/ k!=2;)
		{
		int i = 0;
		int N = massiv[i];
		sum = matr[begin-1][N-1];
		i++;
		std::cout << sum << " ";
		for (; i < n - 1; i++)
		{
			N = massiv[i];
			sum = sum + matr[N - 2][N - 1];
			std::cout << sum << " ";
		}
		k++;
		sum = sum + matr[N-1][begin-1];
		std::cout << sum;
		}
	delete[] massiv;
}
int main()
{
	int** matrix;
	int Gorod,Begin;
	std::cout << "Vvedite Kolichestvo gorodov - ";
	std::cin >> Gorod;
	puts("");
	std::cout << "Vvedite gorod-Nachalo ";
	std::cin >> Begin;
	puts("");
	matrix = new int* [Gorod];
	for (int i = 0; i < Gorod; i++)
		matrix[i] = new int[Gorod];
	RandMatrD(matrix, Gorod, Gorod, 1, 100);
	//InputMatrD(matrix, Gorod, Gorod);
	OutputMatrD(matrix, Gorod, Gorod);
	Perebor(matrix, Gorod, Begin);
}
