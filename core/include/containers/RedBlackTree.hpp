#pragma once

#include <iostream>
#include <vector>

template <typename TKey, typename TValue>
class RedBlackTree {
protected:

    enum Color {
        Red,
        Black
    };

    struct Node {

        int parent;
        int left_node, right_node;

        Color color;

        std::pair<TKey, TValue> data;

        bool is_fictitious;
    };

public:

    class Iterator {
    protected:

        int tree_position = 0;

        RedBlackTree<TKey, TValue>* container;

        Iterator(int start_position, RedBlackTree<TKey, TValue>* container) :
            tree_position(start_position),
            container(container)
        {}

    public:

        std::pair<const TKey&, TValue&> operator*() {
            if (tree_position == -1) {
                throw std::out_of_range("It is forbidden to dereference .end() iterator.");
            }
            return { container->tree[tree_position].data.first, container->tree[tree_position].data.second };
        }

        const std::pair<const TKey&, const TValue&> operator*() const {
            if (tree_position == -1) {
                throw std::out_of_range("It is forbidden to dereference .end() iterator.");
            }
            return { container->tree[tree_position].data.first, container->tree[tree_position].data.second };
        }

        std::pair<TKey, TValue>* operator->() const {
            return &container->tree[tree_position].data;
        }

        Iterator& operator++() {
            int pos = tree_position;

            int right_pos = container->tree[pos].right_node;

            if (!container->tree[right_pos].is_fictitious) {
                pos = container->getLowestPos(right_pos);
            }
            else {
                int prev_pos = container->tree[pos].parent;
                while (prev_pos != -1 && container->tree[prev_pos].right_node == pos) {
                    pos = prev_pos;
                    prev_pos = container->tree[pos].parent;
                }
                pos = prev_pos;
            }

            tree_position = pos;

            return *this;
        }

        bool operator==(const Iterator& other) const {
            return this->tree_position == other.tree_position;
        }

        bool operator!=(const Iterator& other) const {
            return this->tree_position != other.tree_position;
        }

        friend class RedBlackTree;
    };

protected:

    std::vector<Node> tree;
    size_t sz = 0;

    int root;

    std::vector<int> free_poses;

protected:
    Iterator makeIterator(int position) const {
        return Iterator(position, const_cast<RedBlackTree<TKey, TValue>*>(this));
    }

    int createNode(int parent) {
        if (free_poses.empty()) {
            free_poses.push_back((int)tree.size());
            tree.push_back(Node());
        }
        int id = free_poses.back();
        free_poses.pop_back();

        tree[id].parent = parent;
        tree[id].left_node = -1;
        tree[id].right_node = -1;

        tree[id].color = Color::Black;
        tree[id].is_fictitious = true;

        return id;
    }

    void deleteNode(int x) {
        free_poses.push_back(x);
    }

protected:
    void smallLeftRotation(int x) {
        int y = getRightSon(x);

        int subtree_root = getParent(x);

        tree[x].right_node = tree[y].left_node;
        if (getRightSon(x) != -1) {
            tree[getRightSon(x)].parent = x;
        }

        tree[x].parent = y;

        tree[y].parent = subtree_root;
        tree[y].left_node = x;

        changeParent(subtree_root, x, y);
    }

    void smallRightRotation(int x) {
        int y = getLeftSon(x);

        int subtree_root = getParent(x);

        tree[x].left_node = tree[y].right_node;
        if (getLeftSon(x) != -1) {
            tree[getLeftSon(x)].parent = x;
        }

        tree[x].parent = y;

        tree[y].parent = subtree_root;
        tree[y].right_node = x;

        changeParent(subtree_root, x, y);
    }

protected:
    int getLeftSon(int x) const {
        return tree[x].left_node;
    }

    int getRightSon(int x) const {
        return tree[x].right_node;
    }

    int getParent(int x) const {
        return tree[x].parent;
    }

    int getGrandParent(int x) const {
        return getParent(getParent(x));
    }

