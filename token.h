#pragma once
#include <sstream>
#include <string>

class Token
{
public:
	std::string type;
	std::string value;

	Token();

	Token(const Token& t);

	Token(const std::string& s);

	Token(const std::string& type, const std::string& value);

	void operator=(const Token& t);

	void operator+=(const Token& t);

	void operator-=(const Token& t);

	void operator*=(const Token& t);

	void operator/=(const Token& t);
	
	void pow(const Token& t);
};

