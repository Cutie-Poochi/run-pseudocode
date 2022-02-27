#pragma once
#include <string>
#include <unordered_set>

namespace Keyword {
	const std::string IF = "IF";
	const std::string REPEAT = "REPEAT";
	const std::string WHILE = "WHILE";
	const std::string FOR = "FOR";
	const std::string DO = "DO";
	const std::string THEN = "THEN";
	const std::string ELSE = "ELSE";
	const std::string UNTIL = "UNTIL";
	const std::string TO = "TO";
	const std::string STEP = "STEP";
	const std::string NEXT = "NEXT";
	const std::string INPUT = "INPUT";
	const std::string OUTPUT = "OUTPUT";
	const std::string END = "END";
	const std::string ASSIGN = "<-";
	const std::string S_ADD = "+";
	const std::string S_SUB = "-";
	const std::string S_MULT = "*";
	const std::string S_DIV = "/";
	const std::string S_POW = "^";
	const std::string PROCEDURE = "PROCEDURE";
	const std::string CALL = "CALL";
	const std::string COMMA = ",";
	const std::string COLON = ":";
	const std::string FUNCTION = "FUNCTION";
	const std::string RETURN = "RETURN";
	const std::string RETURNS = "RETURNS";
	const std::string INTEGRE = "INTEGRE";
	const std::string REAL = "REAL";
	const std::string CHAR = "CHAR";
	const std::string STRING = "STRING";
	const std::string BOOLEAN = "BOOLEAN";
	const std::string ARRAY = "ARRAY";
	const std::string OF = "OF";
	const std::string DECLARE = "DECLARE";
	const std::string CONSTANT = "CONSTANT";
	const std::string DIV = "DIV";
	const std::string MOD = "MOD";
	const std::string C_EQ = "==";
	const std::string C_LT = "<";
	const std::string C_LE = "<=";
	const std::string C_GT = ">";
	const std::string C_GE = ">=";
	const std::string C_NE = "<>";
	const std::string O_PS = "(";
	const std::string O_PE = ")";
	const std::string O_BS = "[";
	const std::string O_BE = "]";
	const std::string O_DQ = "\"";
	const std::string LENGTH = "LENGTH";
	const std::string UCASE = "UCASE";
	const std::string LCASE = "LCASE";
	const std::string SUBSTRING = "SUBSTRING";
	const std::string ROUND = "ROUND";
	const std::string RANDOM = "RANDOM";
	const std::string CASE = "CASE";
	const std::string OTHERWISE = "OTHERWISE";
	const std::string OPENFILE = "OPENFILE";
	const std::string READ = "READ";
	const std::string WRITE = "WRITE";
	const std::string READFILE = "READFILE";
	const std::string WRITEFILE = "WRITEFILE";
	const std::string CLOSEFILE  = "CLOSEFILE ";

	// not to be parsed, just identifiers ig
	const std::string COMMENT = "//";
	const std::string UNKNOWN = "?";
	const std::string NEWLINE = "\n";
	const std::string INVALID = "ERROR";
	const std::string TRUE = "TRUE";
	const std::string FALSE = "FALSE";
}
