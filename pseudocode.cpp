#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "keywords.h"

class Token
{
public:
	std::string type;
	std::string value;

	Token(const std::string& s)
	{
		if (keywords.find(s) != keywords.end()) {
			type = s;
			return;
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
		type = Keyword::UNKNOWN;
	}

	Token(const std::string& type, const std::string& value)
		: type(type), value(value)
	{
	}
};

std::ostream &operator<<(std::ostream& os, const Token& token) {
	if (token.value.empty())
		return os << '(' << token.type << ')';
	return os << '(' << token.type << ": " << token.value << ')';
}

std::vector<std::vector<Token>> parse(std::ifstream& sourceFile)
{
	std::vector<std::vector<Token>> allTokens;
	std::string line;
	bool isString = false;
	std::string currentTokenString;
	std::vector<Token> lineTokens;
	while (std::getline(sourceFile, line))
	{
		size_t comment_index = line.find(Keyword::COMMENT);
		if (comment_index != std::string::npos)
			line = line.substr(0, comment_index);

		for (char letter : line)
		{
			if (letter == *Keyword::O_DQ.c_str())
			{
				if (isString) {
					lineTokens.emplace_back(Keyword::STRING, currentTokenString);
				} else {
					if (!currentTokenString.empty())
						lineTokens.push_back(currentTokenString);
				}
				currentTokenString.clear();
				isString = not isString;
				continue;
			}
			if (isString) {
				currentTokenString.push_back(letter);
				continue;
			}
			switch(letter) {
				case ' ':
					if (!currentTokenString.empty()) {
						lineTokens.push_back(currentTokenString);
						currentTokenString.clear();
					}
					break;
				default:
					currentTokenString.push_back(letter);
			}
		}
		if (isString) {
			currentTokenString.append(Keyword::NEWLINE);
			continue;
		}
		if (!currentTokenString.empty())
			lineTokens.push_back(currentTokenString);
		currentTokenString.clear();

		if (lineTokens.size() > 0)
			allTokens.push_back(lineTokens);
		lineTokens.clear();
	}
	if (isString) {
		std::cout << "String never ended\n";
		return {};
	}

	return allTokens;
}

void evaluate(std::vector<std::vector<Token>>& tokens) {
	std::map<std::string, Token> variables;
	for (auto lineTokens : tokens)
	{
		if (lineTokens[1].type == Keyword::ASSIGN)
		{
			// variable <- value
			if (lineTokens[0].type != Keyword::UNKNOWN || (lineTokens[2].type != Keyword::STRING && lineTokens[2].type != Keyword::INTEGRE &&lineTokens[2].type != Keyword::BOOLEAN))
			{
			}
			variables.insert(std::pair<std::string, Token>(lineTokens[0].value, lineTokens[2]));
		}

		if (lineTokens[0].type == Keyword::OUTPUT)
		{
			// OUTPUT variable
			if (lineTokens[1].type == Keyword::UNKNOWN) {
				std::map<std::string, Token>::const_iterator pos = variables.find(lineTokens[1].value);
				if (pos != variables.end())
					std::cout << pos->second.value << '\n';
			}
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Give a file\n";
		return 0;
	}
	std::ifstream sourceFile;
	sourceFile.open(argv[1]);
	if (!sourceFile.is_open()) {
		std::cout << "File doesn't exist\n";
		return 0;
	}

	auto tokens = parse(sourceFile);
#define printTokens 0
#if printTokens == 1
	for (auto line : tokens) {
		for (auto token : line)
		std::cout << token << ' ';
		std::cout << '\n';
	}
	std::cout << "\n\n";
#endif
	evaluate(tokens);
	sourceFile.close();
}
