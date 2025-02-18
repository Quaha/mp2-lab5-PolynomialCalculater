#include <gtest/gtest.h>

#include "DoublyLinkedList.hpp"

// creating
TEST(DoublyLinkedList, can_create_an_empty_list) {
    ASSERT_NO_THROW(List<int> list);
}

TEST(DoublyLinkedList, can_create_a_filled_list) {
    ASSERT_NO_THROW(List<int> list(5, 0));
}

TEST(DoublyLinkedList, the_created_list_is_correct) {
    List<int> list(5, 4);
    for (int V : list) {
        EXPECT_EQ(V, 4);
    }
}

TEST(DoublyLinkedList, cant_create_a_list_with_negative_size) {
    ASSERT_ANY_THROW(List<int> list(-4, 0));
}

// copy constructor
TEST(DoublyLinkedList, can_use_the_copy_constructor) {
    List<int> list(5, 0);
    ASSERT_NO_THROW(List<int> copy(list));
}

TEST(DoublyLinkedList, correct_copying_by_the_constructor) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int> copy(list);

    EXPECT_EQ(copy.size(), list.size());
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(copy[i], list[i]);
    }
}

TEST(DoublyLinkedList, the_copied_list_by_the_copy_construcor_has_own_memory) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int> copy(list);
    for (int i = 0; i < 3; i++) {
        copy[i] = i + 1;
    }
    copy.push_back(5);

    EXPECT_NE(copy.size(), list.size());
    for (int i = 0; i < 3; i++) {
        EXPECT_NE(copy[i], list[i]);
    }
}

TEST(DoublyLinkedList, can_copy_the_empty_list) {
    List<int> list;
    List<int> copy(list);

    EXPECT_EQ(copy.size(), 0);
    EXPECT_TRUE(copy.empty());
}

// move constructor
TEST(DoublyLinkedList, can_used_move_constructor) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }
    ASSERT_NO_THROW(List<int> moved(std::move(list)));
}

TEST(DoublyLinkedList, move_constructor_is_correct) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    List<int> moved(std::move(list));
    
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(moved.size(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(moved[i], i);
    }
}

// copy operator
TEST(DoublyLinkedList, copy_assignment_operator_is_correct) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int> assigned;
    assigned = list;

    EXPECT_EQ(assigned.size(), list.size());
    for (int i = 0; i < assigned.size(); i++) {
        EXPECT_EQ(assigned[i], list[i]);
    }
}

TEST(DoublyLinkedList, copy_assignment_operator_self_assignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list = list;

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

// move operator
TEST(DoublyLinkedList, move_assignment_operator_is_correct) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int> assigned;
    assigned = std::move(list);

    EXPECT_EQ(assigned.size(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(assigned[i], i);
    }
}

TEST(DoublyLinkedList, can_move_list_to_itself) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    list = std::move(list);

    EXPECT_EQ(list.size(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(list[i], i);
    }
}

// iterators
TEST(DoublyLinkedList, begin_and_end_iterators) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    List<int>::Iterator it = list.begin();
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    EXPECT_TRUE(it == list.end());
}

TEST(DoublyLinkedList, begin_in_empty_list) {
    List<int> list;
    EXPECT_TRUE(list.begin() == list.end());
}

TEST(DoublyLinkedList, iterator_before_the_end) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int>::Iterator it = list.end();
    --it;
    EXPECT_EQ(*it, 2);
}

TEST(DoublyLinkedList, iterator_after_the_end) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int>::Iterator it = list.end();
    ++it;
    EXPECT_EQ(it, list.begin());
}

TEST(DoublyLinkedList, addition_operator_of_iterator) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(i, *(list.begin() + i));
    }
    ASSERT_ANY_THROW(*(list.begin() + 3));
}

TEST(DoublyLinkedList, substraction_operator_of_iterator) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    for (int i = 1; i <= 3; i++) {
        EXPECT_EQ(3 - i, *(list.end() - i));
    }
    ASSERT_ANY_THROW(*(list.end() - 0));
}

// .front() and .back()
TEST(DoublyLinkedList, front_and_back_non_empty) {
    List<int> list;
    list.push_back(20);
    list.push_back(30);
    list.push_front(10);

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
}

TEST(DoublyLinkedList, front_and_back_after_modification) {
    List<int> list;
    list.push_back(15);
    list.push_front(5);
    list.push_back(25);

    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 25);

    list.pop_front();
    EXPECT_EQ(list.front(), 15);

    list.pop_back();
    EXPECT_EQ(list.back(), 15);
    
    list.pop_back();
    EXPECT_ANY_THROW(list.front());
}


TEST(DoublyLinkedList, front_empty) {
    List<int> list;
    EXPECT_ANY_THROW(list.front());
}

TEST(DoublyLinkedList, back_empty) {
    List<int> list;
    EXPECT_ANY_THROW(list.back());
}

// .insert
TEST(DoublyLinkedList, insert_after) {
    List<int> list;

    list.push_back(10);
    list.push_back(30);
    list.insert_after(20, list.begin());

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(*(++list.begin()), 20);
    EXPECT_EQ(list.back(), 30);
}

TEST(DoublyLinkedList, insert_before) {
    List<int> list;

    list.push_back(20);
    list.push_back(40);
    list.insert_before(30, --list.end());

    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(*(++list.begin()), 30);
    EXPECT_EQ(list.back(), 40);
}

TEST(DoublyLinkedList, insert_before_end) {
    List<int> list;

    list.push_back(20);
    list.push_back(40);
    list.insert_before(30, list.end());

    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(*(++list.begin()), 40);
    EXPECT_EQ(list.back(), 30);
}

TEST(DoublyLinkedList, insert_before_after_empty_list) {
    List<int> list;

    list.push_back(10);
    list.insert_before(5, list.begin());

    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(*(++list.begin()), 10);
}

// .erase
TEST(DoublyLinkedList, pop_front) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_front();

    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 30);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedList, pop_back) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_back();

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedList, erase) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.erase(++list.begin());

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedList, erase_first_element) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);

    list.erase(list.begin());

    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.size(), 1);
}

TEST(DoublyLinkedList, erase_last_element) {
    List<int> list;

    list.push_front(10);
    list.push_back(20);

    list.erase(--list.end());

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
}

TEST(DoublyLinkedList, cant_erase_end_iterator) {
    List<int> list;

    list.push_back(4);

    ASSERT_ANY_THROW(list.erase(list.end()));
}

// operator[]

TEST(DoublyLinkedList, push_front_and_access) {
    List<int> list;

    list.push_front(20);
    list.push_front(10);

    list[0] = 15;

    EXPECT_EQ(list[0], 15);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedList, push_back_and_access) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);

    list[1] = 15;

    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 15);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedList, access_out_of_bounds) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);

    ASSERT_ANY_THROW(list[2]);
}