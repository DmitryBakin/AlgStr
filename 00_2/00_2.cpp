#include <iostream>
#include <string.h>
#include <vector>
int findAll(std::string const str, std::string const substr)
{
	int table[256], strLen = str.size(), substrLen = substr.size(), index = substrLen - 1, indexSubstr, indexStr;
	for (int i = 0; i < 256; i++)
		table[i] = substrLen;
	for (int i = 0; i < substrLen - 1; i++)
		table[substr[i]] = substrLen - 1 - i;
	while (index < strLen)
	{
		indexStr = index;
		indexSubstr = substrLen - 1;
		while (indexSubstr >= 0)
		{
			if (str[indexStr] == substr[indexSubstr])
			{
				indexStr--;
				indexSubstr--;
			}
			else
			{
				index = indexStr + table[str[indexStr]];
				break;
			}
		}
		if (indexSubstr == -1)
			break;
	}
	if (indexSubstr == -1)
	{
		return index - substrLen + 1;
	}
	else
		return -1;
	
}
std::vector<int> findAll(std::string const str, std::string const substr,int const leftBorder, int const rightBorder)
{
	std::string strCopy(str.begin() + leftBorder, str.begin() + rightBorder + 1);
	int table[256], strLen = strCopy.size(), substrLen = substr.size(), index = substrLen - 1, indexSubstr, indexStr;
	std::vector<int> masEntr;
	for (int i = 0; i < 256; i++)
		table[i] = substrLen;
	for (int i = 0; i < substrLen - 1; i++)
		table[substr[i]] = substrLen - 1 - i;
	while (index < strLen)
	{
		indexStr = index;
		indexSubstr = substrLen - 1;
		while (indexSubstr >= 0)
		{
			if (strCopy[indexStr] == substr[indexSubstr])
			{
				indexStr--;
				indexSubstr--;
			}
			else
			{
				index = indexStr + table[strCopy[indexStr]];
				break;
			}
		}
		if (indexSubstr == -1)
		{
			masEntr.push_back(index - substrLen + leftBorder + 1);
			index++;
		}
	}
	return masEntr;
}
void main()
{
	std::string str("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator");
	std::string substr("tor");
	std::vector<int> masEntr;
	masEntr = findAll(str, substr, 0, 91);
	std::cout << "findAll(0, 91) = [ ";
	for (int i = 0; i < masEntr.size(); i++) 
		std::cout << masEntr[i] << " ";
	std::cout << "]";
	puts("\n--------------------------");
	masEntr = findAll(str, substr, 28, 36);
	std::cout << "findAll(28, 36) = [ ";
	for (int i = 0; i < masEntr.size(); i++)
		std::cout << masEntr[i] << " ";
	std::cout << "]";
	puts("\n--------------------------");
	masEntr = findAll(str, substr, 17, 91);
	std::cout << "findAll(17, 91) = [ ";
	for (int i = 0; i < masEntr.size(); i++)
		std::cout << masEntr[i] << " ";
	std::cout << "]";
	puts("\n--------------------------");
	if (findAll(str, substr) != -1)
		std::cout << "First entry index = " << findAll(str, substr);
	else
		std::cout << "No entries found";
	puts("\n--------------------------");
}