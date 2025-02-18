#pragma once

#include "includes.hpp"

template<typename ListType> class List {
private:
    struct Node {
        ListType value;
        Node* next = nullptr;
        Node* prev = nullptr;

        bool is_head = false;

        Node() {}

        Node(const ListType& value) {
            this->value = value;
        }
    };

    int sz = 0;
    Node* head = nullptr;
    // head->next the first element of this list
    // head->prev the last element of this list

public:
    class Iterator {
        friend class List;
    private:
        Node* curr_node = nullptr;

        Iterator(Node* curr_node): curr_node(curr_node) {}
    public:
        Iterator() = delete;

        ListType& operator*() const {
            if (curr_node->is_head) {
                throw std::out_of_range("It is not allowed to dereference the .end() iterator!");
            }
            return curr_node->value;
        }

        ListType* operator->() const {
            if (curr_node->is_head) {
                throw std::out_of_range("It is not allowed to dereference the .end() iterator!");
            }
            return &(curr_node->value);
        }

        bool operator==(const Iterator& other) const {
            return this->curr_node == other.curr_node;
        }

        bool operator!=(const Iterator& other) const {
            return this->curr_node != other.curr_node;
        }
        
        //It is possible to use shift > sz of the list
        Iterator operator+(int shift) const{
            Iterator temp = *this;
            for (int i = 0; i < shift; ++i) {
                ++temp;
            }
            for (int i = 0; i > shift; --i) {
                --temp;
            }
            return temp;
        }

        Iterator operator-(int shift) const {
            return (*this + (-shift));
        }

        Iterator& operator++() {
            curr_node = curr_node->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            curr_node = curr_node->next;
            return temp;
        }

        Iterator& operator--() {
            curr_node = curr_node->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            curr_node = curr_node->prev;
            return temp;
        }
    };

private:

    void createHead(Node* &node) {
        node = new Node;
        node->prev = node;
        node->next = node;
        node->is_head = true;
    }

    void destruct() {
        while (begin() != end()) {
            erase(begin());
        }
        delete head;
        head = nullptr;
    }

    void roughCoping(const List& other) {
        createHead(this->head);
        for (const ListType& value: other) {
            this->push_back(value);
        }
    }

    Iterator insert(const ListType& value, Node* prev_node, Node* next_node) {
        ++sz;

        Node* curr_node = new Node(value);

        curr_node->next = prev_node->next;
        curr_node->prev = next_node->prev;

        next_node->prev = curr_node;
        prev_node->next = curr_node;

        return Iterator(curr_node);
    }

    Iterator erase(Node* curr_node) {
        if (curr_node->is_head) {
            throw std::out_of_range("It is not allowed to erase the .end() iterator!");
        }

        --sz;

        Node* prev_node = curr_node->prev;
        Node* next_node = curr_node->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete curr_node;
        return Iterator(next_node);
    }

public:

    List() {
        createHead(head);
    }

    List(int size, const ListType& value): List() {
        if (size < 0) {
            throw std::logic_error("The size of the list must be non-negative!");
        }
        for (int i = 0; i < size; ++i) {
            push_back(value);
        }
    }

    List(const List& other) {
        roughCoping(other);
    }

    List(List&& other) {
        this->head = other.head;
        this->sz = other.sz;

        createHead(other.head);
        other.sz = 0;
    }

    ~List() {
        destruct();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            destruct();
            roughCoping(other);
        }
        return *this;
    }

    List& operator=(List&& other) {
        if (this != &other) {
            this->head = other.head;
            this->sz = other.sz;

            createHead(other.head);
            other.sz = 0;
        }
        return *this;
    }

    size_t size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    Iterator begin() const {
        return Iterator(head->next);
    }

    Iterator end() const {
        return Iterator(head);
    }

    ListType& front() const {
        if (head->next->is_head) {
            throw std::out_of_range("The .front() method is called on the empty list!");
        }
        return head->next->value;
    }

    ListType& back() const {
        if (head->prev->is_head) {
            throw std::out_of_range("The .back() method is called on the empty list!");
        }
        return head->prev->value;
    }

    Iterator push_front(const ListType& value) {
        return insert(value, head, head->next);
    }

    Iterator push_back(const ListType& value) {
        return insert(value, head->prev, head);
    }

    Iterator insert_after(const ListType& value, Iterator prev) {
        return insert(value, prev.curr_node, prev.curr_node->next);
    }

    Iterator insert_before(const ListType& value, Iterator next) {
        return insert(value, next.curr_node->prev, next.curr_node);
    }

    Iterator pop_front() {
        return erase(Iterator(head->next));
    }

    Iterator pop_back() {
        return erase(Iterator(head->prev));
    }

    Iterator erase(Iterator it) {
        return erase(it.curr_node);
    }

    ListType& operator[](int index) {
        if (index >= sz || index < 0) {
            throw std::out_of_range("List index out of range!");
        }
        return *(begin() + index);
    }

    const ListType& operator[](int index) const {
        if (index >= sz || index < 0) {
            throw std::out_of_range("List index out of range!");
        }
        return *(begin() + index);
    }
};
