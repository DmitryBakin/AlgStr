#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>

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
	for (int i = 0; sum / 2 != 1; i++)
	{
		stepsArr.push_back(sum / 2);
		sum /= 2;
	}
	stepsArr.push_back(sum / 2);
}
void createStepsArr2(std::vector<int>& stepsArr, int const sum)
{
	for (int i = log2(sum); i > 0; i--)
	{
		stepsArr.push_back(pow(2, i) - 1);
	}
	for (int i = 0; i < stepsArr.size(); i++)
		std::cout << stepsArr[i] << " ";
	puts("");
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
void insert(int *array,int const sum, int const b,int const s)
{
	int j = b + s, x, k;
	while (j < sum)
	{
		x = array[j];
		k = j - s;
		while (k >= 0 && array[k] > x)
		{
			array[k+s] = array[k];
			k = k - s;
		}
		array[k+s] = x;
		j += s;
	}
}
void shell(int* array, std::vector<int>& stepsArr, int const sum)
{
	int round = 0, s, b;
	while (round <= stepsArr.size() - 1)
	{
		s = stepsArr[round];
		b = 0;
		while (b < s)
		{
			insert(array, sum, b, s);
			b++;
		}
		round++;
	}
}
void main()
{
	for (int i = 0; i < 1; i++)
	{
		int sum, lf, rf;
		clock_t start, stop;
		double time1, time2;
		std::cout << "Enter the number of elements in the array ";
		std::cin >> sum;
		std::cout << "Enter lf ";
		std::cin >> lf;
		std::cout << "Enter rf ";
		std::cin >> rf;
		std::vector<int> stepsArr;
		int* array;
		array = new int[sum];
		randMasD(array, sum, lf, rf);
		for (int i = 0; i < sum; i++)
			std::cout << array[i] << " ";
		puts("\n------------------------------ ");
		start = clock();
		createStepsArr1(stepsArr, sum);
		shell(array, stepsArr, sum);
		stop = clock();
		time1 = (double)(stop - start) / CLOCKS_PER_SEC;
		std::cout << "Running time of the first algorithm = " << time1 << std::endl;
		if (checkArray(array, sum))
			std::cout << "\nThe array has been sorted\n";
	}
}