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
		std::pair<std::vector<IDataType>, size_t> construct_json_array(std::vector<token>&, size_t);

	public:
		Json(const_reference data) : m_data(data) { }
		Json(const std::vector<token>& data) : tokens(data) { }

		void encode();

		template <class T>
		T get(value_type key);
	};


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