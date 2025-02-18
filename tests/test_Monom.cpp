#include <gtest/gtest.h>

#include "Monom.hpp"

TEST(Monom, DefaultConstructor) {
    Monom m;

    EXPECT_DOUBLE_EQ(m.getCoefficient(), 0.0);
    EXPECT_EQ(m.getXDegree(), 0);
    EXPECT_EQ(m.getYDegree(), 0);
    EXPECT_EQ(m.getZDegree(), 0);
}

TEST(Monom, ParameterizedConstructor) {
    Monom m(2.5, 1, 2, 3);

    EXPECT_DOUBLE_EQ(m.getCoefficient(), 2.5);
    EXPECT_EQ(m.getXDegree(), 1);
    EXPECT_EQ(m.getYDegree(), 2);
    EXPECT_EQ(m.getZDegree(), 3);
}

TEST(Monom, Addition) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 1, 2, 3);
    Monom result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.getCoefficient(), 4.0);
    EXPECT_EQ(result.getXDegree(), 1);
    EXPECT_EQ(result.getYDegree(), 2);
    EXPECT_EQ(result.getZDegree(), 3);
}

TEST(Monom, AdditionWithError) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 5, 2, 3);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(Monom, Subtraction) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 1, 2, 3);
    Monom result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.getCoefficient(), 1.0);
    EXPECT_EQ(result.getXDegree(), 1);
    EXPECT_EQ(result.getYDegree(), 2);
    EXPECT_EQ(result.getZDegree(), 3);
}

TEST(Monom, SubtractionWithError) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 5, 2, 3);

    ASSERT_ANY_THROW(m1 - m2);
}

TEST(Monom, Multiplication) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(3.0, 4, 5, 6);
    Monom result = m1 * m2;

    EXPECT_DOUBLE_EQ(result.getCoefficient(), 6.0);
    EXPECT_EQ(result.getXDegree(), 5);
    EXPECT_EQ(result.getYDegree(), 7);
    EXPECT_EQ(result.getZDegree(), 9);
}

TEST(Monom, AdditionAssignment) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 1, 2, 3);
    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.getCoefficient(), 4.0);
    EXPECT_EQ(m1.getXDegree(), 1);
    EXPECT_EQ(m1.getYDegree(), 2);
    EXPECT_EQ(m1.getZDegree(), 3);
}

TEST(Monom, AdditionAssignmentWithError) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 5, 2, 3);

    ASSERT_ANY_THROW(m1 += m2);
}

TEST(Monom, SubtractionAssignment) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 1, 2, 3);
    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.getCoefficient(), 1.0);
    EXPECT_EQ(m1.getXDegree(), 1);
    EXPECT_EQ(m1.getYDegree(), 2);
    EXPECT_EQ(m1.getZDegree(), 3);
}

TEST(Monom, SubtractionAssignmentWithError) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 5, 2, 3);

    ASSERT_ANY_THROW(m1 -= m2);
}

TEST(Monom, MultiplicationAssignment) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(3.0, 4, 5, 6);
    m1 *= m2;

    EXPECT_DOUBLE_EQ(m1.getCoefficient(), 6.0);
    EXPECT_EQ(m1.getXDegree(), 5);
    EXPECT_EQ(m1.getYDegree(), 7);
    EXPECT_EQ(m1.getZDegree(), 9);
}

TEST(Monom, Equality) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(2.5, 1, 2, 3);

    EXPECT_TRUE(m1 == m2);
}

TEST(Monom, Inequality) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(1.5, 1, 2, 3);

    EXPECT_TRUE(m1 != m2);
}

TEST(Monom, LessThan) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.5, 1, 2, 3);

    EXPECT_TRUE(m1 < m2);
}

TEST(Monom, GreaterThan) {
    Monom m1(3.5, 1, 2, 3);
    Monom m2(2.5, 1, 2, 3);

    EXPECT_TRUE(m1 > m2);
}

TEST(Monom, LessThanOrEqual) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(2.5, 1, 2, 3);

    EXPECT_TRUE(m1 <= m2);
}

TEST(Monom, GreaterThanOrEqual) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(2.5, 1, 2, 3);

    EXPECT_TRUE(m1 >= m2);
}

TEST(Monom, CanBeAdded) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);

    EXPECT_EQ(m1.canBeAdded(m2), 1);
}

TEST(Monom, CantBeAdded) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(3.0, 4, 5, 6);

    EXPECT_EQ(m1.canBeAdded(m2), 0);
}

TEST(Monom, Calculate) {
    Monom m1(2.0, 1, 2, 3);

    EXPECT_DOUBLE_EQ(m1.calculate(1, 1, 1), 2.0);
    EXPECT_DOUBLE_EQ(m1.calculate(2, 3, 4), 2.0 * 2 * 9 * 64);
    EXPECT_DOUBLE_EQ(m1.calculate(0, 5, 10), 0.0);
    EXPECT_DOUBLE_EQ(m1.calculate(-1, 2, 3), 2.0 * (-1) * 4 * 27);
    EXPECT_DOUBLE_EQ(m1.calculate(1.5, 2.5, 3.5), 2.0 * 1.5 * 6.25 * 42.875);
}

TEST(Monom, CalculateWithZeroCoefficient) {
    Monom m2(0.0, 1, 2, 3);

    EXPECT_DOUBLE_EQ(m2.calculate(1, 1, 1), 0.0);
    EXPECT_DOUBLE_EQ(m2.calculate(2, 3, 4), 0.0);
    EXPECT_DOUBLE_EQ(m2.calculate(-1, 5, 10), 0.0);
}

TEST(Monom, CalculateWithZeroDegrees) {
    Monom m3(3.0, 0, 0, 0);

    EXPECT_DOUBLE_EQ(m3.calculate(1, 1, 1), 3.0);
    EXPECT_DOUBLE_EQ(m3.calculate(2, 3, 4), 3.0);
    EXPECT_DOUBLE_EQ(m3.calculate(-1, 5, 10), 3.0);
}
