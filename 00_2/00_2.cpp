#include <iostream>
#include <string.h>
#include <vector>

int main()
{
	std::string stringHead;
	std::cin >> stringHead;
	std::vector<char> string;
	std::cout << std::size(stringHead) << std::endl;
	int i=0;
	while(stringHead[i] != "/0")
	{
		string.push_back(stringHead[i]);
		std::cout << string[i] << std::endl;
		i++;
	}
}