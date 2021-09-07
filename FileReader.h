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
	using reference			= value_type&;
	using const_reference	= const value_type&;

	FileReader() = delete;

private:
	static value_type formate_line(const_reference);

public:

	static std::string read_file(const_reference);

};

