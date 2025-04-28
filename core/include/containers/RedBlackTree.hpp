#pragma once

#include <utility>
#include <vector>

template <typename TKey, typename TValue>
class RedBlackTree {
protected:

    using node_ptr = int;
    const static node_ptr NULL_PTR = -1;

    enum Color {
        Red,
        Black
    };

    struct Node {

        node_ptr parent;
        node_ptr left_node, right_node;

        Color color;

        std::pair<TKey, TValue> data;

        bool is_fictitious;
    };

public:

    class Iterator {
    protected:

        node_ptr ptr = 0;

        RedBlackTree<TKey, TValue>* container_ptr;

        Iterator(node_ptr ptr, RedBlackTree<TKey, TValue>* container_ptr) :
            ptr(ptr),
            container_ptr(container_ptr)
        {}

    public:

        std::pair<const TKey&, TValue&> operator*() {
            if (ptr == NULL_PTR) {
                throw std::out_of_range("It is forbidden to dereference .end() iterator.");
            }
            return { container_ptr->tree[ptr].data.first, container_ptr->tree[ptr].data.second };
        }

        const std::pair<const TKey&, const TValue&> operator*() const {
            if (ptr == NULL_PTR) {
                throw std::out_of_range("It is forbidden to dereference .end() iterator.");
            }
            return { container_ptr->tree[ptr].data.first, container_ptr->tree[ptr].data.second };
        }

        std::pair<TKey, TValue>* operator->() const {
            return &container_ptr->tree[ptr].data;
        }

        Iterator& operator++() {
            node_ptr curr_node_ptr = ptr;
            node_ptr right_son_ptr = container_ptr->tree[curr_node_ptr].right_node;

            if (!container_ptr->tree[right_son_ptr].is_fictitious) {
                ptr = container_ptr->getLowestPos(right_son_ptr);
                return *this;
            }

            node_ptr prev_node_ptr = container_ptr->tree[curr_node_ptr].parent;
            while (prev_node_ptr != NULL_PTR && container_ptr->tree[prev_node_ptr].right_node == curr_node_ptr) {
                curr_node_ptr = prev_node_ptr;
                prev_node_ptr = container_ptr->tree[curr_node_ptr].parent;
            }
            ptr = prev_node_ptr;

            return *this;
        }

        bool operator==(const Iterator& other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const Iterator& other) const {
            return this->ptr != other.ptr;
        }

        friend class RedBlackTree;
    };

protected:

    std::vector<Node> tree;
    size_t count_of_elements = 0;

    node_ptr root;

    std::vector<node_ptr> free_poses;

protected:
    Iterator makeIterator(node_ptr position) const {
        return Iterator(position, const_cast<RedBlackTree<TKey, TValue>*>(this));
    }

    node_ptr createNode(node_ptr parent) {
        if (free_poses.empty()) {
            free_poses.push_back(static_cast<node_ptr>(tree.size()));
            tree.push_back(Node());
        }
        node_ptr ptr = free_poses.back();
        free_poses.pop_back();

        tree[ptr].parent = parent;
        tree[ptr].left_node = NULL_PTR;
        tree[ptr].right_node = NULL_PTR;

        tree[ptr].color = Color::Black;
        tree[ptr].is_fictitious = true;

        return ptr;
    }

    void deleteNode(node_ptr ptr) {
        free_poses.push_back(ptr);
    }

protected:
    void smallLeftRotation(node_ptr x) {
        node_ptr y = getRightSon(x);

        node_ptr subtree_root = getParent(x);

        tree[x].right_node = tree[y].left_node;
        if (getRightSon(x) != NULL_PTR) {
            tree[getRightSon(x)].parent = x;
        }

        tree[x].parent = y;

        tree[y].parent = subtree_root;
        tree[y].left_node = x;

        changeParent(subtree_root, x, y);
    }

    void smallRightRotation(node_ptr x) {
        node_ptr y = getLeftSon(x);

        node_ptr subtree_root = getParent(x);

        tree[x].left_node = tree[y].right_node;
        if (getLeftSon(x) != NULL_PTR) {
            tree[getLeftSon(x)].parent = x;
        }

        tree[x].parent = y;

        tree[y].parent = subtree_root;
        tree[y].right_node = x;

        changeParent(subtree_root, x, y);
    }

protected:
    node_ptr getLeftSon(node_ptr x) const {
        return tree[x].left_node;
    }

    node_ptr getRightSon(node_ptr x) const {
        return tree[x].right_node;
    }

    node_ptr getParent(node_ptr x) const {
        return tree[x].parent;
    }

    node_ptr getGrandParent(node_ptr x) const {
        return getParent(getParent(x));
    }

