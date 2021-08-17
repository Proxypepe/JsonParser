#include <iostream>
#include <vector>
#include <string>
#include "DataType.h"
#include "Lexer.h"
#include "Json.h"



int main()
{
	// Lexer l = Lexer("{ \"hello\":\"10\", \"gg\": \"12  \", \"g\": 12, \"ar\":[ \"12\", 13, 10]}");
	Lexer l = Lexer("{ \"hello\":\"10\", \"gg\": 235167559, \"array\": [ 1, 2, 3], \"a\": 12,\"ss\": [\"14\", \"13\"]}");
	// 
	auto encoded = l.analyze();
	json::Json j{ encoded };

	j.encode();
	auto a =  j.get<int>("\"a\"");
	auto hello = j.get<std::string>("\"hello\"");
	auto array_ = j.get<std::vector<int>>("\"array\"");
	auto ss = j.get<std::vector<std::string>>("\"ss\"");

	std::cout << a << std::endl << hello;

	return 0;
}

