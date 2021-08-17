#include <iostream>
#include <vector>
#include <string>
#include "DataType.h"
#include "Lexer.h"
#include "Json.h"



int main()
{
	// Lexer l = Lexer("{ \"hello\":\"10\", \"gg\": \"12  \", \"g\": 12, \"ar\":[ \"12\", 13, 10]}");
	Lexer l = Lexer("{ \"hello\":\"10\", \"gg\": 235167559, \"array\": [ 1, 2, 3], \"a\": 12}");

	auto encoded = l.analyze();
	json::Json j{ encoded };

	j.encode();
	auto res =  j.get<int>("\"a\"");
	auto s = j.get<std::string>("\"hello\"");
	std::cout << res << std::endl << s;

	return 0;
}