    node_ptr getUncle(node_ptr x) const {
        node_ptr g = getGrandParent(x);
        if (getLeftSon(g) == getParent(x)) {
            return getRightSon(g);
        }
        else {
            return getLeftSon(g);
        }
    }

    node_ptr getBrother(node_ptr x) const {
        if (tree[getParent(x)].left_node == x) {
            return tree[getParent(x)].right_node;
        }
        return tree[getParent(x)].left_node;
    }

    const TKey& getKey(node_ptr x) const {
        return tree[x].data.first;
    }

    const TValue& getValue(node_ptr x) const {
        return tree[x].data.second;
    }

    bool isFictitious(node_ptr x) const {
        return tree[x].is_fictitious;
    }

    void changeParent(node_ptr parent, node_ptr old_son, node_ptr new_son) {
        if (parent == NULL_PTR) {
            root = new_son;
        }
        else {
            if (getLeftSon(parent) == old_son) {
                tree[parent].left_node = new_son;
            }
            else {
                tree[parent].right_node = new_son;
            }
        }
        tree[new_son].parent = parent;
    }

protected:
    int getColor(node_ptr x) const {
        return tree[x].color;
    }

    void setColor(node_ptr x, Color color) {
        tree[x].color = color;
    }

protected:

    node_ptr getLowestPos(node_ptr x) const {
        node_ptr lowest_pos = x;
        while (!isFictitious(getLeftSon(lowest_pos))) {
            lowest_pos = getLeftSon(lowest_pos);
        }
        return lowest_pos;
    }

    node_ptr findPosition(const TKey& key) const {
        node_ptr current_ptr = root;
        while (!isFictitious(current_ptr) && getKey(current_ptr) != key) {
            if (getKey(current_ptr) > key) {
                current_ptr = tree[current_ptr].left_node;
            }
            else {
                current_ptr = tree[current_ptr].right_node;
            }
        }
        return current_ptr;
    }

    void erasePosition(node_ptr x) {
        if (!isFictitious(getLeftSon(x)) && !isFictitious(getRightSon(x))) {
            node_ptr min_right = getLowestPos(getRightSon(x));
            std::swap(tree[x].data, tree[min_right].data);
            erasePosition(min_right);
        }
        else if (isFictitious(getLeftSon(x)) && !isFictitious(getRightSon(x))) {
            changeParent(getParent(x), x, getRightSon(x));
            setColor(getRightSon(x), Color::Black);

            deleteNode(getLeftSon(x));
            deleteNode(x);
        }
        else if (!isFictitious(getLeftSon(x)) && isFictitious(getRightSon(x))) {
            changeParent(getParent(x), x, getLeftSon(x));
            setColor(getLeftSon(x), Color::Black);

            deleteNode(getRightSon(x));
            deleteNode(x);
        }
        else if (isFictitious(getLeftSon(x)) && isFictitious(getRightSon(x))) {
            if (getColor(x) == Color::Red) {
                changeParent(getParent(x), x, getLeftSon(x));

                deleteNode(getRightSon(x));
                deleteNode(x);
            }
            else if (getColor(x) == Color::Black) {

                node_ptr subtree_root = getParent(x);
                node_ptr bad_subtree = getLeftSon(x);

                changeParent(subtree_root, x, bad_subtree);

                deleteNode(getRightSon(x));
                deleteNode(x);

                fixTreeAfterErase(bad_subtree);
            }
        }
    }

    void fixTreeAfterInsert(node_ptr x) {
        if (getParent(x) == NULL_PTR) { // => x is root
            setColor(x, Color::Black);
            return;
        }

        node_ptr y = getParent(x);

        if (getColor(y) == Color::Red) { // x is Red

            node_ptr g = getGrandParent(x);
            node_ptr u = getUncle(x);

            if (getColor(u) == Color::Red) {
                setColor(y, Color::Black);
                setColor(u, Color::Black);
                setColor(g, Color::Red);

                fixTreeAfterInsert(g);
            }
            else { // u is Black

                if (getLeftSon(g) == y && getLeftSon(y) == x) {
                    setColor(y, Color::Black);
                    setColor(g, Color::Red);

                    smallRightRotation(g);
                }
                else if (getRightSon(g) == y && getRightSon(y) == x) {
                    setColor(y, Color::Black);
                    setColor(g, Color::Red);

                    smallLeftRotation(g);
                }
                else if (getLeftSon(g) == y && getRightSon(y) == x) {
                    smallLeftRotation(y);

                    fixTreeAfterInsert(y);
                }
                else if (getRightSon(g) == y && getLeftSon(y) == x) {
                    smallRightRotation(y);

                    fixTreeAfterInsert(y);
                }
            }
        }
    }

