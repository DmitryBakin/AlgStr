#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <iostream>

bool checkArray(std::vector<int>& array)
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
	array.clear();
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

int bitValue(int a, int k)
{
	int mask = 1;
	mask <<= k;
	int result = mask & a;
	if (result != 0)
		return true;
	return false;
}

void bitwiseSort(std::vector<int>& array, int k, int l, int r, bool first)
{
	if (l >= r || k < 0)
		return;
	int i = l, j = r;
	while (i <= j)
	{
		if (first)
		{
			while (i <= j && bitValue(array[i], k) == 1)
				i++;
			while (i <= j && bitValue(array[j], k) == 0)
				j--;
			if (i < j)
			{
				std::swap(array[i], array[j]);
				i++;
				j--;
			}
		}
		else
		{
			while (i <= j && bitValue(array[i], k) == 0)
				i++;
			while (i <= j && bitValue(array[j], k) == 1)
				j--;
			if (i < j)
			{
				std::swap(array[i], array[j]);
				i++;
				j--;
			}
		}
	}
	bitwiseSort(array, k - 1, l, j, 0);
	bitwiseSort(array, k - 1, i, r, 0);
}

void main()
{

	clock_t start, stop;
	double time, totalTime = 0;
	for (int border = 10; border <= 100000; border *= 100)
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			std::vector<int> array;
			int k = 0, b = border;
			while (b > 0)
			{
				b /= 2;
				k++;
			}
			for (int i = 0; i <= 2; i++)
			{
				recFile(array, border, size);
				start = clock();
				bitwiseSort(array, k, 0, size - 1, 1);
				stop = clock();
				time = (double)(stop - start) / CLOCKS_PER_SEC;
				totalTime += time;
			}
			if (checkArray(array))
				std::cout << "Running time of the bitwise sort(border = " << border << ", size = " << size << ") = " << totalTime / 3. << std::endl;
			totalTime = 0;
		}
}