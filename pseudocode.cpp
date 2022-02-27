#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "keywords.h"
#include "token.h"

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
				case '-':
					if (currentTokenString == "<") {
						currentTokenString.push_back(letter);
						break;
					}
				case ',': case '(': case ')': case '+': case '*': case '/': case '^':
					if (!currentTokenString.empty()) {
						lineTokens.push_back(currentTokenString);
						currentTokenString.clear();
					}
					lineTokens.push_back(std::string(1, letter));
					break;
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

void evaluate_number(std::vector<Token>& tokens, size_t irrelevance) {
	// -a^b should be treated as -(a^b) so insert 0 at the beginning
	if (tokens[0].type == Keyword::S_SUB || tokens[0].type == Keyword::S_ADD)
		tokens.insert(tokens.begin(), Token(Keyword::INTEGRE, "0"));
	if (tokens.size() == 3) {
		if (tokens[2].type == Keyword::REAL)
			tokens[0].type == Keyword::REAL;
		if (tokens[1].type == Keyword::S_ADD)
			tokens[0] += tokens[2];
		else if (tokens[1].type == Keyword::S_SUB)
			tokens[0] -= tokens[2];
		else if (tokens[1].type == Keyword::S_MULT)
			tokens[0] *= tokens[2];
		else if (tokens[1].type == Keyword::S_DIV)
			tokens[0] /= tokens[2];
		else if (tokens[1].type == Keyword::S_POW)
			tokens[0].pow(tokens[2]);
		tokens.erase(tokens.begin()+1, tokens.end());
		return;
	}
	if (tokens[3].type == Keyword::S_ADD || tokens[3].type == Keyword::S_SUB) {
		std::vector<Token> temp(tokens.begin(), tokens.begin()+3);
		evaluate_number(temp, 1);
		tokens[0] = temp[0];
		tokens.erase(tokens.begin()+1, tokens.begin()+3);
		return;
	}
	if ((tokens[3].type == Keyword::S_MULT || tokens[3].type == Keyword::S_DIV) && irrelevance > 1) {
		std::vector<Token> temp(tokens.begin(), tokens.begin()+3);
		evaluate_number(temp, 2);
		tokens[0] = temp[0];
		tokens.erase(tokens.begin()+1, tokens.begin()+3);
		return;
	}
	if (tokens[3].type == Keyword::S_POW && irrelevance > 2) {
		std::vector<Token> temp(tokens.begin(), tokens.begin()+3);
		evaluate_number(temp, 3);
		tokens[0] = temp[0];
		tokens.erase(tokens.begin()+1, tokens.begin()+3);
		return;
	}
	Token temp1 = tokens[0];
	Token temp2 = tokens[1];
	tokens.erase(tokens.begin(), tokens.begin()+2);
	evaluate_number(tokens, irrelevance+1);
	tokens.insert(tokens.begin(), temp2);
	tokens.insert(tokens.begin(), temp1);
	return;
}

Token evaluate_printable(std::vector<Token> tokens, std::map<std::string, Token> variables) {
	if (tokens.size() == 0)
		return Token(Keyword::INVALID);
	if (tokens.size() == 1) {
		Token token = tokens[0];
		if (token.type == Keyword::STRING || token.type == Keyword::INTEGRE || token.type == Keyword::REAL || token.type == Keyword::BOOLEAN)
			return token;
		if (token.type == Keyword::UNKNOWN) {
			std::map<std::string, Token>::const_iterator pos = variables.find(token.value);
			if (pos != variables.end())
				return pos->second;
		}
		return Token(Keyword::INVALID);
	}
	while (tokens.size() > 1) {
		// for (auto token : tokens)
			// std::cout << token << '\n';
		// std::cout << "\nSize:" << tokens.size() << "\n";
		evaluate_number(tokens, 1);
	}
	
	return tokens[0];
}

void evaluate(std::vector<std::vector<Token>>& tokens) {
	std::map<std::string, Token> variables;
	for (auto lineTokens : tokens)
	{
		if (lineTokens[1].type == Keyword::ASSIGN)
		{
			// variable <- value
			if (lineTokens[0].type != Keyword::UNKNOWN) {
				std::cout << "Can't use keyword as a variable name\n";
				return;
			}
			Token printable = evaluate_printable(std::vector<Token>(lineTokens.begin()+2, lineTokens.end()), variables);
			variables[lineTokens[0].value] = printable;
			continue;
		}

		if (lineTokens[0].type == Keyword::OUTPUT)
		{
			if (lineTokens.size() == 1) {
				std::cout << "OUTPUT must take at least 1 argument\n";
				return;
			}
			// OUTPUT printable1, printable2, ...
			std::vector<Token>::iterator printableStart = lineTokens.begin()+1;
			std::vector<Token>::iterator printableEnd = lineTokens.begin()+1;
			while (printableEnd != lineTokens.end())
			{
				printableEnd++;
				if (printableEnd->type == Keyword::COMMA) {
					std::cout << evaluate_printable(std::vector<Token>(printableStart, printableEnd), variables).value << ' ';
					printableStart = printableEnd+1;
				}
			}
			if (printableStart == printableEnd) {
				std::cout << "No argument given after comma\n";
				return;
			}
			std::cout << evaluate_printable(std::vector<Token>(printableStart, printableEnd), variables).value << '\n';
		}

		if (lineTokens[0].type == Keyword::INPUT)
		{
			if (lineTokens.size() == 1) {
				std::cout << "\nINPUT must take at least 1 argument\n";
				return;
			}
			// INPUT printable1, printable2, ...
			std::vector<Token>::iterator variablePos = lineTokens.begin()+1;
			if (variablePos->type != Keyword::UNKNOWN) {
				std::cout << "Can't use keyword as a variable name\n";
				return;
			}
			Token input(Keyword::STRING);
			std::getline(std::cin, input.value);
			char* fail;
			strtol(input.value.c_str(), &fail, 10);
			if (*fail) {
				strtod(input.value.c_str(), &fail);
				if (*fail)
					if (input.value == Keyword::TRUE || input.value == Keyword::FALSE)
						input.type = Keyword::BOOLEAN;
				else
					input.type = Keyword::REAL;
			} else
				input.type = Keyword::INTEGRE;
			variables[variablePos->value] = input;
			
			while (++variablePos != lineTokens.end())
			{
				if (variablePos->type != Keyword::COMMA) {
					std::cout << ", expected\n";
					return;
				}
				if (++variablePos == lineTokens.end()) {
					std::cout << "Argument expected\n";
					return;
				}
				if (variablePos->type != Keyword::UNKNOWN) {
					std::cout << "Can't use keyword as a variable name\n";
					return;
				}
				input.type = Keyword::STRING;
				std::getline(std::cin, input.value);
				char* fail;
				strtol(input.value.c_str(), &fail, 10);
				if (*fail) {
					strtod(input.value.c_str(), &fail);
					if (*fail)
						if (input.value == Keyword::TRUE || input.value == Keyword::FALSE)
							input.type = Keyword::BOOLEAN;
					else
						input.type = Keyword::REAL;
				} else
					input.type = Keyword::INTEGRE;
				variables[variablePos->value] = input;
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
	std::cout << '\n';
#endif
	evaluate(tokens);
	sourceFile.close();
}
