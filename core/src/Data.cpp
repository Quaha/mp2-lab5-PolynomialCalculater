#include "includes.hpp"

#include "Data.hpp"
#include "ProgramMemory.hpp"

type Data::getType() const {
    return data_type;
}

string Data::getData() const {
    return data;
}

void Data::makeInteger() {
    if (data_type == INTEGER || data_type == REAL) {
        data = _itos(_stoi(data));
    }
    else {
        throw std::logic_error("ERROR: this type is not a number!");
    }
}

void Data::makeReal() {
    if (data_type == INTEGER || data_type == REAL) {
        data = _rtos(_stor(data));
    }
    else {
        throw std::logic_error("ERROR: this type is not a number!");
    }
}

Data convertToValue(Data data) {
    if (data.getType() == INTEGER || data.getType() == REAL) {
        return data;
    }
    else if (data.getType() == INTEGER_VARIABLE || data.getType() == REAL_VARIABLE) {
        data = global_memory->program_data.getData(data.getData());
        return data;
    }
    else {
        throw std::logic_error("ERROR: incorrect type!");
    }
}

Data convertToInteger(Data data) {
    data = convertToValue(data);
    if (data.getType() == REAL) {
        data.data_type = INTEGER;
        data.data = _itos(_stoi(data.getData()));
    }
    return data;
}

Data convertToReal(Data data) {
    data = convertToValue(data);
    if (data.getType() == INTEGER) {
        data.data_type = REAL;
        data.data = _rtos(_stor(data.getData()));
    }
    return data;
}