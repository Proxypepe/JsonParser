#include "Json.h"

std::pair<std::vector<IDataType>, size_t> json::Json::construct_json_array(std::vector<token>&, size_t)
{



	return std::pair<std::vector<IDataType>, size_t>();
}

void json::Json::encode()
{
	std::pair<value_type, data_pointer> var;
	for (size_t i = 0; i < tokens.size() - 2; i++)
	{
		if (tokens[i].first == TokenType::STRING && tokens[i + 1].first == TokenType::COLON)
		{
			var.first = tokens[i].second;
			if (tokens[i + 2].first == TokenType::STRING)
			{
				var.second = std::make_shared<StringType>(tokens[i + 2].second);
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



			}
		}
	}
}

