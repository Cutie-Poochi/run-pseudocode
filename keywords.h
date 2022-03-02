#pragma once
#include <cstring>
#include <unordered_set>

namespace Keyword {
	const char* const IF = "IF";
	const char* const REPEAT = "REPEAT";
	const char* const WHILE = "WHILE";
	const char* const FOR = "FOR";
	const char* const DO = "DO";
	const char* const THEN = "THEN";
	const char* const ELSE = "ELSE";
	const char* const UNTIL = "UNTIL";
	const char* const TO = "TO";
	const char* const STEP = "STEP";
	const char* const NEXT = "NEXT";
	const char* const INPUT = "INPUT";
	const char* const OUTPUT = "OUTPUT";
	const char* const END = "END";
	const char* const ASSIGN = "<-";
	const char* const S_ADD = "+";
	const char* const S_SUB = "-";
	const char* const S_MULT = "*";
	const char* const S_DIV = "/";
	const char* const S_POW = "^";
	const char* const PROCEDURE = "PROCEDURE";
	const char* const CALL = "CALL";
	const char* const COMMA = ",";
	const char* const COLON = ":";
	const char* const FUNCTION = "FUNCTION";
	const char* const RETURN = "RETURN";
	const char* const RETURNS = "RETURNS";
	const char* const INTEGRE = "INTEGRE";
	const char* const REAL = "REAL";
	const char* const CHAR = "CHAR";
	const char* const STRING = "STRING";
	const char* const BOOLEAN = "BOOLEAN";
	const char* const ARRAY = "ARRAY";
	const char* const OF = "OF";
	const char* const DECLARE = "DECLARE";
	const char* const CONSTANT = "CONSTANT";
	const char* const DIV = "DIV";
	const char* const MOD = "MOD";
	const char* const C_EQ = "==";
	const char* const C_LT = "<";
	const char* const C_LE = "<=";
	const char* const C_GT = ">";
	const char* const C_GE = ">=";
	const char* const C_NE = "<>";
	const char* const O_PS = "(";
	const char* const O_PE = ")";
	const char* const O_BS = "[";
	const char* const O_BE = "]";
	const char* const O_DQ = "\"";
	const char* const LENGTH = "LENGTH";
	const char* const UCASE = "UCASE";
	const char* const LCASE = "LCASE";
	const char* const SUBSTRING = "SUBSTRING";
	const char* const ROUND = "ROUND";
	const char* const RANDOM = "RANDOM";
	const char* const CASE = "CASE";
	const char* const OTHERWISE = "OTHERWISE";
	const char* const OPENFILE = "OPENFILE";
	const char* const READ = "READ";
	const char* const WRITE = "WRITE";
	const char* const READFILE = "READFILE";
	const char* const WRITEFILE = "WRITEFILE";
	const char* const CLOSEFILE  = "CLOSEFILE ";

	// not to be parsed, just identifiers ig
	const char* const COMMENT = "//";
	const char* const UNKNOWN = "?";
	const char* const NEWLINE = "\n";
	const char* const INVALID = "ERROR";
	const char* const TRUE = "TRUE";
	const char* const FALSE = "FALSE";
}
