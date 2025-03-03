#include <gtest/gtest.h>

#include "includes.hpp"

#include "Interpreter.hpp"

TEST(Interpreter, SimpleSum) {

    string line = "1+1";
    string result = "2";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, SimpleSubtraction) {

    string line = "1-1";
    string result = "0";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, SimpleMultiplication) {

    string line = "1*1";
    string result = "1";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, UnaryMinus) {

    string line = "-1";
    string result = "-1";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, SimpleOperations) {

    string line = "2+2*4";
    string result = "10";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationsWithZero) {

    string line = "0-0+0";
    string result = "0";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets1) {
    string line = "((2 * 7) - (1 + 5))";
    string result = "8";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets2) {
    string line = "((3 * 5) + (6 - 9))";
    string result = "12";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets3) {
    string line = "((3 + 7) - (6 * 5))";
    string result = "-20";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets4) {
    string line = "((9 - 8) * (5 + 1))";
    string result = "6";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets5) {
    string line = "((10 + 9) - ((10) - 4))";
    string result = "13";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets6) {
    string line = "((2 + 4) + (8 - 4))";
    string result = "10";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, OperationWithBrackets7) {
    string line = "(1.0/2+2)*3-1*(2-3*4)+1";
    string result = "18.5";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

// Polynomial tests

TEST(Interpreter, PolynomialInterpretator1) {
    string expression = "x^0y^0z^0";
    string x = "1";
    string y = "1";
    string z = "1";
    string result = "1";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator2) {
    string expression = "x^0y^0z^0";
    string x = "0";
    string y = "0";
    string z = "0";
    string result = "1";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator3) {
    string expression = "x^4y^3z^1";
    string x = "4";
    string y = "5";
    string z = "0";
    string result = "0";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator4) {
    string expression = "x^1y^1z^1 + x^2y^2z^2";
    string x = "2";
    string y = "3";
    string z = "4";
    string result = "600";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator5) {
    string expression = "5.0 * x^1y^1z^1";
    string x = "1";
    string y = "1";
    string z = "1";
    string result = "5";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator6) {
    string expression = "5.0 * x^1y^1z^1 + 10.0";
    string x = "1";
    string y = "1";
    string z = "1";
    string result = "15";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator7) {
    string expression = "2.5 * x^10y^2z^3";
    string x = "2";
    string y = "3";
    string z = "9";
    string result = "16796160";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator8) {
    string expression = "(2.5 * x^10y^2z^3 + 8.0) / 2.0";
    string x = "2";
    string y = "3";
    string z = "9";
    string result = "8398084";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator9) {
    string expression = "(2.5 * x^10y^2z^3 + 8.0) / 2.0 - (2.5 * x^10y^2z^3 + 8.0) / 2.0";
    string x = "2";
    string y = "3";
    string z = "9";
    string result = "0";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator10) {
    string expression = "10.0 * x^2y^2z^2 / 4.0";
    string x = "2";
    string y = "2";
    string z = "2";
    string result = "160";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretato11) {
    string expression = "7.8 * x^3y^1z^0 + 7.9 * x^5y^1z^3";
    string x = "3";
    string y = "2";
    string z = "1";
    string result = "4260.6";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator12) {
    string expression = "2.0 * 3.9 * x^3y^1z^0 + 7.9 * x^5y^1z^3 + ((2.5 * x^10y^2z^3 + 8.0) / 2.0 - (2.5 * x^10y^2z^3 + 8.0) / 2.0)";
    string x = "3";
    string y = "2";
    string z = "1";
    string result = "4260";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator13) {
    string expression = "(2.5 * x^1y^2z^3) * (2 * x^3y^2z^0)";
    string x = "3";
    string y = "2";
    string z = "4";
    string result = "414720";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator14) {
    string expression = "(2.5 * x^1y^2z^3) * (2 * x^3y^2z^0) / 10.0";
    string x = "3";
    string y = "2";
    string z = "4";
    string result = "41472";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator15) {
    string expression = "2.5 * x^1y^2z^3 * 0.0";
    string x = "3";
    string y = "2";
    string z = "4";
    string result = "0";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator16) {
    string expression = "0.1 * x^2y^2z^4";
    string x = "3.3";
    string y = "0.8";
    string z = "4";
    string result = "178.42176";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator17) {
    string expression = "-178.42176 + 0.1 * x^2y^2z^4";
    string x = "3.3";
    string y = "0.8";
    string z = "4";
    string result = "0";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator18) {
    string expression = "10.2 * x^6y^7z^1";
    string x = "7";
    string y = "8";
    string z = "9";
    string result = "22649615312486.4";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator19) {
    string expression = "2.0 * x^10y^10z^10";
    string x = "2";
    string y = "2";
    string z = "2";
    string result = "2147483648";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}

TEST(Interpreter, PolynomialInterpretator20) {
    string expression = "(1.0/2+2)*3-1*(2-3*4)+x^5y^9z^7";
    string x = "1";
    string y = "1";
    string z = "1";
    string result = "18.5";

    string line = "calcValue(" + expression + ", " + x + ", " + y + ", " + z + ")";

    Interpreter program;
    Data temp = program.execute(line);

    EXPECT_EQ(temp.getData(), result);
}
