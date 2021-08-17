#pragma once
#include <string>
#include <map>
#include <memory>
#include "Lexer.h"
#include "DataType.h"
#include "Factory.h"

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
		std::pair<data_pointer, size_t> construct_json_array(const std::vector<token>&, const size_t&);

	public:
		Json(const_reference data) : m_data(data) { }
		Json(const std::vector<token>& data) : tokens(data) { }

		void encode();

		template <class T>
		T get(const_reference key);

		template <class T>
		void set(const_reference key, T value);
	};


	template<class T>
	inline std::pair<std::shared_ptr<IDataType>, size_t> Json::construct_json_array(const std::vector<token>& tokens,const size_t &start_pos)
	{
		std::vector<T> json_vector;
		size_t curr_pos = start_pos;
		T element;
		Factory factory;
		for (curr_pos; tokens[curr_pos].first != TokenType::CLOSE_ARRAY; curr_pos++)
		{
			if (tokens[curr_pos].first != TokenType::COMMA)
			{
				if (tokens[curr_pos].first == TokenType::INT)
					element = stoi(tokens[curr_pos].second);
				else if constexpr (std::is_same<T, std::string>::value)
					if (tokens[curr_pos].first == TokenType::STRING)
						element = tokens[curr_pos].second;
				json_vector.push_back(element);
			}
		}
		auto ptr = factory.get_instance<decltype(json_vector)>(json_vector);
		return std::make_pair(ptr, curr_pos);
	}

	template<class T>
	inline T Json::get(const_reference key)
	{
		std::shared_ptr<GetValue<T>> visitor;
		visitor = std::make_shared<GetValue<T>>();
		auto var = parsed_data[key].get();
		var->accept(visitor.get());
		auto res = visitor.get()->get_value();
		return res;
	}

	template<class T>
	inline void Json::set(const_reference key, T value)
	{



	}


}