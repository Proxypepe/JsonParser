#pragma once
#include <fstream>
#include <string>
#include <exception>

class FileNotFound : public  std::exception
{
	const char* what() const throw ()
	{
		return "FileNotFound";
	}
};


class FileReader
{
public:
	using value_type		= std::string;
	using reference			= std::string&;
	using const_reference	= const std::string&;

	FileReader() = delete;

	static std::string read_file(const_reference);
};

