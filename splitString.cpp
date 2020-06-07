#include "splitString.h"

std::vector<std::string> splitString(std::string input)
{
	splitString(input, ' ');
}

std::vector<std::string> splitString(std::string input, char delim)
{
	int start = 0;
	std::string string;
	std::vector<std::string> temp;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == delim)
		{
			string = "";
			for (int x = start; x < i; x++)
			{
				string += input[x];
			}
			temp.push_back(string);
			start = i + 1;
		}
	}

	string = "";
	for (int x = start; x < input.length(); x++)
	{
		string += input[x];
	}
	temp.push_back(string);

	return temp;
}