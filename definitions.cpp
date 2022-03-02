#include "token.h"
#include "keywords.h"
#include <iostream>
#include <cmath>

const std::unordered_set<const char*> keywords = {
	Keyword::IF,
	Keyword::REPEAT,
	Keyword::WHILE,
	Keyword::FOR,
	Keyword::DO,
	Keyword::THEN,
	Keyword::ELSE,
	Keyword::UNTIL,
	Keyword::TO,
	Keyword::STEP,
	Keyword::NEXT,
	Keyword::INPUT,
	Keyword::OUTPUT,
	Keyword::END,
	Keyword::ASSIGN,
	Keyword::S_ADD,
	Keyword::S_SUB,
	Keyword::S_MULT,
	Keyword::S_DIV,
	Keyword::S_POW,
	Keyword::PROCEDURE,
	Keyword::CALL,
	Keyword::COMMA,
	Keyword::COLON,
	Keyword::FUNCTION,
	Keyword::RETURN,
	Keyword::RETURNS,
	Keyword::INTEGRE,
	Keyword::REAL,
	Keyword::CHAR,
	Keyword::STRING,
	Keyword::BOOLEAN,
	Keyword::ARRAY,
	Keyword::OF,
	Keyword::DECLARE,
	Keyword::CONSTANT,
	Keyword::DIV,
	Keyword::MOD,
	Keyword::C_EQ,
	Keyword::C_LT,
	Keyword::C_LE,
	Keyword::C_GT,
	Keyword::C_GE,
	Keyword::C_NE,
	Keyword::O_PS,
	Keyword::O_PE,
	Keyword::O_BS,
	Keyword::O_BE,
	Keyword::LENGTH,
	Keyword::UCASE,
	Keyword::LCASE,
	Keyword::SUBSTRING,
	Keyword::ROUND,
	Keyword::RANDOM,
	Keyword::CASE,
	Keyword::OTHERWISE,
	Keyword::OPENFILE,
	Keyword::READ,
	Keyword::WRITE,
	Keyword::READFILE,
	Keyword::WRITEFILE,
	Keyword::CLOSEFILE
};

Token::Token() {}

Token::Token(const Token& t)
	:type(t.type), value(t.value)
{
}

Token::Token(const std::string& s)
{
	std::cout << s << '\n';
	auto keywordsIterator = keywords.begin();
	while (keywordsIterator != keywords.end()) {
		++keywordsIterator;
		if (strcmp(*keywordsIterator, s.c_str()) != 0) {
			type = *keywordsIterator;
			return;
		}
	}
	value = s;
	char* fail;
	strtol(s.c_str(), &fail, 10);
	if (!*fail) {
		type = Keyword::INTEGRE;
		return;
	}
	strtod(s.c_str(), &fail);
	if (!*fail) {
		type = Keyword::REAL;
		return;
	}
	if (s == Keyword::TRUE || s == Keyword::FALSE) {
		type = Keyword::BOOLEAN;
		return;
	}
	type = Keyword::UNKNOWN;
}

Token::Token(const std::string& type, const std::string& value)
	: type(type), value(value)
{
}

void Token::operator=(const Token& t) {
	type = t.type;
	value = t.value;
}

void Token::operator+=(const Token& t) {
	std::stringstream ss;
	ss << strtod(value.c_str(), nullptr) + strtod(t.value.c_str(), nullptr);
	value = ss.str();
}

void Token::operator-=(const Token& t) {
	std::stringstream ss;
	ss << strtod(value.c_str(), nullptr) - strtod(t.value.c_str(), nullptr);
	value = ss.str();
}

void Token::operator*=(const Token& t) {
	std::stringstream ss;
	ss << strtod(value.c_str(), nullptr) * strtod(t.value.c_str(), nullptr);
	value = ss.str();
}

void Token::operator/=(const Token& t) {
	std::stringstream ss;
	ss << strtod(value.c_str(), nullptr) / strtod(t.value.c_str(), nullptr);
	value = ss.str();
}

void Token::pow(const Token& t) {
	std::stringstream ss;
	ss << std::pow(strtod(value.c_str(), nullptr), strtod(t.value.c_str(), nullptr));
	value = ss.str();
}

