#include <gtest/gtest.h>

#include "includes.hpp"


// Fixture
template <class Table>
class TableTest : public ::testing::Test {
protected: 
	Table table;
};

// Tables types (add new tables here)
using TableTypes = ::testing::Types<
	OrderedTable<std::string, double>,
	UnorderedTable<std::string, double>,
	RedBlackTree<std::string, double>,
	AVLTree<std::string, double>,
	HashTableCA<std::string, double>,
	HashTableOA<std::string, double>
>;

TYPED_TEST_SUITE(TableTest, TableTypes);

/* --- Basic tests --- */

TYPED_TEST(TableTest, defaultConstructor) {
	EXPECT_TRUE(this->table.empty()); 
	EXPECT_EQ(this->table.size(), 0); 
}

TYPED_TEST(TableTest, canInsertElement) {
	this->table.insert("key", 10);

	EXPECT_FALSE(this->table.empty());
	EXPECT_EQ(this->table.size(), 1);
}

TYPED_TEST(TableTest, canFindElement) {
	this->table.insert("key", 10);
	auto It = this->table.find("key");
	
	EXPECT_NE(It, this->table.end());
	EXPECT_EQ((*It).second, 10);
}

TYPED_TEST(TableTest, cantFindNonExistingElement) {
	auto It = this->table.find("notAKey");
	
	EXPECT_EQ(It, this->table.end());
}

TYPED_TEST(TableTest, canEraseElement) {
	this->table.insert("key", 10);
	this->table.erase("key");
	
	EXPECT_TRUE(this->table.empty());
	EXPECT_EQ(this->table.size(), 0);
}

TYPED_TEST(TableTest, canAccessElement) {
	this->table.insert("key", 10);
	
	EXPECT_EQ(this->table["key"], 10);
}

TYPED_TEST(TableTest, cantAccessNonExistingElement) {
	EXPECT_ANY_THROW(this->table["notAKey"]);
}

TYPED_TEST(TableTest, canGetSize1) {
	EXPECT_EQ(this->table.size(), 0);
}

TYPED_TEST(TableTest, canGetSize2) {
	this->table.insert("key", 10);

	EXPECT_EQ(this->table.size(), 1);
}

TYPED_TEST(TableTest, canGetSize3) {
	for (int i = 0; i < 10; i++) {
		this->table.insert("key" + std::to_string(i), i);
	}

	EXPECT_EQ(this->table.size(), 10);
}

TYPED_TEST(TableTest, canCheckForEmptiness) {
	EXPECT_TRUE(this->table.empty());
}

TYPED_TEST(TableTest, notEmptyTableIsNotEmpty) {
	this->table.insert("key", 10);

	EXPECT_FALSE(this->table.empty());
}

TYPED_TEST(TableTest, canClear) {
	for (int i = 0; i < 10; i++) {
		this->table.insert("key" + std::to_string(i), i);
	}
	this->table.clear();
	
	EXPECT_TRUE(this->table.empty());
	EXPECT_EQ(this->table.size(), 0);
}

TYPED_TEST(TableTest, canCheckForExistence) {
	this->table.insert("key", 10);

	EXPECT_TRUE(this->table.isExist("key"));
	EXPECT_FALSE(this->table.isExist("notAKey"));
}

TYPED_TEST(TableTest, BeginIterator) {
	this->table.insert("key", 10);
	auto It = this->table.begin();

	EXPECT_EQ((*It).second, 10);
}

TYPED_TEST(TableTest, EndIterator) {
	this->table.insert("key", 10);
	auto It = this->table.end();

	EXPECT_EQ(It, this->table.find("notAKey"));
}

TYPED_TEST(TableTest, IteratorsWorkRightInEmptyTable) {
	EXPECT_EQ(this->table.begin(), this->table.end());
}

TYPED_TEST(TableTest, CanEraseFromEmptyTable) {
	EXPECT_NO_THROW(this->table.erase("notAKey"));
}

TYPED_TEST(TableTest, CanInsertManyElements) {
	for (int i = 0; i < 10000; i++) {
		this->table.insert("key" + std::to_string(i), i);
	}
	EXPECT_EQ(this->table.size(), 10000);
}

TYPED_TEST(TableTest, CanEraseManyElements) {
	for (int i = 0; i < 100; i++) {
		this->table.insert("key" + std::to_string(i), i);
	}
	for (int i = 0; i < 100; i++) {
		this->table.erase("key" + std::to_string(i));
	}
	EXPECT_EQ(this->table.size(), 0);
	EXPECT_TRUE(this->table.empty());
}

TYPED_TEST(TableTest, CanClearManyElementss) {
	for (int i = 0; i < 100; i++) {
		this->table.insert("key" + std::to_string(i), i);
	}
	this->table.clear();

	EXPECT_TRUE(this->table.empty());
}

TYPED_TEST(TableTest, RepeatedInsertAndErase) {
	for (int i = 0; i < 10; i++) {
		this->table.insert("key", i);
		this->table.erase("key");
	}

	EXPECT_TRUE(this->table.empty());
}
