#include "Json.h"


std::string json::Json::delete_quotes(value_type str)
{
	std::string result = "";
	if (!str.empty())
		for (size_t i = 1; i < str.length() - 1; i++)
			result += str[i];
	return result;
}

void json::Json::encode()
{
	std::pair<value_type, data_pointer> var;
	for (size_t i = 0; i < tokens.size() - 2; i++)
	{
		if (tokens[i].first == TokenType::STRING && tokens[i + 1].first == TokenType::COLON)
		{
			var.first = delete_quotes(tokens[i].second);
			if (tokens[i + 2].first == TokenType::STRING)
			{
				auto formated_str = delete_quotes(tokens[i + 2].second);
				var.second = std::make_shared<StringType>(formated_str);
				i += 2;
				parsed_data[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::INT)
			{
				int32_t converted = stoi(tokens[i + 2].second);
				var.second = std::make_shared<IntType>(converted);
				i += 2;
				parsed_data[var.first] = var.second;
			}
			else if (tokens[i + 2].first == TokenType::OPEN_ARRAY)
			{
				i += 3;
				std::pair < std::shared_ptr<IDataType>, size_t> vector_shift;
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
				parsed_data[var.first] = var.second;
			}
		}
	}
}

