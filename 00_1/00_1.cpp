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

void CreateMassivPuti(int n, int begin, int* massiv)
{
	int m = 1;
	massiv[0] = begin;
	massiv[n] = begin;
	for (int i = 1; m <= n; m++)
	{
		if (begin != m)
		{
			massiv[i] = m;
			i++;
		}
	}
	for (int i = 0; i < n + 1; i++)
		std::cout << massiv[i] << " ";
}
int PricePuti(int** matr, int* massiv, int n, int begin)
{
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		sum = sum + matr[massiv[i - 1] - 1][massiv[i] - 1];
	}
	return sum;
}
void Perebor(int** matr, int n, int begin)
{

}
int main()
{
	int** matrix;
	int Gorod,Begin;
	int* massiv;
	
	std::cout << "Vvedite Kolichestvo gorodov - ";
	std::cin >> Gorod;
	puts("");
	std::cout << "Vvedite gorod-Nachalo ";
	std::cin >> Begin;
	puts("");
	massiv = new int[Gorod + 1];
	matrix = new int* [Gorod];
	for (int i = 0; i < Gorod; i++)
		matrix[i] = new int[Gorod];
	RandMatrD(matrix, Gorod, Gorod, 1, 100);
	//InputMatrD(matrix, Gorod, Gorod);
	OutputMatrD(matrix, Gorod, Gorod);
	//Perebor(matrix, Gorod, Begin);
	CreateMassivPuti(Gorod, Begin, massiv);
	/*int sum = PricePuti(matrix, massiv, Gorod, Begin);
	std::cout << "\n" << sum;*/
	delete[] massiv;
}
