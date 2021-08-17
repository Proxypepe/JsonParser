#pragma once
#include <string>
#include <map>
#include <memory>
#include "Lexer.h"
#include "DataType.h"


namespace json
{
	class Json
	{
		using value_type	  = std::string;
		using reference		  = std::string&;
		using const_reference = const std::string&;

		using data_pointer	  = std::shared_ptr<IDataType>;
		using const_pointer   = const std::shared_ptr<IDataType>;

		using token			  = std::pair<TokenType, std::string>;

	private:
		value_type			m_data;
		std::vector<token>	tokens;

		std::map<value_type, data_pointer> parsed_data;

	private:
		template<class T>
		std::pair<data_pointer, size_t> construct_json_array(std::vector<token>&, size_t);

	public:
		Json(const_reference data) : m_data(data) { }
		Json(const std::vector<token>& data) : tokens(data) { }

		void encode();

		template <class T>
		T get(value_type key);
	};


	template<>
	inline std::pair<std::shared_ptr<IDataType>, size_t> Json::construct_json_array<int32_t>(std::vector<token>& tokens, size_t start_pos)
	{
		std::vector<int32_t> json_vector;
		size_t curr_pos = start_pos;
		int32_t element;
		for (curr_pos; tokens[curr_pos].first != TokenType::CLOSE_ARRAY; curr_pos++)
		{
			if (tokens[curr_pos].first != TokenType::COMMA)
			{
				element = stoi(tokens[curr_pos].second);
				json_vector.push_back(element);
			}
		}
		auto ptr = std::make_shared<ArrayIntType>(json_vector);
		return std::make_pair(ptr, curr_pos);
	}

	template<>
	inline std::pair<std::shared_ptr<IDataType>, size_t> Json::construct_json_array<std::string>(std::vector<token>& tokens, size_t start_pos)
	{
		std::vector<std::string> json_vector;
		size_t curr_pos = start_pos;
		for (curr_pos; tokens[curr_pos].first != TokenType::CLOSE_ARRAY; curr_pos++)
			if (tokens[curr_pos].first != TokenType::COMMA)
				json_vector.push_back(tokens[curr_pos].second);
		auto ptr = std::make_shared<ArrayStringType>(json_vector);
		return std::make_pair(ptr, curr_pos);
	}

	template<class T>
	inline T Json::get(value_type key)
	{
		std::shared_ptr<GetValue<T>> visitor;
		visitor = std::make_shared<GetValue<T>>();
		auto var = parsed_data[key].get();
		var->accept(visitor.get());
		auto res = visitor.get()->get_value();
		return res;
	}

}