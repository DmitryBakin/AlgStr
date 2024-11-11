#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <string>

bool checkArray(int* array,int const size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] > array[i + 1])
			return false;
	}
	return true;
}
void randMasD(int* array, int size, int lf, int rt)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	srand(time(0));
	for (int i = 0; i < size; i++) 
		array[i] = rd() % (rt - lf + 1) + lf;
}
void createStepsArr1(std::vector<int>& stepsArr, int size)
{
	for (int i = 0; size / 2 > 0; i++)
	{
		stepsArr.push_back(size / 2);
		size /= 2;
	}
}
void createStepsArr2(std::vector<int>& stepsArr, int const size)
{
	for (int i = log2(size); i > 0; i--)
	{
		stepsArr.push_back(pow(2, i) - 1);
	}
}
void createStepsArr3(std::vector<int>& stepsArr, int const size)
{
	int log = log2(size);
	stepsArr.push_back(1);
	for (int i = 1; i < (log - 1) ; i++)
	{
		stepsArr.insert(stepsArr.begin(), 3 * stepsArr[0] + 1);
	}
}
void insert(int *array,int const size, int const firstElementIndex,int const step)
{
	int j = firstElementIndex + step, x, k;
	while (j < size)
	{
		x = array[j];
		k = j - step;
		while (k >= 0 && array[k] > x)
		{
			array[k+step] = array[k];
			k -= step;
		}
		array[k+step] = x;
		j += step;
	}
}
void shell(int* array, std::vector<int>& stepsArr, int const size)
{
	int round = 0, step, firstElementIndex;
	while (round <= stepsArr.size() - 1)
	{
		step = stepsArr[round];
		firstElementIndex = 0;
		while (firstElementIndex < step)
		{
			insert(array, size, firstElementIndex, step);
			firstElementIndex++;
		}
		round++;
	}
}
void main()
{
	std::ofstream* files = new std::ofstream[9];
	for (int i = 0, border = 10; border <= 100000; border *= 100)
	{
		for (int size = 10000; size <= 1000000; size *= 10,i++)
		{
			clock_t start, stop;
			double time1, time2;
			std::vector<int> stepsArr;
			int* array;
			int* arrayCopy;
			array = new int[size];
			arrayCopy = new int[size];
			randMasD(array, size, -border, border);
			for (int k = 0; k < size; k++)
				arrayCopy[k] = array[k];
			files[i].open("random_mas_" + std::to_string(size) + "_" + std::to_string(border) + ".txt");
			for (int g = 0; g < size; g++)
				files[i] << array[g] << " ";
			puts("\n------------------------------ ");
			start = clock();
			createStepsArr1(stepsArr, size);
			shell(array, stepsArr, size);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the first algorithm(border = "<< border << ", size = " << size << ") = " << time1 << std::endl;
			if (checkArray(array, size))
				std::cout << "\nThe array has been sorted\n";
			puts("\n------------------------------ ");
			for (int k = 0; k < size; k++)
				array[k] = arrayCopy[k];
			stepsArr.clear();
			start = clock();
			createStepsArr2(stepsArr, size);
			shell(array, stepsArr, size);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the second algorithm(border = " << border << ", size = " << size << ") = " << time1 << std::endl;
			if (checkArray(array, size))
				std::cout << "\nThe array has been sorted\n";
			puts("\n------------------------------ ");
			stepsArr.clear();
			for (int k = 0; k < size; k++)
				array[k] = arrayCopy[k];
			start = clock();
			createStepsArr3(stepsArr, size);
			shell(array, stepsArr, size);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the third algorithm(border = " << border << ", size = " << size << ") = " << time1 << std::endl;
			if (checkArray(array, size))
				std::cout << "\nThe array has been sorted\n";
			delete[]array;
		}
	}
	delete[]files;
}