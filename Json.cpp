#include "Json.h"


std::string json::Json::delete_quotes(value_type str) noexcept
{
	std::string result = "";

	if (!str.empty())
		for (size_t i = 1; i < str.length() - 1; i++)
			result += str[i];

	return result;
}

json::Json::JObject json::Json::create_object(size_t& i)
{
	std::pair<value_type, data_pointer> var;
	JObject json_object;
	for (; i < tokens.size() - 2; i++)
	{
		if (tokens[i].first == TokenType::STRING && tokens[i + 1].first == TokenType::COLON)
		{
			var.first = delete_quotes(tokens[i].second);
			if (tokens[i + 2].first == TokenType::STRING)
			{
				std::string formated_str = delete_quotes(tokens[i + 2].second);
				var.second = std::make_shared<StringType>(formated_str);
				i += 2;
				json_object[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::INT)
			{
				int32_t converted = stoi(tokens[i + 2].second);
				var.second = std::make_shared<IntType>(converted);
				i += 2;
				json_object[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::BOOL)
			{
				bool value = tokens[i + 2].second == "true" ? true : false;
				var.second = std::make_shared<BoolType>(value);
				i += 2;
				json_object[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::OPEN_ARRAY)
			{
				i += 3;
				std::pair < data_pointer, size_t> vector_shift;
				if (tokens[i].first == TokenType::INT)
				{
					vector_shift = construct_json_array<int32_t>(tokens, i);
				}
				else if (tokens[i].first == TokenType::STRING)
				{

					vector_shift = construct_json_array<std::string>(tokens, i);
				}
				var.second = vector_shift.first;
				i = vector_shift.second;
				json_object[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::OPEN_DICT)
			{
				i += 2;
				json_object[var.first] = std::make_shared<ObjectType>(create_object(i));
			}
		}
		else if (tokens[i].first == TokenType::CLOSE_DICT)
		{
			return json_object;
		}
	}
	return json_object;
}

void json::Json::serialize()
{



}

json::Json::Json(const_reference data, const_reference data_type)
{
	std::string tmp_data;

	if (data_type == "file")
		tmp_data = FileReader::read_file(data);
	
	else if (data_type == "str")
		tmp_data = data;
	
	Lexer lexer = Lexer(tmp_data);
	tokens = lexer.analyze();
	encode();
}

void json::Json::encode() noexcept
{
	size_t pointer = 0;
	parsed_data = create_object(pointer);
}
