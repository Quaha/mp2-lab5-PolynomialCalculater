#pragma once

class Monom {
private:

	double coefficient = 0;
	unsigned int x_degree = 0, y_degree = 0, z_degree = 0;

	static inline const double EPS = 1e-7;

public:

	Monom() = default;

	Monom(double c, unsigned int x, unsigned int y, unsigned int z);

	~Monom() = default;

	Monom(const Monom&) = default;
	Monom& operator=(const Monom&) = default;

	Monom(Monom&&) = default;
	Monom& operator=(Monom&&) = default;

	Monom operator+(const Monom&) const;
	Monom& operator+=(const Monom&);

	Monom operator+() const;

	Monom operator-(const Monom&) const;
	Monom& operator-=(const Monom&);

	Monom operator-() const;

	Monom operator*(const Monom&) const;
	Monom& operator*=(const Monom&);

	Monom operator/(const Monom&) const;
	Monom& operator/=(const Monom&);

	Monom operator*(double) const;
	Monom& operator*=(double);

	//The comparison of monomials takes place first by degree x, then by y, then by z, then by coefficient
	bool operator==(const Monom&) const;
	bool operator!=(const Monom&) const;
	bool operator<(const Monom&) const;
	bool operator>(const Monom&) const;
	bool operator<=(const Monom&) const;
	bool operator>=(const Monom&) const;

	bool canBeAdded(const Monom&) const;
	bool canBeDivided(const Monom&) const;

	double getCoefficient() const;
	unsigned int getXDegree() const;
	unsigned int getYDegree() const;
	unsigned int getZDegree() const;

	void setCoefficient(double c);
	void setXDegree(unsigned int x);
	void setYDegree(unsigned int y);
	void setZDegree(unsigned int z);

	double calculate(double x, double y, double z) const;

	static double getEPS();
};

Monom operator*(double, const Monom&);