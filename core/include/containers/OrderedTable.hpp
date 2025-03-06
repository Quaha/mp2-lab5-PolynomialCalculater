#pragma once

#include <iostream>
#include <vector>

using std::pair;
using std::vector;

template <class TKey, class TValue> class OrderedTable {
protected:
    vector<pair<TKey, TValue>> data;

public:

    template <class TKey, class TValue> class Iterator {
    protected:

        int data_position = 0;
        OrderedTable<TKey, TValue>* container;

        Iterator(int start_position, OrderedTable<TKey, TValue>* container)
            : data_position(start_position), container(container) {}

    public:

        std::pair<TKey, TValue>& operator*(){
            return container->data[data_position];
        }

        const std::pair<TKey, TValue>& operator*() const {
            return container->data[data_position];
        }

        Iterator& operator++() {
            ++data_position;
            if (data_position > container->data.size()) {
                data_position = 0;
            }
            return *this;
        }

        Iterator& operator--(){
            --data_position;
            if (data_position < 0) {
                data_position = container->data.size();
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return this->data_position == other.data_position;
        }

        bool operator!=(const Iterator& other) const {
            return this->data_position != other.data_position;
        }

        friend class OrderedTable;
    };

    OrderedTable() {

    }

    ~OrderedTable(){

    }

    Iterator<TKey, TValue> begin() {
        return Iterator<TKey, TValue>(0, this);
    }

    Iterator<TKey, TValue> end() {
        return Iterator<TKey, TValue>(data.size(), this);
    }

    Iterator<TKey, TValue> insert(const TKey& key, const TValue& value) {
        data.push_back(std::make_pair(key, value));
        int curr_pos = data.size() - 1;
        while (curr_pos > 0 && data[curr_pos - 1].first > data[curr_pos].first) {
            swap(data[curr_pos - 1], data[curr_pos]);
            --curr_pos;
        }
        return Iterator<TKey, TValue>(curr_pos, this);
    }

    Iterator<TKey, TValue> erase(const TKey& key) {
        Iterator<TKey, TValue> it = find(key);
        int pos = it->data_position;

        if (pos != data.size()) {
            while (pos < data.size() - 1) {
                swap(data[pos], data[pos + 1]);
                pos++;
            }

            data.pop_back();
        }

        return it;
    }

    Iterator<TKey, TValue> find(const TKey& key){

        int l = 0;
        int r = data.size() - 1;

        if (data[l].first >= key) {
            r = l;
        }

        if (data[r].first < key) {
            l = r;
        }

        while (r - l > 1) {
            int m = (l + r) / 2;
            if (data[m].first < key) {
                l = m;
            }
            else {
                r = m;
            }
        }

        if (data[r].first != key) {
            return end();
        }

        return Iterator<TKey, TValue>(r, this);
    }

    bool isExist(const TKey& key) {
        return this->find(key) != this->end();
    }

    TValue& operator[](const TKey& key) {
        if (!this->isExist(key)) {
            this->insert(key, TValue());
        }
        return (*this->find(key)).second;
    }

    int size() const{
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear(){
        data.clear();
    }
};