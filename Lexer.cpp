#include "Lexer.h"

void Lexer::push_str_symbol(std::vector<value_type>& vec, reference str, const_reference symbol)
{
    vec.push_back(str);
    str = "";
    vec.push_back(symbol);
}

std::vector<std::string> Lexer::splite()
{
    std::vector<std::string> result;
    std::string tmp_string = "";
    std::string tmp_symbol = "";
    int8_t in_quotes = 1;
    for (auto c : m_data)
    {
        if (c == '"')
        {
            //tmp_string += "\"";
            in_quotes *= -1;
        }
        else if (!tmp_string.empty())
        {
            if ((c == ':' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',') && in_quotes == 1)
            {
                tmp_symbol = c;
                push_str_symbol(result, tmp_string, tmp_symbol);
            }
        }
        else if (tmp_string.empty())
        {
            if (c == '[' || c == ']' || c == '{' || c == '}')
            {
                tmp_symbol = c;
                result.push_back(tmp_symbol);
            }
        }
        if (in_quotes == -1 && c != '"')
        {
                tmp_string += c;
        }
        else
        {
            if ( c != ':' && c != '{' && c != '}' && c != ']' && c != '[' && c != ' ' && c != ',')
            {
                tmp_string += c;
            }
        }
        // ((c != ' ' || (c == ' ' && in_quotes == -1)) && )
    }
    return result;
}

std::vector<std::pair<TokenType, std::string>> Lexer::parse(std::vector<value_type>& vec)
{
    std::vector<std::pair<TokenType, std::string>> result;
    std::pair<TokenType, std::string> tmp;
    
    for (auto& token : vec)
    {
        tmp.first = recognize_token_dt(token);
        tmp.second = token;
        result.push_back(tmp);
    }
    return result;
}


TokenType Lexer::recognize_token_dt(reference token)
{
    if (token.length() == 1)
    {
        if (token[0] == '[')
        {
            return TokenType::OPEN_ARRAY;
        }
        else if (token[0] == ']')
        {
            return TokenType::CLOSE_ARRAY;
        }
        else if (token[0] == '{')
        {
            return TokenType::OPEN_DICT;
        }
        else if (token[0] == '}')
        {
            return TokenType::CLOSE_DICT;
        }
        else if (token[0] == ':')
        {
            return TokenType::COLON;
        }
        else if (token[0] == ',')
        {
            return TokenType::COMMA;
        }
    }
    else if (token[0] == '"' && token[token.length() - 1] == '"')
    {
        return TokenType::STRING;
    }
    else if (token == "true" or token == "false")
    {
        return TokenType::BOOL;
    }
    else if (token == "null")
    {
        return TokenType::NULLPTR;
    }
    return TokenType::INT;
}

std::vector<std::pair<TokenType, std::string>> Lexer::analyze()
{
    auto splited_data = splite();
    auto parsed_data  = parse(splited_data);

    return parsed_data;
}
