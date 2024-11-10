﻿#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

bool checkArray(std::vector<int> array)
{
	for (int i = 0; i < array.size() - 1; i++)
	{
		if (array[i] > array[i + 1])
			return false;
	}
	return true;
}

void recFile(std::vector<int>& array, int const border, int const size)
{
	std::ifstream file;
	int value = 0;
	std::string ch;
	file.open("random_mas_" + std::to_string(size) + "_" + std::to_string(border) + ".txt");
	while (!file.eof())
	{
		ch = "";
		file >> ch;
		if (ch != "")
		{
			value = stoi(ch);
			array.push_back(value);
		}
	}
	file.close();
}

void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}

void sift(std::vector<int>& array, int const size, int index)
{
	int j = 2 * index + 1, x = array[index], f = 1;
	while (j < size && f)
	{
		if (j + 1 < size && array[j + 1] > array[j])
			j+=1;
		if (array[j] > x)
		{
			array[index] = array[j];
			index = j;
			j = 2 * index + 1;
		}
		else
			f = 0;
	}
	array[index] = x;
}

void buildPyramid(std::vector<int>& array, int const size)
{
	int index = size / 2 - 1;
	while (index >= 0)
	{
		sift(array, size, index);
		index--;
	}
}

void sortPyramid(std::vector<int>& array, int const size)
{
	buildPyramid(array, size);
	int index = size - 1;
	while (index >= 1)
	{
		swap(array[0], array[index]);
		sift(array, index - 1, 0);
		index--;
	}
}

void main()
{
	clock_t start, stop;
	double time, totalTime;
	double* arrTime;
	std::vector<int> array;
	for (int border = 10; border <= 100000; border *= 100)
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			arrTime = new double[3];
			for (int i = 0; i <= 2; i++)
			{
				recFile(array, border, size);
				start = clock();
				sortPyramid(array, size);
				stop = clock();
				time = (double)(stop - start) / CLOCKS_PER_SEC;
				arrTime[i] = time;
				if (i == 2)
				{
					totalTime = (arrTime[0] + arrTime[1] + arrTime[2]) / 3;
					if (checkArray(array))
						std::cout << "Running time of the pyramid sort(border = " << border << ", size = " << size << ") = " << totalTime << std::endl;
					delete []arrTime;
				}
				array.clear();
			}
		}
}