    void fixTreeAfterErase(node_ptr x) {
        if (x == root) {
            return;
        }

        node_ptr A = getParent(x);
        node_ptr B = getBrother(x);

        if (getColor(A) == Color::Red) {
            if (getLeftSon(B) != NULL_PTR && getColor(getLeftSon(B)) == Color::Red) {
                if (getLeftSon(A) == B) {
                    /*
                            A
                           /
                          B
                    */

                    if (getColor(getRightSon(B)) == Color::Black) {
                        smallRightRotation(A);
                    }
                    else {
                        setColor(B, Color::Red);
                        setColor(getLeftSon(B), Color::Black);
                        setColor(getRightSon(B), Color::Black);

                        smallRightRotation(A);
                        smallRightRotation(A);
                    }
                }
                else {
                    /*
                        A
                         \
                          B
                    */
                    setColor(A, Color::Black);

                    smallRightRotation(B);
                    smallLeftRotation(A);
                }
            }
            else if (getRightSon(B) != NULL_PTR && getColor(getRightSon(B)) == Color::Red) {
                if (getLeftSon(A) == B) {
                    /*
                       A
                      /
                     B
                    */
                    setColor(A, Color::Black);

                    smallLeftRotation(B);
                    smallRightRotation(A);
                }
                else {
                    /*
                       A
                        \
                         B
                    */

                    if (getColor(getLeftSon(B)) == Color::Black) {
                        smallLeftRotation(A);
                    }
                    else {
                        setColor(B, Color::Red);
                        setColor(getLeftSon(B), Color::Black);
                        setColor(getRightSon(B), Color::Black);

                        smallLeftRotation(A);
                        smallLeftRotation(A);
                    }
                }
            }
            else {
                setColor(A, Color::Black);
                setColor(B, Color::Red);
            }
        }
        else if (getColor(A) == Color::Black) {
            if (getColor(B) == Color::Red) {
                setColor(A, Color::Red);
                setColor(B, Color::Black);
                if (getLeftSon(A) == B) {
                    smallRightRotation(A);
                }
                else {
                    smallLeftRotation(A);
                }
                fixTreeAfterErase(x);
            }
            else if (getColor(B) == Color::Black) {
                if (getLeftSon(B) != NULL_PTR && getColor(getLeftSon(B)) == Color::Red) {
                    node_ptr C = getLeftSon(B);
                    if (getLeftSon(A) == B) {
                        /*
                                A
                               /
                              B
                             /
                            C
                        */

                        setColor(C, Color::Black);

                        smallRightRotation(A);
                    }
                    else {
                        /*
                            A
                             \
                              B
                             /
                            C
                        */
                        setColor(C, Color::Black);

                        smallRightRotation(B);
                        smallLeftRotation(A);
                    }
                }
                else if (getRightSon(B) != NULL_PTR && getColor(getRightSon(B)) == Color::Red) {
                    node_ptr C = getRightSon(B);
                    if (getLeftSon(A) == B) {
                        /*
                           A
                          /
                         B
                          \
                           C
                        */
                        setColor(C, Color::Black);

                        smallLeftRotation(B);
                        smallRightRotation(A);
                    }
                    else {
                        /*
                           A
                            \
                             B
                              \
                               C
                        */

                        setColor(C, Color::Black);

                        smallLeftRotation(A);
                    }
                }
                else {
                    setColor(B, Color::Red);
                    fixTreeAfterErase(A);
                }
            }
        }
    }

    void lowerBound(const TKey& key, node_ptr x, node_ptr& nearest_pos) const {
        if (isFictitious(x)) {
            return;
        }
        if (getKey(x) >= key) {
            nearest_pos = x;
            lowerBound(key, getLeftSon(x), nearest_pos);
        }
        else {
            lowerBound(key, getRightSon(x), nearest_pos);
        }
    }

    void upperBound(const TKey& key, node_ptr x, node_ptr& nearest_pos) const {
        if (isFictitious(x)) {
            return;
        }
        if (getKey(x) > key) {
            nearest_pos = x;
            upperBound(key, getLeftSon(x), nearest_pos);
        }
        else {
            upperBound(key, getRightSon(x), nearest_pos);
        }
    }

public:

    RedBlackTree() {
        root = createNode(NULL_PTR);
    }

    Iterator begin() const {
        if (empty()) {
            return end();
        }
        node_ptr lowest_pos = getLowestPos(root);
        return makeIterator(lowest_pos);
    }

    Iterator end() const {
        return makeIterator(NULL_PTR);
    }

    Iterator lowerBound(const TKey& key) {
        node_ptr nearest_pos = NULL_PTR;
        lowerBound(key, root, nearest_pos);
        return makeIterator(nearest_pos);
    }

    Iterator upperBound(const TKey& key) {
        node_ptr nearest_pos = NULL_PTR;
        upperBound(key, root, nearest_pos);
        return makeIterator(nearest_pos);
    }

