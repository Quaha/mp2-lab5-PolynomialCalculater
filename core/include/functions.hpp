#pragma once

#include "includes.hpp"

#include "Data.hpp"

Data __LEFT__BRACKET__OPERATOR__(const vector<Data>& parameters);

Data __PLUS__OPERATOR__(const vector<Data>& parameters);

Data __MINUS__OPERATOR__(const vector<Data>& parameters);

Data __MULTIPLY__OPERATOR__(const vector<Data>& parameters);

Data __DIVISION__OPERATOR__(const vector<Data>& parameters);

Data __EQUAL__OPERATOR__(const vector<Data>& parameters);

Data sum(const vector<Data>& parameters);
