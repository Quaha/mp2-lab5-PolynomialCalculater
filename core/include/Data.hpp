#pragma once

#include "includes.hpp"

struct Data {
    type data_type = NONE;
    string data;

    Data() {};
    Data(type data_type, string data): data_type(data_type), data(data) {}

    type getType() const;
    string getData() const;
};

Data convertToValue(Data data);