    Iterator insert(const TKey& key, const TValue& value) {
        node_ptr ptr = findPosition(key);
        if (isFictitious(ptr)) {
            ++count_of_elements;

            tree[ptr].data.first = key;
            tree[ptr].data.second = value;

            tree[ptr].color = Color::Red;
            tree[ptr].is_fictitious = false;

            tree[ptr].left_node = createNode(ptr);
            tree[ptr].right_node = createNode(ptr);

            fixTreeAfterInsert(ptr);
        }
        return makeIterator(ptr);
    }

    Iterator erase(const TKey& key) {
        return erase(find(key));
    }

    Iterator erase(Iterator it) {
        if (it == end()) {
            return it;
        }
        --count_of_elements;
        auto result = it;
        ++result;
        erasePosition(it.ptr);
        return result;
    }

    Iterator find(const TKey& key) const {
        node_ptr ptr = findPosition(key);
        if (isFictitious(ptr)) {
            return end();
        }
        return makeIterator(ptr);
    }

    bool isExist(const TKey& key) const {
        return find(key) != end();
    }

    TValue& operator[](const TKey& key) {
        if (!isExist(key)) {
            throw std::runtime_error("No such key in table");
        }
        return (*find(key)).second;
    }

    const TValue& operator[](const TKey& key) const {
        if (!isExist(key)) {
            throw std::runtime_error("No such key in table");
        }
        return (*find(key)).second;
    }

    size_t size() const {
        return count_of_elements;
    }

    bool empty() const {
        return count_of_elements == 0U;
    }

    void clear() {
        tree.clear();
        this->count_of_elements = 0U;

        free_poses.clear();

        root = createNode(root);
    }
};


#pragma once

#include "RedBlackTree.hpp"

template <typename TKey, typename TValue>
class TestableRedBlackTree : public RedBlackTree<TKey, TValue> {

    using typename RedBlackTree<TKey, TValue>::node_ptr;
    using typename RedBlackTree<TKey, TValue>::Color;

    using RedBlackTree<TKey, TValue>::NULL_PTR;

protected:
    size_t getBlackHeight(bool& is_correct_bh, node_ptr x) const {
        if (x == NULL_PTR) {
            return 0U;
        }

        size_t left_bh = getBlackHeight(is_correct_bh, this->getLeftSon(x));
        size_t right_bh = getBlackHeight(is_correct_bh, this->getRightSon(x));

        if (left_bh != right_bh) {
            is_correct_bh = false;
        }

        size_t result = left_bh;
        if (this->getColor(x) == Color::Black) {
            ++result;
        }

        return result;
    }

    bool isCorrectRedVertices(node_ptr x) const {
        if (this->getLeftSon(x) != NULL_PTR) {
            if (this->getColor(x) == Color::Red && this->getColor(this->getLeftSon(x)) == Color::Red) {
                return false;
            }
            if (!isCorrectRedVertices(this->getLeftSon(x))) {
                return false;
            }
        }

        if (this->getRightSon(x) != NULL_PTR) {
            if (this->getColor(x) == Color::Red && this->getColor(this->getRightSon(x)) == Color::Red) {
                return false;
            }
            if (!isCorrectRedVertices(this->getRightSon(x))) {
                return false;
            }
        }

        return true;
    }

    size_t getCountOfCorrectNode(node_ptr x) const {
        if (x == NULL_PTR) {
            return 0U;
        }

        size_t count = 0;

        count += getCountOfCorrectNode(this->getLeftSon(x));
        count += getCountOfCorrectNode(this->getRightSon(x));

        if (!this->isFictitious(x)) {
            ++count;
        }

        return count;
    }

    bool isSearchTree(node_ptr x, node_ptr prev_x) const {
        if (this->isFictitious(x)) {
            return true;
        }
        if (x != this->root && this->getParent(x) != prev_x) {
            return false;
        }
        if (!this->isFictitious(this->getLeftSon(x))) {
            if (this->getKey(x) <= this->getKey(this->getLeftSon(x))) {
                return false;
            }
            if (!isSearchTree(this->getLeftSon(x), x)) {
                return false;
            }
        }
        if (!this->isFictitious(this->getRightSon(x))) {
            if (this->getKey(x) >= this->getKey(this->getRightSon(x))) {
                return false;
            }
            if (!isSearchTree(this->getRightSon(x), x)) {
                return false;
            }
        }
        return true;
    }

public:

    bool isTreeCorrect() {
        bool is_correct_bh = true;
        getBlackHeight(is_correct_bh, this->root);

        bool is_correct_red_vertices = isCorrectRedVertices(this->root);
        bool is_search_tree = isSearchTree(this->root, this->root);
        bool is_correct_size = (this->size() == getCountOfCorrectNode(this->root));

        return is_correct_bh && is_correct_red_vertices && is_search_tree && is_correct_size;
    }
};