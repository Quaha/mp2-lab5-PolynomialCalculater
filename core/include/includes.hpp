#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iomanip>

using std::vector;
using std::string;
using std::map;
using std::set;

// Basic conversions

using integer_type = long long;
using real_type = long double;

inline real_type _itor(integer_type value) { // integer to real
	return static_cast<real_type>(value);
}

inline integer_type _rtoi(real_type value) { // real to integer
	return static_cast<integer_type>(value);
}

inline integer_type _stoi(const std::string value) { // string to integer
	return static_cast<integer_type>(stoll(value));
}

inline real_type _stor(const std::string value) { // string to real
	return static_cast<real_type>(stold(value));
}

inline std::string _itos(integer_type value) { // integer to string
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

inline std::string _rtos(real_type value) { // real to string
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

using std::unique_ptr;
using std::shared_ptr;

using type = int;

enum STATUSES : type {
	NONE = 0,
	INTEGER = 1,
	REAL = 2,
	VARIABLE = 3,
	INTEGER_VARIABLE = 4,
	REAL_VARIABLE = 5,
	FUNCTION = 6,
	SPECIAL_SYMBOL = 7,
	ERROR = 8,
	OPERATOR = 9
};

const int STATUSES_COUNT = 10;

/* Special Symbols:
	The right bracket ")" is a special characters, which performs the last function
	In fact, left bracket "(" is a function, which takes one number and return it

	The space " " and "`" is a special characters, which serves as a visual text separator.
	When processing data, it is deleted.

	The colon ";" is the end of the string. After it, the line reading will end. You don't
	have to specify it at the end of the line, it is inserted automatically

	The comma "," is a special character that separates the arguments of the function
*/