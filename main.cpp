#include <iostream>
#include <vector>
#include <string>
#include "Test.h"

TEST_F(JsonTest, IntField)
{
	int r = j.get<int>("gg");
	EXPECT_EQ(r, 1333);
}

TEST_F(JsonTest, StringField)
{
	auto r = j.get<std::string>("hello");
	EXPECT_EQ(r, "10");
}

TEST_F(JsonTest, ArrayIntField)
{
	auto r2 = j.get<std::vector<int>>("array");
	std::vector<int> ans = { 1, 2, 3 };
	EXPECT_EQ(r2.size(), ans.size());
	EXPECT_EQ(r2, ans);
}

TEST_F(JsonTest, ArrayStringField)
{
	auto r2 = j.get<std::vector<std::string>>("ss");
	std::vector<std::string> ans = { "14", "13"};
	EXPECT_EQ(r2.size(), ans.size());
	EXPECT_EQ(r2, ans);
}

TEST_F(JsonTest, BoolTypeField)
{
	bool r1 = j.get<bool>("boolf");
	EXPECT_EQ(r1, false);

	auto r2 = j.get<bool>("boolt");
	EXPECT_EQ(r2, true);
}

TEST_F(JsonTest, SetValue)
{
	l = Lexer("{\"hello\":10, \"gg\": 12}");
	auto encoded = l.analyze();
	j.set_tokens(encoded);
	j.encode();
	int r = j.get<int>("hello");
	EXPECT_EQ(r, 10);
	j.set<int>("hello", 12);
	r = j.get<int>("hello");
	EXPECT_EQ(r, 12);
}

TEST_F(JsonTest, Constructor)
{
	std::string json_string = "{\"hello\":10, \"gg\": 12}";
	Json json{ json_string, "str" };
	int r = json.get<int>("hello");
	EXPECT_EQ(r, 10);
}

TEST_F(JsonTest, FileReading)
{
	std::string file_name = "test.json";
	Json json{ file_name, "file" };
	int r = json.get<int>("hello");
	EXPECT_EQ(r, 10);
}



int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

