#include <gtest/gtest.h>

#include "includes.hpp"

#include "PrefixTree.hpp"

TEST(PrefixTree, addAndGetData) {
    PrefixTree<string> tree;

    tree.insert("apple", "A fruit");
    tree.insert("banana", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("banana"), "Another fruit");
}

TEST(PrefixTree, wordExists) {
    PrefixTree<string> tree;

    tree.insert("apple", "A fruit");

    EXPECT_TRUE(tree.isExist("apple"));
    EXPECT_FALSE(tree.isExist("banana"));
}

TEST(PrefixTree, nonExistentWordThrowsException) {
    PrefixTree<string> tree;

    tree.insert("apple", "A fruit");

    ASSERT_ANY_THROW(tree.getData("banana"));
}

TEST(PrefixTree, emptyWord) {
    PrefixTree<string> tree;
    tree.insert("", "An empty word");

    EXPECT_EQ(tree.getData(""), "An empty word");
}

TEST(PrefixTree, insertsAndCheckOrder) {
    PrefixTree<int> tree;

    tree.insert("apple", 1);
    tree.insert("banana", 2);

    EXPECT_EQ(tree.getData("apple"), 1);
    EXPECT_EQ(tree.getData("banana"), 2);
}

TEST(PrefixTree, LongChainOfWords) {
    PrefixTree<string> tree;
    tree.insert("thisisaverylongword", "A very long word");

    EXPECT_EQ(tree.getData("thisisaverylongword"), "A very long word");
}

TEST(PrefixTree, handleMultipleWordsWithCommonPrefix) {
    PrefixTree<string> tree;
    tree.insert("apple", "A fruit");
    tree.insert("apricot", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("apricot"), "Another fruit");
}

TEST(PrefixTree, handleNestedWords) {
    PrefixTree<string> tree;
    tree.insert("hello", "A greeting");
    tree.insert("hell", "A word meaning underworld");

    EXPECT_EQ(tree.getData("hello"), "A greeting");
    EXPECT_EQ(tree.getData("hell"), "A word meaning underworld");
}