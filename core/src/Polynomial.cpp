#include "Polynomial.hpp"
#include "Monom.hpp"

#include <cmath>

void Polynomial::rebalance() {
	List<Monom>::Iterator iter = polynomial.begin();
	while (iter + 1 != polynomial.end()) {
		if (iter->canBeAdded(*(iter + 1))) {
			*iter += *(iter + 1);
			polynomial.erase(iter + 1);
		}
		else {
			++iter;
		}
	}
}

void Polynomial::insertMonom(const Monom& mon) {
	List<Monom>::Iterator iter = polynomial.begin();

	while (iter != polynomial.end() && !mon.canBeAdded(*iter) && mon <= *iter) {
		++iter;
	}

	polynomial.insert_before(mon, iter);
}

Polynomial::Polynomial() {
	polynomial.push_back({ 0.0, 0, 0, 0 });
}

Polynomial::Polynomial(const Monom& mon) {
	polynomial.push_back({ 0.0, 0, 0, 0 });
	this->insertMonom(mon);
	this->rebalance();	
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
	Polynomial result;
	
	result.polynomial.erase(result.polynomial.begin());

	auto it1 = this->polynomial.begin();
	auto it2 = other.polynomial.begin();

	while (it1 != this->polynomial.end() && it2 != other.polynomial.end()) {
		if (it1->canBeAdded(*it2)) {
			Monom temp = *it1 + *it2;
			result.polynomial.insert_before(temp, result.polynomial.end());
			++it1;
			++it2;
		}
		else if (*it1 < *it2) {
			result.polynomial.insert_before(*it2, result.polynomial.end());
			++it2;
		}
		else {
			result.polynomial.insert_before(*it1, result.polynomial.end());
			++it1;
		}
	}

	while (it1 != this->polynomial.end()) {
		result.polynomial.insert_before(*it1, result.polynomial.end());
		++it1;
	}

	while (it2 != other.polynomial.end()) {
		result.polynomial.insert_before(*it2, result.polynomial.end());
		++it2;
	}


	return result;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
	for (const Monom& mon : other.polynomial) {
		this->insertMonom(mon);
	}
	this->rebalance();
	
	return *this;
}

Polynomial Polynomial::operator+() const {
	return *this;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
	return *this + (-other);
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
	return *this += (-other);
}

Polynomial Polynomial::operator-() const {
	Polynomial result = *this;
	for (Monom& mon : result.polynomial) {
		mon = -mon;
	}
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
	Polynomial result;
	for (const Monom& mon : other.polynomial) {
		result += *this * mon;
	}
	return result;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
	*this = *this * other;
	return *this;
}

Polynomial Polynomial::operator*(const Monom& mon) const {
	Polynomial result = *this;
	for (Monom& rmon : result.polynomial) {
		rmon *= mon;
	}
	return result;
}

Polynomial& Polynomial::operator*=(const Monom& mon) {
	*this = *this * mon;
	return *this;
}

Polynomial Polynomial::operator*(double c) const {
	Polynomial result = *this;
	for (Monom& mon : result.polynomial) {
		mon.setCoefficient(mon.getCoefficient() * c);
	}
	return result;
}

Polynomial& Polynomial::operator*=(double c) {
	for (Monom& mon : this->polynomial) {
		mon.setCoefficient(mon.getCoefficient() * c);
	}
	return *this;
}

Polynomial Polynomial::operator/(const Monom& mon) const {
	Polynomial result;
	for (const Monom& pmon : polynomial) {
		if (pmon.canBeDivided(mon)) {
			result += pmon / mon;
		}
	}
	return result;
}

Polynomial& Polynomial::operator/=(const Monom& mon) {
	*this = *this / mon;
	return *this;
}

Polynomial Polynomial::operator%(const Monom& mon) const {
	Polynomial result;
	for (const Monom& pmon : polynomial) {
		if (!pmon.canBeDivided(mon)) {
			result += pmon;
		}
	}
	return result;
}

Polynomial& Polynomial::operator%=(const Monom& mon) {
	*this = *this % mon;
	return *this;
}

Polynomial Polynomial::operator/(double c) const {
	if (std::abs(c) < Monom::getEPS()) {
		throw std::invalid_argument("It is not allowed to divide by 0!");
	}
	Polynomial result = *this;
	for (Monom& mon : result.polynomial) {
		mon.setCoefficient(mon.getCoefficient() / c);
	}
	return result;
}

Polynomial& Polynomial::operator/=(double c) {
	if (std::abs(c) < Monom::getEPS()) {
		throw std::invalid_argument("It is not allowed to divide by 0!");
	}
	for (Monom& mon : this->polynomial) {
		mon.setCoefficient(mon.getCoefficient() / c);
	}
	return *this;
}

double Polynomial::calculate(double x, double y, double z) const {
	double result = 0;
	for (const Monom& mon : this->polynomial) {
		result += mon.calculate(x, y, z);
	}
	return result;
}

Polynomial operator*(double c, const Polynomial& pol) {
	return pol * c;
}

Polynomial operator*(const Monom& mon, const Polynomial& pol) {
	return pol * mon;
}