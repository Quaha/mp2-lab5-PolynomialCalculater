#pragma once

#include <iostream>
#include <stack>
#include <utility>

template <typename TKey, typename TValue>
class AVLTree {
public:
    class Node {
    public:
        Node* lChild;
        Node* rChild;

        std::pair<TKey, TValue> data;

        int height;

        Node(TKey key, TValue value) {
            data = { key, value };
            lChild = nullptr;
            rChild = nullptr;
            height = 1;
        }
    };

    Node* root;
    int sz;

    class Iterator {
    protected:

        void goLeft(Node* nd) {
            while (nd) {
                nodes.push(nd);
                nd = nd->lChild;
            }
        }

    public:

        std::stack<Node*> nodes;

        Iterator(Node* root) {
            goLeft(root);
        }

        std::pair<TKey, TValue> operator*() const {
            if (nodes.empty()) {
                throw std::runtime_error("Iterator is empty");
            }
            return nodes.top()->data;
        }

        std::pair<TKey, TValue>* operator->() const {
            if (nodes.empty()) {
                throw std::runtime_error("Iterator is empty");
            }
            return &(nodes.top()->data);
        }

        Iterator& operator++() {
            Node* nd = nodes.top()->rChild;
            nodes.pop();
            goLeft(nd);
            return *this;
        }

        bool operator==(const Iterator& It) const {
            if (nodes.empty() && It.nodes.empty()) {
                return true;
            }
            if (nodes.empty() || It.nodes.empty()) {
                return false;
            }
            return nodes.top() == It.nodes.top();
        }

        bool operator!=(const Iterator& It) const {
            if (nodes.empty() || It.nodes.empty()) return true;
            return !(*this == It);
        }
    };

    AVLTree() : root(nullptr), sz(0) {};
    ~AVLTree() { 
        clear(root); 
    }
    AVLTree(const AVLTree& t) : root(nullptr), sz(0) {
        if (t.root) {
            root = rebuildTree(t.root); 
            sz = t.sz;               
        }
    }
    AVLTree& operator=(const AVLTree& t) {
        if (this != &t) {           
            clear();                    
            if (t.root) {
                root = rebuildTree(t.root); 
                sz = t.sz;               
            }
        }
        return *this; 
    }

    /* --- Helping functions --- */
protected:
    Node* rebuildTree(Node* nd) {
        if (!nd) return nullptr; 

        Node* newNode = new Node(nd->data.first, nd->data.second);
        newNode->height = nd->height;                             
        newNode->lChild = rebuildTree(nd->lChild);                  
        newNode->rChild = rebuildTree(nd->rChild);                 

        return newNode; 
    }

    int getHeight(Node* nd) {
        if (nd == nullptr) return 0;
        return nd->height;
    }
    int updHeight(Node* nd) {
        nd->height = std::max(getHeight(nd->lChild), getHeight(nd->rChild)) + 1;
        return nd->height;
    }
    int getDifferenceInHeights(Node* nd) {
        return getHeight(nd->lChild) - getHeight(nd->rChild);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->lChild;
        Node* z = x->rChild;
        x->rChild = y;
        y->lChild = z;
        /*

             y            x
            / \          / \
           x   yr  ->   xl  y
          / \              / \
         xr  z            z  yr

        */
        updHeight(x);
        updHeight(y);
        return x;
    }

    Node* rotateLeft(Node* y) {
        Node* x = y->rChild;
        Node* z = x->lChild;
        x->lChild = y;
        y->rChild = z;
        /*

            y             x
           / \           / \
          yl  x    ->   y   xr
             / \       / \
            z   xr    yl  z

        */
        updHeight(x);
        updHeight(y);
        return x;
    }

    Node* balanceNode(Node* nd) {
        updHeight(nd);

        if (getDifferenceInHeights(nd) > 1) {
            if (getDifferenceInHeights(nd->lChild) < 0) {
                nd->lChild = rotateLeft(nd->lChild);
            }
            return rotateRight(nd);
        }

        if (getDifferenceInHeights(nd) < -1) {
            if (getDifferenceInHeights(nd->rChild) > 0) {
                nd->rChild = rotateRight(nd->rChild);
            }
            return rotateLeft(nd);
        }

        return nd;
    }

    Node* insert(Node* nd, TKey key, TValue value) {
        if (!nd) {
            sz++;
            return new Node(key, value);
        }

        if (key == nd->data.first) throw std::runtime_error("Cant add element with the same key");
        else if (key < nd->data.first) {
            nd->lChild = insert(nd->lChild, key, value);
        }
        else {
            nd->rChild = insert(nd->rChild, key, value);
        }

        return balanceNode(nd);
    }

    Node* findMin(Node* nd) const {
        if (!nd->lChild) return nd;
        return findMin(nd->lChild);
    }

    Node* eraseMin(Node* nd) {
        if (!nd->lChild) return nd->rChild;
        nd->lChild = eraseMin(nd->lChild);
        return balanceNode(nd);
    }

    Node* erase(Node* nd, TKey key) {
        if (!nd) return nullptr;

        if (key < nd->data.first) {
            nd->lChild = erase(nd->lChild, key);
        }
        else if (key > nd->data.first) {
            nd->rChild = erase(nd->rChild, key);
        }
        else {
            Node* lNode = nd->lChild;
            Node* rNode = nd->rChild;
            delete nd;

            if (!rNode) {
                sz--;
                return lNode;
            }
            Node* mn = findMin(rNode);
            mn->rChild = eraseMin(rNode);
            mn->lChild = lNode;

            sz--;
            return balanceNode(mn);
        }

        return balanceNode(nd);
    }

    void clear(Node* nd) {
        if (!nd) return;
        clear(nd->lChild);
        clear(nd->rChild);
        delete nd;
    }

    /* --- Functions for testing --- */

    bool isSearchTree(Node* root) {
        // If no children
        if (!root->lChild) return true;
        // If only left child
        if (!root->rChild) {
            return ((root->data.first > root->lChild->data.first) && isSearchTree(root->lChild));
        }
        // If both
        return ((root->data.first > root->lChild->data.first) && isSearchTree(root->lChild)
            && (root->data.first < root->rChild->data.first) && isSearchTree(root->rChild));
    }


public:
    bool isTreeCorrect() {
        if (empty()) return 1;
        bool is_search_tree = isSearchTree(root);

        return is_search_tree;
    }

    /* --- Main functions --- */
    Iterator find(const TKey& key) {
        Node* current = root;
        Iterator it(nullptr);
        while (current) {
            it.nodes.push(current);
            if (key < current->data.first) {
                current = current->lChild;
            }
            else if (key > current->data.first) {
                current = current->rChild;
            }
            else {
                return it;
            }
        }
        return end();
    }

    Iterator insert(TKey key, TValue value) {
        root = insert(root, key, value);
        return Iterator(find(key));
    }
    void erase(TKey key) {
        root = erase(root, key);
    }
    Iterator begin() const {
        return Iterator(root);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }
    bool empty() {
        return sz == 0;
    }
    int size() {
        return sz;
    }
    void clear() {
        clear(root);
        root = nullptr;
        sz = 0;
    }
    bool isExist(const TKey& key) {
        Iterator it = find(key);
        return !it.nodes.empty();
    }
    TValue operator[](const TKey& key) {
        auto itNd = find(key);
        if (itNd != end()) {
            return (*itNd).second;
        }
        else {
            throw std::runtime_error("Cant access non existing element");
        }
    }
};