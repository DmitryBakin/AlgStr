#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void randMatrD(int** matr, int m, int lf, int rt)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			if (i == j)
				matr[i][j] = 0;
			else
				matr[i][j] = rand() % (rt - lf + 1) + lf;
		}
}
void inputMatrD(int** matr, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) scanf_s(" %d", &matr[i][j]);
}
void outputMatrD(int** matr, int m)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++) printf(" % 4d", matr[i][j]);
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
void copyMatrix(int **matrix,int **matrixCopy,int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrixCopy[i][j] = matrix[i][j];
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
void createMassivWay(int n, int begin, int* massiv)
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
int priceWay(int** matr, int* massiv, int n)
{
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		sum = sum + matr[massiv[i - 1] - 1][massiv[i] - 1];
	}
	return sum;
}
void perebor(int** matr,int *massiv, int n)
{
	int i_max = 1, j_max = 1;
	for (int i = 2; i < n-1 ; i++)
		if (massiv[i] > 0 && massiv[i] < massiv[i + 1])
			i_max = i;
	for(int j=i_max+1;(j>i_max && j<=n-1); j++)
		if(massiv[i_max] < massiv[j])
			j_max = j;
	swap(massiv[j_max], massiv[i_max]);
	sheiker(massiv, i_max + 1, n-1);
}
void delStrStl(int** matrix,int n, int line, int column)
{
	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		matrix[i][column] = 0;
	}
}
int main()
{
	int** matrix; int** matrixCopy;
	int *massiv,*masEvristika;
	int Gorod, Begin, sumWay = 1,sumWayEvr = 1, priceMax = 0, priceMin = 0, sumEvristika = 0;
	std::cout << "Vvedite Kolichestvo gorodov - ";
	std::cin >> Gorod;
	puts("");
	std::cout << "Vvedite gorod-Nachalo ";
	std::cin >> Begin;
	puts("");
	massiv = new int[Gorod + 1];
	masEvristika = new int[Gorod + 1];
	matrix = new int* [Gorod];
	for (int i = 0; i < Gorod; i++)
		matrix[i] = new int[Gorod];
	randMatrD(matrix, Gorod, 1, 100);
	outputMatrD(matrix, Gorod);
	createMassivWay(Gorod, Begin, massiv);
	if(Gorod < 1)
		for (int i = 0; i < Gorod + 1; i++)
			std::cout << massiv[i] << " ";
	priceMin = priceWay(matrix,massiv,Gorod);
	priceMax = priceWay(matrix, massiv, Gorod);
	if(Gorod<1)
		std::cout << "  Ssuma Puti = " << priceMax << "\n";
	while (sumWay!= factorial((Gorod-1))) 
	{
		int Price;
		perebor(matrix, massiv, Gorod);
		Price = priceWay(matrix, massiv, Gorod);
		if (Gorod < 1)
		{
			for (int i = 0; i < Gorod + 1; i++)
				std::cout << massiv[i] << " ";
			std::cout << "  Ssuma Puti = " << Price << "\n";
		}
		if (Price > priceMax)
			priceMax = Price;
		if (Price < priceMin)
			priceMin = Price;
		sumWay++;
	}
	std::cout << "\n" << "Minimalni put = " << priceMin << "\n" << "Maximalni put = " << priceMax;
	puts("");
	delete[] massiv;
	masEvristika[0] = Begin;
	masEvristika[Gorod] = Begin;
	matrixCopy = new int* [Gorod];
	for (int i = 0; i < Gorod; i++)
		matrixCopy[i] = new int[Gorod];
	copyMatrix(matrix, matrixCopy, Gorod);
	while (sumWayEvr < Gorod)
	{
		int minCol = 0;
			minCol = 0;
			for (int j = 1; j <= Gorod; j++)
			{
				if (matrix[Begin - 1][minCol] == 0)
					minCol++;
				if (matrix[Begin - 1][j] < matrix[Begin - 1][minCol] && matrix[Begin - 1][j] > 0)
					minCol = j;
			}
			masEvristika[sumWayEvr] = minCol + 1;
			for(int proverka=0;proverka<sumWayEvr;proverka++)
				if (masEvristika[proverka] == minCol + 1)
				{
					matrix[Begin - 1][minCol] = 0;
					minCol = Begin - 1;
					sumWayEvr--;
				}
			std::cout << matrix[Begin - 1][minCol] << "\n" << Begin << " " << minCol + 1 <<"\n" << sumWayEvr <<"\n" << "\n";
			if(minCol+1 != Begin)
				delStrStl(matrix, Gorod, Begin - 1, minCol);
			//outputMatrD(matrix, Gorod);
			matrix[minCol][Begin - 1] = 0;
			Begin = minCol + 1;
			sumWayEvr++;
	}
	for (int i = 0; i <= Gorod; i++)
		std::cout << masEvristika[i]<< " ";
	sumEvristika = priceWay(matrixCopy, masEvristika, Gorod);
	std::cout << "\nSumEvristika = " << sumEvristika;
	delete[] masEvristika;
	for (int i = 0; i < Gorod; i++) delete[] matrix[i];
	delete[] matrix;
	for (int i = 0; i < Gorod; i++) delete[] matrixCopy[i];
	delete[] matrixCopy;
}









/*
for (int i = 0; i < Gorod; i++)
{
	int minStr = 0, minStl = 0;
	for (int j = 1; j <= Gorod; j++)
	{
		if (matrix[Begin - 1][minStl] == 0)
			minStl++;
		if (matrix[Begin - 1][j] < matrix[Begin - 1][minStl] && matrix[Begin - 1][j] > 0)
			minStl = j;
	}
	sumEvristika = sumEvristika + matrix[Begin - 1][minStl];
	delStrStl(matrix, Gorod, Begin - 1, minStl);
	outputMatrD(matrix, Gorod);
	std::cout << Begin << " " << minStl + 1 << " " << sumEvristika << "\n";
	matrix[minStl][Begin - 1] = 0;
	Begin = minStl + 1;
	std::cout << Begin;
	puts("");

}*/