#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>

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



void hoareSort2(std::vector<int>& array, int l, int r)
{
	if (l >= r)
		return;
	int i = l + 1, j = r, x = array[l];
	while (i <= j)
	{
		while (j >= i && array[i] <= x)
			i++;
		while (j >= i && array[j] > x)
			j--;
		if (i < j)
		{
			std::swap(array[i], array[j]);
			i++;
			j--;
		}
	}
	std::swap(array[l], array[j]);
	j--;
	hoareSort2(array, l, j);
	hoareSort2(array, i, r);
}

void hoareSort3(std::vector<int>& array, int l, int r)
{
	if(l >= r)
		return;
	int i = l, j = r, x = array[(l + r) / 2];
	while (i <= j)
	{
		while (array[i] < x)
			i++;
		while (array[j] > x)
			j--;
		if (i <= j)
		{
			std::swap(array[i], array[j]);
			i++;
			j--;
		}
	}
	hoareSort3(array, l, j);
	hoareSort3(array, i, r);
}

void main()
{

	clock_t start, stop;
	double time, totalTime = 0;
	for (int border = 10; border <= 100000; border *= 100)
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			std::vector<int> array;
			for (int i = 0; i <= 2; i++)
			{
				recFile(array, border, size);
				start = clock();
				hoareSort3(array, 0, size - 1);
				stop = clock(); 
				time = (double)(stop - start) / CLOCKS_PER_SEC;
				totalTime += time;
			}
			if (checkArray(array))
				std::cout << "Running time of the hoare sort(border = " << border << ", size = " << size << ") = " << totalTime / 3. << std::endl;
			totalTime = 0;
		}
}