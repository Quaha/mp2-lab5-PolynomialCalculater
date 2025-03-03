#include "Monom.hpp"

#include <iostream>
#include <cmath>

Monom::Monom(long double c, unsigned int x, unsigned int y, unsigned int z) {
	coefficient = c;
	x_degree = x;
	y_degree = y;
	z_degree = z;
}

Monom Monom::operator+(const Monom& other) const {
	if (this->x_degree != other.x_degree || this->y_degree != other.y_degree || this->z_degree != other.z_degree) {
		throw std::runtime_error("It is not allowed to add monomials with different degrees!");
	}

	long double new_c = this->coefficient + other.coefficient;
	unsigned int new_x = this->x_degree;
	unsigned int new_y = this->y_degree;
	unsigned int new_z = this->z_degree;

	return Monom(new_c, new_x, new_y, new_z);
}

Monom& Monom::operator+=(const Monom& other) {
	if (this->x_degree != other.x_degree || this->y_degree != other.y_degree || this->z_degree != other.z_degree) {
		throw std::runtime_error("It is not allowed to add monomials with different degrees!");
	}

	this->coefficient += other.coefficient;
	return *this;
}

Monom Monom::operator+() const {
	return (*this);
}

Monom Monom::operator-(const Monom& other) const {
	if (this->x_degree != other.x_degree || this->y_degree != other.y_degree || this->z_degree != other.z_degree) {
		throw std::runtime_error("It is not allowed to add monomials with different degrees!");
	}

	long double new_c = this->coefficient - other.coefficient;
	unsigned int new_x = this->x_degree;
	unsigned int new_y = this->y_degree;
	unsigned int new_z = this->z_degree;

	return Monom(new_c, new_x, new_y, new_z);
}

Monom& Monom::operator-=(const Monom& other) {
	if (this->x_degree != other.x_degree || this->y_degree != other.y_degree || this->z_degree != other.z_degree) {
		throw std::runtime_error("It is not allowed to add monomials with different degrees!");
	}

	this->coefficient -= other.coefficient;
	return *this;
}

Monom Monom::operator-() const {
	Monom result = *this;
	result.coefficient = -result.coefficient;
	return result;
}

Monom Monom::operator*(const Monom& other) const {
	long double new_c = this->coefficient * other.coefficient;
	unsigned int new_x = this->x_degree + other.x_degree;
	unsigned int new_y = this->y_degree + other.y_degree;
	unsigned int new_z = this->z_degree + +other.z_degree;

	return Monom(new_c, new_x, new_y, new_z);
}

Monom& Monom::operator*=(const Monom& other) {
	this->coefficient *= other.coefficient;
	this->x_degree += other.x_degree;
	this->y_degree += other.y_degree;
	this->z_degree += other.z_degree;

	return *this;
}

Monom Monom::operator/(const Monom& other) const {
	if (!this->canBeDivided(other)) {
		throw std::invalid_argument("Monom is not divisible by the divisor!");
	}

	return Monom(
		this->coefficient / other.coefficient,
		this->x_degree - other.x_degree,
		this->y_degree - other.y_degree,
		this->z_degree - other.z_degree
	);
}

Monom& Monom::operator/=(const Monom& other) {
	if (!this->canBeDivided(other)) {
		throw std::invalid_argument("Monom is not divisible by the divisor!");
	}

	this->coefficient /= other.coefficient;
	this->x_degree /= other.x_degree;
	this->y_degree /= other.y_degree;
	this->z_degree /= other.z_degree;

	return *this;
}

Monom Monom::operator*(long double c) const {
	Monom result = *this;
	result.coefficient *= c;

	return result;
}

Monom& Monom::operator*=(long double c) {
	this->coefficient *= c;

	return *this;
}

Monom operator*(long double c, const Monom& mon) {
	return mon * c;
}

bool Monom::operator==(const Monom& other) const {
	if (this->x_degree != other.x_degree) {
		return false;
	}
	if (this->y_degree != other.y_degree) {
		return false;
	}
	if (this->z_degree != other.z_degree) {
		return false;
	}
	if (std::abs(this->coefficient - other.coefficient) >= Monom::EPS) {
		return false;
	}
	return true;
}

bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}

bool  Monom::operator<(const Monom& other) const {
	if (this->x_degree == other.x_degree) {
		if (this->y_degree == other.y_degree) {
			if (this->z_degree == other.z_degree) {
				if (std::abs(this->coefficient - other.coefficient) < Monom::EPS) {
					return false;
				}
				return this->coefficient < other.coefficient;
			}
			return this->z_degree < other.z_degree;
		}
		return this->y_degree < other.y_degree;
	}
	return this->x_degree < other.x_degree;
}

bool Monom::operator>(const Monom& other) const {
	return other < *this;
}

bool Monom::operator<=(const Monom& other) const {
	return (*this < other) || (*this == other);
}

bool Monom::operator>=(const Monom& other) const {
	return (*this > other) || (*this == other);
}

bool Monom::canBeAdded(const Monom& other) const {
	return this->x_degree == other.x_degree && this->y_degree == other.y_degree && this->z_degree == other.z_degree;
}

bool Monom::canBeDivided(const Monom& other) const {
	return std::abs(other.coefficient) > EPS && this->x_degree >= other.x_degree && this->y_degree >= other.y_degree && this->z_degree >= other.z_degree;
}

long double Monom::getCoefficient() const {
	return this->coefficient;
}

unsigned int Monom::getXDegree() const {
	return this->x_degree;
}

unsigned int Monom::getYDegree() const {
	return this->y_degree;
}

unsigned int Monom::getZDegree() const {
	return this->z_degree;
}

void Monom::setCoefficient(long double c) {
	this->coefficient = c;
}

void Monom::setXDegree(unsigned int x) {
	this->x_degree = x;
}

void Monom::setYDegree(unsigned int y) {
	this->y_degree = y;
}

void Monom::setZDegree(unsigned int z) {
	this->z_degree = z;
}

long double Monom::calculate(long double x, long double y, long double z) const {
	return coefficient * pow(x, x_degree) * pow(y, y_degree) * pow(z, z_degree);
}

long double Monom::getEPS() {
	return Monom::EPS;
}