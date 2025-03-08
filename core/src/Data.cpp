#include "includes.hpp"

#include "Data.hpp"
#include "ProgramMemory.hpp"

type Data::getType() const {
    return data_type;
}

string Data::getData() const {
    return data;
}

Data convertToValue(Data data) {
    if (data.getType() == POLYNOMIAL || data.getType() == REAL) {
        return data;
    }
    else if (data.getType() == POLYNOMIAL_VARIABLE || data.getType() == REAL_VARIABLE) {
        data = global_memory->program_data[data.getData()];
        return data;
    }
    else {
        throw std::logic_error("ERROR: incorrect type!");
    }
}