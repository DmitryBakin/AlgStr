#include <iostream>
#include <string.h>
#include <vector>
int findFirst(std::string& const str, std::string& const substr,int leftBorder = 0 ,int rightBorder = -1)
{
	if (leftBorder < 0)
	{
		leftBorder += str.size();
	}
	if (rightBorder < 0)
	{
		rightBorder += str.size();
	}
	if (leftBorder >= rightBorder || leftBorder > str.size() || rightBorder >= str.size())
		return -1;
	int table[256];
	int strLen = str.size(), substrLen = substr.size();
	int index = substrLen - 1, indexSubstr, indexStr;
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
				index += table[str[index]];
				break;
			}
		}
		if (indexSubstr == -1 && index - substrLen + 1 >= leftBorder && index - substrLen + 1 < rightBorder)
			break;
		if (indexSubstr == -1 && (index - substrLen + 1 < leftBorder || index - substrLen + 1 > rightBorder))
			if (strLen > index + substrLen)
				index++;
			else 
				break;
	}
	if (indexSubstr == -1 && index - substrLen + 1 >= leftBorder && index - substrLen + 1 < rightBorder)
		return index - substrLen + 1;
	if (indexSubstr == -1 && (index - substrLen + 1 < leftBorder || index - substrLen + 1 > rightBorder))
		return -1;
}

std::vector<int> findAll(std::string& const str, std::string& const substr, int const leftBorder, int const rightBorder)
{
	std::vector<int> masEntr;
	int entr = findFirst(str, substr);
	while(entr != -1)
	{
		if(entr >= leftBorder && entr < rightBorder)
			masEntr.push_back(entr);
		entr = findFirst(str, substr, entr + 1, rightBorder);
	}
	return masEntr;
}
void main()
{
	std::string str("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator");
	std::string substr("tor");
	std::vector<int> masEntr;
	if (findFirst(str, substr) != -1)
		std::cout << "First entry index = " << findFirst(str, substr);
	else
		std::cout << "No entries found";
	puts("\n--------------------------");

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
}