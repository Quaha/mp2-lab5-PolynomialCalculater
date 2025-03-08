#include "includes.hpp"

#include "functions.hpp"
#include "Data.hpp"
#include "ProgramMemory.hpp"
#include "convertations.hpp"

vector<Data> getValues(const vector<Data>& parameters, int start_pos = 0) {

    vector<Data> values(std::max((int)parameters.size() - start_pos, 0));

    for (int j = start_pos; j < parameters.size(); j++) {
        int i = j - start_pos;
        values[i] = convertToValue(parameters[j]);
    }

    return values;
}

Data __LEFT__BRACKET__OPERATOR__(const vector<Data>& parameters) {

	if (parameters.size() != 1) {
		throw std::invalid_argument("ERROR: invalid number of arguments!");
	}

    vector<Data> values = getValues(parameters);
    return values[0];
}

Data __PLUS__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() == 0 || parameters.size() > 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (parameters.size() == 1) {
        return values[0];
    }

    Data result;

    if (values[0].getType() == REAL && values[1].getType() == REAL) {
        result.data_type = REAL;
        result.data = _rtos(_stor(values[0].getData()) + _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) + _stop(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == REAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) + Polynomial(Monom(_stor(values[1].getData()), 0, 0, 0)));
        return result;
    }
    if (values[0].getType() == REAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(Polynomial(Monom(_stor(values[0].getData()), 0, 0, 0)) + _stop(values[1].getData()));
        return result;
    }

    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __MINUS__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() == 0 || parameters.size() > 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (parameters.size() == 1) {
        if (values[0].getType() == REAL) {
            values[0].data = _rtos(-_stor(values[0].data));
        }
        else {
            Polynomial p = _stop(values[0].data);
            p = -p;
            values[0].data = _ptos(p);
        }
        return values[0];
    }

    Data result;

    if (values[0].getType() == REAL && values[1].getType() == REAL) {
        result.data_type = REAL;
        result.data = _rtos(_stor(values[0].getData()) - _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) - _stop(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == REAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) - Polynomial(Monom(_stor(values[1].getData()), 0, 0, 0)));
        return result;
    }
    if (values[0].getType() == REAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(Polynomial(Monom(_stor(values[0].getData()), 0, 0, 0)) - _stop(values[1].getData()));
        return result;
    }

    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __MULTIPLY__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    Data result;

    if (values[0].getType() == REAL && values[1].getType() == REAL) {
        result.data_type = REAL;
        result.data = _rtos(_stor(values[0].getData()) * _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) * _stop(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == REAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) *(_stor(values[1].getData())));
        return result;
    }
    if (values[0].getType() == REAL && values[1].getType() == POLYNOMIAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(Polynomial(Monom(_stor(values[0].getData()), 0, 0, 0)) * _stop(values[1].getData()));
        return result;
    }

    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __DIVISION__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    Data result;

    if (values[0].getType() == REAL && values[1].getType() == REAL) {
        result.data_type = REAL;
        result.data = _rtos(_stor(values[0].getData()) / _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == POLYNOMIAL) {
        throw std::invalid_argument("ERROR:it is forbidden to divide a polynomial into a polynomial!");
    }
    if (values[0].getType() == POLYNOMIAL && values[1].getType() == REAL) {
        result.data_type = POLYNOMIAL;
        result.data = _ptos(_stop(values[0].getData()) / _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == REAL && values[1].getType() == POLYNOMIAL) {
        throw std::invalid_argument("ERROR:it is forbidden to divide a real number into a polynomial!");
    }

    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __EQUAL__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters, 1);

    string name = parameters[0].getData();
    if (parameters[0].getType() != VARIABLE && parameters[0].getType() != REAL_VARIABLE && parameters[0].getType() != POLYNOMIAL_VARIABLE) {
        throw std::invalid_argument("ERROR: value can only be assigned to a variable!");
    }

    global_memory->program_data.insert(name, values[0]);

    return values[0];
}

Data sum(const vector<Data>& parameters) {
    if (parameters.size() == 0) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    bool isPoly = false;
    for (int i = 0; i < values.size(); i++) {
        if (values[i].getType() == POLYNOMIAL) {
            isPoly = true;
        }
    }

    if (!isPoly) {
        real_type temp = 0;
        for (int i = 0; i < values.size(); i++) {
            temp += _stor(values[i].getData());
        }

        Data result;
        result.data_type = REAL;
        result.data = _rtos(temp);
        return result;
    }

    Data result;
    if (values[0].getType() == REAL) {
        result.data = _ptos(_rtop(_stor(values[0].getData())));
    }
    else {
        result.data = values[0].data;
    }
    result.data_type = POLYNOMIAL;

    for (int i = 1; i < values.size(); i++) {
        if (values[i].getType() == REAL) {
            result.data = _ptos(_stop(result.data) + _rtop(_stor(values[0].getData())));
        }
        if (values[i].getType() == POLYNOMIAL) {
            result.data = _ptos(_stop(result.data) + _stop(values[i].data));
        }
    }

    return result;
}

Data calcValue(const vector<Data>& parameters) {

    if (parameters.size() == 0) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (values[1].getType() != REAL || values[2].getType() != REAL || values[3].getType() != REAL) {
        throw std::invalid_argument("ERROR: invalid type of arguments!");
    }

    if (values[0].getType() == REAL) {
        return values[0];
    }

    Polynomial p = _stop(values[0].getData());
    real_type xd = _stor(values[1].getData());
    real_type yd = _stor(values[2].getData());
    real_type zd = _stor(values[3].getData());

    real_type res = p.calculate(xd, yd, zd);

    Data result;
    result.data_type = REAL;
    result.data = _rtos(res);
    return result;
}
