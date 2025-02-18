#pragma once

#include "DoublyLinkedList.hpp"
#include "Monom.hpp"

class Polynomial {
private:

	List<Monom> polynomial;

	void rebalance();
	void insertMonom(const Monom&);

public:

	Polynomial();
	Polynomial(const Monom&);

	~Polynomial() = default;

	Polynomial(const Polynomial&) = default;
	Polynomial& operator=(const Polynomial&) = default;

	Polynomial(Polynomial&&) = default;
	Polynomial& operator=(Polynomial&&) = default;

	Polynomial operator+(const Polynomial&) const;
	Polynomial& operator+=(const Polynomial&);

	Polynomial operator+() const;

	Polynomial operator-(const Polynomial&) const;
	Polynomial& operator-=(const Polynomial&);

	Polynomial operator-() const;

	Polynomial operator*(const Polynomial&) const;
	Polynomial& operator*=(const Polynomial&);

	Polynomial operator*(const Monom&) const;
	Polynomial& operator*=(const Monom&);

	Polynomial operator*(double) const;
	Polynomial& operator*=(double);

	Polynomial operator/(const Monom&) const;
	Polynomial& operator/=(const Monom&);

	Polynomial operator%(const Monom&) const;
	Polynomial& operator%=(const Monom&);

	Polynomial operator/(double) const;
	Polynomial& operator/=(double);

	double calculate(double x, double y, double z) const;
};

Polynomial operator*(double, const Polynomial&);
Polynomial operator*(const Monom&, const Polynomial&);