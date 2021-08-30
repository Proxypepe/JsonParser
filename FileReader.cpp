#include "FileReader.h"

std::string FileReader::read_file(const_reference file_name)
{
	std::ifstream file(file_name);
	std::string line;
	std::string result = "";
	if (file.is_open())
	{
		while (getline(file, line))
		{
			result += line;
		}
		file.close();
	}
	else
	{
		throw FileNotFound();
	}
	return result;
}
