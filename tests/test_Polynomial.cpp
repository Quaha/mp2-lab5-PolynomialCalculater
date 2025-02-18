#include <gtest/gtest.h>

#include "Polynomial.hpp"
#include "Monom.hpp"

TEST(Polynomial, DefaultConstructor) {
    Polynomial p;

    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 0.0);
}

TEST(Polynomial, MonomConstructor) {
    Polynomial p({ 2.0, 1, 2, 3 });// 2 x^1 y^2 z^3

    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 2.0 * 1 * 1 * 1);
}

TEST(Polynomial, AdditionOperator1) {
    Polynomial p1({ 2.0, 1, 2, 3 }); // 2 x^1 y^2 z^3
    Polynomial p2({ 3.0, 1, 2, 3 }); // 3 x^1 y^2 z^3
    Polynomial result = p1 + p2;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 2.0 * 1 * 1 * 1 + 3.0 * 1 * 1 * 1);
}
TEST(Polynomial, AdditionOperator2) {
    Polynomial p1({ 2.0, 2, 2, 2 }); // 2 x^2 y^2 z^2
    Polynomial p2({ 3.0, 3, 3, 3 }); // 3 x^3 y^3 z^3
    Polynomial result = p1 + p2;

    EXPECT_DOUBLE_EQ(result.calculate(2, 2, 2), 2.0 * 4 * 4 * 4 + 3.0 * 8 * 8 * 8);
}

TEST(Polynomial, SubtractionOperator1) {
    Polynomial p1({ 5.0, 1, 2, 3 }); // 5 x^1 y^2 z^3
    Polynomial p2({ 3.0, 1, 2, 3 }); // 3 x^1 y^2 z^3
    Polynomial result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 5.0 * 1 * 1 * 1 - 3.0 * 1 * 1 * 1);
}

TEST(Polynomial, SubtractionOperator2) {
    Polynomial p1({ 5.0, 2, 2, 2 }); // 5 x^2 y^2 z^2
    Polynomial p2({ 3.0, 3, 3, 3 }); // 3 x^3 y^3 z^3
    Polynomial result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.calculate(2, 2, 2), 5.0 * 4 * 4 * 4 - 3.0 * 8 * 8 * 8);
}

TEST(Polynomial, UnaryMinusOperator) {
    Polynomial p({ 2.0, 1, 2, 3 }); // 2 x^1 y^2 z^3
    Polynomial result = -p;

    EXPECT_DOUBLE_EQ(result.calculate(1, 3, 1), -2.0 * 1 * 3 * 3 * 1);
}

TEST(Polynomial, ScalarMultiplicationOperator1) {
    Polynomial p({ 2.0, 1, 2, 3 }); // 2 x^1 y^2 z^3
    Polynomial result = p * 3.0;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 2.0 * 3.0);
}

TEST(Polynomial, ScalarMultiplicationOperator2) {
    Polynomial p({ 2.0, 1, 2, 3 }); // 2 x^1 y^2 z^3
    Polynomial result = 3.0 * p;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 2.0 * 3.0);
}

TEST(Polynomial, PolynomialMultiplicationOperator) {
    Polynomial p1({ 2.0, 1, 0, 0 }); // 2 x^1 y^0 z^0
    Polynomial p2({ 3.0, 0, 1, 0 }); // 3 x^0 y^1 z^0
    Polynomial result = p1 * p2;

    EXPECT_DOUBLE_EQ(result.calculate(2, 1, 1), 2.0 * 2 * 3);
}

TEST(Polynomial, MultiplicationPolynomialAndMonom) {
    Monom m1(2.0, 1, 0, 0); // 2 x^1 y^0 z^0
    Monom m2(3.0, 0, 1, 0); // 3 x^0 y^1 z^0
    Polynomial p(m1);
    Polynomial result = p * m2;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 2.0 * 3.0);
}

TEST(Polynomial, Calculate) {
    Monom m1(2.0, 1, 2, 3); // 2 x^1 y^2 z^3
    Monom m2(3.0, 0, 1, 0); // 3 x^0 y^1 z^0
    Polynomial p;
    p += m1;
    p += m2;

    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 2.0 + 3.0);
    EXPECT_DOUBLE_EQ(p.calculate(2, 3, 4), 2.0 * 2 * 9 * 64 + 3.0 * 3);
}

TEST(Polynomial, DivisionByMonom1) {
    Polynomial pol;
    pol += Monom(4.0, 2, 3, 1);  // 4 x^2 y^3 z^1
    pol += Monom(6.0, 1, 2, 0);  // 6 x^1 y^2 z^0

    Monom div(2.0, 1, 2, 0);  // 2 x^1 y^2 z^0

    Polynomial result1 = pol / div; // 2 x^1 y^1 z^1 + 3 x^0 y^0 z^0

    EXPECT_DOUBLE_EQ(result1.calculate(3, 4, 5), 2.0 * 3 * 4 * 5 + 3);
}

TEST(Polynomial, DivisionByMonom2) {
    Polynomial pol;
    pol += Monom(4.0, 2, 3, 1);  // 4 x^2 y^3 z^1
    pol += Monom(6.0, 1, 2, 0);  // 6 x^1 y^2 z^0

    Monom div(2.0, 1, 2, 0);  // 2 x^1 y^2 z^0

    Polynomial result1 = pol % div; // 0

    EXPECT_DOUBLE_EQ(result1.calculate(3, 4, 5), 0.0);
}

TEST(Polynomial, DivisionByNumber1) {
    Polynomial pol;
    pol += Monom(4.0, 2, 3, 1);  // 4 x^2 y^3 z^1

    Polynomial result1 = pol / 2;

    EXPECT_DOUBLE_EQ(result1.calculate(2, 3, 4), 4.0 / 2.0 * 2 * 2 * 3 * 3 * 3 * 4);
}
