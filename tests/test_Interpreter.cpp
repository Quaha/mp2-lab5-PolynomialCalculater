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
