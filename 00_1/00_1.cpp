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
}
int PricePuti(int** matr, int* massiv, int n)
{
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		sum = sum + matr[massiv[i - 1] - 1][massiv[i] - 1];
	}
	return sum;
}
void Perebor(int** matr,int *massiv, int n)
{
	int i_max = 1, j_max = 1;
	for (int i = 2; i < n-1 ; i++)
		if (massiv[i] > 0 && massiv[i] < massiv[i + 1])
			i_max = i;
	//std::cout << "\n" << i_max;
	for(int j=i_max+1;(j>i_max && j<=n-1); j++)
		if(massiv[i_max] < massiv[j])
			j_max = j;
	//std::cout << "\n" << j_max;
	swap(massiv[j_max], massiv[i_max]);
	sheiker(massiv, i_max + 1, n-1);
}
int main()
{
	int** matrix;
	int Gorod, Begin, k = 0, Price_Max = 0, Price_Min = 0;
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
	OutputMatrD(matrix, Gorod, Gorod);
	CreateMassivPuti(Gorod, Begin, massiv);
	if(Gorod < 6)
		for (int i = 0; i < Gorod + 1; i++)
			std::cout << massiv[i] << " ";
	Price_Min = PricePuti(matrix,massiv,Gorod);
	Price_Max = PricePuti(matrix, massiv, Gorod);
	if(Gorod<6)
		std::cout << "  Ssuma Puti = " << Price_Max << "\n";
	while (k!= factorial((Gorod-1)) - 1) 
	{
		int Price;
		Perebor(matrix, massiv, Gorod);
		if (Gorod < 6)
			for (int i = 0; i < Gorod + 1; i++)
				std::cout << massiv[i] << " ";
		Price = PricePuti(matrix, massiv, Gorod);
		if(Gorod < 6)
			std::cout << "  Ssuma Puti = " << Price << "\n";
		if (Price > Price_Max)
			Price_Max = Price;
		if (Price < Price_Min)
			Price_Min = Price;
		k++;
	}
	std::cout << "\n" << "Minimalni put = " << Price_Min << "\n" << "Maximalni put = " << Price_Max;
	delete[] massiv;
	for (int i = 0; i < Gorod; i++) delete[] matrix[i];
	delete[] matrix;
}
