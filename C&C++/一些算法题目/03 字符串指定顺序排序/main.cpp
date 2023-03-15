#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

int main()
{
	std::map<char, int> map;
	for (size_t i = 0; i < 'N' - 'A'; i++)
	{
		map['A' + i] = 2 * i + 1;
	}

	for (size_t i = 0; i <= 'Z' - 'N'; i++)
	{
		map[i+'N'] = 26 - 2 * i;
	}


	std::string str = "C1bZc5A3wBa";

	int index = str.size()-1;
	for (int i = str.size() - 1; i > 0 ; --i)
	{
		if (isdigit(str[i]))
		{
			std::swap(str[i], str[index]);
			index--;
		}
	}

	std::sort(str.begin(), str.begin() + index+1, [&](char a,char b)
		{
			//if (map[toupper(a)] == map[toupper(b)])
			if (toupper(a) == toupper(b))
			{
				return a > b;
			}
			return   map[toupper(a)] < map[toupper(b)];
		});

	std::cout << str << std::endl;

	return 0;
}
