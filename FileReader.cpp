#include "FileReader.h"


FileReader::value_type FileReader::formate_line(const_reference line)
{
	value_type formated_line = "";

	for (auto c : line)
		if (c != '\t')
			formated_line += c;

	return formated_line;
}

std::string FileReader::read_file(const_reference file_name)
{
	std::ifstream file(file_name);
	std::string line;
	std::string result = "";
	if (file.is_open())
	{
		while (getline(file, line))
		{
			result += formate_line(line);
		}
		file.close();
	}
	else
	{
		throw FileNotFound();
	}
	return result;
}
