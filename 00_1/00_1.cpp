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
void PutMasPtr(int* a, int n)
{
	for (int* p = a; p < a + n; p++)
		scanf_s("%d", &*p);
}
void sheiker(int* massiv, int L,int R)
{
	while (L <= R)
	{
		for (int i = L; i < R; i++)
			if (massiv[i] > massiv[i + 1])
				swap(massiv[i], massiv[i + 1]);
		R--;
		for (int i = R; i > L; i--)
			if (massiv[i] < massiv[i - 1])
				swap(massiv[i], massiv[i - 1]);
		L++;
	}
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
void Perebor(int** matr,int *massiv, int n, int begin)
{
	int i_max = 1, j_max = 1;
	for (int i = 1; i < n-1 ; i++)
		if (massiv[i] > massiv[i_max] && massiv[i] < massiv[i + 1])
			i_max = i;
	std::cout << "\n" << i_max;
	if(i_max!=0)
	{
		for(int j=i_max+1;(j>i_max && j<=n-1); j++)
			if(massiv[j] > massiv[j_max] && massiv[i_max] < massiv[j])
				j_max = j;
	}
	std::cout << "\n" << j_max;
	puts("");
	swap(massiv[j_max], massiv[i_max]);
	sheiker(massiv, i_max + 1, n-1);
	for(int i=0;i<n+1;i++)
		std::cout << " " << massiv[i];
}
int main()
{
	int** matrix;
	int Gorod, Begin, k = 0;
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
	//PutMasPtr(massiv, Gorod + 1);
	CreateMassivPuti(Gorod, Begin, massiv);
	/*int sum = PricePuti(matrix, massiv, Gorod, Begin);
	std::cout << "\n" << sum;*/
	puts("");
	while (k!= factorial(Gorod-1))
	{
		Perebor(matrix, massiv, Gorod, Begin);
		k++;
	}
	delete[] massiv;
}
