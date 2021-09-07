#pragma once
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <variant>
#include "Lexer.h"
#include "DataType.h"
#include "Factory.h"
#include "FileReader.h"

namespace json
{
	class Json
	{
	public:
		using value_type	  = std::string;
		using reference		  = value_type&;
		using const_reference = const value_type&;

		using data_pointer	  = std::shared_ptr<IDataType>;
		using const_pointer   = const std::shared_ptr<IDataType>;

		using token			  = std::pair<TokenType, std::string>;

		using JInt			  = int32_t;
		using JString		  = std::string;
		using JBool			  = bool;
		using JIarray		  = std::vector<int32_t>;
		using JSarray		  = std::vector<value_type>;
		using JObject		  = std::map<value_type, data_pointer>;

	private:
		value_type			m_data;
		std::vector<token>	tokens;

		JObject parsed_data;

	private:
		template<class T>
		std::pair<data_pointer, size_t> construct_json_array(const std::vector<token>&, const size_t&);
		std::string delete_quotes(value_type) noexcept;
		JObject create_object(size_t&);
		void serialize();
	public:
		explicit Json(const_reference data) : m_data(data) { }
		explicit Json(value_type&& data) : m_data(std::move(data)) { }
		explicit Json(const std::vector<token>& data) : tokens(data) { }
		explicit Json(const_reference data, const_reference data_type);
		Json() {}


		void set_tokens(const std::vector<token>& tokens) noexcept { this->tokens = tokens; }
		void encode() noexcept;

		template <class T>
		T get(const_reference key);

		template <class T>
		void set(const_reference key, T value);

		data_pointer get_pointer(const_reference key) { return parsed_data[key]; }
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
				{
					element = stoi(tokens[curr_pos].second);
				}
				else if (tokens[curr_pos].first == TokenType::STRING)
				{
					if constexpr (std::is_same<T, std::string>::value)
						element = delete_quotes(tokens[curr_pos].second);
				}
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
		Factory factory;
		auto ptr = factory.get_instance<T>(value);
		parsed_data[key] = ptr;
	}

	template<class T>
	T get(Json::data_pointer data)
	{
		std::shared_ptr<GetValue<T>> visitor;
		visitor = std::make_shared<GetValue<T>>();
		data->accept(visitor.get());
		T res = visitor.get()->get_value();
		return res;
	}
	
	template<class T>
	T get(Json j, Json::const_reference key)
	{
		std::shared_ptr<GetValue<T>> visitor;
		visitor = std::make_shared<GetValue<T>>();
		auto var = j.get_pointer(key).get();
		j.get_pointer(key).get()->accept(visitor.get());
		auto res = visitor.get()->get_value();
		return res;
	}
}
