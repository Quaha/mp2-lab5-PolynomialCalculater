#include <gtest/gtest.h>

#include <random>
#include <vector>
#include <set>
#include <algorithm>

#include "includes.hpp"

template <typename TreeType>
class SearchTreeTest : public ::testing::Test {
protected:
    TreeType tree;
};

const int BIG_TESTS_SIZE = 3000;

using TreeImplementations = ::testing::Types<TestableRedBlackTree<int, int>, AVLTree<int, int>>;
TYPED_TEST_SUITE(SearchTreeTest, TreeImplementations);

TYPED_TEST(SearchTreeTest, IsEmptyContainerAfterInitializing) {
    EXPECT_TRUE(this->tree.empty());
}

TYPED_TEST(SearchTreeTest, CanInsertOneElement) {
    EXPECT_NO_THROW(this->tree.insert(0, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, CanInsertSomeElements1) {
    EXPECT_NO_THROW(this->tree.insert(0, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(1, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(2, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, CanInsertSomeElements2) {
    EXPECT_NO_THROW(this->tree.insert(2, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(1, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(0, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, CanInsertSomeElements3) {
    EXPECT_NO_THROW(this->tree.insert(1, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(2, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(0, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, CanInsertSomeElements4) {
    EXPECT_NO_THROW(this->tree.insert(1, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(0, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());

    EXPECT_NO_THROW(this->tree.insert(2, 0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, CanInsertALotOfElements) {

    const size_t cnt = BIG_TESTS_SIZE;

    std::vector<int> keys;
    std::set<int> was;

    while (keys.size() < cnt) {
        int key = std::rand();

        if (!was.contains(key)) {
            was.insert(key);
            keys.push_back(key);
        }
    }

    for (int key: keys) {
        EXPECT_NO_THROW(this->tree.insert(key, 0));
        EXPECT_TRUE(this->tree.isTreeCorrect());
    }
}

TYPED_TEST(SearchTreeTest, CantFindWrongElement) {
    EXPECT_EQ(this->tree.find(0), this->tree.end());
}

TYPED_TEST(SearchTreeTest, DoesntExistWrongElemnt) {
    EXPECT_FALSE(this->tree.isExist(0));
}

TYPED_TEST(SearchTreeTest, ExistsCorrectElemnt) {
    this->tree.insert(0, 0);
    EXPECT_TRUE(this->tree.isExist(0));
}

TYPED_TEST(SearchTreeTest, CanFindOneElement) {
    this->tree.insert(0, 0);
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 0));
}

TYPED_TEST(SearchTreeTest, CanFindSomeElements1) {
    this->tree.insert(0, 0);
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 0));

    this->tree.insert(1, 0);
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 0));

    this->tree.insert(2, 0);
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 0));
}

TYPED_TEST(SearchTreeTest, CanFindSomeElements2) {
    this->tree.insert(2, 0);
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 0));

    this->tree.insert(1, 0);
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 0));

    this->tree.insert(0, 0);
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 0));
}

TYPED_TEST(SearchTreeTest, CanFindSomeElements3) {
    this->tree.insert(1, 0);
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 0));

    this->tree.insert(2, 0);
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 0));

    this->tree.insert(0, 0);
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 0));
}

TYPED_TEST(SearchTreeTest, CanFindSomeElements4) {
    this->tree.insert(1, 0);
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 0));

    this->tree.insert(0, 0);
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 0));

    this->tree.insert(2, 0);
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 0));
}

TYPED_TEST(SearchTreeTest, CanFindALotOfElements) {

    const size_t cnt = BIG_TESTS_SIZE;

    std::vector<int> keys;
    std::set<int> was;

    while (keys.size() < cnt) {
        int key = std::rand();

        if (!was.contains(key)) {
            was.insert(key);
            keys.push_back(key);
        }
    }

    for (int key : keys) {
        this->tree.insert(key, 0);
    }

    for (int key : keys) {
        EXPECT_EQ(*this->tree.find(key), std::make_pair(key, 0));
    }
}


TYPED_TEST(SearchTreeTest, IsCorrectBeginIteratorFromEmptyTree) {
    EXPECT_EQ(this->tree.begin(), this->tree.end());
}


TYPED_TEST(SearchTreeTest, CanEraseOneElement) {
    this->tree.insert(0, 0);

    EXPECT_NO_THROW(this->tree.erase(0));
    EXPECT_TRUE(this->tree.isTreeCorrect());
}

TYPED_TEST(SearchTreeTest, SpecialDebugTest) {

    std::vector<int> insert_order = { 1, 2, 3, 5, 6, 4 };
    std::vector<int> erase_order = { 1, 2, 3, 4, 5, 6 };

    for (int key : insert_order) {
        this->tree.insert(key, 0);
    }

    for (int key : erase_order) {
        EXPECT_NO_THROW(this->tree.erase(key));
        ASSERT_TRUE(this->tree.isTreeCorrect());
    }
}

TYPED_TEST(SearchTreeTest, CanEraseSomeElements) {

    /*
    
    If something went wrong then use the upper test to fix it!
    
    */

    std::vector<int> insert_order = { 1, 2, 3, 4, 5, 6};
    
    do {
        std::vector<int> erase_order = { 1, 2, 3, 4, 5, 6};
        do {

            for (int key : insert_order) {
                this->tree.insert(key, 0);
                EXPECT_TRUE(this->tree.isTreeCorrect());
            }

            for (int key : erase_order) {
                EXPECT_NO_THROW(this->tree.erase(key));
                EXPECT_TRUE(this->tree.isTreeCorrect());

                if (!this->tree.isTreeCorrect()) {
                    int b = 5;
                    b += 5;
                    b++;
                }

            }


        } while (std::next_permutation(erase_order.begin(), erase_order.end()));

    } while (std::next_permutation(insert_order.begin(), insert_order.end()));
}

