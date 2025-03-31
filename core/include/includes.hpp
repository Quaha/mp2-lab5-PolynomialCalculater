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
#include <utility>

// containers
#include "UnorderedTable.hpp"
#include "OrderedTable.hpp"
#include "RedBlackTree.hpp"
#include "AVLTree.hpp"

using std::vector;
using std::string;
using std::map;
using std::set;

class Polynomial;

using real_type = long double;

using std::unique_ptr;
using std::shared_ptr;

using type = int;

enum STATUSES : type {
	NONE = 0,
	REAL = 1,
	VARIABLE = 2,
	POLYNOMIAL_VARIABLE = 3,
	REAL_VARIABLE = 4,
	FUNCTION = 5,
	SPECIAL_SYMBOL = 6,
	ERROR = 7,
	OPERATOR = 8,
	POLYNOMIAL = 9,
	INTEGER = 10
};

const int STATUSES_COUNT = 11;

/* Special Symbols:
	The right bracket ")" is a special characters, which performs the last function
	In fact, left bracket "(" is a function, which takes one number and return it

	The space " " and "`" is a special characters, which serves as a visual text separator.
	When processing data, it is deleted.

	The colon ";" is the end of the string. After it, the line reading will end. You don't
	have to specify it at the end of the line, it is inserted automatically

	The comma "," is a special character that separates the arguments of the function
*/