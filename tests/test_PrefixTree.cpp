#include <gtest/gtest.h>

#include "includes.hpp"

#include "PrefixTree.hpp"

TEST(PrefixTree, addAndGetData) {
    PrefixTree<string, string, char> tree;

    tree.setWord("apple", "A fruit");
    tree.setWord("banana", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("banana"), "Another fruit");
}

TEST(PrefixTree, wordExists) {
    PrefixTree<string, string, char> tree;

    tree.setWord("apple", "A fruit");

    EXPECT_TRUE(tree.exists("apple"));
    EXPECT_FALSE(tree.exists("banana"));
}

TEST(PrefixTree, nonExistentWordThrowsException) {
    PrefixTree<string, string, char> tree;

    tree.setWord("apple", "A fruit");

    ASSERT_ANY_THROW(tree.getData("banana"));
}

TEST(PrefixTree, emptyWord) {
    PrefixTree<string, string, char> tree;
    tree.setWord("", "An empty word");

    EXPECT_EQ(tree.getData(""), "An empty word");
}

TEST(PrefixTree, setWordsAndCheckOrder) {
    PrefixTree<int, string, char> tree;

    tree.setWord("apple", 1);
    tree.setWord("banana", 2);

    EXPECT_EQ(tree.getData("apple"), 1);
    EXPECT_EQ(tree.getData("banana"), 2);
}

TEST(PrefixTree, LongChainOfWords) {
    PrefixTree<string, string, char> tree;
    tree.setWord("thisisaverylongword", "A very long word");

    EXPECT_EQ(tree.getData("thisisaverylongword"), "A very long word");
}

TEST(PrefixTree, handleMultipleWordsWithCommonPrefix) {
    PrefixTree<string, string, char> tree;
    tree.setWord("apple", "A fruit");
    tree.setWord("apricot", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("apricot"), "Another fruit");
}

TEST(PrefixTree, handleNestedWords) {
    PrefixTree<string, string, char> tree;
    tree.setWord("hello", "A greeting");
    tree.setWord("hell", "A word meaning underworld");

    EXPECT_EQ(tree.getData("hello"), "A greeting");
    EXPECT_EQ(tree.getData("hell"), "A word meaning underworld");
}