TYPED_TEST(SearchTreeTest, CanEraseALotOfElements) {

    for (int seed = 0; seed <= 30; seed++) {

        std::srand(seed);

        const size_t cnt = BIG_TESTS_SIZE / 10;

        std::vector<int> keys;
        std::set<int> was;

        while (keys.size() < cnt) {
            int key = std::rand();

            if (!was.contains(key)) {
                was.insert(key);
                keys.push_back(key);
            }
        }

        for (int key : keys) {
            this->tree.insert(key, 0);
        }

        for (int key : keys) {
            EXPECT_NO_THROW(this->tree.erase(key));
            EXPECT_TRUE(this->tree.isTreeCorrect());
        }
    }
}


/*

TYPED_TEST(SearchTreeTest, CanChangeSomeElements1) {
    this->tree.insert(0, 0);
    (*this->tree.find(0)).second = 1;
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 1));

    this->tree.insert(1, 0);
    (*this->tree.find(1)).second = 1;
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 1));

    this->tree.insert(2, 0);
    (*this->tree.find(2)).second = 1;
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 1));
}

TYPED_TEST(SearchTreeTest, CanChangeSomeElements2) {
    this->tree.insert(2, 0);
    (*this->tree.find(2)).second = 1;
    EXPECT_EQ(*this->tree.find(2), std::make_pair(2, 1));

    this->tree.insert(1, 0);
    (*this->tree.find(1)).second = 1;
    EXPECT_EQ(*this->tree.find(1), std::make_pair(1, 1));

    this->tree.insert(0, 0);
    (*this->tree.find(0)).second = 1;
    EXPECT_EQ(*this->tree.find(0), std::make_pair(0, 1));
}

TYPED_TEST(SearchTreeTest, CanChangeALotOfElements) {

    const size_t cnt = BIG_TESTS_SIZE;

    std::vector<int> keys;
    std::set<int> was;

    while (keys.size() < cnt) {
        int key = std::rand();

        if (!was.contains(key)) {
            was.insert(key);
            keys.push_back(key);
        }
    }

    for (int key : keys) {
        this->tree.insert(key, 0);
    }

    for (int key : keys) {
        (*this->tree.find(key)).second = 1;
    }

    for (int key : keys) {
        EXPECT_EQ(*this->tree.find(key), std::make_pair(key, 1));
    }
}

TYPED_TEST(SearchTreeTest, RangeBasedIterators) {

    const size_t cnt = BIG_TESTS_SIZE;

    std::vector<int> keys;
    std::set<int> was;

    while (keys.size() < cnt) {
        int key = std::rand();

        if (!was.contains(key)) {
            was.insert(key);
            keys.push_back(key);
        }
    }

    for (int key : keys) {
        this->tree.insert(key, key);
    }

    std::sort(keys.begin(), keys.end());

    int p = 0;
    for (auto [key, value] : this->tree) {
        EXPECT_EQ(key, keys[p]);
        EXPECT_EQ(value, keys[p++]);
    }
}

TYPED_TEST(SearchTreeTest, DereferencingEndPointer) {
    EXPECT_ANY_THROW(*this->tree.end());
}

TYPED_TEST(SearchTreeTest, LowerBound) {
    this->tree.insert(1, 10);
    this->tree.insert(3, 30);
    this->tree.insert(5, 50);

    auto it = this->tree.lowerBound(3);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 30);

    it = this->tree.lowerBound(2);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 30);

    it = this->tree.lowerBound(6);
    EXPECT_EQ(it, this->tree.end());
}

TYPED_TEST(SearchTreeTest, UpperBound) {
    this->tree.insert(1, 10);
    this->tree.insert(3, 30);
    this->tree.insert(5, 50);

    auto it = this->tree.upperBound(3);
    EXPECT_EQ(it->first, 5);
    EXPECT_EQ(it->second, 50);

    it = this->tree.upperBound(2);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 30);

    it = this->tree.upperBound(5);
    EXPECT_EQ(it, this->tree.end());
}

TYPED_TEST(SearchTreeTest, LowerAndUpperBoundOnEmptyTree) {
    auto it = this->tree.lowerBound(10);
    EXPECT_EQ(it, this->tree.end());

    it = this->tree.upperBound(10);
    EXPECT_EQ(it, this->tree.end());
}

TYPED_TEST(SearchTreeTest, LowerAndUpperBoundOnLargeTree) {
    const size_t cnt = BIG_TESTS_SIZE;
    std::vector<int> keys;
    std::set<int> was;

    while (keys.size() < cnt) {
        int key = std::rand();
        if (!was.contains(key)) {
            was.insert(key);
            keys.push_back(key);
        }
    }

    for (int key : keys) {
        this->tree.insert(key, key);
    }

    std::sort(keys.begin(), keys.end());

    for (size_t i = 0; i < cnt; ++i) {
        int key = keys[i];

        auto it_lower = this->tree.lowerBound(key);
        auto it_upper = this->tree.upperBound(key);

        if (i == cnt - 1) {
            EXPECT_EQ(it_lower->first, key);
            EXPECT_EQ(it_upper, this->tree.end());
        }
        else {
            EXPECT_EQ(it_lower->first, key);
            EXPECT_EQ(it_upper->first, keys[i + 1]);
        }
    }
}
*/


