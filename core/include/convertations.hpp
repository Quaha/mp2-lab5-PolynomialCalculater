#pragma once

#include "includes.hpp"
#include "Automat.hpp"

inline real_type _stor(const std::string value) { // string to real
	return static_cast<real_type>(stold(value));
}

inline Monom _stom(const std::string value) { // string to Monom
	int x_pos = -1;
	int y_pos = -1;
	int z_pos = -1;

	while (x_pos != 'x' && x_pos < value.size()) {
		x_pos++;
	}
	while (y_pos != 'y' && y_pos < value.size()) {
		y_pos++;
	}
	while (z_pos != 'z' && z_pos < value.size()) {
		z_pos++;
	}

	real_type coef = 1;
	if (x_pos != 1) {
		coef = _stor(value.substr(0, x_pos - 1));
	}

	long long x_deg = 0, y_deg = 0, z_deg = 0;
	x_deg = std::stoll(value.substr(x_pos + 2, y_pos - x_pos - 2));
	y_deg = std::stoll(value.substr(y_pos + 2, z_pos - y_pos - 2));
	z_deg = std::stoll(value.substr(z_pos + 2, value.size() - z_pos - 2));
	return Monom(coef, x_deg, y_deg, z_deg);
}

inline polynomial_type _stop(const std::string value) { // string to Polynom

	string temp = "";
	temp.push_back(value[0]);

	polynomial_type result;
	for (int i = 1; i < value.size(); i++) {
		if (value[i] == '+' || value[i] == '-') {
			result += _stom(temp);
			temp.clear();
			temp.push_back(value[i]);
		}
	}
	result += _stom(temp);
	return result;
}

inline polynomial_type _rtop(const real_type value) { // real to Polynom
	return Polynomial(Monom(value, 0, 0, 0));
}

inline std::string _rtos(real_type value) { // real to string
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

inline std::string _ptos(polynomial_type value) { // Polynomial to string
	std::ostringstream oss;
	for (auto Monom : value.getMonoms()) {
		oss << Monom.getCoefficient() << "*" << Monom.getXDegree() << Monom.getYDegree() << Monom.getZDegree();
	}
	return oss.str();
}
