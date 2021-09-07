#pragma once
#include <string>
#include <vector>


enum class TokenType
{
	INT,
	STRING,
	BOOL,
	NULLPTR,
	OPEN_ARRAY,
	CLOSE_ARRAY,
	OPEN_DICT,
	CLOSE_DICT,
	COLON,
	COMMA,
	VAR_NAME
};

class Lexer
{
	using value_type = std::string;
	using reference = std::string&;
	using const_reference = const std::string&;
	using token = std::pair<TokenType, std::string>;

private:
	value_type m_data;

private:
	void push_str_symbol(std::vector<value_type>&, reference, const_reference);
	std::vector<value_type> splite();
	std::vector<token> parse(std::vector<value_type>&);
	TokenType recognize_token_dt(reference);
public:
	Lexer(const_reference data) : m_data(data) {}
	Lexer() : m_data(value_type()) { }
	std::vector<token> analyze();
};
