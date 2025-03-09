#pragma once

#include "includes.hpp"

template <class TKey, class TValue> class OrderedTable {
protected:

    std::vector<std::pair<TKey, TValue>> data;

public:
    class Iterator {
    protected:

        int data_position = 0;
        OrderedTable<TKey, TValue>* container;

        Iterator(int start_position, OrderedTable<TKey, TValue>* container):
            data_position(start_position),
            container(container)
        {}

    public:

        std::pair<const TKey&, TValue&> operator*() {
            return { container->data[data_position].first, container->data[data_position].second };
        }

        const std::pair<const TKey&, const TValue&> operator*() const {
            return { container->data[data_position].first, container->data[data_position].second };
        }

        std::pair<TKey, TValue>* operator->() const {
            return &container[data_position];
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

    Iterator begin() const {
        return Iterator(0, const_cast<OrderedTable<TKey, TValue>*>(this));
    }

    Iterator end() const {
        return Iterator((int)data.size(), const_cast<OrderedTable<TKey, TValue>*>(this));
    }

    Iterator insert(const TKey& key, const TValue& value) {
        data.push_back(std::make_pair(key, value));

        int curr_pos = (int)data.size() - 1;
        while (curr_pos > 0 && data[curr_pos - 1].first > data[curr_pos].first) {
            std::swap(data[curr_pos - 1], data[curr_pos]);
            --curr_pos;
        }
        return Iterator(curr_pos, this);
    }

    Iterator erase(const TKey& key) {
        Iterator it = find(key);

        if (it != this->end()) {
            int pos = it.data_position;
            data.erase(data.begin() + pos);
        }

        return it;
    }

    Iterator find(const TKey& key) const {

        if (this->empty()) {
            return this->end();
        }

        int l = 0;
        int r = (int)data.size() - 1;

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
            return this->end();
        }

        return Iterator(r, const_cast<OrderedTable<TKey, TValue>*>(this));
    }

    bool isExist(const TKey& key) const {
        return this->find(key) != this->end();
    }

    TValue& operator[](const TKey& key) {
        if (!this->isExist(key)) {
            throw std::runtime_error("No such key in table");
    }
        return (*this->find(key)).second;
    }

    const TValue& operator[](const TKey& key) const {
        if (!this->isExist(key)) {
            throw std::runtime_error("No such key in table");
        }
        return (*this->find(key)).second;
    }

    size_t size() const{
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear(){
        data.clear();
    }
};