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

	Polynomial operator*(long double) const;
	Polynomial& operator*=(long double);

	Polynomial operator/(const Monom&) const;
	Polynomial& operator/=(const Monom&);

	Polynomial operator%(const Monom&) const;
	Polynomial& operator%=(const Monom&);

	Polynomial operator/(long double) const;
	Polynomial& operator/=(long double);

	long double calculate(long double x, long double y, long double z) const;

	List<Monom> getMonoms() const;
};

Polynomial operator*(long double, const Polynomial&);
Polynomial operator*(const Monom&, const Polynomial&);