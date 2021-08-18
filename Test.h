#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "DataType.h"
#include "Lexer.h"
#include "Json.h"


using namespace json;

class JsonTest : public ::testing::Test
{
public:
	Lexer l;
	Json j;

public:
	JsonTest() {}
protected:
	void SetUp() override
	{
		l = Lexer("{ \"hello\":\"10\", \"gg\": 1333, \"array\": [ 1, 2, 3], \"a\": 12,\"ss\": [\"14\", \"13\"]}");
		auto encoded = l.analyze();
		j.set_tokens(encoded);
		j.encode();
	}
};