    int getUncle(int x) const {
        int g = getGrandParent(x);
        if (getLeftSon(g) == getParent(x)) {
            return getRightSon(g);
        }
        else {
            return getLeftSon(g);
        }
    }

    int getCousin(int x) const {
        if (tree[getParent(x)].left_node == x) {
            return tree[getParent(x)].right_node;
        }
        return tree[getParent(x)].left_node;
    }

    const TKey& getKey(int x) const {
        return tree[x].data.first;
    }

    const TValue& getValue(int x) const {
        return tree[x].data.second;
    }

    bool isFictitious(int x) const {
        return tree[x].is_fictitious;
    }

    void changeParent(int parent, int old_son, int new_son) {
        if (parent == -1) {
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
    int getColor(int x) const {
        return tree[x].color;
    }

    void setColor(int x, Color color) {
        tree[x].color = color;
    }

private:
    int getBlackHeight(bool& flag, int x) const {
        if (x == -1) {
            return 0;
        }

        int left_bh = getBlackHeight(flag, getLeftSon(x));
        int right_bh = getBlackHeight(flag, getRightSon(x));

        if (left_bh != right_bh) {
            flag = false;
        }
        return left_bh + (tree[x].color == Color::Black);
    }

    bool isCorrectRedVertices(int x) const {

        if (getLeftSon(x) != -1) {
            if (getColor(x) == Color::Red && getColor(getLeftSon(x)) == Color::Red) {
                return false;
            }
            if (!isCorrectRedVertices(getLeftSon(x))) {
                return false;
            }
        }

        if (getRightSon(x) != -1) {
            if (getColor(x) == Color::Red && getColor(getRightSon(x)) == Color::Red) {
                return false;
            }
            if (!isCorrectRedVertices(getRightSon(x))) {
                return false;
            }
        }
        return true;
    }

    int getCountOfCorrectNode(int x) const {
        if (x == -1) {
            return 0;
        }
        return getCountOfCorrectNode(getLeftSon(x)) + getCountOfCorrectNode(getRightSon(x)) + (!isFictitious(x));
    }

    bool isSearchTree(int x, int prev_x) const {
        if (isFictitious(x)) {
            return true;
        }
        if (x != root && getParent(x) != prev_x) {
            return false;
        }
        if (!isFictitious(getLeftSon(x))) {
            if (getKey(x) <= getKey(getLeftSon(x))) {
                return false;
            }
            if (!isSearchTree(getLeftSon(x), x)) {
                return false;
            }
        }
        if (!isFictitious(getRightSon(x))) {
            if (getKey(x) >= getKey(getRightSon(x))) {
                return false;
            }
            if (!isSearchTree(getRightSon(x), x)) {
                return false;
            }
        }
        return true;
    }

protected:

    int getLowestPos(int x) const {
        int lowest_pos = x;
        while (!isFictitious(getLeftSon(lowest_pos))) {
            lowest_pos = getLeftSon(lowest_pos);
        }
        return lowest_pos;
    }

    int findPosition(const TKey& key) const {
        int current_pos = root;
        while (!isFictitious(current_pos) && getKey(current_pos) != key) {
            if (getKey(current_pos) > key) {
                current_pos = tree[current_pos].left_node;
            }
            else {
                current_pos = tree[current_pos].right_node;
            }
        }
        return current_pos;
    }

    void erasePosition(int x) {
        if (!isFictitious(getLeftSon(x)) && !isFictitious(getRightSon(x))) {
            int min_right = getLowestPos(getRightSon(x));
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
            else {

                int subtree_root = getParent(x);
                int bad_subtree = getLeftSon(x);

                changeParent(subtree_root, x, bad_subtree);

                deleteNode(getRightSon(x));
                deleteNode(x);

                fixTreeAfterErase(bad_subtree);
            }
        }
    }

    void fixTreeAfterInsert(int x) {
        if (getParent(x) == -1) { // => x is root
            setColor(x, Color::Black);
            return;
        }

        int y = getParent(x);

        if (getColor(y) == Color::Red) { // x is Red

            int g = getGrandParent(x);
            int u = getUncle(x);

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

    void fixTreeAfterErase(int x) {
        if (x == root) {
            return;
        }

        int A = getParent(x);
        int B = getCousin(x);

        if (getColor(A) == Color::Red) {
            if (getLeftSon(B) != -1 && getColor(getLeftSon(B)) == Color::Red) {
                if (getLeftSon(A) == B) {
                    /*
                            A
                           /
                          B
                         /
                        C
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
                         /
                        C
                    */
                    setColor(A, Color::Black);

                    smallRightRotation(B);
                    smallLeftRotation(A);
                }
            }
            else if (getRightSon(B) != -1 && getColor(getRightSon(B)) == Color::Red) {
                if (getLeftSon(A) == B) {
                    /*
                       A
                      /
                     B
                      \
                       C
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
                          \
                           Ñ
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
                if (getLeftSon(B) != -1 && getColor(getLeftSon(B)) == Color::Red) {
                    int C = getLeftSon(B);
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
                else if (getRightSon(B) != -1 && getColor(getRightSon(B)) == Color::Red) {
                    int C = getRightSon(B);
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
                               Ñ
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

    void lowerBound(const TKey& key, int x, int &best_pos) const {
        if (isFictitious(x)) {
            return;
        }
        if (getKey(x) >= key) {
            best_pos = x;
            lowerBound(key, getLeftSon(x), best_pos);
        }
        else{
            lowerBound(key, getRightSon(x), best_pos);
        }
    }

    void upperBound(const TKey& key, int x, int &best_pos) const {
        if (isFictitious(x)) {
            return;
        }
        if (getKey(x) > key) {
            best_pos = x;
            upperBound(key, getLeftSon(x), best_pos);
        }
        else {
            upperBound(key, getRightSon(x), best_pos);
        }
    }

public:
    bool isTreeCorrect() {
        bool is_correct_bh = true;
        getBlackHeight(is_correct_bh, root);

        bool is_correct_red_vertices = isCorrectRedVertices(root);

        bool is_search_tree = isSearchTree(root, root);

        bool is_correct_size = (size() == getCountOfCorrectNode(root));

        return is_correct_bh && is_correct_red_vertices && is_search_tree && is_correct_size;
    }

    RedBlackTree() {
        root = createNode(-1);
    }

    Iterator begin() const {
        if (empty()) {
            return end();
        }
        int lowest_pos = getLowestPos(root);
        return makeIterator(lowest_pos);
    }

    Iterator end() const {
        return makeIterator(-1);
    }

    Iterator lowerBound(const TKey& key) {
        int best_pos = -1;
        lowerBound(key, root, best_pos);
        return makeIterator(best_pos);
    }

    Iterator upperBound(const TKey& key) {
        int best_pos = -1;
        upperBound(key, root, best_pos);
        return makeIterator(best_pos);
    }

    Iterator insert(const TKey& key, const TValue& value) {
        int pos = findPosition(key);
        if (isFictitious(pos)) {
            ++sz;

            tree[pos].data.first = key;
            tree[pos].data.second = value;

            tree[pos].color = Color::Red;
            tree[pos].is_fictitious = false;

            tree[pos].left_node = createNode(pos);
            tree[pos].right_node = createNode(pos);

            fixTreeAfterInsert(pos);
        }
        return makeIterator(pos);
    }

    Iterator erase(const TKey& key) {
        return erase(find(key));
    }

    Iterator erase(Iterator it) {
        if (it == end()) {
            return it;
        }
        --sz;
        auto result = it;
        ++result;
        erasePosition(it.tree_position);
        return result;
    }

    Iterator find(const TKey& key) const {
        int pos = findPosition(key);
        if (isFictitious(pos)) {
            return end();
        }
        return makeIterator(pos);
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
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void clear() {
        tree.clear();
        this->sz = 0;

        free_poses.clear();

        root = createNode(root);
    }
};