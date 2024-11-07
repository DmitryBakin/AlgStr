#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <string>

bool checkArray(int* array,int const sum)
{
	for (int i = 0; i < sum - 1; i++)
	{
		if (array[i] > array[i + 1])
			return false;
	}
	return true;
}
void randMasD(int* a, int n, int lf, int rt)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	srand(time(0));
	for (int i = 0; i < n; i++) a[i] = rd() % (rt - lf + 1) + lf;
}
void createStepsArr1(std::vector<int>& stepsArr, int sum)
{
	for (int i = 0; sum / 2 > 0; i++)
	{
		stepsArr.push_back(sum / 2);
		sum /= 2;
	}
}
void createStepsArr2(std::vector<int>& stepsArr, int const sum)
{
	for (int i = log2(sum); i > 0; i--)
	{
		stepsArr.push_back(pow(2, i) - 1);
	}
}
void createStepsArr3(std::vector<int>& stepsArr, int const sum)
{
	int log = log2(sum);
	stepsArr.push_back(1);
	for (int i = 1; i < (log - 1) ; i++)
	{
		stepsArr.insert(stepsArr.begin(), 3 * stepsArr[0] + 1);
	}
}
void insert(int *array,int const sum, int const firstElementIndex,int const step)
{
	int j = firstElementIndex + step, x, k;
	while (j < sum)
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
void shell(int* array, std::vector<int>& stepsArr, int const sum)
{
	int round = 0, step, firstElementIndex;
	while (round <= stepsArr.size() - 1)
	{
		step = stepsArr[round];
		firstElementIndex = 0;
		while (firstElementIndex < step)
		{
			insert(array, sum, firstElementIndex, step);
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
		for (int sum = 10000; sum <= 1000000; sum *= 10,i++)
		{
			clock_t start, stop;
			double time1, time2;
			std::vector<int> stepsArr;
			int* array;
			int* arrayCopy;
			array = new int[sum];
			arrayCopy = new int[sum];
			randMasD(array, sum, -border, border);
			for (int k = 0; k < sum; k++)
				arrayCopy[k] = array[k];
			files[i].open("random_mas_" + std::to_string(sum) + "_" + std::to_string(border) + ".txt");
			for (int g = 0; g < sum; g++)
				files[i] << array[g] << " ";
			puts("\n------------------------------ ");
			start = clock();
			createStepsArr1(stepsArr, sum);
			shell(array, stepsArr, sum);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the first algorithm(border = "<< border << ", size = " << sum << ") = " << time1 << std::endl;
			if (checkArray(array, sum))
				std::cout << "\nThe array has been sorted\n";
			puts("\n------------------------------ ");
			for (int k = 0; k < sum; k++)
				array[k] = arrayCopy[k];
			stepsArr.clear();
			start = clock();
			createStepsArr2(stepsArr, sum);
			shell(array, stepsArr, sum);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the second algorithm(border = " << border << ", size = " << sum << ") = " << time1 << std::endl;
			if (checkArray(array, sum))
				std::cout << "\nThe array has been sorted\n";
			puts("\n------------------------------ ");
			stepsArr.clear();
			for (int k = 0; k < sum; k++)
				array[k] = arrayCopy[k];
			start = clock();
			createStepsArr3(stepsArr, sum);
			shell(array, stepsArr, sum);
			stop = clock();
			time1 = (double)(stop - start) / CLOCKS_PER_SEC;
			std::cout << "Running time of the third algorithm(border = " << border << ", size = " << sum << ") = " << time1 << std::endl;
			if (checkArray(array, sum))
				std::cout << "\nThe array has been sorted\n";
			delete[]array;
		}
	}
	delete[]files;
}